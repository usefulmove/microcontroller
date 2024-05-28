(defvar addr 112)

(defun set (bri)
  (with-i2c (stream addr)
            (write-byte #x21 stream)
            (restart-i2c stream)
            (write-byte #x81 stream)
            (restart-i2c stream)
            (write-byte (+ #xe0 bri) stream)))

(defun clr ()
  (with-i2c (stream addr)
            (dotimes (x 16)
              (write-byte #x00 stream))))

(defun byte-correct (byte)
  (logior (/ byte 2)
          (ash (logand 1 byte) 7)))

(defun display (bytes)
  (when bytes
    (with-i2c
     (stream addr)
     (dotimes (n 8)
       (write-byte #x00 stream)
       (write-byte (byte-correct (nth n bytes)) stream)))))

; question mark
(display '(#x18 #x00 #x18 #x38 #x60 #x66 #x3c #x00))
; exclamation point
(display '(#x00 #x18 #x00 #x18 #x18 #x3c #x3c #x18))
; heart
(display '(#x18 #x3c #x7e #xff #xff #xff #x66 #x00))
; file
(display '(#x00 #x7e #x7e #x7e #x66 #x7e #x00 #x00))
; smiley face
(display '(#x3c #x42 #x99 #xa5 #x81 #xa5 #x42 #x3c))
; apple
(display '(#x34 #x7a #xff #xff #xff #x76 #x8 #x18))
; space invader
(display '(#x66 #xc3 #xff #xdb #xdb #x7e #x24 #x42))
; eight
(display '(#x3c #x66 #x66 #x3c #x66 #x66 #x3c #x00))
; pac-man ghost
(display '(#x9b #xff #xff #xff #xdb #x93 #x7e #x3c))
(display '(#xd9 #xff #xff #xff #xdb #xc9 #x7e #x3c))

; right arrow one
(display '(#x10 #x18 #xfc #xfe #xfc #x18 #x10 #x00))
; right arrow two
(display '(#x08 #x0c #x7e #x7f #x7e #x0c #x08 #x00))
; right arrow three
(display '(#x04 #x06 #x3f #x3f #x3f #x06 #x04 #x00))
; right arrow four
(display '(#x02 #x03 #x1f #x1f #x1f #x03 #x02 #x00))
; right arrow five
(display '(#x01 #x01 #x0f #x0f #x0f #x01 #x01 #x00))

(defun arrow-loop ()
  (loop 
   (display '(#x10 #x18 #xfc #xfe #xfc #x18 #x10 #x00))
   (delay 1000)
   (display '(#x08 #x0c #x7e #x7f #x7e #x0c #x08 #x00))
   (delay 1000)
   (display '(#x04 #x06 #x3f #x3f #x3f #x06 #x04 #x00))
   (delay 1000)
   (display '(#x02 #x03 #x1f #x1f #x1f #x03 #x02 #x00))
   (delay 1000)
   (display '(#x01 #x01 #x0f #x0f #x0f #x01 #x01 #x00))
   (delay 1000)))

(defun arrow-loop2 ()
  (loop 
   (display '(#x33 #x66 #xcc #x99 #x99 #xcc #x66 #x33))
   (delay 200)
   (display '(#x66 #xcc #x99 #x33 #x33 #x99 #xcc #x66))
   (delay 200)
   (display '(#xcc #x99 #x33 #x66 #x66 #x33 #x99 #xcc))
   (delay 200)
   (display '(#x99 #x33 #x66 #xcc #xcc #x66 #x33 #x99))
   (delay 200)))

(defun heart-beat ()
  (loop 
   (display '(#x00 #x00 #x18 #x3c #x3c #x18 #x00 #x00))
   (set 0)
   (delay 100)
   (display '(#x18 #x3c #x7e #xff #xff #xff #x66 #x00))
   (set 4)
   (delay 10000)))

(defun bullseye-loop ()
  (loop 
   (display '(#x3c #x66 #xc3 #x99 #x99 #xc3 #x66 #x3c))
   (delay 200)
   (display '(#x66 #xc3 #x99 #x3c #x3c #x99 #xc3 #x66))
   (delay 200)
   (display '(#xc3 #x99 #x3c #x66 #x66 #x3c #x99 #xc3))
   (delay 200)
   (display '(#x99 #x3c #x66 #xc3 #xc3 #x66 #x3c #x99))
   (delay 200)))

(defun ghost-loop ()
  (loop 
   (display '(#x9b #xff #xff #xff #xdb #x93 #x7e #x3c))
   (delay 1000)
   (display '(#xd9 #xff #xff #xff #xdb #xc9 #x7e #x3c))
   (delay 5000)))

(display '(#x00 #x7e #x42 #x00 #x00 #x66 #x66 #x00))

(display '(#x2a #x7f #x22 #x63 #x22 #x7f #x22 #x00))
(display '(#x00 #x2a #x7f #x22 #x63 #x22 #x7f #x22))
(display '(#x00 #x54 #xfe #x44 #xc6 #x44 #xfe #x44))
(display '(#x54 #xfe #x44 #xc6 #x44 #xfe #x44 #x00))

(display '(#xff #x80 #xb6 #xb6 #x80 #xb6 #xb6 #x80))
(display '(#x80 #xb6 #xb6 #x80 #xb6 #xb6 #x80 #xff))
(display '(#x01 #x6d #x6d #x01 #x6d #x6d #x01 #xff))
(display '(#xff #x01 #x6d #x6d #x01 #x6d #x6d #x01))