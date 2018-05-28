from flask import Flask, jsonify, render_template, request


app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello World!'


@app.route('/command1', methods=['GET'])
def command1():
    if request.method == 'GET':
        signal1 = {"delay_time": "20", "M1": "90", "M2": "90", "M3": "90", "M4": "90", "M5": "90", "M6": "30"}
        return jsonify(signal1)
    else:
        return render_template("error.html")


if __name__ == '__main__':
    app.run()
