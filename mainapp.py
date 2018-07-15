import sys
sys.path.append('/home/pi/Project/BabySpy-code/')
import zway
import rest
from Philips_Hue import test_flashing
import requests


def main():
    """
    main function to implement reasoning part
    :return:
    """
    triggered = False
    previous_intervent = False
    sensors = zway.connect()
    zway.set_devices(sensors, True)
    while True:

