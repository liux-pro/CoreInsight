import serial
import time

# 打开串口
ser = serial.Serial('COM12', 9600)  # 替换为您的串口和波特率

try:
    while True:
        # 将 DTR 和 RTS 引脚设置为高电平
        ser.dtr = True
        ser.rts = True
        print("DTR and RTS are HIGH")
        time.sleep(0.5)  # 保持高电平 0.5 秒

        # 将 DTR 和 RTS 引脚设置为低电平
        ser.dtr = False
        ser.rts = False
        print("DTR and RTS are LOW")
        time.sleep(0.5)  # 保持低电平 0.5 秒

except KeyboardInterrupt:
    # 捕获 Ctrl+C 以便在按下 Ctrl+C 时退出循环
    print("Program interrupted")

finally:
    # 确保在程序结束时关闭串口
    ser.close()
    print("Serial port closed")
