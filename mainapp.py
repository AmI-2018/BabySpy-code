import sys
sys.path.append('/home/pi/Project/BabySpy-code/')
import zway
import rest
import time
from Philips_Hue import test_flashing

light_motion_id = '2'
door_id = '3'
base_url = ''


def main():
    """
    main function to implement reasoning part
    :return:
    """
    triggered = False
    previous_intervent = False
    last_intervent = ''
    sensors = zway.connect()
    zway.set_devices(sensors, True)
    while True:
        time.sleep(10)
        sensor_lm = zway.get_values(sensors, light_motion_id)
        lminosity = sensor_lm.pop(0)
        motion = sensor_lm.pop(0)
        sensor_door = zway.get_values(sensors, door_id)
        drawer_opened = sensor_door.pop(0)
        triggered = motion or drawer_opened
        if triggered:
            global motion
            if motion:
                intervent ='motion'
            else:
                intervent = 'drawer'
            print(intervent + " detected " + time.asctime(time.localtime(time.time())))
            if not previous_intervent:
                # distract(intervent, luminosity)
            else:
                if intervent == last_intervent:
                    data = {'event' : intervent}
                    rest.send('POST', url=base_url + '/api/danger', data=data)
                else:
                    # distract*intervent, luminosity)
                last_intervent = intervent
        elif not triggered and previous_intervent:
            previous_intervent = False
