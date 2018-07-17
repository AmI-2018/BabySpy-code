"""
    @author
    Amir
"""

import rest
import time

def normal():

    # the base URL
    base_url = 'http://192.168.0.201'

    username = '5UsL1ptHh6tp2M0yDdJDXJtOG4J9UO1bYbhpz2Cd'

    # lights URL
    lights_url = base_url + '/api/' + username + '/lights/'

    # get the Hue lights
    all_the_lights = rest.send(url=lights_url)

    #set the normal color and turn the lights on
    if type(all_the_lights) is dict:
        # iterate over the Hue lights, turn them on with the color loop effect
        light = '3'
        #for light in all_the_lights:
        url_to_call = lights_url + light + '/state'
        body = '{ "on" : true, "hue" : 56100 }'
        time.sleep(1)
        rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})
        value = 1
        check(value)
        return value

    else:
        print('Error:', all_the_lights[0]['error'])



def off():

    # the base URL
    base_url = 'http://192.168.0.201'

    username = '5UsL1ptHh6tp2M0yDdJDXJtOG4J9UO1bYbhpz2Cd'

    # lights URL
    lights_url = base_url + '/api/' + username + '/lights/'

    # get the Hue lights
    all_the_lights = rest.send(url=lights_url)

    #Turn off the lights
    if type(all_the_lights) is dict:
        # iterate over the Hue lights, turn them on with the color loop effect
        light = '3'
        #for light in all_the_lights:
        url_to_call = lights_url + light + '/state'
        body = '{ "on" : false}'
        time.sleep(1)
        rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})
        value = 2
        check(value)
        return value

    else:
        print('Error:', all_the_lights[0]['error'])



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
        light = '3'
        #for light in all_the_lights:
        url_to_call = lights_url + light + '/state'
        body = '{ "on" : true, "hue" : 12750 }'
        time.sleep(1)
        rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})
        value = 3
        check(value)
        return value

    else:
        print('Error:', all_the_lights[0]['error'])



def tv():

    # the base URL
    base_url = 'http://192.168.0.201'

    username = '5UsL1ptHh6tp2M0yDdJDXJtOG4J9UO1bYbhpz2Cd'

    # lights URL
    lights_url = base_url + '/api/' + username + '/lights/'

    # get the Hue lights
    all_the_lights = rest.send(url=lights_url)

    #setting the light color for TV mode
    if type(all_the_lights) is dict:
        # iterate over the Hue lights, turn them on with the color loop effect
        light = '3'
        #for light in all_the_lights:
        url_to_call = lights_url + light + '/state'
        body = '{ "on" : true, "hue" : 46920 }'
        time.sleep(1)
        rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})
        value = 4
        check(value)
        return value

    else:
        print('Error:', all_the_lights[0]['error'])


def check(item):

    if item == 1:
        print("It is the Normal mode")
    if item == 2:
        print("It is the Off mode")
    if item == 3:
        print("It is the Reading mode")
    if item == 4:
        print("It is the TV mode")
        