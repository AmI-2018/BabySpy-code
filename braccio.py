

# Function to calculate the angles for the motors based on the position
# and writes it into a file
def calculate(position, action):
    # Calculate the angles
    #slots = {"1": "10", "2": "20", "3": "30", "4": "40", "5": "50", "6": "60"}
    signal = {"delay_time": ["15", "15", "15", "", "", "", "", "", "", ""],
              "M1": ["45", "90", "50", "", "", "", "", "", "", ""],
              "M2": ["30", "50", "75", "", "", "", "", "", "", ""],
              "M3": ["75", "30", "60", "", "", "", "", "", "", ""],
              "M4": ["20", "60", "30", "", "", "", "", "", "", ""],
              "M5": ["30", "75", "20", "", "", "", "", "", "", ""],
              "M6": ["45", "20", "60", "", "", "", "", "", "", ""]}

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
