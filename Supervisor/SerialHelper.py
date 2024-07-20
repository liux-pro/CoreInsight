import threading
import time
import serial
import serial.tools.list_ports


# todo 不好用，以后改
class SerialHelper:
    def __init__(self, vid, pid):
        self.vid = vid
        self.pid = pid
        self.ser = None

    def _connect(self):
        while True:
            ports = list(serial.tools.list_ports.comports())
            for port in ports:
                if port.vid == self.vid and port.pid == self.pid:
                    self.ser = serial.Serial(port.device)
                    return
            time.sleep(1)

    def write(self, data):
        if self.ser and self.ser.is_open:
            self.ser.write(data)

    def stop(self):
        if self.ser:
            self.ser.close()
            self.ser = None
