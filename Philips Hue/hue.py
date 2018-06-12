"""
Created on Apr 4, 2014
Updated on May 16, 2018
@author: Dario Bonino
@author: Luigi De Russis
Modified By Amir
Copyright (c) 2014-2018 Dario Bonino and Luigi De Russis

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License
"""

import rest
import time

if __name__ == '__main__':

    # the base URL
    base_url = 'http://192.168.0.201'
    # if you are using the emulator, probably the base_url will be:
    # base_url = 'http://localhost:8000'

    # example username, generated by following https://www.developers.meethue.com/documentation/getting-started
    username = '5UsL1ptHh6tp2M0yDdJDXJtOG4J9UO1bYbhpz2Cd'
    # if you are using the emulator, the username is:
    # username = 'newdeveloper'

    # lights URL
    lights_url = base_url + '/api/' + username + '/lights/'

    # get the Hue lights
    all_the_lights = rest.send(url=lights_url)

for alert in range (0,2):
    if type(all_the_lights) is dict:
        # iterate over the Hue lights, turn them on with the color loop effect
        for light in all_the_lights:
            url_to_call = lights_url + light + '/state'
            body = '{ "on" : true, "hue" : 0 }'
            # to set the red color
            # body = '{ "hue" : 0 }'
            # more colors: https://www.developers.meethue.com/documentation/core-concepts
            rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})

        # wait 10 seconds...
        for i in range(0, 2):
            time.sleep(1)
            print(2-i)

        # iterate over the Hue lights and turn them off
        for light in all_the_lights:
            url_to_call = lights_url + light + '/state'
            body = '{ "on" : false }'
            rest.send('PUT', url_to_call, body, {'Content-Type': 'application/json'})
    else:
        print('Error:', all_the_lights[0]['error'])