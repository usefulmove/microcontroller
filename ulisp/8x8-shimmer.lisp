(defvar addr 112)

(defun set (bri)
  (with-i2c (s addr)
            (write-byte #x21 s)
            (restart-i2c s)
            (write-byte #x81 s)
            (restart-i2c s)
            (write-byte (+ #xe0 bri) s)))

(defun clr ()
  (with-i2c (s addr)
            (dotimes (x 16)
              (write-byte #x00 s))))

(defun byte-correct (byte)
  (logior (/ byte 2)
          (ash (logand 1 byte) 7)))

(defun display (bytes)
  (when bytes
    (with-i2c
     (s addr)
     (dotimes (n 8)
       (write-byte #x00 s)
       (write-byte (byte-correct (nth n bytes)) s)))))

(defvar chess '(#xaa #x55 #xaa #x55 #xaa #x55 #xaa #x55))
(defvar anti-chess '(#x55 #xaa #x55 #xaa #x55 #xaa #x55 #xaa ))

(defun shimmer ()
  (loop
   (display chess)
   (delay 500)
   (display anti-chess)
   (delay 500)))
