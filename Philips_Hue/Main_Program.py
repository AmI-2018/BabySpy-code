


"""
@author AmirZeraa
"""

#coding main program to autorun the system

#import functions
import zway
import Normal_Mood
import braccio



def main():

  data = zway.get_values()
  while data[2] == 'true':
    if data is 'true':
      import test_flashing
      test_flashing.light()
    else:
        Normal_Mood.normal()
        print ("Safe Condition")

    if data is 'true':
        braccio.read()
    else:
      print("Safe Condition")



