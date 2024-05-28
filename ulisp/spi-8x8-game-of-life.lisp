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
  (delay 60)
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

(defun enumerate (lst &optional (index 0))
  "Return association list with index position and list value."
  (cond ((null lst) '())
        (t (cons (cons index
                       (car lst))
                 (enumerate (cdr lst) (+ 1 index))))))

(defun fold-left (f acc lst)
  (cond ((null lst) acc)
        (t (fold-left f (f acc (car lst)) (cdr lst)))))

(defun blink ()
  (pinmode 2 :output)
  (digitalwrite 2 :high)
  (delay 80)
  (digitalwrite 2 :low))

(defun update-generation (matrix)
  (let ((cell-alive? (lambda (cell)
                       (not (= 0 cell))))
        (cell-dead 0)
        (cell-alive 1))
    (mapcar
     (lambda (row-pair)
       (let ((row-ind (car row-pair))
             (row (cdr row-pair)))
         (mapcar
          (lambda (cell-pair)
            (let* ((col-ind (car cell-pair))
                   (cell (cdr cell-pair))
                   (get-value (lambda (matrix row col)
                                (let ((num-rows (length matrix))
                                      (num-cols (length (car matrix))))
                                  (cond ((or (< row 0)
                                             (< col 0)
                                             (>= row num-rows)
                                             (>= col num-cols)) 0)
                                        (t (nth col (nth row matrix)))))))
                   (neighbors (+ (get-value matrix (- row-ind 1) (- col-ind 1))
                                 (get-value matrix (- row-ind 1) col-ind)
                                 (get-value matrix (- row-ind 1) (+ col-ind 1))
                                 (get-value matrix row-ind (- col-ind 1))
                                 (get-value matrix row-ind (+ col-ind 1))
                                 (get-value matrix (+ row-ind 1) (- col-ind 1))
                                 (get-value matrix (+ row-ind 1) col-ind)
                                 (get-value matrix (+ row-ind 1) (+ col-ind 1)))))
              (cond ((cell-alive? cell)
                     (if (or (= 2 neighbors)
                             (= 3 neighbors))
                         cell-alive
                       cell-dead))
                    (t (if (= 3 neighbors)
                           cell-alive
                         cell-dead)))))
          (enumerate row))))
     (enumerate matrix))))

(defun display-generation (generation)
  (update-display (mapcar #'binary-list-to-number generation)))

(defun binary-list-to-number (lst)
  (fold-left
   (lambda (acc pair)
     (let ((ind (car pair))
           (bit (cdr pair)))
       (+ acc (* bit (expt 2 ind)))))
   0
   (enumerate lst)))

(defun game-of-life (generation)
  (let ((next-generation))
    (loop
     (display-generation (reverse generation))
     (setq next-generation (update-generation generation))
     (if (equal generation next-generation)
         (return)
         (progn 
           (setq generation next-generation))))))

(spi-begin)

(init-display)

(game-of-life '((1 0 0 1 0 0 0 0)
                (0 0 0 0 1 0 0 0)
                (1 0 0 0 1 0 0 0)
                (0 1 1 1 1 0 0 0)
                (0 0 0 0 0 0 0 0)
                (0 0 0 0 0 0 0 0)
                (0 0 0 0 0 0 0 0)
                (0 0 0 0 0 0 0 0)))

(game-of-life (mapcar
               (lambda (row)
                 (mapcar
                  (lambda (cell)
                    (random 2))
                  row))
               '((0 0 0 0 0 0 0 0)
                 (0 0 0 0 0 0 0 0)
                 (0 0 0 0 0 0 0 0)
                 (0 0 0 0 0 0 0 0)
                 (0 0 0 0 0 0 0 0)
                 (0 0 0 0 0 0 0 0)
                 (0 0 0 0 0 0 0 0)
                 (0 0 0 0 0 0 0 0))))

(loop
 (blink)
 (game-of-life (mapcar
                (lambda (row)
                  (mapcar
                   (lambda (cell)
                     (random 2))
                   row))
                '((0 0 0 0 0 0 0 0)
                  (0 0 0 0 0 0 0 0)
                  (0 0 0 0 0 0 0 0)
                  (0 0 0 0 0 0 0 0)
                  (0 0 0 0 0 0 0 0)
                  (0 0 0 0 0 0 0 0)
                  (0 0 0 0 0 0 0 0)
                  (0 0 0 0 0 0 0 0)))))
