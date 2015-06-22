from time import sleep

import serial
from visualisation import v

SERIAL_PORT = '/dev/cu.usbmodem1411'


def send(ser):
    data, beat = v.get()
    message = ''.join(chr(i) for i in data + [int(beat)])

    print repr(message), data, beat
    ser.write(message)


if __name__ == "__main__":
    try:
        ser = serial.Serial(SERIAL_PORT, 9600)

        while True:
            send(ser)
            sleep(0.04)
    finally:
        v.end()