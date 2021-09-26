;lab3
;First
(defun isEqual(l1 l2)
    (cond
        ((null l1) t)
        ((equal (car l1) (car l2)) (isEqual (cdr l1) (cdr l2)))
        (t nil)
		)
)

(isEqual '(1 2) '(1 2))

;Second
(defun ccar (lst)
     (cond ((null lst) nil)
           (t (cons (caar lst) (ccar (cdr lst)))))
)

(defun ccdr (lst)
     (cond ((null lst) nil)
           (t (cons (cdar lst) (ccdr (cdr lst)))))
)

(defun transpose (matr)
  (cond ((null (car matr)) Nil)
        (t (cons (ccar matr) (transpose (ccdr matr)))))
)

(transpose '((1 2 3)(4 5 6)(7 8 9)))

;Third
(defun func (p lst)
  (cond ((null lst) nil)
        ((funcall p (car lst)) t)
        (t (func p (cdr lst))))
)

(func (lambda (x) (cond((< x 0) t))) '(1 2 -3 4))
(func (lambda (x) (cond((< x 0) t))) '(1 2 3 4))
(func 'symbolp '(a 1 2 3))
(func 'symbolp '(1 1 2 3))