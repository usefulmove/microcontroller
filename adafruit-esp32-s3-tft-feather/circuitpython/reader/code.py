import board
import digitalio
import displayio
import terminalio
import time
from adafruit_bitmap_font import bitmap_font
from adafruit_display_text import label

# message to display
message = "Physical concepts are free creations of the human mind, and are not, however it may seem, uniquely determined by the external world. In our endeavor to understand reality we are somewhat like a man trying to understand the mechanism of a closed watch. He sees the face and the moving hands, even hears its ticking, but he has no way of opening the case. If he is ingenious, he may form some picture of a mechanism which could be responsible for all the things he observes, but he may never be quite sure his picture is the only one which could explain his observations. He will never be able to compare his picture with the real mechanism and he cannot even imagine the possibility or the meaning of such a comparison."
#message = "\"You think your pain and your heartbreak are un- precedented in the history of the world, but then you read. It was books that taught me that the things that tormented me most were the very things that connected me with all the people who were alive, who had ever been alive.\""

# set up display
display = displayio.Group()
board.DISPLAY.root_group = display

# load font
font = bitmap_font.load_font("/fonts/icl16x16u.bdf")

# configure labels
message_label = label.Label(terminalio.FONT, text="", color=0x181818, x=25, y=60)
display.append(message_label)

reader_label = label.Label(font, text="", color=0xf9e4bc, x=25, y=60)
display.append(reader_label)

def clear_display():
    message_label.text = ""
    reader_label.text = ""

# reading parameters
words_per_minute = 240
sentence_pause = 0.5
comma_pause = 0.2

# configure boot button
boot_button = digitalio.DigitalInOut(board.BOOT0)
boot_button.direction = digitalio.Direction.INPUT
boot_button.pull = digitalio.Pull.UP

while True:
    message_label.text = "( press boot button to begin )"

    # wait for button press
    while boot_button.value:
        pass

    # clear display
    clear_display()
    time.sleep(1)

    # display words
    for word in message.split():
        reader_label.text = word

        if word[-1] in {".", "?", "!", "\""}:
            time.sleep(sentence_pause)
        elif word[-1] == ",":
            time.sleep(comma_pause)

        time.sleep(60 / words_per_minute)
    time.sleep(1)

    # clear display
    clear_display()
    time.sleep(3)
