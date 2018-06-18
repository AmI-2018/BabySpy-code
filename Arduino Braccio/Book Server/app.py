from flask import Flask, render_template, redirect, url_for, request


app = Flask(__name__)


@app.route('/')
def welcome_page():

    return render_template('welcome.html')


@app.route('/Retrieve')
def retrieve():

    return render_template('retrieve.html')


@app.route('/Return')
def place():

    return render_template('place.html')


@app.route('/Throw')
def throw():

    return render_template('throw.html')


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080, debug=True)
