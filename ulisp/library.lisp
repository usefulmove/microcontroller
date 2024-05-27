(defun init-i2c ()
  (with-i2c (stream 112)
            (princ "I2C initialized")))

(defun test-led ()
  (with-i2c (stream 112)
            (write-byte #x00 stream)
            (write-byte #x01 stream)))

(defun run-test ()
  (init-i2c)
  (test-led)
  (princ "Command sent"))

(defun i2c-scan ()
  (dotimes (addr 127)
    (with-i2c (stream addr)
              (when stream
                (print addr)))))

(defun iota (n)
  (if (<= n 0)
      '()
    (append (iota (- n 1))
            (list (- n 1)))))

(defun filter (pred lst)
  (cond ((null lst) '())
        ((pred (car lst)) (cons (car lst)
                                (filter pred (cdr lst))))
        (t (filter pred (cdr lst)))))

(defun fold-left (f acc lst)
  (cond ((null lst) acc)
        (t (fold-left f (f acc (car lst)) (cdr lst)))))

(defun enumerate (lst &optional index)
  (let ((index (if index index 0)))
    (cond ((null lst) '())
          (t (cons (cons index
                         (car lst))
                   (enumerate (cdr lst) (+ 1 index)))))))

(defun blink (times &optional output)
  (let ((output (if output output :led-builtin))
        (pause 500))
    (if (> times 0)
        (progn 
          (pinmode output :output)
          (digitalwrite output 1)
          (delay pause)
          (digitalwrite output 0)
          (delay pause)
          (blink (- times 1) output)))))
