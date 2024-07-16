import time
import cv2
import numpy as np
import hid #pip install hidapi

# Read the image
image = cv2.imread('img.jpg')
image = cv2.resize(image, (320, 240))

# Convert color space from BGR to RGB
image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

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

# Flatten the array for sending
data_to_send = image_rgb565.flatten()

# Open HID device
device = hid.device()
device.open(0x34BF, 0xFF01)  # TREZOR VendorID/ProductID
device.set_nonblocking(1)

device.write("\0@REFRESH#".encode())

# Define the chunk size
chunk_size = 64  # Adjust the chunk size based on the HID device characteristics
report_id = 0  # Usually, the HID report ID is 0

# Send the data in chunks
start_time = time.time()

for i in range(0, len(data_to_send), chunk_size // 2):  # Each chunk contains 32 uint16
    chunk = data_to_send[i:i + (chunk_size // 2)]
    byte_chunk = bytearray()
    byte_chunk.append(report_id)
    for value in chunk:
        byte_chunk.extend(int(value).to_bytes(2, byteorder='big'))  # Convert numpy.uint16 to int before using to_bytes
    device.write(byte_chunk)

elapsed_time = time.time() - start_time
print(f"Data sent in {elapsed_time:.2f} seconds")

# Close the device
device.close()
