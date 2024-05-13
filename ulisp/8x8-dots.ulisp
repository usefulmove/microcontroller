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
            (dotimes (_ 16)
              (write-byte #x00 stream))))

(defun plot (x y)
  (let (b)
    (with-i2c (stream addr)
              (write-byte (* x 2) stream)
              (restart-i2c stream 1)
              (setq b (read-byte stream))
              (restart-i2c stream)
              (write-byte (* x 2) stream)
              (write-byte
               (logxor b (ash 1 (logand (+ y 7) 7))) stream))))

(defun dots ()
  (loop
   (dotimes (_ 4)
     (plot (random 8) (random 8)))
   (delay 309)))
