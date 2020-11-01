LOGZZ

General overview

    Q:What is this project about?
    A:This project is an online training log. Unlike a physical training log, it will not let its user down (you can't lose it, you can't destroy it, ...), moreover it gives us lots of additional data like graphs of volume by muscle group, …

    Q:What audience is it aimed at?
    A:This project is designed mostly for confirmed athletes. It is not guided and the user must know how to interpret a volume graph, the average RPE, …

Sport overview

    Q:What is RPE?
    A:RPE stands for Rate of Perceived Exertion, or basically how hard a particular set felt. It’s fairly common to hear people tell about an “easy triple” or a single they really had to grind out. These terms are quite ambiguous and will mean different things to different people. It's noted by a @ and a number of a numerical scale from one to ten based on how hard a set feels.

    Q:What is volume?
    A:Volume is the total weight you lifted. If you did 5x5x200, then 5*5*200 is 5000 kg. Since the weight lifted varies according to leverages, this can only be compared to the same lift. Here as I always use the same exercise for each muscle group, you can approximate the lift to the muscle group, this is what is done with the volume graphs by muscle group.

Technical overview

    Q:How is the database structured?
    A:https://dbdiagram.io/d/5f9c92773a78976d7b79e597

    Q:How are volume graphs by muscle group generated?
    A:To achieve this goal, I use Matplotlib (a comprehensive library for creating static, animated, and interactive visualizations in Python).

    Q:How do interactions with flask and the sqlite database work?
    A:I use the built-in CS50 library to craft and send sql query to a sqlite3 database.

About me

    Q:Who am I?
    A:My name is Stanislas LUCINSKI-KADRI, I'm a computer science and fitness enthusiast. I’m currently studying at the ESILV engineering school, however I’m also very curious and a big fan of self-pace learning, that’s why I love this CS50 course!

    Q:Why this project?
    A:I had the great opportunity to be coached by a world champion in powerlifting, he taught me to have a global vision of the variable of my training like the fatigue management or the bloc periodization… It is to continue in this way that I chose to carry out this project, simplifying and centralizing the data in a database and providing me with feedback on them.