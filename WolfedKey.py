import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

userin = input("> ")

ser.write(userin.encode('utf-8'))
while True:
    print(chr(int(ser.readline().decode('utf-8'))))
