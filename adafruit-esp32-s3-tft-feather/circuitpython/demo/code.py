import board
import displayio
import terminalio
import time
from adafruit_display_text import label

boot_button = board.BOOT0

splash = displayio.Group()
board.DISPLAY.root_group = splash

message = "\"You are so brave and so quiet\n I forget you are suffering.\""
message_area = label.Label(terminalio.FONT, text=message, color=0xF9E4BC, x=30, y=45)
splash.append(message_area)

update_area = label.Label(terminalio.FONT, text="", color=0x0080FF, x=55, y=85)
splash.append(update_area)

count = 0
while True:
    time.sleep(1)
    update_area.text = "seconds since boot: " + str(count)
    count = count + 1
