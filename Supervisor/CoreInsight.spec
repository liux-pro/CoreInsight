# -*- mode: python ; coding: utf-8 -*-


a = Analysis(
    ['CoreInsight.py'],
    pathex=[],
    binaries=[],
    datas=[
        ("MapleMono-SC-NF-Bold.ttf", "."),
        ("DSEG7Modern-Bold.ttf", "."),
        ("CoreInsight.ico", "."),
        ("nvidia.png", "."),
        ("intel.png", "."),
        ("amd.png", "."),
        ("background.jpg", "."),
        ("lock.jpg", "."),
        ("RemoteHWInfo.exe", ".")
    ],
    hiddenimports=[],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
    optimize=0,
)
pyz = PYZ(a.pure)
splash = Splash(
    'splash.jpg',
    binaries=a.binaries,
    datas=a.datas,
    text_pos=None,
    text_size=12,
    minify_script=True,
    always_on_top=True,
)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.datas,
    splash,
    splash.binaries,
    [],
    name='CoreInsight',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=False,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
    icon='CoreInsight.ico'
)
