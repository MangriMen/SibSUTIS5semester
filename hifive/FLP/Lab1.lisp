;(1 (2 (3 4) *) 5)
(car(cddadr '(1 (2 (3 4) *) 5)))

;Explain cons command
(cons '(a (b c)) nil)

;((1)(2 3)) with list and cons only
(list (list 1) (list 2 3))
(cons (cons 1 nil) (cons (cons 2 (cons 3 nil))nil))

;Swap 3rd and last elements
(defun swap(swList)
	(append
		(list(car swList))
		(list(cadr swList))
		(last swList)
		(cdddr (butlast swList))
		(list(caddr swList))
	)
)

(swap '(1 2 3 4 5 6 7 8 9))