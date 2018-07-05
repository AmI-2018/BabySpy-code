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
    list = "select * from --DATABASE--"
    connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
    cursor = connection.cursor()
    cursor.execute(list)
    results = cursor.fetchall()
    # find a way upload the results to the webpage
    """

    results = [{"title": "Dog", "author": "Snoop", "publisher": "JK"},
               {"title": "Cat", "author": "Feline", "publisher": "Not JK"}]
    return render_template("retrieve.html", book_list = results)


@app.route('/replace')
def replace():
    # Access the data and provide the list of books
    """
    list = "select * from --DATABASE--"
    connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
    cursor = connection.cursor()
    cursor.execute(list)
    results = cursor.fetchall()
    # find a way upload the results to the webpage
    """
    results = [{"title": "Dog", "author": "Snoop", "publisher": "JK"},
               {"title": "Cat", "author": "Feline", "publisher": "Not JK"}]
    return render_template("replace.html", book_list = results)


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
        list = "select * from --DATABASE--"
        connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
        cursor = connection.cursor()
        cursor.execute(list)
        signal = cursor.fetchall()
        # find a way upload the results to the webpage
        """

        return jsonify(signal)
    return render_template("throw.html")


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080, debug=True)
