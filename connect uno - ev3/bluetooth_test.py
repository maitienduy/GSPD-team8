import bluetooth
import threading
import json
import time

hostMACAddress = 'CC:78:AB:51:51:97'
clientMACAddress = 'A0:E4:53:A1:57:F6'
arduinoMACAddress = '40:2C:F4:6F:FC:C5'

server_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
port = 1
server_socket.bind(("", port))
server_socket.listen(1)
client_client = None
arduino_client = None


class ConnectedClient(threading.Thread):
    def __init__(self, socket, client_info):
        threading.Thread.__init__(self)
        self.socket = socket
        self.client_info = client_info
        self.message = None
        self.message_to_send = None

    def run(self):
        try:
            while True:
                data = self.socket.recv(1024)
                if len(data) == 0:
                    break
                str_data = data.decode('utf-8')
                self.message = json.loads(str_data)
                if self.message_to_send is not None:
                    print("sending")
                    self.socket.send(self.message_to_send)
                    self.message_to_send = None
        except IOError:
            pass
        self.socket.close()
        print(self.client_info, ": disconnected")


while True:
    print("Waiting for client")
    if arduino_client is None or client_client is None:
        client_socket, client_info = server_socket.accept()
        print(client_info, ": connection accepted")
        print(client_info[0])
        if client_info[0] == clientMACAddress:
            print("client_client")
            client_client = ConnectedClient(client_socket, client_info)
            client_client.setDaemon(True)
            client_client.start()

        elif client_info[0] == arduinoMACAddress:
            print("arduino_client")
            arduino_client = ConnectedClient(client_socket, client_info)
            arduino_client.setDaemon(True)
            arduino_client.start()
    arduino_client.message_to_send = "test"
    time.sleep(1)

server_socket.close()
