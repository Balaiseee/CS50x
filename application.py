import os, requests, json
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash, safe_str_cmp
from helpers import apology, login_required, lookup, usd

# Configures application
app = Flask(__name__)

# Ensures templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configures CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query database for stocks owned by the current user
    cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])[0]["cash"]
    stocks = db.execute("SELECT symbol, name, quantity, price, price*quantity FROM stocks WHERE user_id=:id", id=session["user_id"])
    return render_template("index.html", stocks=stocks, cash="{:01.2f}".format(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        #Ensures user have enought money
        user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])[0]["cash"]
        share_price = int(request.form.get("shares"))*lookup(request.form.get("symbol"))["price"]
        if user_cash >= share_price:

            #Sets the new cash of the user
            new_cash = user_cash - share_price

            #Updates cash
            db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=new_cash, id=session["user_id"])

            #Checks if user already owned this stock
            if db.execute("SELECT * FROM stocks WHERE user_id=:user_id AND symbol=:symbol", user_id=session["user_id"], symbol=request.form.get("symbol")) == []:
                #Create new row if not
                db.execute("INSERT INTO stocks (symbol, quantity, name, price, user_id) VALUES (:symbol, :quantity, :name, :price, :id)", symbol=request.form.get("symbol"), quantity=int(request.form.get("shares")),name=lookup(request.form.get("symbol"))["name"] , price=lookup(request.form.get("symbol"))["price"], id=session["user_id"])
                db.execute("INSERT INTO transactions (symbol, quantity, price, date, user_id) VALUES (:symbol, :quantity, :price, datetime('now') ,:id)", symbol=request.form.get("symbol"), quantity=int(request.form.get("shares")), price=lookup(request.form.get("symbol"))["price"], id=session["user_id"])

            else:
                #Updates the current row
                quantity_already_owned = db.execute("SELECT quantity FROM stocks WHERE user_id=:user_id AND symbol=:symbol", user_id=session["user_id"], symbol=request.form.get("symbol"))[0]["quantity"]
                quantity_bought=int(request.form.get("shares"))
                new_quantity = quantity_already_owned + quantity_bought
                db.execute("UPDATE stocks SET quantity=:quantity WHERE user_id=:user_id AND symbol=:symbol", user_id=session["user_id"], symbol=request.form.get("symbol"), quantity=new_quantity)
                db.execute("INSERT INTO transactions (symbol, quantity, price, date, user_id) VALUES (:symbol, :quantity, :price, datetime('now') ,:id)", symbol=request.form.get("symbol"), quantity=int(request.form.get("shares")), price=lookup(request.form.get("symbol"))["price"], id=session["user_id"])

            return redirect("/")

        else:
            return apology("Not enought money")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query database for transactions
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=:id", id=session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forgets any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensures username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensures password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensures username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remembers which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirects user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forgets any user_id
    session.clear()

    # Redirects user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        #Crafts the request for the api IEX Cloud API
        url = "https://cloud-sse.iexapis.com/stable/stock/" + request.form.get("symbol") + "/quote?token=" + os.environ.get("API_KEY")

        #Saves the response request
        result = requests.get(url)

        #Ensures symbol exists
        if result.status_code == 200:
            return render_template("quoted.html", share=json.loads(result.text))

        else:
            return apology("symbol does not exist")

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        # Ensures username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensures password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensures username not already exists
        elif next(iter(db.execute("SELECT EXISTS(SELECT 1 FROM users WHERE username=:username)", username=request.form.get("username"))[0].values())) == 1:
            return apology("THE CURRENT USERNAME ALREADY EXISTS", 403)

        #Ensures password matches the confirmation password
        elif not safe_str_cmp(request.form.get("password"), request.form.get("confirmation")):
            return apology("PASSWORD DOES NOT MATCH THE CONFIRMATION PASSWORD", 403)

        else:
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        stocks = db.execute("SELECT * FROM stocks WHERE user_id=:id", id=session["user_id"])
        return render_template("sell.html", stocks=stocks)

    else:
        quantity_owned = db.execute("SELECT quantity FROM stocks WHERE user_id=:user_id AND id=:id", user_id=session["user_id"], id=request.form.get("symbol"))[0]["quantity"]
        symbol = db.execute("SELECT symbol FROM stocks WHERE user_id=:user_id AND id=:id", user_id=session["user_id"], id=request.form.get("symbol"))[0]["symbol"]

        #Ensures the user sells only shares that he has
        if quantity_owned < int(request.form.get("shares")):
            return apology("not enought shares")

        else:
            quantity_sold = quantity_owned - int(request.form.get("shares"))
            user_cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])[0]["cash"]
            share_price = int(request.form.get("shares"))*lookup(symbol)["price"]
            new_cash = user_cash + share_price
            db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=new_cash, id=session["user_id"])
            db.execute("UPDATE stocks SET quantity=:quantity WHERE user_id=:user_id AND id=:id", quantity=quantity_sold, user_id=session["user_id"], id=request.form.get("symbol"))
            db.execute("INSERT INTO transactions (symbol, quantity, price, date, user_id) VALUES (:symbol, :quantity, :price, datetime('now') ,:id)", symbol=symbol, quantity=-int(request.form.get("shares")), price=lookup(symbol)["price"], id=session["user_id"])

        return redirect("/")


def errorhandler(e):
    """Handle error"""

    if not isinstance(e, HTTPException):
        e = InternalServerError()

    return apology(e.name, e.code)


# Listens for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)