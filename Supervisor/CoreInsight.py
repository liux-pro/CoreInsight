import math
import multiprocessing
import threading
import time
from datetime import datetime
from functools import wraps

from PIL import Image, ImageDraw, ImageFont

import tray
from PowerSettingChecker import PowerSettingChecker
from RemoteHWInfo import get_sensor_readings
from ScreenLockChecker import ScreenLockChecker
from SerialHelper import SerialHelper
from communicate import *

from pyinstaller_tool import *

close_splash()

# 常量定义
VID = 0x34BF
PID = 0xFFFF
FONT_PATH = resource_path('MapleMono-SC-NF-Bold.ttf')
FONT2_PATH = resource_path("DSEG7Modern-Bold.ttf")
BG_PATH = resource_path('background.jpg')

CMD_PREFIX = b'@@@'

# 初始化串口
serial_helper = SerialHelper(VID, PID)


def create_cmd_set_window(x, y, w, h):
    cmd = bytearray(CMD_PREFIX)
    cmd.append(CMD_SET_WINDOW)
    cmd.extend(int(x).to_bytes(2, byteorder='big'))
    cmd.extend(int(y).to_bytes(2, byteorder='big'))
    cmd.extend(int(w).to_bytes(2, byteorder='big'))
    cmd.extend(int(h).to_bytes(2, byteorder='big'))
    cmd.extend([0x00] * (31 - len(cmd)))
    return cmd


def create_cmd_set_brightness(brightness):
    """设置背光亮度 0~255 """
    cmd = bytearray(CMD_PREFIX)
    cmd.append(CMD_SET_BRIGHTNESS)
    cmd.extend(int(brightness).to_bytes(1, byteorder='big'))
    cmd.extend([0x00] * (31 - len(cmd)))
    print(cmd)
    return cmd


def send_data(cmd):
    serial_helper.write(cmd)


