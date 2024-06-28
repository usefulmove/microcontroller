import board
import digitalio
import displayio
import terminalio
import time
from adafruit_bitmap_font import bitmap_font
from adafruit_display_text import label

# reading parameters
words_per_minute = 280
sentence_pause = 1.2
comma_pause = 0.4

word_pause = 60 / words_per_minute

# message to display
message = "\"The capacity to be alone is the capacity to love. It may look paradoxical to you, but it's not. It is an existential truth: only those people who are capable of being alone are capable of love, of sharing, of going into the deepest core of another person without possessing the other, without becoming dependent on the other, without reducing the other to a thing, and without becoming addicted to the other. They allow the other absolute freedom, because they know that if the other leaves, they will be as happy as they are now. Their happiness cannot be taken by the other, because it is not given by the other.\""
author = "Osho"

#message = "\"Physical concepts are free creations of the human mind, and are not, however it may seem, uniquely determined by the external world. In our endeavor to understand reality we are somewhat like a man trying to understand the mechanism of a closed watch. He sees the face and the moving hands, even hears its ticking, but he has no way of opening the case. If he is ingenious, he may form some picture of a mechanism which could be responsible for all the things he observes, but he may never be quite sure his picture is the only one which could explain his observations. He will never be able to compare his picture with the real mechanism and he cannot even imagine the possibility or the meaning of such a comparison.\""
#author = "A. Einstein"

#message = "\"You think your pain and your heartbreak are un- precedented in the history of the world, but then you read. It was books that taught me that the things that tormented me most were the very things that connected me with all the people who were alive, who had ever been alive.\""
#author = "J. Baldwin"

splash = "popcorn"

# set up display
display = displayio.Group()
board.DISPLAY.root_group = display

# load fonts
splash_font = bitmap_font.load_font("/fonts/Comforta-Regular-20.bdf")
reader_font = bitmap_font.load_font("/fonts/SourceCodePro-Regular-18.bdf")
author_font = bitmap_font.load_font("/fonts/Comforta-Regular-20.bdf")

# configure labels
#splash_label = label.Label(splash_font, text="", color=0x202020, x=24, y=60)
splash_label = label.Label(splash_font, text="", color=0xffffff, x=24, y=60)
reader_label = label.Label(reader_font, text="", color=0xf9e4bc, x=24, y=58)
dummy_label = label.Label(reader_font, text="", color=0x000000, x=24, y=58)
author_label = label.Label(author_font, text="", color=0xef9d6e, x=24, y=58)

display.append(splash_label)
display.append(reader_label)
display.append(author_label)

# configure boot button
boot_button = digitalio.DigitalInOut(board.BOOT0)
boot_button.direction = digitalio.Direction.INPUT
boot_button.pull = digitalio.Pull.UP

def clear_display(delay=0):
    splash_label.text = ""
    reader_label.text = ""
    author_label.text = ""
    time.sleep(delay)

def display_typed_text(label, text):
    for i in range(len(text) + 1):
        label.text = text[:i] + "|"
        time.sleep(0.05)
    label.text = text

# cache word bitmaps for speed of rendering
for word in message.split():
    dummy_label.text = word.lower()
clear_display()

while True:
    display_typed_text(splash_label, splash)

    # wait for button press
    while boot_button.value:
        pass

    # clear display
    clear_display(2)

    # display words
    for word in message.split():
        reader_label.text = word.lower()

        if word[-1] in {".", "?", "!", "\"", ";", "—", "–", "-"}:
            time.sleep(sentence_pause)
        elif word[-1] in {",", ":"}:
            time.sleep(comma_pause)

        time.sleep(word_pause)
    time.sleep(0.8)

    # clear display
    clear_display(2)

    # display author with typewriter effect
    display_typed_text(author_label, author)
    time.sleep(2.5)

    # clear display
    clear_display(1)
