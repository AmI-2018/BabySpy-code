

"""
@author AmirZeraa
"""

#coding main program to autorun the system

#import rest from Z-wave
#import jason


if __name__ == '__main__':

  jason = 'true'
  while jason == 'true':

    wave_url = jason #+ '/api/'

    if wave_url is 'true':
      import test_flashing
      test_flashing.light()
    else:
        print ("Safe Condition")

  while jason == 'true':

    wave_url = jason + '/api/'

    if wave_url is 'true':
      import Arduino_JASON_API
      #function

    else:
      print("Safe Condition")



