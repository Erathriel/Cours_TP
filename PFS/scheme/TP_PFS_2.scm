#!r7rs

(import (scheme base) (scheme write))

(define (writeln/return x)
  ;;  Fonction très utile pour pouvoir afficher un résultat suivi d'un passage
  ;;  à la ligne, tout en pouvant récupérer ce résultat dans une variable. Les
  ;;  trois expressions suivantes sont évaluées en séquence et la valeur de la
  ;;  dernière est retournée.
  (write x)
  (newline)
  x)

(define (first-mystery n)
  ;;  Rappelons que les fonctions "quotient" et "remainder" retournent
  ;;  respectivement le quotient entier et le reste d'une division euclidienne,
  ;;  à condition, bien sûr, que le diviseur ne soit pas nul.
  (if (< n 10) n (+ (first-mystery (quotient n 10)) (remainder n 10))))

(define (second-mystery n p)
  ;;
  (define (rec-mystery n0 p0)
    ;;  Rappelons �galement qu'une forme sp�ciale "define" interne � une forme
    ;;  "lambda " est �quivalente � l'utilisation d'une forme sp�ciale
    ;;  "letrec*".
    (if (zero? (remainder n0 p0)) (rec-mystery (quotient n0 p0) p0) n0))
  ;;
  ;;  Principal call:
  (if (or (zero? p) (zero? n)) n (rec-mystery n p)))

(define volume-at
  (lambda (t v0 l0)
    (* v0 (+ 1 (* t l0)))))

(define body->volume-at
  (lambda(l1)
    (lambda(t1 v1)
      (volume-at t1 v1 l1))))

(define gas->volume-at
    (body->volume-at(/ 1 273.15)))

(writeln/return (volume-at 30 1 1e-5))
(writeln/return (gas->volume-at 30 1))

(define in-inches
    (lambda( m y f i)
      (+ (* m 1760 3 12) (* y 3 12) (* f 12) i)))

(writeln/return (in-inches 1 0 0 0))

(define inches-to-meters
  (lambda(i)
    (/(* i 25.4)1000)))
              
(writeln/return (inches-to-meters 2))

(define british-to-metric
  (lambda(m1 y1 f1 i1)
    (inches-to-meters (in-inches m1 y1 f1 i1))))

(writeln/return (british-to-metric 3 61 2 10))

(define to-metric
  (lambda ( nb1 nb2 nb3 metric0)
    (lambda ( u1 u2 u3 u4)
      (*(+(*(+(*(+(* nb1 u1) u2) nb2) u3) nb3) u4) metric0))))

(define british-to-metric-v2
  (lambda ( v1 v2 v3 v4)
    ((to-metric 1760 3 12 0.0254) v1 v2 v3 v4)))

(define british-to-metric-v3 (to-metric 1760 3 12 0.0254))

(writeln/return (british-to-metric-v3 3 61 2 10))

(define time-to-seconds (to-metric 24 60 60 1))

(writeln/return (time-to-seconds 1 3 47 48))

;; calcule la somme des chiffres du nombre en paramètre.

(writeln/return (first-mystery 2009))
(writeln/return (first-mystery 2017))
(writeln/return (first-mystery 2004))
(writeln/return (first-mystery 4501))
(writeln/return (first-mystery 450))

(define one-digit
  (lambda (n)
    (if (< n 10) n
        (one-digit (first-mystery n)))))

(writeln/return (one-digit 2009))
(writeln/return (one-digit 2017))



(writeln/return (second-mystery 12 3))

(define hamming-number?
  (lambda (n)
    (= 1 (second-mystery (second-mystery (second-mystery n 2) 3) 5))))

(writeln/return (hamming-number? 14))

(define diag
  (lambda (n)
    (if (<= 0 n)
        (cons 0 0)
        (let* ((pq (diag(- n 1)))
        (p (car pq))
        (q (cdr pq)))
    (if (zero? q)
        (cons 0 (+ p 1))
        (cons (+ p 1)
              (- q 1)))))))