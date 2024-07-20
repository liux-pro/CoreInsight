import subprocess
import time
import cv2
import numpy as np
import serial
import time
import serial.tools.list_ports
from PIL import Image, ImageDraw, ImageFont
import numpy as np
import cv2
from communicate import *
from multiprocessing import Process

from numba import njit

from SerialHelper import SerialHelper

vid = 0x34BF
pid = 0xFFFF

# 初始化串口
s = SerialHelper(vid, pid)
s._connect()


def create_cmd(x, y, w, h):
    cmd = bytearray()
    cmd.append(ord("@"))
    cmd.append(ord("@"))
    cmd.append(ord("@"))
    cmd.append(CMD_SET_WINDOW)
    cmd.extend(int(x).to_bytes(2, byteorder='big'))
    cmd.extend(int(y).to_bytes(2, byteorder='big'))
    cmd.extend(int(w).to_bytes(2, byteorder='big'))
    cmd.extend(int(h).to_bytes(2, byteorder='big'))
    for _ in range(31 - len(cmd)):
        cmd.append(0)
    return cmd


def send_image(image):
    data_to_send = convert_image_to_rgb565(image)

    # Define the chunk size
    chunk_size = 64  # Adjust the chunk size based on the HID device characteristics

    for i in range(0, len(data_to_send), chunk_size // 2):  # Each chunk contains 32 uint16
        chunk = data_to_send[i:i + (chunk_size // 2)]
        byte_chunk = bytearray()
        for value in chunk:
            byte_chunk.extend(
                int(value).to_bytes(2, byteorder='big'))  # Convert numpy.uint16 to int before using to_bytes
        s.write(byte_chunk)


@njit
def convert_image_to_rgb565(image_rgb):
    height, width, _ = image_rgb.shape
    image_rgb565 = np.empty((height, width), dtype=np.uint16)

    for i in range(height):
        for j in range(width):
            pixel = image_rgb[i, j]
            r = pixel[0] >> 3  # 提取红色通道的前5位
            g = pixel[1] >> 2  # 提取绿色通道的前6位
            b = pixel[2] >> 3  # 提取蓝色通道的前5位
            image_rgb565[i, j] = (r << 11) | (g << 5) | b  # 组合成RGB565格式

    return image_rgb565.flatten()


process = subprocess.Popen(
    ['RemoteHWInfo.exe', '-LOG', str(0)],
    creationflags=subprocess.CREATE_NEW_PROCESS_GROUP
)

w = 200
h = 100

i = 1

for _ in range(99999):
    start_time = time.time()
    s.write(create_cmd(0, 0, w, h))

    image = Image.new('RGB', (w, h), (0, 0, 0))

    # 加载自定义字体（请替换为自定义字体文件的路径）
    font = ImageFont.truetype('AlimamaDaoLiTi.ttf', 100)

    # 创建一个 ImageDraw 对象
    draw = ImageDraw.Draw(image)

    # 绘制文本
    text = str(i)
    i += 1
    text_position = (0, 0)
    text_color = (255, 255, 255)  # 白色
    draw.text(text_position, text, font=font, fill=text_color)

    # 将 Pillow 图像转换为 NumPy 数组
    # todo 优化 zero copy
    image_np = np.array(image)

    send_image(image_np)

    elapsed_time = time.time() - start_time
    print(f"Data sent in {elapsed_time:.2f} seconds")
