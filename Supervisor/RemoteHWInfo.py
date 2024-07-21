import requests
import time
import subprocess
import atexit


class SensorReadings:
    def __init__(self, data):
        # Extract the readings from the JSON data
        readings = {reading["labelOriginal"]: reading["value"] for reading in data["hwinfo"]["readings"]}

        # Initialize properties with appropriate data
        self.current_up_rate = readings.get('Current UP rate', 'Not found')
        self.current_dl_rate = readings.get('Current DL rate', 'Not found')
        self.total_cpu_usage = readings.get('Total CPU Usage', 'Not found')
        self.gpu_temperature = readings.get('GPU Temperature', 'Not found')
        self.physical_memory_load = readings.get('Physical Memory Load', 'Not found')

        # Determine CPU temperature
        cpu_temp = readings.get('CPU Package') or readings.get('CPU Core')
        self.cpu_temperature = cpu_temp if cpu_temp is not None else 'CPU Package or CPU Core not found'


def start_hwinfo_process():
    # Start the RemoteHWInfo.exe process
    global hwinfo_process
    hwinfo_process = subprocess.Popen(
        ['RemoteHWInfo.exe', '-LOG', '0'],
        creationflags=subprocess.CREATE_NEW_PROCESS_GROUP
    )

    # Register a function to kill the process on script exit
    atexit.register(lambda: hwinfo_process.kill())


def get_sensor_readings():
    try:
        # Fetch JSON data from the local server
        result = requests.get("http://127.0.0.1:60000/json.json")
        result.raise_for_status()  # Check if request was successful
        data = result.json()

        # Create and return SensorReadings object
        return SensorReadings(data)

    except requests.RequestException as e:
        print(f"Request error: {e}")
    except ValueError as e:
        print(f"Error parsing JSON: {e}")
    except KeyError as e:
        print(f"Missing key in JSON data: {e}")


# Start the HWInfo process
start_hwinfo_process()

# Main loop to fetch and print sensor readings
if __name__ == "__main__":
    while True:
        sensor_readings = get_sensor_readings()
        if sensor_readings:
            print(f"Current UP Rate: {sensor_readings.current_up_rate}")
            print(f"Current DL Rate: {sensor_readings.current_dl_rate}")
            print(f"Total CPU Usage: {sensor_readings.total_cpu_usage}")
            print(f"GPU Temperature: {sensor_readings.gpu_temperature}")
            print(f"Physical Memory Load: {sensor_readings.physical_memory_load}")
            print(f"CPU Temperature: {sensor_readings.cpu_temperature}")
        time.sleep(1)
