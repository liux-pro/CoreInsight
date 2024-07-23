import time
from ctypes import windll
from threading import Thread, Event


class ScreenLockChecker:
    def __init__(self):
        # Variable to keep track of screen lock status
        self._is_locked = False
        self._stop_event = Event()  # Event to signal the thread to stop
        self._thread = Thread(target=self._check_lock_status, daemon=True)  # Daemon thread

        # Automatically start the thread when an instance is created
        self._thread.start()

    def _check_lock_status(self):
        """
        Private method to check if the screen is locked. Updates the `self._is_locked` variable
        only if the foreground window handle is 0 for five consecutive checks.
        """
        consecutive_count = 0
        u = windll.LoadLibrary('user32.dll')  # Load the user32.dll library

        while not self._stop_event.is_set():
            result = u.GetForegroundWindow()
            if result == 0:
                consecutive_count += 1
                if consecutive_count >= 3:
                    self._is_locked = True
            else:
                consecutive_count = 0
                self._is_locked = False

            time.sleep(0.5)  # Check every second

    def check_screen_lock(self):
        """
        Check the screen lock status immediately by returning the current value of `self._is_locked`.

        :return: True if the screen is locked (5 consecutive checks of zero), otherwise False.
        """
        # Return the current screen lock status immediately
        return self._is_locked


if __name__ == '__main__':
    # Example usage of the ScreenLockChecker class
    checker = ScreenLockChecker()

    try:
        while True:
            # Call the check_screen_lock method to get the current lock status
            if checker.check_screen_lock():
                print("The screen is locked.")
            else:
                print("The screen is not locked.")

            time.sleep(1)  # Main loop checks every second
    except KeyboardInterrupt:
        # Gracefully stop the checking thread when interrupted
        print("Exiting...")
