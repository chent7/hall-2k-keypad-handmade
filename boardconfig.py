Import("env")

board_config = env.BoardConfig()

board_config.update("name", "Hall Effect Keypad")
board_config.update("vendor", "chent7")
board_config.update("build.usb_product", "Hall Effect Keypad")
board_config.update("build.hwids", [
    ["0xc007","0x0001"]
])
