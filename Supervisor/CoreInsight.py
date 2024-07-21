import math
import time
import numpy as np
from PIL import Image, ImageDraw, ImageFont
from numba import njit

from RemoteHWInfo import get_sensor_readings
from SerialHelper import SerialHelper
from communicate import *

# 常量定义
VID = 0x34BF
PID = 0xFFFF
FONT_PATH = 'MapleMono-SC-NF-Bold.ttf'
BG_PATH = 'background.jpg'
GAUGE_FONT_SIZE = 36
LABEL_FONT_SIZE = 20
CMD_PREFIX = b'@@@'
CMD_FILL_BYTE = 0

# 初始化串口
serial_helper = SerialHelper(VID, PID)
serial_helper._connect()


def create_cmd(x, y, w, h):
    cmd = bytearray(CMD_PREFIX)
    cmd.append(CMD_SET_WINDOW)
    cmd.extend(int(x).to_bytes(2, byteorder='big'))
    cmd.extend(int(y).to_bytes(2, byteorder='big'))
    cmd.extend(int(w).to_bytes(2, byteorder='big'))
    cmd.extend(int(h).to_bytes(2, byteorder='big'))
    cmd.extend([CMD_FILL_BYTE] * (31 - len(cmd)))
    return cmd


def send_image(image, x=0, y=0):
    if isinstance(image, Image.Image):
        image = np.array(image)
    data_to_send = convert_image_to_rgb565(image)
    h, w, _ = image.shape
    serial_helper.write(create_cmd(x, y, w, h))
    chunk_size = 64
    for i in range(0, len(data_to_send), chunk_size // 2):
        chunk = data_to_send[i:i + (chunk_size // 2)]
        byte_chunk = bytearray()
        for value in chunk:
            byte_chunk.extend(int(value).to_bytes(2, byteorder='big'))
        serial_helper.write(byte_chunk)


@njit
def convert_image_to_rgb565(image_rgb):
    height, width, _ = image_rgb.shape
    image_rgb565 = np.empty((height, width), dtype=np.uint16)
    for i in range(height):
        for j in range(width):
            pixel = image_rgb[i, j]
            r = pixel[0] >> 3
            g = pixel[1] >> 2
            b = pixel[2] >> 3
            image_rgb565[i, j] = (r << 11) | (g << 5) | b
    return image_rgb565.flatten()


def resize_and_crop(image, target_width, target_height):
    original_width, original_height = image.size
    scale = max(target_width / original_width, target_height / original_height)
    resized_image = image.resize((int(original_width * scale), int(original_height * scale)))
    resized_width, resized_height = resized_image.size
    left = (resized_width - target_width) / 2
    top = (resized_height - target_height) / 2
    right = (resized_width + target_width) / 2
    bottom = (resized_height + target_height) / 2
    return resized_image.crop((left, top, right, bottom))


def draw_gauge_image(image, value, font_path=FONT_PATH, font_size=GAUGE_FONT_SIZE, text_offset_x=0, text_offset_y=0):
    w, h = image.size
    padding = 5
    inner_w, inner_h = w - 2 * padding, h - 2 * padding
    draw = ImageDraw.Draw(image)
    font = ImageFont.truetype(font_path, font_size)
    radius = inner_w / 2 - padding
    center_x, center_y = padding + inner_w // 2, h - padding
    bbox = [center_x - radius, center_y - radius, center_x + radius, center_y + radius]
    draw.arc(bbox, start=180, end=360, fill=(200, 200, 200), width=3)

    angle = math.radians(180 - (value / 100) * 180)
    pointer_x = center_x + (radius - 1.5) * math.cos(angle)
    pointer_y = center_y - (radius - 1.5) * math.sin(angle)
    draw.ellipse((pointer_x - 5, pointer_y - 5, pointer_x + 6, pointer_y + 6), fill=(255, 255, 255))

    text = str(value)
    text_bbox = draw.textbbox((0, 0), text, font=font)
    text_width, text_height = text_bbox[2] - text_bbox[0], text_bbox[3] - text_bbox[1]
    text_x, text_y = center_x - text_width // 2, padding + (inner_h - text_height) // 2
    draw.text((text_x + text_offset_x, text_y + text_offset_y), text, font=font, fill=(255, 255, 255))

    return image


def update_display(bg_image, sensor_readings):
    coordinates = [(75, 0, 100, 50), (75, 50, 100, 50)]
    values = [int(sensor_readings.total_cpu_usage), int(sensor_readings.physical_memory_load)]
    for i, (x, y, w, h) in enumerate(coordinates):
        tile = bg_image.crop((x, y, x + w, y + h))
        tile = draw_gauge_image(tile, values[i])
        send_image(tile, x, y)

    def format_speed(speed_kbps):
        units = ["KB/s", "MB/s", "GB/s", "TB/s"]
        unit_index = 0

        while speed_kbps >= 1024 and unit_index < len(units) - 1:
            speed_kbps /= 1024
            unit_index += 1

        return f"{speed_kbps:.0f}{units[unit_index]}"

    coordinates = [(80, 150, 110, 36), (80, 180, 110, 36)]
    labels = [format_speed(sensor_readings.current_up_rate), format_speed(sensor_readings.current_dl_rate)]
    for i, (x, y, w, h) in enumerate(coordinates):
        tile = bg_image.crop((x, y, x + w, y + h))
        draw = ImageDraw.Draw(tile)

        text_width = draw.textlength(labels[i], font=ImageFont.truetype(FONT_PATH, 24))

        draw.text((w - text_width, 0), labels[i], font=ImageFont.truetype(FONT_PATH, 24))
        send_image(tile, x, y)

    coordinates = [(176, 0, 144, 36), (176, 36, 144, 36)]
    values = [f"CPU {sensor_readings.cpu_temperature:.1f}°C", f"GPU {sensor_readings.gpu_temperature:.1f}°C"]
    for i, (x, y, w, h) in enumerate(coordinates):
        tile = bg_image.crop((x, y, x + w, y + h))
        draw = ImageDraw.Draw(tile)


        draw.text((0, 0), values[i], font=ImageFont.truetype(FONT_PATH, 24))
        send_image(tile, x, y)


bg_image = resize_and_crop(Image.open(BG_PATH), 320, 240)
send_image(bg_image)

coordinates = [(0, 10, 80, 50), (0, 60, 80, 50)]
labels = ["CPU", "Mem"]
for i, (x, y, w, h) in enumerate(coordinates):
    tile = bg_image.crop((x, y, x + w, y + h))
    draw = ImageDraw.Draw(tile)
    draw.text((0, 0), labels[i], font=ImageFont.truetype(FONT_PATH, 36))
    send_image(tile, x, y)

coordinates = [(0, 150, 150, 36), (0, 180, 150, 36)]
labels = [f"上传:", f"下载:"]
for i, (x, y, w, h) in enumerate(coordinates):
    tile = bg_image.crop((x, y, x + w, y + h))
    draw = ImageDraw.Draw(tile)
    draw.text((0, 0), labels[i], font=ImageFont.truetype(FONT_PATH, 24))
    send_image(tile, x, y)


x=230
y=100
w=64
h=64
cpu_logo = Image.open(f"amd.png")
cpu_logo = cpu_logo.resize((w, int(w * cpu_logo.height / cpu_logo.width)))
tile = bg_image.crop((x, y, x + w, y + h))
tile.paste(cpu_logo, (0, 0), cpu_logo)
send_image(tile, x, y)

while True:
    sensor_readings = get_sensor_readings()
    update_display(bg_image, sensor_readings)
