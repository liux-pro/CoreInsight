import time
import cv2
import numpy as np
import serial
import time
import serial.tools.list_ports

from communicate import *

from numba import njit

from SerialHelper import SerialHelper

w = 96
h = 54
vid = 0x34BF
pid = 0xFFFF

# Read the image
cap = cv2.VideoCapture("input.mp4")

# 列出所有串口
ports = serial.tools.list_ports.comports()

# 初始化串口
s = SerialHelper(vid, pid)

time.sleep(2)


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
    # Get the dimensions of the image
    height, width, _ = image_rgb.shape

    # Create an empty RGB565 image
    image_rgb565 = np.zeros((height, width), dtype=np.uint16)

    # Convert to RGB565 format
    for i in range(height):
        for j in range(width):
            r = image_rgb[i, j, 0] >> 3  # Take the top 5 bits of red
            g = image_rgb[i, j, 1] >> 2  # Take the top 6 bits of green
            b = image_rgb[i, j, 2] >> 3  # Take the top 5 bits of blue
            rgb565 = (r << 11) | (g << 5) | b
            image_rgb565[i, j] = rgb565

    return image_rgb565.flatten()


for _ in range(99999):
    start_time = time.time()
    s.write(create_cmd(100, 100, w, h))
    # Send the data in chunks
    ret, image = cap.read()

    if not ret:
        break
    image = cv2.resize(image, (w, h))
    # Convert color space from BGR to RGB
    image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

    send_image(image_rgb)

    elapsed_time = time.time() - start_time
    print(f"Data sent in {elapsed_time:.2f} seconds")
