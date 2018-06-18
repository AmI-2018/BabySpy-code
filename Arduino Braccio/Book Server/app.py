from flask import Flask, render_template, redirect, url_for, request, jsonify


app = Flask(__name__)


@app.route('/')
def welcome_page(name):
    return render_template('welcome.html', name=name)


@app.route('/Retrieve', methods=['GET', 'POST'])
def retrieve():
    if request.methods == 'POST':
        return render_template('retrieve.html')


@app.route('/Return', methods=['GET', 'POST'])
def place():
    if request.methods == 'POST':
        return render_template('place.html')


@app.route('/Throw', methods=['GET', 'POST'])
def throw():
    if request.methods == 'POST':
        return jsonify("ERROR!")
    if request.methods == 'GET':
        signal = direction()
        return jsonify(signal)
    return render_template('throw.html')


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080, debug=True)


#Function to provide the direction of the throw based on which sensor
def direction():
    command = dict()
    #Don't forget the json data format
    return command