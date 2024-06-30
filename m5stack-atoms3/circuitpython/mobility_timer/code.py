import board
import displayio
import terminalio
import time
from adafruit_bitmap_font import bitmap_font
from adafruit_display_text import label

# timer settings
base_time = 20
rest_time =  5

# screen dimensions
screen_height = 128
screen_width = 128

# font colors
countdown_font_color = 0x00c0ff
rest_font_color = 0xf9e4bc

# font paths
countdown_font_path = "/fonts/Comfortaa-Regular-60.bdf"
rest_font_path = "/fonts/Comfortaa-Regular-20.bdf"

# set up display
display = displayio.Group()
board.DISPLAY.root_group = display

# load fonts
countdown_font = bitmap_font.load_font(countdown_font_path)
rest_font = bitmap_font.load_font(rest_font_path)

# configure labels
countdown_label = label.Label(
    countdown_font,
    text="",
    color=countdown_font_color,
    anchor_point=(0.5, 0.5),
    anchored_position=(screen_width//2, screen_height//2),
)
rest_label = label.Label(
    rest_font,
    text="ahora",
    color=rest_font_color,
    anchor_point=(0.5, 0.5),
    anchored_position=(screen_width//2, screen_height//2),
)

display.append(countdown_label)
display.append(rest_label)

def clear_display(delay=0):
    countdown_label.text = ""
    rest_label.text = ""
    time.sleep(delay)

time.sleep(3)

while True:
    clear_display(1)

    for count in list(range(base_time+1))[::-1]:
        countdown_label.text = str(count)
        time.sleep(1.5)

    clear_display(1)

    for count in list(range(rest_time+1))[::-1]:
        rest_label.text = str(count)
        time.sleep(1.5)
