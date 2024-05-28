(defvar cs-pin 5) ; chip select enable pin

; MAX7219 LED display driver registers
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

(spi-begin)

(init-display)