#!r7rs

; Exemple tp !

(import (scheme base) (scheme inexact) (scheme write))
;;  Importation des bibliothèques prédéfinies nécessaires. Pour l'instant,
;;  retenez simplement que vous aurez toujours besoin de "base". De même, nous
;;  importerons toujours "write" pour réaliser des affichages à l'écran. Nous
;;  vous signalerons l'importation d'autres bibliothèques le cas échéant : ici,
;;  "inexact", car nous utilisons quelques fonctions trigonométriques et
;;  logarithmiques.

(write (+ 2017 (* (+ 22 1) (/ 14 (- 9 2)))))  ;  (*)

(newline)
(write "Hello world!")
(newline)
(display "Hello world!")
(newline)

(write ((lambda (x) (* x x)) 2016))  ;  (**)

(newline)

(define crash          ;  (***)  Pour bien montrer que Scheme n'�value pas sous
  (lambda () (/ 0)))   ;  la forme sp�ciale "lambda".

(define derive-wrt
  (lambda (f1 h)
    (lambda (x) (/ (- (f1 (+ x h)) (f1 x)) h))))

(write ((derive-wrt (lambda (x) (* x x)) 0.0001) 2))
(newline)

(write ((derive-wrt + 0.0001) 2))  ;  (****)

(define fact
  (lambda (n) (if (zero? n) 1 (* n (fact (- n 1))))))

(newline)
(write (fact 6))
(newline)

(define pi (* 4 (atan 1)))  ;  "atan" est la fonction "Arc tangente" en Scheme.

(define power
  (lambda (U I f0) (* U I (cos (* 2 pi f0)))))

(define fq->power
  (lambda (f0)
    (let ((coefficient (cos (* 2 pi f0))))
      (lambda (U I) (* coefficient U I)))))

; TP 2.1

(write(+))
(newline)
(write(+ 6 10 2017 1))
(newline)
(write(*))
(newline)
(write(* 12 10 2017 2))

;(write(-))
(newline)
(write(- 1))
(newline)
(write(- 7 2 2017 2))
(newline)

(write(/ 6 3))
(newline)
(write(/ 3 2))
(newline)

(write(/ 3.0 2.0))
(newline)

(write(+ 1 1.1))
(newline)
(write(/ 3.0 2))
(newline)

(write(/ 4 3))
(newline)
(write(quotient 4 3))
(newline)

(write(remainder 4 3))
(newline)

(write(+ (* 4.1 9.8)
         (/ (* 2 pi)
            3)))
(newline)

(write(+ (exp pi)
         (log (sin 2.1))
         (sin (+ (/ 1 pi)
                 pi))))
(newline)

(write ((lambda (x) (* x x)) 2017))
(newline)
;(write ((lambda (x y) (* x y y)) 2017))
(write ((lambda (x y) (* x y y)) 2017 2016))
(newline)
;(write ((lambda (x y) (* x y y)) 2017 2016 2015))
(newline)
(write 2017)
(newline)

;(write lambda() 2017)
(write (lambda() 2017))
(newline)

;(write +)
(write(+))
(newline)

;(write(2017))
(newline)
(write((lambda () 2017)))
(newline)
;(write(((lambda () 2017))))
(newline)
(write(((lambda () (lambda () 2017)))))
(newline)

;(write((derive-wrt (lambda(x y) (+ (* 2 x)
;                                  y))
;                   0.0001)
;       2))
(write (power 220 7 50))
(newline)

(define power-50 (fq->power 50))
(write (power-50 220 7))
(newline)

(write((fq->power 50) 220 7))
(newline)

;(define fact
;  (lambda (n) (if (zero? n) 1 (* n (fact (- n 1))))))

(define (euclide a b)
  (cond ((= b 0) a)
        (else (euclide b (remainder a b)))))

(define pgcd
  (lambda(a b)
    (cond ((or (= b 0) (< a b))  #f)
          (else (euclide a b)))))

(define (pgcd2 a b)
  (cond ((or (= b 0) (< a b))  #f)
              (else (euclide a b))))

(write(gcd 12 8))
(newline)
(write (pgcd 12 80))
(newline)
(write(pgcd2 12 80))
(newline)
