from flask import Flask, render_template, request, jsonify


app = Flask(__name__)


@app.route('/')
def welcome_page():
    #name = request.form['username']
    return render_template("welcome.html")


@app.route('/shelf')
def retrieve():
    if request.form == ['action']:
        return render_template("retrieve.html")
    if request.form == ['reaction']:
        return render_template("return.html")


@app.route('/K')
def something():
    return render_template("retrieve.html")


@app.route('/Throw', methods=['GET'])
def throw():
    if request.method == 'POST':
        error = "Error! Wrong type of method!"
        return jsonify(error)
    if request.method == 'GET':
        signal = direction()
        return jsonify(signal)
    return render_template("throw.html")


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=8080, debug=True)


# Function to provide the direction of the throw based on which sensor
def direction():
    command = "Command to throw!"
    # Don't forget the json data format
    return command


# Provides the movmements to retrieve an object
def take():
    signal = dict()
    return signal


# Provides the movmements to retrieve an object
def replace():
    signal = dict()
    return signal
