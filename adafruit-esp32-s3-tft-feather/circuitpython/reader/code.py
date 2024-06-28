import board
import digitalio
import displayio
import terminalio
import time
from adafruit_bitmap_font import bitmap_font
from adafruit_display_text import label

boot_button = board.BOOT0

splash = displayio.Group()
board.DISPLAY.root_group = splash

font = bitmap_font.load_font("/fonts/icl16x16u.bdf")

reader_area = label.Label(font, text="", color=0xf9e4bc, x=25, y=60)
splash.append(reader_area)

wpm = 240

message = "\"You think your pain and your heartbreak are un- precedented in the history of the world, but then you read. It was books that taught me that the things that tormented me most were the very things that connected me with all the people who were alive, who had ever been alive.\""
words = message.split()

button = digitalio.DigitalInOut(boot_button)
button.direction = digitalio.Direction.INPUT
button.pull = digitalio.Pull.UP

while True:
    while button.value:
        pass

    time.sleep(1)
    for word in words:
        reader_area.text = word
        time.sleep(60 / wpm)

    time.sleep(1)
    reader_area.text = ""
