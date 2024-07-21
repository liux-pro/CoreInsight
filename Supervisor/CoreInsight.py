import math
import time

import numpy as np
from PIL import Image, ImageDraw, ImageFont
from numba import njit

from RemoteHWInfo import get_sensor_readings
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


def draw_gauge_image(cropped_image, value, font_path='AlimamaDaoLiTi.ttf',font_size=36, text_offset_x=0, text_offset_y=0):
    """
    绘制包含仪表盘和指针的图像。

    参数:
        cropped_image (Image): 裁剪后的图像。
        value (int): 仪表盘的刻度值 (0 到 100)。
        font_path (str): 自定义字体文件的路径。

    返回:
        Image: 绘制后的图像。
    """
    w, h = cropped_image.size
    padding = 5  # 添加一个填充，以避免绘图内容超出图像范围
    inner_w, inner_h = w - 2 * padding, h - 2 * padding

    # 创建一个 ImageDraw 对象
    draw = ImageDraw.Draw(cropped_image)

    # 加载自定义字体
    font = ImageFont.truetype(font_path, font_size)

    # 设定圆的半径和中心点
    radius = inner_w / 2 - padding
    center_x, center_y = padding + inner_w // 2, h - padding

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

    # 绘制小圆球
    pointer_x, pointer_y = calculate_pointer_position(center_x, center_y, radius - 1.5, value)
    draw.ellipse((pointer_x - 5, pointer_y - 5, pointer_x + 5 + 1, pointer_y + 5 + 1), fill=(255, 0, 0))

    # 获取文本尺寸
    text = str(value)
    text_bbox = draw.textbbox((0, 0), text, font=font)
    text_width = text_bbox[2] - text_bbox[0]
    text_height = text_bbox[3] - text_bbox[1]

    # 计算文本位置，使其居中
    text_x = center_x - text_width // 2
    text_y = padding + (inner_h - text_height) // 2

    # 绘制文本
    draw.text((text_x + text_offset_x, text_y + text_offset_y), text, font=font, fill=(255, 0, 0))

    return cropped_image


bg = Image.open('background.jpg')
bg = resize_and_crop(bg, 320, 240)

canvas = bg.copy()
send_image(bg)

# 假设你已经定义了这些变量
i = 0
w, h = 100, 50

for i in range(99999):
    sensor_readings = get_sensor_readings()

    x = 120
    y = 0
    # 从背景中裁剪图像
    tile = bg.crop((x, y, x + w, y + h))
    tile = draw_gauge_image(tile, int(sensor_readings.total_cpu_usage))
    send_image(tile, x, y)

    x = 120
    y = 50
    tile = bg.crop((x, y, x + 100, y + 24))
    draw = ImageDraw.Draw(tile)
    draw.text((0,0),"CPU使用率",font=ImageFont.truetype("AlimamaDaoLiTi.ttf", 20))
    send_image(tile, x, y)

    w, h = 100, 50
    x = 220
    y = 0
    # 从背景中裁剪图像
    tile = bg.crop((x, y, x + w, y + h))
    tile = draw_gauge_image(tile, int(sensor_readings.physical_memory_load))
    send_image(tile, x, y)
    x = 220
    y = 50
    tile = bg.crop((x, y, x + 100, y + 24))
    draw = ImageDraw.Draw(tile)
    draw.text((0,0),"内存使用率",font=ImageFont.truetype("AlimamaDaoLiTi.ttf", 20))
    send_image(tile, x, y)

    time.sleep(0.1)
