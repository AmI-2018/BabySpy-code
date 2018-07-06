"""
    @author
    Amir
"""


from . import rest
import time

def light():


    # the base URL
    base_url = 'http://192.168.0.201'
    # if you are using the emulator, probably the base_url will be:
    # base_url = 'http://localhost:8000'

    username = '5UsL1ptHh6tp2M0yDdJDXJtOG4J9UO1bYbhpz2Cd'
    # if you are using the emulator, the username is:
    # username = 'newdeveloper'

    # lights URL
    lights_url = base_url + '/api/' + username + '/lights/'

    # get the Hue lights
    all_the_lights = rest.send(url=lights_url)

    #Changing the color
    colors = [0, 12750, 25500, 46920, 56100, 65280]
    for color in colors:
        #Flashing
        for alert in range (0,1):
            if type(all_the_lights) is dict:
                    # iterate over the Hue lights, turn them on with the color loop effect
                    light = '9'
                    #for light in all_the_lights:
                    url_to_call = lights_url + light + '/state'
                    body = '{ "on" : true, "hue" : %s }' %color
                    print(color)
                    # to set the red color
                    # body = '{ "hue" : 0 }'
                    rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})

                    # wait 10 seconds...
                    for i in range(0, 2):
                        time.sleep(1)
                        print(2-i)

                    # iterate over the Hue lights and turn them off
                    #for light in all_the_lights:
                    #url_to_call = lights_url + light + '/state'
                    body = '{ "on" : false }'
                    rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})
                    time.sleep(2)
            else:
                print('Error:', all_the_lights[0]['error'])
