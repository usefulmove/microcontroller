import board
import neopixel
import random
import time
import touchio

pixels = neopixel.NeoPixel(board.NEOPIXEL, 4, brightness=0.03)

# capacitive touch sensors
touch1 = touchio.TouchIn(board.TOUCH1)
touch2 = touchio.TouchIn(board.TOUCH2)

# pomodoro durations
durations = [10, 20, 30, 60]
duration = durations[1]

# neopixel colors
active = (0, 0, 255)
done = (0, 162, 0)
mode = (82, 21, 82)


def pixels_off():
    pixels.fill((0, 0, 0))


def pixels_on(color=(85, 85, 85), number=4):
    for i in range(number):
        pixels[i] = color


while True:
    pixels_off()

    if (touch1.value == True):
        start_time = time.monotonic()
        step = 0

        while (time.monotonic() - start_time) < duration * 60:
            pixels[step % 4] = active
            time.sleep(0.120)
            pixels_off()
            step = step + 1

        time.sleep(0.25)
        pixels_on(done)
        time.sleep(0.1)
        pixels_off()
        time.sleep(0.1)

        while (touch2.value == False):
            pixels_on(done)

        pixels_off()
        time.sleep(1.0)

    if (touch2.value == True):
        if (duration == durations[0]):
            duration = durations[1]
            pixels_on(mode, 2)
        elif (duration == durations[1]):
            duration = durations[2]
            pixels_on(mode, 3)
        elif (duration == durations[2]):
            duration = durations[3]
            pixels_on(mode)
        else:
            duration = durations[0]
            pixels_on(mode, 1)
        time.sleep(0.3)
