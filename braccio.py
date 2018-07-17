

# Function to calculate the angles for the motors based on the position
# and writes it into a file
def calculate(position, action):
    # Calculate the angles
    slots = {"1": "10", "2": "20", "3": "30", "4": "40", "5": "50", "6": "60"}
    string = {
      "delay_time": ["", "", "", "", "", "", "", "", "", ""],
      "M1": ["", "", "", "", "", "", "", "", "", ""],
      "M2": ["", "", "", "", "", "", "", "", "", ""],
      "M3": ["", "", "", "", "", "", "", "", "", ""],
      "M4": ["", "", "", "", "", "", "", "", "", ""],
      "M5": ["", "", "", "", "", "", "", "", "", ""],
      "M6": ["", "", "", "", "", "", "", "", "", ""]
    }

    path = "/static/command.txt"
    file = open(path, 'w')
    file.write(str(string))
    file.close()
    return


# Function to read the JSON from the file
def read():
    path = "/static/command.txt"
    file = open(path, 'r')
    buffer = file.read()
    # Remove the new line character when read
    movement = buffer.rstrip()
    file.close()
    return movement
