from Zway import rest
import time

#base url of the ZWave API
base_url = 'http://192.168.0.202:8083'
device_url = base_url + '/ZWaveAPI/Run/devices[{}].instances[{}].commandClasses[{}]'
#useful command classes
comm_classes = {"sensor_multi": '49', "sensor_binary": '48'}
# user credentials
username = ''
password = ''


def connect():
    """
    The function initializes the connection to the z-wave controller
    and get the list of all devices connected to it
    :return: list of all devices connected to the controller
    """

    #get z-wave devices
    all_devices = rest.send(url=base_url+'/ZWaveAPI/Data/0', auth=(username, password))

    #clean up all_devices and removing the controller
    all_devices = all_devices['devices']
    all_devices.pop('1')
    return all_devices


def set_device(all_devices, device_key, command, value):
    """
    Turn the selected device on or off
    :param device_key: the key of the device required
    :param command_class: which type of interface to act on
    :param value: true for getting on, false for getting off
    :return:
    """
    if all_devices[device_key] is not None:
        instances = all_devices[device_key]['instances']
        for instance in instances:
            if comm_classes[command] in all_devices[device_key]['instances'][instance]['commandClasses']:
                #turn it on (255)
                url_to_call = (device_url + '.Set(255)').format(device_key, instance, comm_classes[command])
                rest.send(url=url_to_call, auth=(username,password))
