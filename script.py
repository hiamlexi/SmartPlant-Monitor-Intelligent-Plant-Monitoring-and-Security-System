import time
import requests
import serial.tools.list_ports
import serial
import math

TOKEN = "BBUS-AIPzvW9BVPqbibGMfAGSZyX1nx36yR"  # Put your TOKEN here
DEVICE_LABEL = "My_PC"  # Put your device label here 
VARIABLE_LABEL_1 = "t"  # Put your temperature variable label here
VARIABLE_LABEL_2 = "h"  # Put your humidity variable label here
VARIABLE_LABEL_3 = "currentDistance"  # Put your third variable label here

def list_ports():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        print(f"{port.device}: {port.description}")
    return [port.device for port in ports]

def get_serial_port():
    available_ports = list_ports()
    if 'COM5' in available_ports:
        return 'COM5'
    else:
        print("COM5 is not available. Available ports are:", available_ports)
        return None

def is_nan(value):
    try:
        return math.isnan(float(value))
    except ValueError:
        return True 

def build_payload(variable_1, variable_2,variable_3, data):
    value_1 = float(data[0]) if not is_nan(data[0]) else None
    value_2 = float(data[1]) if not is_nan(data[1]) else None
    value_3 = float(data[2]) if not is_nan(data[2]) else None


    payload = {variable_1: value_1, variable_2: value_2, variable_3: value_3}
    return payload

def post_request(payload):
    url = "http://industrial.api.ubidots.com/api/v1.6/devices/{}".format(DEVICE_LABEL)
    headers = {"X-Auth-Token": TOKEN, "Content-Type": "application/json"}

    status = 400
    attempts = 0
    while status >= 400 and attempts <= 5:
        req = requests.post(url=url, headers=headers, json=payload)
        status = req.status_code
        attempts += 1
        time.sleep(1)

    if status >= 400:
        print("[ERROR] Could not send data after 5 attempts, please check your token credentials and internet connection")
        return False

    print("Device ID updated...wait for data transfer")
    return True

def main():
    ser_port = get_serial_port()
    if ser_port is None:
        print("Exiting due to unavailable COM port.")
        return

    try:
        ser = serial.Serial(ser_port, 9600, timeout=1)
        print("Reading data from serial port.....")
        time.sleep(2)
        ser.reset_input_buffer()

        while True:
            line = ser.readline()
            if line:
                rxdata = line.decode().strip()
                tmp = rxdata.split(',')

                payload = build_payload(VARIABLE_LABEL_1, VARIABLE_LABEL_2,VARIABLE_LABEL_3, tmp)
                print(tmp[0], tmp[1], tmp[2])
                print("Data transfer started")
                post_request(payload)
                print("Data Successfully sent to cloud")
            time.sleep(1)
    except serial.SerialException as e:
        print(f"Error: {e}")
        if "Access is denied" in str(e):
          
            print("COM5 is in use by another application. Please close any other applications using this port and try again.")

if __name__ == '__main__':
    main()
