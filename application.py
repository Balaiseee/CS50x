import io
import datetime
from cs50 import SQL
from flask import Flask, render_template, request, redirect, Response
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure
from matplotlib import rcParams, pyplot as plt

rcParams.update({'figure.autolayout': True})

app = Flask(__name__)

db = SQL("sqlite:///logzz.db")

def clean_date(seances):
    for seance in seances:
        seance["date"] = datetime.datetime.strptime(seance["date"], '%Y-%m-%d').strftime("%A %d %B %Y")
    return seances

def clean_seance(seances):
    for seance in seances:
        ateliers = db.execute("SELECT exercice, serie, repetition, charge, rpe, commentaire, Seances.date FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE Seances.id = :id", id=seance["id"])
        if not ateliers:
            seances.remove(seance)
    return seances

@app.route("/", methods=["GET","POST"])
def index():
    seances = db.execute("SELECT id, date FROM Seances ORDER BY date ASC")
    seances = clean_seance(clean_date(seances))
    groupes = db.execute("SELECT DISTINCT groupe FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE serie*repetition*charge > 0")
    if request.method == "GET":
        return render_template("index.html", seances=seances, groupes=groupes)
    else:
        id = request.form.get("seance")
        date = db.execute("SELECT date FROM Seances WHERE id = :id", id=id)
        rows = db.execute("SELECT exercice, serie, repetition, charge, rpe, commentaire, Seances.date FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE Seances.id = :id ORDER BY Seances.id DESC, ordre ASC", id=id)
        rpeAverage = db.execute("SELECT AVG(rpe), Seances.id FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE Seances.id = :id", id=id)
        volumes = db.execute("SELECT groupe, sum(serie*repetition*charge) FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE Seances.id = :id GROUP BY groupe ORDER BY sum(serie*repetition*charge) DESC", id=id)
        return render_template("index.html", seances=seances, rows=rows, id=id, date=clean_date(date)[0]["date"], rpeAverage="{:01.1f}".format(rpeAverage[0]["AVG(rpe)"]), volumes=volumes)

@app.route("/volume", methods=["POST"])
def volume():
    groupes = db.execute("SELECT DISTINCT groupe FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE serie*repetition*charge > 0")
    groupe = request.form.get("groupe")
    return render_template("index.html", groupes=groupes, groupe=groupe)

@app.route("/exercice", methods=["GET"])
def exercice():
    seances = db.execute("SELECT id, date FROM Seances ORDER BY date ASC")
    groupes = db.execute("SELECT DISTINCT groupe FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE serie*repetition*charge > 0")
    exercices = db.execute("SELECT DISTINCT exercice FROM Ateliers")
    ateliers = db.execute("SELECT Ateliers.id, exercice, groupe, serie, repetition, charge, rpe, ordre, commentaire, Seances.date FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id ORDER BY date ASC")
    return render_template("exercice.html", seanceCount=len(seances), ateliers=clean_date(ateliers), seances=clean_date(seances), groupes=groupes, exercices=exercices)

@app.route("/add", methods=["POST"])
def add():
    exercice = request.form.get("exercice")
    groupe = request.form.get("groupe")
    serie = request.form.get("serie")
    repetition = request.form.get("repetition")
    charge = request.form.get("charge")
    rpe = request.form.get("rpe")
    ordre = request.form.get("ordre")
    commentaire = request.form.get("commentaire")
    seance = request.form.get("seance")
    db.execute("INSERT INTO Ateliers (exercice, groupe, serie, repetition, charge, rpe, ordre, commentaire, seance_id) VALUES (:exercice, :groupe, :serie, :repetition, :charge, :rpe, :ordre, :commentaire, :seance_id)", exercice=exercice, groupe=groupe, serie=serie,repetition=repetition, charge=charge, rpe=rpe, ordre=ordre, commentaire=commentaire, seance_id=seance)
    return redirect("/exercice")

@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    db.execute("DELETE FROM Ateliers WHERE id=:id",id=id)
    return redirect("/exercice")

@app.route("/update", methods=["POST"])
def update():
    id = request.form.get("id")
    type = request.form.get("type")
    contenu = request.form.get("contenu")
    db.execute("UPDATE Ateliers SET :type=:contenu WHERE id=:id",type=type, contenu=contenu, id=id)
    return redirect("/exercice")

#https://stackoverflow.com/questions/50728328/python-how-to-show-matplotlib-in-flask
@app.route('/plot/<groupe>', methods=["GET"])
def plot(groupe):
    if not groupe:
        return redirect("/")
    fig = create_figure(groupe)
    output = io.BytesIO()
    FigureCanvas(fig).print_png(output)
    return Response(output.getvalue(), mimetype='image/png')
def create_figure(groupe):
    groupe = '%' + groupe + '%'
    seance = db.execute("SELECT DISTINCT Seances.id,date FROM Seances JOIN Ateliers ON Ateliers.seance_id = Seances.id WHERE Ateliers.groupe LIKE :groupe AND  serie*repetition*charge > 0 ", groupe=groupe)
    seance = clean_date(seance)
    seanceCount= len(seance)
    seances = []
    names = []
    for i in range(seanceCount):
        seances.append(seance[i]["id"])
        names.append(seance[i]["date"])
    volumes = []
    for i in seances:
        volume = db.execute("SELECT sum(serie*repetition*charge) FROM Ateliers JOIN Seances ON Ateliers.seance_id = Seances.id WHERE Seances.id = :i AND Ateliers.groupe LIKE :groupe", i=i, groupe=groupe)
        if volume[0]["sum(serie*repetition*charge)"] is not None:
            volumes.append(volume[0]["sum(serie*repetition*charge)"])
    fig = Figure()
    axis = fig.add_subplot(1, 1, 1, frameon=False)
    xs = range(0, seanceCount)
    ys = [volumes[x] for x in xs]
    axis.plot(xs, ys, '#007bff')
    axis.fill_between(xs, ys, color = '#007bff')
    axis.set_xticks(range(seanceCount))
    axis.set_xticklabels(names)
    axis.tick_params(axis='x', colors='black')
    axis.tick_params(axis='y', colors='black')
    fig.patch.set_facecolor('#fff')
    plt.setp(axis.xaxis.get_majorticklabels(), rotation=90)
    return fig

@app.route("/seance", methods=["GET"])
def seance():
    seances = db.execute("SELECT id, date FROM Seances ORDER BY date ASC")
    if request.method == "GET":
        blocs = db.execute("SELECT id FROM Blocs")
        return render_template("seance.html", blocs=blocs, seances=clean_date(seances))

@app.route("/add_seance", methods=["POST"])
def add_seance():
    date = request.form.get("date")
    bloc = request.form.get("bloc")
    db.execute("INSERT INTO Seances (date, bloc_id) VALUES (:date, :bloc)", date=date, bloc=bloc)
    return redirect("/seance")

@app.route("/delete_seance", methods=["POST"])
def delete_seance():
    id = request.form.get("id")
    db.execute("DELETE FROM Ateliers WHERE seance_id=:id",id=id)
    db.execute("DELETE FROM Seances WHERE id=:id",id=id)
    return redirect("/seance")

@app.route("/update_seance", methods=["POST"])
def update_seance():
    id = request.form.get("id")
    date = request.form.get("date")
    db.execute("UPDATE Seances SET date=:date WHERE id=:id", date=date, id=id)
    return redirect("/seance")

@app.route("/faq", methods=["GET"])
def faq():
    return render_template("faq.html")
