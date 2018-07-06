import pymysql
from flask import Flask, render_template, request, jsonify


app = Flask(__name__, template_folder='templates')


@app.route('/')
def welcome_page():
    return render_template("welcome.html")


@app.route('/retrieve')
def retrieve():
    # Access the data and provide the list of books
    """
    sql = "select * from --DATABASE--"
    connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
    cursor = connection.cursor()
    cursor.execute(sql)
    results = cursor.fetchall()
    cursor.close()
    connection.close()
    # find a way upload the results to the webpage
    """

    results = [{"title": "Dog", "author": "Snoop", "publisher": "JK"},
               {"title": "Cat", "author": "Feline", "publisher": "Not JK"}]
    return render_template("retrieve.html", book_list = results)


@app.route('/replace')
def replace():
    # Access the data and provide the list of books
    """
    sql1 = "select * from --DATABASE--"
    connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
    cursor = connection.cursor()
    cursor.execute(sql1)
    results = cursor.fetchall()
    cursor.close()
    connection.close()
    # find a way upload the results to the webpage
    """
    results = [{"title": "Dog", "author": "Snoop", "publisher": "JK"},
               {"title": "Cat", "author": "Feline", "publisher": "Not JK"}]
    return render_template("replace.html", book_list = results)


@app.route('/login', methods=['POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        sql2 = "select * from shelf"
        connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
        cursor = connection.cursor()
        cursor.execute(sql2)
        results = cursor.fetchall()
        cursor.close()
        connection.close()
        for users in results:
            if username in users.username and password in users.password:
                return render_template("setting.html", username=username)
            elif request.form.get('new_user'):
                # Add the new user to the database
                return render_template("setting.html", username=username)
            else:
                return render_template("error_login.html")


@app.route('/throw', methods=['GET'])
def throw():
    # Throw function should provide an API command for the Braccio
    if request.method == 'POST':
        error = "Error! Wrong type of method!"
        return jsonify(error)
    if request.method == 'GET':
        # Access the data and provide the list of books
        signal = dict()
        """
        sql3 = "select * from --DATABASE--"
        connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
        cursor = connection.cursor()
        cursor.execute(sql3)
        signal = cursor.fetchall()
        cursor.close()
        connection.close()
        # find a way upload the results to the webpage
        """

        return jsonify(signal)
    return render_template("throw.html")


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080, debug=True)
