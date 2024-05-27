(defvar cs-pin 5) ; chip select enable pin

#| MAX7219 LED display driver registers |#
(defvar :decode-mode-reg #x09)
(defvar :intensity-reg #x0a)
(defvar :scan-limit-reg #x0b)
(defvar :shutdown-reg #x0c)
(defvar :display-test-reg #x0f)

(defun spi-begin ()
  "Start SPI connection."
  (with-spi (stream cs-pin)
            stream))

(defun spi-cmd (addr data)
  "Send data to SPI register."
  (with-spi (stream cs-pin)
            (write-byte addr stream)
            (write-byte data stream)))

(defun init-display ()
  "Initialize LED display."
  (spi-cmd :shutdown-reg 0) ; turn off display
  (spi-cmd :decode-mode-reg 0) ; no decode
  (spi-cmd :scan-limit-reg 7) ; display all rows
  (spi-cmd :shutdown-reg 1) ; turn on display
  (spi-cmd :display-test-reg 1) ; turn on test display
  (delay 120)
  (spi-cmd :display-test-reg 0) ; turn off test display
  (spi-cmd :intensity-reg 8) ; set brightness
  (clear-display))

(defun set-brightness (level)
  "Set brightness level (0-15)."
  (spi-cmd :intensity-reg level))

(defun clear-display ()
  "Clear LED display."
  (dotimes (index 8)
    (spi-cmd (+ 1 index) #x00)))

(defun update-display (bytes)
  "Update display to reflect byte data list."
  (when bytes
    (mapcar
     (lambda (pair)
       (let ((addr (+ 1 (car pair)))
             (data (cdr pair)))
         (spi-cmd addr data)))
     (enumerate bytes))))

(defun enumerate (lst &optional index)
  "Return association list with index position and list value."
  (let ((index (if index index 0)))
    (cond ((null lst) '())
          (t (cons (cons index
                         (car lst))
                   (enumerate (cdr lst) (+ 1 index)))))))

(defun blink ()
  (pinmode 2 :output)
  (digitalwrite 2 :high)
  (delay 80)
  (digitalwrite 2 :low))

(defun demo ()
  #| arrow animation |#
  (blink)
  (let ((frames (list
                 '(#x00 #x00 #x00 #x00 #x00 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x80 #x00 #x00 #x00 #x00)
                 '(#x00 #x00 #x80 #xc0 #x80 #x00 #x00 #x00)
                 '(#x00 #x80 #xc0 #xe0 #xc0 #x80 #x00 #x00)
                 '(#x80 #xc0 #xe0 #xf0 #xe0 #xc0 #x80 #x00)
                 '(#x40 #x60 #xf0 #xf8 #xf0 #x60 #x40 #x00)
                 '(#x20 #x30 #xf8 #xfc #xf8 #x30 #x20 #x00)
                 '(#x10 #x18 #xfc #xfe #xfc #x18 #x10 #x00)
                 '(#x08 #x0c #x7e #x7f #x7e #x0c #x08 #x00)
                 '(#x04 #x06 #x3f #x3f #x3f #x06 #x04 #x00)
                 '(#x02 #x03 #x1f #x1f #x1f #x03 #x02 #x00)
                 '(#x01 #x01 #x0f #x0f #x0f #x01 #x01 #x00)
                 '(#x00 #x00 #x07 #x07 #x07 #x00 #x00 #x00)
                 '(#x00 #x00 #x03 #x03 #x03 #x00 #x00 #x00)
                 '(#x00 #x00 #x01 #x01 #x01 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x00 #x00 #x00 #x00 #x00)))
        (pause 100))
    (dotimes (_ 3) 
      (dolist (frame frames)
        (update-display frame)
        (delay pause))))
  (clear-display)
  (delay 350)

  #| pac-man ghost animation |#
  (blink)
  (dotimes (_ 2)
    (update-display '(#x9b #xff #xff #xff #xdb #x93 #x7e #x3c))
    (delay 400)
    (update-display '(#xd9 #xff #xff #xff #xdb #xc9 #x7e #x3c))
    (delay 2000))
  (clear-display)
  (delay 350)

  #| water animation |#
  (blink)
  (dotimes (_ 14)
    (update-display '(#x3c #x66 #xc3 #x99 #x99 #xc3 #x66 #x3c))
    (delay 200)
    (update-display '(#x66 #xc3 #x99 #x3c #x3c #x99 #xc3 #x66))
    (delay 200)
    (update-display '(#xc3 #x99 #x3c #x66 #x66 #x3c #x99 #xc3))
    (delay 200)
    (update-display '(#x99 #x3c #x66 #xc3 #xc3 #x66 #x3c #x99))
    (delay 200))
  (clear-display)
  (delay 350)

  #| snake animation |#
  (blink)
  (let ((frames (list
                 '(#x00 #x01 #x00 #x00 #x00 #x00 #x00 #x00)
                 '(#x00 #x03 #x00 #x00 #x00 #x00 #x00 #x00)
                 '(#x00 #x03 #x02 #x00 #x00 #x00 #x00 #x00)
                 '(#x00 #x03 #x02 #x02 #x00 #x00 #x00 #x00)
                 '(#x00 #x03 #x02 #x06 #x00 #x00 #x00 #x00)
                 '(#x00 #x03 #x02 #x0e #x00 #x00 #x00 #x00)
                 '(#x00 #x03 #x0a #x0e #x00 #x00 #x00 #x00)
                 '(#x00 #x03 #x1a #x0e #x00 #x00 #x00 #x00)
                 '(#x00 #x02 #x3a #x0e #x00 #x00 #x00 #x00)
                 '(#x00 #x00 #x7a #x0e #x00 #x00 #x00 #x00)
                 '(#x00 #x00 #x78 #x4e #x00 #x00 #x00 #x00)
                 '(#x00 #x00 #x78 #x4c #x40 #x00 #x00 #x00)
                 '(#x00 #x00 #x78 #x48 #x40 #x40 #x00 #x00)
                 '(#x00 #x00 #x78 #x40 #x40 #x40 #x40 #x00)
                 '(#x00 #x00 #x70 #x40 #x40 #x40 #x60 #x00)
                 '(#x00 #x00 #x60 #x40 #x40 #x40 #x70 #x00)
                 '(#x00 #x00 #x40 #x40 #x40 #x40 #x78 #x00)
                 '(#x00 #x00 #x00 #x40 #x40 #x40 #x7c #x00)
                 '(#x00 #x00 #x00 #x00 #x40 #x44 #x7c #x00)
                 '(#x00 #x00 #x00 #x00 #x04 #x44 #x7c #x00)
                 '(#x00 #x00 #x00 #x04 #x04 #x04 #x7c #x00)
                 '(#x00 #x00 #x00 #x0c #x04 #x04 #x3c #x00)
                 '(#x00 #x00 #x00 #x1c #x04 #x04 #x1c #x00)
                 '(#x00 #x00 #x00 #x3c #x04 #x04 #x0c #x00)
                 '(#x00 #x00 #x20 #x3c #x04 #x04 #x04 #x00)
                 '(#x00 #x20 #x20 #x3c #x04 #x04 #x00 #x00)
                 '(#x00 #x30 #x20 #x3c #x04 #x00 #x00 #x00)
                 '(#x00 #x38 #x20 #x3c #x00 #x00 #x00 #x00)
                 '(#x00 #x3c #x20 #x38 #x00 #x00 #x00 #x00)
                 '(#x04 #x3c #x20 #x30 #x00 #x00 #x00 #x00)
                 '(#x06 #x3c #x20 #x20 #x00 #x00 #x00 #x00)
                 '(#x07 #x3c #x20 #x00 #x00 #x00 #x00 #x00)
                 '(#x07 #x3d #x00 #x00 #x00 #x00 #x00 #x00)
                 '(#x07 #x1d #x01 #x00 #x00 #x00 #x00 #x00)
                 '(#x07 #x0d #x01 #x01 #x00 #x00 #x00 #x00)
                 '(#x07 #x05 #x01 #x01 #x01 #x00 #x00 #x00)
                 '(#x07 #x01 #x01 #x01 #x01 #x01 #x00 #x00)
                 '(#x03 #x01 #x01 #x01 #x01 #x01 #x01 #x00)
                 '(#x01 #x01 #x01 #x01 #x01 #x01 #x03 #x00)
                 '(#x00 #x01 #x01 #x01 #x01 #x01 #x03 #x02)
                 '(#x00 #x00 #x01 #x01 #x01 #x01 #x03 #x06)
                 '(#x00 #x00 #x00 #x01 #x01 #x01 #x03 #x0e)
                 '(#x00 #x00 #x00 #x00 #x01 #x01 #x0b #x0e)
                 '(#x00 #x00 #x00 #x00 #x00 #x01 #x1b #x0e)
                 '(#x00 #x00 #x00 #x00 #x00 #x00 #x3b #x0e)
                 '(#x00 #x00 #x00 #x00 #x00 #x00 #x7a #x0e)
                 '(#x00 #x00 #x00 #x00 #x00 #x40 #x78 #x0e)
                 '(#x00 #x00 #x00 #x00 #x40 #x40 #x78 #x0c)
                 '(#x00 #x00 #x00 #x00 #x60 #x40 #x78 #x08)
                 '(#x00 #x00 #x00 #x00 #x70 #x40 #x78 #x00)
                 '(#x00 #x00 #x00 #x00 #x78 #x40 #x70 #x00)
                 '(#x00 #x00 #x00 #x00 #x7c #x40 #x60 #x00)
                 '(#x00 #x00 #x00 #x00 #x7c #x44 #x40 #x00)
                 '(#x00 #x00 #x00 #x00 #x7c #x44 #x04 #x00)
                 '(#x00 #x00 #x00 #x00 #x7c #x04 #x0c #x00)
                 '(#x00 #x00 #x00 #x00 #x3c #x04 #x1c #x00)
                 '(#x00 #x00 #x00 #x00 #x1c #x14 #x1c #x00)
                 '(#x00 #x00 #x00 #x10 #x14 #x14 #x1c #x00)
                 '(#x00 #x00 #x00 #x30 #x10 #x14 #x1c #x00)
                 '(#x00 #x00 #x00 #x70 #x10 #x10 #x1c #x00)
                 '(#x00 #x00 #x00 #x70 #x50 #x10 #x18 #x00)
                 '(#x00 #x00 #x00 #x70 #xd0 #x10 #x10 #x00)
                 '(#x00 #x00 #x00 #x70 #xd0 #x10 #x00 #x00)
                 '(#x00 #x00 #x00 #x70 #xd0 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x70 #xc0 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x60 #xc0 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x40 #xc0 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x00 #xc0 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x00 #x80 #x00 #x00 #x00)
                 '(#x00 #x00 #x00 #x00 #x00 #x00 #x00 #x00)))
          (pause 100))
    (dolist (frame frames)
      (update-display frame)
      (delay pause)))
  (clear-display)
  (delay 350)

  #| space invader |#
  (blink)
  (progn
    (update-display '(#x66 #xc3 #xff #xdb #xdb #x7e #x24 #x42))
    (delay 120)
    (update-display '(#x66 #xc3 #xff #xdb #xdb #x7e #x24 #x24))
    (delay 120)
    (update-display '(#x66 #xc3 #xff #xdb #xdb #x7e #x24 #x42))
    (delay 120)
    (update-display '(#x66 #xc3 #xff #xdb #xdb #x7e #x24 #x24))
    (delay 120)
    (update-display '(#x66 #xc3 #xff #xdb #xdb #x7e #x24 #x42))
    (delay 2500))
  (clear-display)
  (delay 350))

(spi-begin)

(init-display)