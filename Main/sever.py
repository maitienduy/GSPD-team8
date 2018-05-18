import serial
import time

print("Start")
port="COM4"#This will be different for various devices and on windows it will probably be a COM port.
bluetooth=serial.Serial(port, 9600, timeout=1)#Start communications with the bluetooth unit
print("Connected")
#bluetooth.flushInput() #This gives the bluetooth a little kick
bluetooth.write(b"data test")
while True :
        input_data=bluetooth.readline()#This reads the incoming data. In this particular example it will be the "Hello from Blue" line
        print(input_data.decode())
        time.sleep(1) #A pause between bursts
bluetooth.close() #Otherwise the connection will remain open until a timeout which ties up the /dev/thingamabob
print("Done")
