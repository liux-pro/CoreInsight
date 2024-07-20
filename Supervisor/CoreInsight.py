import math
import subprocess
import time

import numpy as np
from PIL import Image, ImageDraw, ImageFont
from numba import njit

from SerialHelper import SerialHelper
from communicate import *

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


def send_image(image, x=0, y=0):
    if isinstance(image, Image.Image):
        image = np.array(image)

    data_to_send = convert_image_to_rgb565(image)
    h, w, _ = image.shape

    s.write(create_cmd(x, y, w, h))

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


def resize_and_crop(image, target_width, target_height):
    # 获取原始尺寸
    original_width, original_height = image.size

    # 计算缩放比例
    scale = max(target_width / original_width, target_height / original_height)

    # 缩放图片
    new_size = (int(original_width * scale), int(original_height * scale))
    resized_image = image.resize(new_size)

    # 获取缩放后的尺寸
    resized_width, resized_height = resized_image.size

    # 计算裁剪的位置
    left = (resized_width - target_width) / 2
    top = (resized_height - target_height) / 2
    right = (resized_width + target_width) / 2
    bottom = (resized_height + target_height) / 2

    # 裁剪图片
    cropped_image = resized_image.crop((left, top, right, bottom))

    return cropped_image


bg = Image.open('background.jpg')
bg = resize_and_crop(bg, 320, 240)

canvas = bg.copy()
send_image(bg)




w = 100
h = 50

x = 30
y = 30

i = 1

for _ in range(99999):
    image = bg.crop((x, y, w + x, h + y))

    # 加载自定义字体（请替换为自定义字体文件的路径）
    font = ImageFont.truetype('AlimamaDaoLiTi.ttf', 24)

    # 创建一个 ImageDraw 对象
    draw = ImageDraw.Draw(image)

    # 设定圆的半径和中心点
    radius = w // 2
    center_x, center_y = w // 2, h

    # 计算外圈的圆弧范围
    bbox = [center_x - radius, center_y - radius, center_x + radius, center_y + radius]

    # 绘制四分之三圆的外圈
    draw.arc(bbox, start=180, end=360, fill="blue", width=3)

    def calculate_pointer_position(center_x, center_y, pointer_radius, value):
        angle = 180 - (value / 100) * 180

        # 角度转换为弧度
        angle_rad = math.radians(angle)
        pointer_x = center_x + pointer_radius * math.cos(angle_rad)
        pointer_y = center_y - pointer_radius * math.sin(angle_rad)
        return pointer_x, pointer_y


    draw.circle(calculate_pointer_position(center_x, center_y, center_x - 1.5, i % 100), 5, fill=(255, 0, 0))
    i = i + 1

    draw.text((40,20), str(i%100), font=font, fill=(255, 0, 0))

    send_image(image, x, y)
