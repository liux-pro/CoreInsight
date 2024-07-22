import sys
import os


def close_splash():
    """
    关闭pyinstaller的启动窗口
    """
    if getattr(sys, 'frozen', False):
        import pyi_splash

        pyi_splash.close()


def resource_path(relative_path):
    """
    相对路径转绝对路径，在pyinstaller打包后，数据文件会被释放到临时目录，用这个还原相对路径成绝对路径
    """
    if getattr(sys, 'frozen', False):  # 是否Bundle Resource
        base_path = sys._MEIPASS
    else:
        base_path = os.path.abspath(".")
    return os.path.join(base_path, relative_path)
