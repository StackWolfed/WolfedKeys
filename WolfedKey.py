import serial
import serial.tools.list_ports
ports = list(serial.tools.list_ports.comports())
devicePort = ""
for p in ports:
    if "Arduino" in p.description:
        devicePort = p.device
try:
    ser = serial.Serial(devicePort, 9600, timeout=10)
except:
    print("Belin, we got an error connecting to the Arduino, please make sure it's connected before launching this")
    exit()
#
# userin = input("> ")
#
# ser.write(userin.encode('utf-8'))
# while True:
#     print(chr((ser.readline().decode('utf-8'))))


def editButton():
    btn = str(input("Button number: "))
    buffer = []
    for i in range(0, 9):
        if i % 2 == 0:
            buffer.append(str(input(i)))
        else:
            buffer.append(str(chr(int(float(input(i))))))
    sendMsg = ""
    sendMsg = str(sendMsg + btn + buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] + buffer[6] + buffer[7] + buffer[8])
    print(sendMsg)
    ser.write(bytes(sendMsg.encode('utf-8')))

def readButton():
    btn = str(input("Button number: "))
    sendMsg = "`" + btn;
    ser.write(sendMsg.encode('utf-8'))
    for i in range(0, 9):
        print(ser.readline().decode('utf-8'))

while True:
    menumsg = "Select Option:\n1 = Configure new button combo\n2 = Read Button\n3 = Exit"
    userin = input(menumsg)
    if userin == "1":
        editButton()
    elif userin == "2":
        readButton()
    else:
        exit()
