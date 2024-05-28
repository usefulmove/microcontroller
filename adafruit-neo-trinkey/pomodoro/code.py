import time
import board
import neopixel
import touchio

pixels = neopixel.NeoPixel(board.NEOPIXEL, 4, brightness=0.05)

touch1 = touchio.TouchIn(board.TOUCH1)
touch2 = touchio.TouchIn(board.TOUCH2)

while True:
    pixels.fill((0, 0, 0))
    if (touch1.value == True):
        start_time = time.monotonic()
        step = 0
        while (time.monotonic() - start_time) <= 20 * 60:
            pixels[step % 4] = (0, 25, 230)
            time.sleep(0.120)
            pixels.fill((0, 0, 0))
            step = step + 1
        time.sleep(0.25)
        pixels.fill((0, 255, 0))
        time.sleep(0.1)
        pixels.fill((0, 0, 0))
        time.sleep(0.1)
        pixels.fill((0, 255, 0))
        time.sleep(2.0)
        pixels.fill((0, 0, 0))
