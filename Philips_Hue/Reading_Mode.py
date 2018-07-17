
"""
    @author
    Amir
"""

from . import rest
import time

def reading():

    # the base URL
    base_url = 'http://192.168.0.201'

    username = '5UsL1ptHh6tp2M0yDdJDXJtOG4J9UO1bYbhpz2Cd'

    # lights URL
    lights_url = base_url + '/api/' + username + '/lights/'

    # get the Hue lights
    all_the_lights = rest.send(url=lights_url)

    #set a specific color and turn on
    if type(all_the_lights) is dict:
        # iterate over the Hue lights, turn them on with the color loop effect
        light = '9'
        #for light in all_the_lights:
        url_to_call = lights_url + light + '/state'
        body = '{ "on" : true, "hue" : "12750" }'
        time.sleep(1)
        rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})

    else:
        print('Error:', all_the_lights[0]['error'])