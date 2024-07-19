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
        self._stop_event = threading.Event()
        self._connect_thread = threading.Thread(target=self._connect)
        self._connect_thread.start()

    def _connect(self):
        while not self._stop_event.is_set():
            ports = list(serial.tools.list_ports.comports())
            found = False
            for port in ports:
                if port.vid == self.vid and port.pid == self.pid:
                    found = True
                    if self.ser and self.ser.is_open:
                        break  # 已经连接，无需重新连接
                    try:
                        self.ser = serial.Serial(port.device)
                        time.sleep(1)
                    except serial.SerialException:
                        self.ser = None
                        # 继续尝试连接
            if not found:
                time.sleep(1)

    def write(self, data):
        if self.ser and self.ser.is_open:
            try:
                self.ser.write(data)
            except serial.SerialException:
                self.ser = None

    def stop(self):
        self._stop_event.set()
        self._connect_thread.join()
        if self.ser:
            self.ser.close()
            self.ser = None
