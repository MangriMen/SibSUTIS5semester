;5 group

;1
;(3 5 (7) (4 1))
(defun isListEq(l1 l2)
 (cond
  ((and (null l1) (null l2)) t) 
  ((equal (car l1) (car l2)) (isListEq (cdr l1) (cdr l2)))
  (t nil)
 )
)

(isListEq '(3 5 (7 (1) (4 1))) '(3 5 (7 (1)) (4 1)))

;8
(defun mkStrFromFirst(m)
 (cond
  ((null m) nil)
  (t (cons (caar m) (mkStrFromFirst (cdr m))))
 )
)

;(mkStrFromFirst '((1 2 3 4) (5 6 7 8) (9 10 11 12)))

(defun mkStrFromLast(m)
 (cond
  ((null m) nil)
  (t (cons (cdar m) (mkStrFromLast (cdr m))))
 )
)

;(mkStrFromLast '((1 2 3 4) (5 6 7 8) (9 10 11 12)))

(defun matrixT(m)
 (cond
  ((null (car m)) nil)
  (t (cons (mkStrFromFirst m) (matrixT (mkStrFromLast m))))
 )
)

(matrixT '((1 2 3 4) (5 6 7 8) (9 10 11 12)))

;13
(defun alo(fun l)
 (cond 
  ((null l) nil)
  ((funcall fun (car l)) t)
  (t (alo fun (cdr l)))
 )
)

(alo (lambda (x) (cond ((< x 0) t))) '(3 5 7 -3 0 2))
(alo (lambda (x) (cond ((< x 0) t))) '(5 6 8))
(alo 'symbolp '(3 5 7 * 0 2))
(alo 'symbolp '(5 6 8))