import board
import digitalio
import displayio
import terminalio
import time
from adafruit_bitmap_font import bitmap_font
from adafruit_display_text import label

splash = "popcorn"
version = "0.0.3"

# reading parameters
words_per_minute = 260
sentence_pause = 1.2
comma_pause = 0.4

word_pause = 60 / words_per_minute

# screen dimensions
screen_height = 135
screen_width = 240

# font colors
splash_font_color = 0xf9e4bc
reader_font_color = 0xfaf6ea
author_font_color = 0xef9d6e
version_font_color = 0x282828

# font paths
splash_font_path = "/fonts/Comforta-Regular-20.bdf"
reader_font_path = "/fonts/SourceCodePro-Regular-18.bdf"
author_font_path = "/fonts/Comforta-Regular-20.bdf"

# message to display
messages = []
authors = []

messages.append("\"The capacity to be alone is the capacity to love. It may look paradoxical to you, but it's not. It is an existential truth: only those people who are capable of being alone are capable of love, of sharing, of going into the deepest core of another person without possessing the other, without becoming dependent on the other, without reducing the other to a thing, and without becoming addicted to the other. They allow the other absolute freedom, because they know that if the other leaves, they will be as happy as they are now. Their happiness cannot be taken by the other, because it is not given by the other.\"")
authors.append("Osho")

messages.append("\"Physical concepts are free creations of the human mind, and are not, however it may seem, uniquely determined by the external world. In our endeavor to understand reality we are somewhat like a man trying to understand the mechanism of a closed watch. He sees the face and the moving hands, even hears its ticking, but he has no way of opening the case. If he is ingenious, he may form some picture of a mechanism which could be responsible for all the things he observes, but he may never be quite sure his picture is the only one which could explain his observations. He will never be able to compare his picture with the real mechanism and he cannot even imagine the possibility or the meaning of such a comparison.\"")
authors.append("A. Einstein")

messages.append("\"You think your pain and your heartbreak are un- precedented in the history of the world, but then you read. It was books that taught me that the things that tormented me most were the very things that connected me with all the people who were alive, who had ever been alive.\"")
authors.append("J. Baldwin")

# set up display
display = displayio.Group()
board.DISPLAY.root_group = display

# load fonts
splash_font = bitmap_font.load_font(splash_font_path)
reader_font = bitmap_font.load_font(reader_font_path)
author_font = bitmap_font.load_font(author_font_path)

# configure labels
splash_label = label.Label(
    splash_font,
    text="",
    color=splash_font_color,
    anchor_point=(0.0, 0.5),
    anchored_position=(24, screen_height//2),
)
reader_label = label.Label(
    reader_font,
    text="",
    color=reader_font_color,
    anchor_point=(0.5, 0.5),
    anchored_position=(screen_width//2, screen_height//2),
)
author_label = label.Label(
    author_font,
    text="",
    color=author_font_color,
    anchor_point=(0.0, 0.5),
    anchored_position=(24, screen_height//2),
)
version_label = label.Label(
    terminalio.FONT,
    text=version,
    color=version_font_color,
    anchor_point=(1.0, 1.0),
    anchored_position=(screen_width-8, screen_height-8),
)

cache_splash_label = label.Label(
    splash_font,
    text="",
    color=0x000000,
    anchor_point=(0.0, 0.5),
    anchored_position=(24, screen_height//2),
)
cache_reader_label = label.Label(
    reader_font,
    text="",
    color=0x000000,
    anchor_point=(0.5, 0.5),
    anchored_position=(screen_width//2, screen_height//2),
)
cache_author_label = label.Label(
    author_font,
    text="",
    color=0x000000,
    anchor_point=(0.0, 0.5),
    anchored_position=(24, screen_height//2),
)

display.append(splash_label)
display.append(reader_label)
display.append(author_label)
display.append(version_label)

# configure boot button
boot_button = digitalio.DigitalInOut(board.BOOT0)
boot_button.direction = digitalio.Direction.INPUT
boot_button.pull = digitalio.Pull.UP

def clear_display(delay=0):
    splash_label.text = ""
    reader_label.text = ""
    author_label.text = ""
    time.sleep(delay)

# display with typewriter effect
def display_typed_text(label, text, delay=0.05, cache_label=None):
    if cache_label is not None:
        for i in range(len(text) + 1):
            cache_label.text = text[:i] + "|"

    for i in range(len(text) + 1):
        label.text = text[:i] + "|"
        time.sleep(delay)
    label.text = text

message_index = 0
while True:
    # display splash
    display_typed_text(
        splash_label,
        splash,
        cache_label=cache_splash_label
    )

    # wait for button press
    while boot_button.value:
        pass

    clear_display(2)
    
    # display words
    words = messages[message_index].split()

    for word in words: # cache bitmaps
        cache_reader_label.text = word.lower()
    clear_display()

    for word in words:
        reader_label.text = word.lower()

        if word[-1] in {".", "?", "!", "\"", ";", "—", "–"}:
            time.sleep(sentence_pause)
        elif word[-1] in {",", ":"}:
            time.sleep(comma_pause)

        time.sleep(word_pause)
    time.sleep(0.8)

    clear_display(1)

    # display author
    display_typed_text(
        author_label,
        authors[message_index],
        cache_label=cache_author_label
    )
    time.sleep(3.5)

    clear_display(1)

    message_index = (message_index + 1) % len(messages)
