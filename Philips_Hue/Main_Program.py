


"""
@author AmirZeraa
"""

#coding main program to autorun the system

#import functions
import zway
import Normal_Mood
import braccio
import time



def main():
    #getting value from the zwave
  data = zway.get_values()
    #check if the sensre detect the child in a dangrouse situation
  while data[2] == 'true':
    #if yes start to distract the child by lights
    if data is 'true':
      import test_flashing
      test_flashing.light()
    #if not turn the lights on in the normal mode
    else:
        Normal_Mood.normal()
        print ("Safe Condition")

    time.sleep(5)
    #try to distract the child by Braccio
    if data is 'true':
        braccio.read()
    else:
      print("Safe Condition")



