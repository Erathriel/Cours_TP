#!r7rs

(import (scheme base) (scheme write))

(define (writeln/return x)
  (write x)
  (newline)
  x)

(writeln/return (call-with-values (lambda () (values 'L 3)) cons))

(writeln/return (let ((a 'sure)
		      (b 'here)
		      (x 'little)
		      (y 'players))
		  (let-values (((a b) (values x y))
			       ((x y) (values a b)))
		    (list a b x y))))

(writeln/return (let ((a 'sure)
		      (b 'here)
		      (x 'little)
		      (y 'players))
		  (let*-values (((a b) (values x y))
				((x y) (values a b)))
		    (list a b x y))))

(writeln/return (let-values (((first) (car '(very little players)))
			     ((the-quotient the-remainder) (truncate/ 2000 9)))
		  (cons the-quotient (cons the-remainder first))))

(define (take n l)
  (if (zero? n) '() (cons (car l) (take (- n 1) (cdr l)))))

(define (drop n l)
  (if (zero? n) l (drop (- n 1) (cdr l))))

(define (take-while p1? l)
  (if (null? l)
      '()
      (let ((first (car l)))
	(if (p1? first) (cons first (take-while p1? (cdr l))) '()))))

(define (drop-while p1? l)
  (if (or (null? l) (not (p1? (car l)))) l (drop-while p1? (cdr l))))

(define-syntax write-values
  (syntax-rules ()
    ((write-values the-values) (let ((nothing-string "*nothing*")
				     (and-string " *and* "))
				 (call-with-values (lambda () the-values)
				   (lambda arg-list
				     (if (null? arg-list)
					 (display nothing-string)
					 (begin
					   (write (car arg-list))
					   (for-each (lambda (arg)
						       (display and-string)
						       (write arg))
						     (cdr arg-list))))
				     (newline)
				     #t))))))

(define (split-at n l)
  (if (zero? (n))
      (value '() l)
      (let-values ((gauche droite) (split-at (- n 1) (cdr l)))
        (values (cons (car l) gauche droite )))))