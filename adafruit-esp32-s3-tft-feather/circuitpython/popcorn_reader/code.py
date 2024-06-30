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
sentence_modifier = 4.8
comma_modifier = 2.2
long_word_modifier = 1.5

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
splash_font_path = "/fonts/Comfortaa-Regular-20.bdf"
reader_font_path = "/fonts/SourceCodePro-Regular-18.bdf"
author_font_path = "/fonts/Comfortaa-Regular-16.bdf"

# message to display
messages = []
authors = []

messages.append("\"It is not the critic who counts; not the man who points out how the strong man stumbles, or where the doer of deeds could have done them better. The credit belongs to the man who is actually in the arena, whose face is marred by dust and sweat and blood; who strives valiantly; who errs, who comes short again and again, because there is no effort without error and shortcoming; but who does actually strive to do the deeds; who knows great enthusiasms, the great devotions; who spends himself in a worthy cause; who at the best knows in the end the triumph of high achievement, and who at the worst, if he fails, at least fails while daring greatly, so that his place shall never be with those cold and timid souls who neither know victory nor defeat.\"")
authors.append("Theodore\nRoosevelt Jr.")

messages.append("\"The capacity to be alone is the capacity to love. It may look paradoxical to you, but it's not. It is an existential truth: only those people who are capable of being alone are capable of love, of sharing, of going into the deepest core of another person without possessing the other, without becoming dependent on the other, without reducing the other to a thing, and without becoming addicted to the other. They allow the other absolute freedom, because they know that if the other leaves, they will be as happy as they are now. Their happiness cannot be taken by the other, because it is not given by the other.\"")
authors.append("Osho")

messages.append("\"Physical concepts are free creations of the human mind, and are not, however it may seem, uniquely determined by the external world. In our endeavor to understand reality we are somewhat like a man trying to understand the mechanism of a closed watch. He sees the face and the moving hands, even hears its ticking, but he has no way of opening the case. If he is ingenious, he may form some picture of a mechanism which could be responsible for all the things he observes, but he may never be quite sure his picture is the only one which could explain his observations. He will never be able to compare his picture with the real mechanism and he cannot even imagine the possibility or the meaning of such a comparison.\"")
authors.append("Albert Einstein")

messages.append("\"You think your pain and your heartbreak are un- precedented in the history of the world, but then you read. It was books that taught me that the things that tormented me most were the very things that connected me with all the people who were alive, who had ever been alive.\"")
authors.append("James Baldwin")

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
    anchored_position=(screen_width//10, screen_height//2),
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
    anchored_position=(screen_width//10, screen_height//2),
    line_spacing=1.0,
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
    anchored_position=(screen_width//10, screen_height//2),
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
    anchored_position=(screen_width//10, screen_height//2),
    line_spacing=1.0,
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

    clear_display(1)
    
    # display words
    words = messages[message_index].split()

    for word in words: # cache bitmaps
        cache_reader_label.text = word
    clear_display()

    for word in words:
        reader_label.text = word

        if word[-1] in {".", "?", "!", "\""}:
            time.sleep(word_pause * sentence_modifier)
        elif word[-1] in {",", ":", ";"}:
            time.sleep(word_pause * comma_modifier)
        elif len(word) > 8:
            time.sleep(word_pause * long_word_modifier)
        else:
            time.sleep(word_pause)

    clear_display(0.3)

    # display author
    display_typed_text(
        author_label,
        authors[message_index],
        cache_label=cache_author_label
    )
    time.sleep(3.5)

    clear_display(1)

    message_index = (message_index + 1) % len(messages)
