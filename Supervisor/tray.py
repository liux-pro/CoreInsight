from PIL import Image, ImageDraw
import pystray
from pystray import MenuItem

from PoserSetting import screenOff
from pyinstaller_tool import resource_path

import webbrowser


def on_exit(icon, item, exit_event):
    icon.stop()
    exit_event.set()


def run_tray(exit_event):
    # Create the menu
    menu = (
        MenuItem('主页', lambda: webbrowser.open("https://oshwhub.com/legend-tech/core-insight")),
        MenuItem('关闭屏幕', screenOff),
        MenuItem('退出', lambda icon, item: on_exit(icon, item, exit_event)),
    )

    # Create the icon
    icon = pystray.Icon("icon")
    icon.icon = Image.open(resource_path("CoreInsight.ico"))
    icon.title = "CoreInsight"
    icon.menu = menu

    # Run the icon
    icon.run()
