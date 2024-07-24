import threading
import time
import serial
import serial.tools.list_ports

class SerialHelper:
    def __init__(self, vid, pid):
        self.vid = vid
        self.pid = pid
        self.ser = None
        self.auto_reconnect = False  # Flag to indicate if reconnection happened
        self._stop_event = threading.Event()  # Event to control the thread
        self._connection_thread = threading.Thread(target=self._connection_monitor,daemon=True)
        self._connection_thread.start()

    def _connect(self):
        """Try to connect to the device with specified VID and PID."""
        while not self._stop_event.is_set():  # Run until stop is requested
            ports = list(serial.tools.list_ports.comports())
            for port in ports:
                if port.vid == self.vid and port.pid == self.pid:
                    try:
                        self.ser = serial.Serial(port.device)
                        self.auto_reconnect = True  # Set reconnection flag
                        print(f"Connected to {port.device}")
                        return
                    except serial.SerialException as e:
                        print(f"Failed to connect: {e}")
            time.sleep(1)

    def _connection_monitor(self):
        """Continuously monitor the connection and attempt to reconnect if lost."""
        while not self._stop_event.is_set():
            if self.ser is None or not self.ser.is_open:
                self._connect()
            else:
                try:
                    self.ser.in_waiting  # Check if the serial port is responsive
                except serial.SerialException:
                    print("Connection lost. Attempting to reconnect...")
                    self.ser.close()
                    self.ser = None
                    self.auto_reconnect = True  # Set reconnection flag
            time.sleep(1)

    def write(self, data):
        """Write data to the serial port."""
        if self.ser and self.ser.is_open:
            try:
                self.ser.write(data)
            except serial.SerialException as e:
                print(f"Write error: {e}")
                self.ser.close()
                self.ser = None
                self.auto_reconnect = True  # Set reconnection flag

    def stop(self):
        """Stop the serial helper and close the connection."""
        self._stop_event.set()
        self._connection_thread.join()  # Wait for the thread to finish
        if self.ser:
            self.ser.close()
            self.ser = None

    def has_reconnected(self):
        """Check if an automatic reconnection has occurred."""
        if self.auto_reconnect:
            self.auto_reconnect = False  # Reset flag after checking
            return True
        return False
