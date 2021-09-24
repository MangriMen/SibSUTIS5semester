;5 group

;5
(defun deleteFrontN(l n)
 (cond
   ((<= n 0) l)
   (t (deleteFrontN (cdr l) (- n 1)))
 )
)

(deleteFrontN '(2 6 1 7 0) 3)

;15
(defun shiftLeftN(l n)
 (cond
  ((<= n 0) l)
  (t (shiftLeftN (append (cdr l) (cons (car l) nil)) (- n 1)))
 )
)

(shiftLeftN '(a s d f g) 3)

;25
(defun countElement(l element &optional (counter 0))
 (cond 
  ((null l) (list element counter))
  (t (countElement (cdr l) element (cond ((equal (car l) element) (+ counter 1)) (t counter))))
 )
)

(defun countElementList(l &optional (out nil))
 (cond
   ((null l) out)
   (t (countElementList (remove (car l) l) (append out (list (countElement l (car l))))))
 )
)

(countElementList '(a b a a c b))