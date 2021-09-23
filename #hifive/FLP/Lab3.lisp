;lab3
;First
(defun equal_p(l1 l2)
    (cond
        ((null l1) t)
        ((equal (car l1) (car l2)) (equal_p (cdr l1) (cdr l2)))
        (t nil))
)

(equal_p '(1 2) '(1 2))

;Second
((1 2 3)(4 5 6)(7 8 9))
(defun ccar (lst)
     (cond ((null lst) nil)
           (t (cons (caar lst) (ccar (cdr lst)))))
)
(1 4 7)

(defun ccdr (lst)
     (cond ((null lst) nil)
           (t (cons (cdar lst) (ccdr (cdr lst)))))
)
((2 3)(5 6)(8 9))

(defun transp-r (matr)
  (cond ((null (car matr)) Nil)
        (t (cons (ccar matr) (transp-r (ccdr matr)))))
)

(transp-r '((1 2 3)(4 5 6)(7 8 9)))

;Third
(defun f (p lst)
  (cond ((null lst) nil)
        ((funcall p (car lst)) t)
        (t (f p (cdr lst))))
)

(f (lambda (x) (cond((< x 0) t))) '(1 2 -3 4))
(f (lambda (x) (cond((< x 0) t))) '(1 2 3 4))
(f 'symbolp '(a 1 2 3))
(f 'symbolp '(1 1 2 3))