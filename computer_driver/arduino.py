from time import sleep

import serial
from visualisation import v

SERIAL_PORT = '/dev/cu.usbmodem1411'


def send(ser):
    data, beat, power = v.get()

    message = [chr(0)] * 8
    message[:5] = [chr(i) for i in data]
    message[5] = chr(beat)
    message[6] = chr(power)

    print repr(message), data, beat, power
    ser.write(''.join(message))


if __name__ == "__main__":
    try:
        ser = serial.Serial(SERIAL_PORT, 9600)

        while True:
            send(ser)
            sleep(0.04)
    finally:
        v.end()