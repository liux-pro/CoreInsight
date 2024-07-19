from PIL import Image, ImageDraw, ImageFont
import numpy as np
import cv2

for _ in range(99999999):
    # 创建一个空白图像
    width, height = 1000, 1000
    image = Image.new('RGB', (width, height), (0, 0, 0))

    # 加载自定义字体（请替换为自定义字体文件的路径）
    font = ImageFont.truetype('AlimamaDaoLiTi.ttf', 100)

    # 创建一个 ImageDraw 对象
    draw = ImageDraw.Draw(image)

    # 绘制文本
    text = "123 "
    text_position = (0, 0)
    text_color = (255, 255, 255)  # 白色
    draw.text(text_position, text, font=font, fill=text_color)

    # 将 Pillow 图像转换为 NumPy 数组
    image_np = np.array(image)

# 使用 OpenCV 显示图像
cv2.imshow('Custom Font Image', image_np)
cv2.waitKey(0)
cv2.destroyAllWindows()
