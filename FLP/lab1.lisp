; 1
(car (cddadr '(1 (2 (3 4) *) 5)))

; 2
(cons '(a (b c)) nil)

; 3
(cons (cons 1 nil) (cons (cons 2 (cons 3 nil)) nil))

(list(list 1)(list 2 3))

; 4
(defun zamena(l)
 (
   list (car l) (cadr l) (car (last l)) (car (last (butlast l))) (caddr l )
 )
)

(zamena '(1 2 3 4 5))