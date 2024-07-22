from PIL import Image, ImageDraw
import pystray
from pystray import MenuItem as item


def create_image(width, height, color1, color2):
    # Generate an image and draw a pattern
    image = Image.new('RGB', (width, height), color1)
    dc = ImageDraw.Draw(image)
    dc.rectangle(
        (width // 2, 0, width, height // 2),
        fill=color2)
    dc.rectangle(
        (0, height // 2, width // 2, height),
        fill=color2)
    return image


def on_exit(icon, item, exit_event):
    icon.stop()
    exit_event.set()


def on_hello(icon, item):
    print("Hello, World!")


def run_tray(exit_event):
    # Create the menu
    menu = (item('Hello', on_hello), item('Exit', lambda icon, item: on_exit(icon, item, exit_event)))

    # Create the icon
    icon = pystray.Icon("test_icon")
    icon.icon = create_image(64, 64, 'black', 'white')
    icon.title = "Test Icon"
    icon.menu = menu

    # Run the icon
    icon.run()
