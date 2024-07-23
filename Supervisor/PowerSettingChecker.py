import win32con
import win32api
import win32gui
import time
import threading
from ctypes import POINTER, windll, Structure, cast, CFUNCTYPE, c_int, c_uint, c_void_p, c_bool
from comtypes import GUID
from ctypes.wintypes import HANDLE, DWORD

# Power setting change constants
PBT_POWERSETTINGCHANGE = 0x8013

# GUIDs for power settings
GUIDS = {
    'GUID_CONSOLE_DISPLAY_STATE': '{6FE69556-704A-47A0-8F24-C28D936FDA47}',
    'GUID_ACDC_POWER_SOURCE': '{5D3E9A59-E9D5-4B00-A6BD-FF34FF516548}',
    'GUID_BATTERY_PERCENTAGE_REMAINING': '{A7AD8041-B45A-4CAE-87A3-EECBB468A9E1}',
    'GUID_MONITOR_POWER_ON': '{02731015-4510-4526-99E6-E5A17EBD1AEA}'
}


class PowerBroadcastSetting(Structure):
    _fields_ = [("PowerSetting", GUID),
                ("DataLength", DWORD),
                ("Data", DWORD)]


class PowerSettingChecker:
    def __init__(self):
        self.hwnd = None
        self.guids = GUIDS
        self.registered_notifications = {}
        self.notifications_received = {key: False for key in self.guids}
        self.thread = None
        self.running = False

        # Initialize properties to save the state of power settings
        self.console_display_state = False
        self.acdc_power_source = False
        self.battery_percentage_remaining = 0
        self.monitor_power_on = False

    def wndproc(self, hwnd, msg, wparam, lparam):
        """
        Window procedure to handle power broadcast messages.
        """
        if msg == win32con.WM_POWERBROADCAST:
            if wparam == win32con.PBT_APMPOWERSTATUSCHANGE:
                self.handle_power_status_change()
            elif wparam == win32con.PBT_APMRESUMEAUTOMATIC:
                self.handle_system_resume_automatic()
            elif wparam == win32con.PBT_APMRESUMESUSPEND:
                self.handle_system_resume_suspend()
            elif wparam == win32con.PBT_APMSUSPEND:
                self.handle_system_suspend()
            elif wparam == PBT_POWERSETTINGCHANGE:
                self.handle_power_setting_change(lparam)
            return True
        return False

    def handle_power_status_change(self):
        print('Power status has changed')

    def handle_system_resume_automatic(self):
        print('System resumed automatically')

    def handle_system_resume_suspend(self):
        print('System resumed by user input')

    def handle_system_suspend(self):
        print('System is suspending')

    def handle_power_setting_change(self, lparam):
        settings = cast(lparam, POINTER(PowerBroadcastSetting)).contents
        power_setting = str(settings.PowerSetting)
        data = settings.Data

        if power_setting == self.guids['GUID_CONSOLE_DISPLAY_STATE']:
            self.handle_console_display_state(data)
            self.notifications_received['GUID_CONSOLE_DISPLAY_STATE'] = True
        elif power_setting == self.guids['GUID_ACDC_POWER_SOURCE']:
            self.handle_acdc_power_source(data)
            self.notifications_received['GUID_ACDC_POWER_SOURCE'] = True
        elif power_setting == self.guids['GUID_BATTERY_PERCENTAGE_REMAINING']:
            self.handle_battery_percentage_remaining(data)
            self.notifications_received['GUID_BATTERY_PERCENTAGE_REMAINING'] = True
        elif power_setting == self.guids['GUID_MONITOR_POWER_ON']:
            self.handle_monitor_power_on(data)
            self.notifications_received['GUID_MONITOR_POWER_ON'] = True
        else:
            print('Unknown GUID:', power_setting)

    def handle_console_display_state(self, data):
        if data == 0:
            print('Display off')
            self.console_display_state = False
        elif data == 1:
            print('Display on')
            self.console_display_state = True
        elif data == 2:
            print('Display dimmed')
            self.console_display_state = True

    def handle_acdc_power_source(self, data):
        if data == 0:
            print('AC power')
            self.acdc_power_source = True
        elif data == 1:
            print('Battery power')
            self.acdc_power_source = False
        elif data == 2:
            print('Short term power')
            self.acdc_power_source = False

    def handle_battery_percentage_remaining(self, data):
        print('Battery remaining: %d%%' % data)
        self.battery_percentage_remaining = data

    def handle_monitor_power_on(self, data):
        if data == 0:
            print('Monitor off')
            self.monitor_power_on = False
        elif data == 1:
            print('Monitor on')
            self.monitor_power_on = True

    def all_notifications_received(self):
        """
        Check if all power settings have received notifications.
        """
        return all(self.notifications_received.values())

    def create_window(self):
        """
        Create a hidden window to receive power setting change messages.
        """
        hinst = win32api.GetModuleHandle(None)
        wndclass = win32gui.WNDCLASS()
        wndclass.hInstance = hinst
        wndclass.lpszClassName = "PowerSettingListener"
        CMPFUNC = CFUNCTYPE(c_bool, c_int, c_uint, c_uint, c_void_p)
        wndproc_pointer = CMPFUNC(self.wndproc)
        wndclass.lpfnWndProc = {win32con.WM_POWERBROADCAST: wndproc_pointer}

        try:
            myWindowClass = win32gui.RegisterClass(wndclass)
            self.hwnd = win32gui.CreateWindowEx(
                win32con.WS_EX_LEFT,
                myWindowClass,
                "PowerSettingListenerWindow",
                0,
                0,
                0,
                win32con.CW_USEDEFAULT,
                win32con.CW_USEDEFAULT,
                0,
                0,
                hinst,
                None
            )
        except Exception as e:
            print("Exception during window creation:", str(e))
            return False

        return self.hwnd is not None

    def register_power_notifications(self):
        """
        Register to receive notifications for specified power settings.
        """
        if not self.hwnd:
            print("Window handle is not created.")
            return False

        for name, guid_info in self.guids.items():
            result = windll.user32.RegisterPowerSettingNotification(
                HANDLE(self.hwnd), GUID(guid_info), DWORD(0)
            )
            if result:
                print(f'Registered {name} successfully.')
                self.registered_notifications[name] = result
            else:
                print(f'Failed to register {name}. Error code:', win32api.GetLastError())

        return len(self.registered_notifications) == len(self.guids)

    def start_listening(self):
        """
        Start the message loop to listen for power setting changes in a separate thread.
        """
        if not self.hwnd:
            if not self.create_window():
                print("Failed to create the window for listening.")
                return

        if not self.register_power_notifications():
            print("Failed to register power notifications.")
            return

        print('Listening for power setting changes. Press Ctrl+C to exit.')

        self.running = True
        try:
            while self.running:
                win32gui.PumpWaitingMessages()
                time.sleep(1)
        except KeyboardInterrupt:
            print("\nExiting program.")
            self.running = False

    def start(self):
        """
        Start the listener in a new thread.
        """
        if self.thread is None:
            self.thread = threading.Thread(target=self.start_listening, daemon=True)
            self.thread.start()
            print("Listener started in a new thread.")

    def stop(self):
        """
        Stop the listener.
        """
        self.running = False
        if self.thread is not None:
            self.thread.join()
            self.thread = None
            print("Listener stopped.")


# Example usage
if __name__ == "__main__":
    listener = PowerSettingChecker()
    listener.start()  # Start the listener in a new thread

    # Wait for some time and then access the states
    time.sleep(10)  # Let it run for a while

    # Access the saved states
    print("Console Display State:", listener.console_display_state)
    print("AC Power Source:", listener.acdc_power_source)
    print("Battery Percentage Remaining:", listener.battery_percentage_remaining)
    print("Monitor Power On:", listener.monitor_power_on)

    listener.stop()
