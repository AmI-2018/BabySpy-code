from flask import Flask, jsonify, request, render_template

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello World!'


@app.route('/command', methods=['GET'])
def command():
    if request.method == 'GET':
        signal = {"delay_time": "20", "M1": "90", "M2": "60", "M3": "45", "M4": "30", "M5": "75", "M6": "10"}
        return jsonify(signal)
    else:
        return render_template("error.html")


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
