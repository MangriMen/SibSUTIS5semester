;5 group

; 5
(defun popN(l n)
 (
  if (> n 0) (popN (cdr l) (- n 1)) l
 )
)

(popN '(1 2 3 4 5 6) 3)

; 15
(defun cycleLeftN(l n)
 (
  if (> n 0) (cycleLeftN (append (cdr l) (cons (car l) nil)) (- n 1)) l
 )
)

(cycleLeftN '(a b c d f) 3)

; 25
(defun letterCount(l letter &optional (counter 0))
 (
  cond
	((null l) (list letter counter))
    ((equal (car l) letter) (letterCount (cdr l) letter (+ counter 1)))
    (t (letterCount (cdr l) letter counter))
 )
)

(defun listLettersEntryCount(l &optional (out nil))
 (
  if (null l) out (listLettersEntryCount (remove (car l) l) (append out (cons (letterCount l (car l)) nil)))
 )
)

(listLettersEntryCount '(a b a a b b b c b))