def send_image(image, x=0, y=0):
    data_to_send = convert_pillow_image_to_rgb565(image)
    w, h = image.size

    send_data(create_cmd_set_window(x, y, w, h))
    chunk_size = 64
    for i in range(0, len(data_to_send), chunk_size // 2):
        chunk = data_to_send[i:i + (chunk_size // 2)]
        byte_chunk = bytearray()
        for value in chunk:
            byte_chunk.extend(int(value).to_bytes(2, byteorder='big'))
        send_data(byte_chunk)


def convert_pillow_image_to_rgb565(image):
    """
    将Pillow图像转换为RGB565格式。

    参数:
    image (PIL.Image): Pillow图像对象，模式为"RGB"。

    返回:
    list: 扁平化的一维RGB565格式数据列表。
    """

    if image.mode != "RGB":
        raise ValueError("输入图像必须为RGB模式")

    # 使用getdata获取像素数据
    pixels = list(image.getdata())

    # 使用列表推导式转换像素数据为RGB565
    rgb565_data = [
        ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)
        for r, g, b in pixels
    ]

    return rgb565_data


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


def draw_gauge_image(image, value, font_path=FONT_PATH, font_size=36, text_offset_x=0, text_offset_y=0):
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


def run(interval):
    """
    装饰器，限制函数在指定时间间隔内只能被调用一次。

    :param interval: 时间间隔（以秒为单位）
    """

    def decorator(func):
        last_run = [0]  # 使用列表来保存可变的last_run时间戳

        @wraps(func)
        def wrapper(*args, **kwargs):
            current_time = time.time()
            if current_time - last_run[0] >= interval:
                result = func(*args, **kwargs)
                last_run[0] = current_time  # 更新last_run时间戳
                return result
            else:
                return None

        return wrapper

    return decorator


@run(20)
def update_data(bg_image):
    current_time = datetime.now()

    coordinates = [(2, 200, 210, 36)]
    values = [f"{current_time.year % 100:02}年{current_time.month:02}月{current_time.day:02}日"]
    for i, (x, y, w, h) in enumerate(coordinates):
        tile = bg_image.crop((x, y, x + w, y + h))
        draw = ImageDraw.Draw(tile)

        draw.text((0, 0), values[i], font=ImageFont.truetype(FONT_PATH, 28))
        send_image(tile, x, y)


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

    coordinates = [(80, 130, 110, 36), (80, 160, 110, 36)]
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

    current_time = datetime.now()

    coordinates = [(210, 200, 100, 36)]
    values = [f"{current_time.hour:02}:{current_time.minute:02}"]
    for i, (x, y, w, h) in enumerate(coordinates):
        tile = bg_image.crop((x, y, x + w, y + h))
        draw = ImageDraw.Draw(tile)

        draw.text((0, 0), values[i], font=ImageFont.truetype(FONT2_PATH, 30))
        send_image(tile, x, y)
    update_data(bg_image)


def init_background(bg_image):
    send_image(bg_image)
    coordinates = [(0, 10, 80, 50), (0, 60, 80, 50)]
    labels = ["CPU", "Mem"]
    for i, (x, y, w, h) in enumerate(coordinates):
        tile = bg_image.crop((x, y, x + w, y + h))
        draw = ImageDraw.Draw(tile)
        draw.text((0, 0), labels[i], font=ImageFont.truetype(FONT_PATH, 36))
        send_image(tile, x, y)

    coordinates = [(0, 130, 150, 36), (0, 160, 150, 36)]
    labels = [f"上传:", f"下载:"]
    for i, (x, y, w, h) in enumerate(coordinates):
        tile = bg_image.crop((x, y, x + w, y + h))
        draw = ImageDraw.Draw(tile)
        draw.text((0, 0), labels[i], font=ImageFont.truetype(FONT_PATH, 24))
        send_image(tile, x, y)

    x = 230
    y = 100
    w = 64
    h = 64
    cpu_logo = Image.open(resource_path(f"{get_sensor_readings().cpu}.png"))
    cpu_logo = cpu_logo.resize((w, int(w * cpu_logo.height / cpu_logo.width)))
    tile = bg_image.crop((x, y, x + w, y + h))
    tile.paste(cpu_logo, (0, 0), cpu_logo)
    send_image(tile, x, y)


bg_image = resize_and_crop(Image.open("background.jpg" if os.path.isfile("background.jpg") else resource_path(BG_PATH)), 320, 240)
init_background(bg_image)

powerSettingChecker = PowerSettingChecker()
powerSettingChecker.start()  # Start the listener in a new thread

screenLockChecker = ScreenLockChecker()

lock = resize_and_crop(Image.open(resource_path(f"lock.jpg")), 320, 240)

if __name__ == "__main__":
    # Create an event object
    exit_event = multiprocessing.Event()

    # Run the tray icon in a separate thread
    tray_thread = threading.Thread(target=tray.run_tray, args=(exit_event,), daemon=True)
    tray_thread.start()

    # Main program loop
    print("Tray icon is running in a separate thread. Main program is running.")
    try:
        while not exit_event.is_set():
            if serial_helper.ser is None or (serial_helper.ser and not serial_helper.ser.is_open):
                time.sleep(1)

            if serial_helper.has_reconnected():
                init_background(bg_image)

            if (powerSettingChecker.all_notifications_received() is True
                    and powerSettingChecker.console_display_state is False):
                send_data(create_cmd_set_brightness(0))
                while not powerSettingChecker.console_display_state:
                    time.sleep(1)
                send_data(create_cmd_set_brightness(255))

            if screenLockChecker.check_screen_lock():
                send_image(lock)
                while screenLockChecker.check_screen_lock():
                    time.sleep(1)
                init_background(bg_image)

            sensor_readings = get_sensor_readings()
            update_display(bg_image, sensor_readings)

    except KeyboardInterrupt:
        print("Keyboard interrupt received. Exiting program.")
        exit_event.set()

    print("Main program is exiting.")
