import pymysql
from flask import Flask, render_template, request, jsonify
# from Book Server import fun


app = Flask(__name__)


@app.route('/')
def welcome_page():
    return render_template("welcome.html")


"""
# Check if this route is really required?
@app.route('/shelf')
def shelf():
    if request.form == ['action']:
        return render_template("retrieve.html")
    if request.form == ['reaction']:
        return render_template("return.html")
"""


@app.route('/retrieve')
def retrieve():
    #Access the data and provide the list of books
    list = "select * from --DATABASE--"
    connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
    cursor = connection.cursor()
    cursor.execute(list)
    results = cursor.fetchall()
    #find a way upload the results to the webpage

    return render_template("retrieve.html")


@app.route('/replace')
def replace():
    # Access the data and provide the list of books
    list = "select * from --DATABASE--"
    connection = pymysql.connect(user="root", password="", host="localhost", database="--DATABASE--")
    cursor = connection.cursor()
    cursor.execute(list)
    results = cursor.fetchall()
    # find a way upload the results to the webpage

    return render_template("replace.html")


@app.route('/throw', methods=['GET'])
def throw():
    if request.method == 'POST':
        error = "Error! Wrong type of method!"
        return jsonify(error)
    if request.method == 'GET':
        signal = dict()
        return jsonify(signal)
    return render_template("throw.html")


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080, debug=True)


"""
port:port_no/command/
"""