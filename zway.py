import rest
import time

# base url of the ZWave API
base_url = 'http://localhost:8083'
device_url = base_url + '/ZWaveAPI/Run/devices[{}].instances[{}].commandClasses[{}]'
# update url
update_url = base_url + '/ZAutomation/api/v1/ZWayVDev_zway_{}-0-{}-{}/command/update'
# useful command classes
comm_classes = {"sensor_multi": '49', "sensor_binary": '48'}
# user credentials
username = 'admin'
password = 'BaBySpy-zway.18'


def connect():
    """
    The function initializes the connection to the z-wave controller
    and get the list of all devices connected to it
    :return: list of all devices connected to the controller, exluded the latter
    """

    # get z-wave devices
    all_devices = rest.send(url=base_url + '/ZWaveAPI/Data/0', auth=(username, password))
    # print(all_devices)

    # clean up all_devices and removing the controller
    all_devices = all_devices['devices']
    all_devices.pop('1')
    # print(all_devices)
    return all_devices


def set_devices(all_devices, value):
    """
    Turn the devices on or off
    :param all_devices: the list of devices (entire list) to be switched
    :param value: true for getting on, false for getting off
    :return:
    """
    for device_key in all_devices:
        if all_devices[device_key] is not None:
            instances = all_devices[device_key]['instances']
            if value:
                for instance in instances:
                    for command_class in all_devices[device_key]['instances'][instance]['commandClasses']:
                        # turn it on (255)
                        url_to_call = (device_url + '.Set(255)').format(device_key, instance, command_class)
                        rest.send(url=url_to_call, auth=(username, password))
            else:
                for instance in instances:
                    for command_class in all_devices[device_key]['instances'][instance]['commandClasses']:
                        # turn it off (0)
                        url_to_call = (device_url + '.Set(0)').format(device_key, instance, command_class)
                        rest.send(url=url_to_call, auth=(username, password))


def get_value(all_devices, device_key, instance):
    """
    :param all_devices: the list of the devices of the system
    :param device_key: the device which we need to access information from
    :param instance: the particular instance of the device we are retrieving information from
    :return: all the values of the different classes the device support, joined inside a list
    """
    if all_devices[device_key]['instances'][instance] is not None:
        data = list()
        if comm_classes["sensor_multi"] in all_devices[device_key]['instances'][instance]['commandClasses']:
            url_to_update = update_url.format(device_key, comm_classes['sensor_multi'], instance)
            # print(device_key + "\t" + instance)
            rest.send(url=url_to_update, auth=(username, password))
            url_to_call = device_url.format(device_key, instance, comm_classes["sensor_multi"])
            response = rest.send(url=url_to_call, auth=(username, password))
            data.append(response['data']['3']['val']['value'])
        if comm_classes["sensor_binary"] in all_devices[device_key]['instances'][instance]['commandClasses']:
            url_to_update = update_url.format(device_key, comm_classes['sensor_binary'], instance)
            # print(device_key + "\t" + instance)
            rest.send(url=url_to_update, auth=(username, password))
            url_to_call = device_url.format(device_key, instance, comm_classes["sensor_binary"])
            response = rest.send(url=url_to_call, auth=(username, password))
            data.append(response['data']['1']['level']['value'])
    else:
        data = None
    # print(data)
    return data


def get_values(all_devices, device_key):
    """
    :param all_devices: the list of the devices of the system
    :param device_key: the device which we need to access information from
    :return: the collection of all the values of all classes of the all instances of that device as a list
    """
    data = list()
    for instance in all_devices[device_key]['instances']:
        value = get_value(all_devices, device_key, instance)
        if value is not None:
            data.append(value.copy())
    if len(data) == 0:
        data = None
    return data


if __name__ == '__main__':
    devices = connect()
    for device in devices:
        print("This is the device ID: " + device)
    set_devices(devices, True)
    for i in range(0, 10):
        time.sleep(3)
        motion = get_values(devices, '2')
        door_window = get_values(devices, '3')
        print(motion)
        time.sleep(1)
        print(door_window)
    time.sleep(2)
    print("Turning devices off")
    set_devices(devices, False)
    print("Ending")
