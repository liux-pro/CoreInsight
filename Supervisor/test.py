import time
from ctypes import *
while True:
    u = windll.LoadLibrary('user32.dll')
    result = u.GetForegroundWindow()
    time.sleep(5)
    print(result) # 0则表示锁屏