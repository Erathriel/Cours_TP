#!r7rs

;NORO Geoffrey

(import (scheme base)
        (scheme cxr)
        (scheme write)
        )

;;;;  =========================================================================
;;;;
;;;;            Lab class examination --- Definitions given to students
;;;;
;;;;  =========================================================================
;;;;
;;;;  Author: J.-M. Hufflen
;;;;  Date: November 2017
;;;;
;;;;  =========================================================================

;;;  ==========================================================================

(define (writeln/return x)
  (write x)
  (newline)
  x)

(define (mk-music-album album-key-0 author-key-0 year-0 instruments-0 title-0
			piece-nb-0 some-piece-titles-0)
  (cons album-key-0
	(cons author-key-0
	      (cons year-0
		    (cons instruments-0
			  (cons title-0
				(cons piece-nb-0 some-piece-titles-0)))))))

(define music-album-list
  (list (mk-music-album 
	 'aubry1995 'aubry 1995 '() "Ne m'oublie pas" 13
	 '(#t "Chanson d'Adrien" "Cortège" "Le bal des patineurs"))
	(mk-music-album 'aubry1993 'aubry 1993 '() "Après la pluie" 11
			'("Take My Hand" "Vertige" #t))
	(mk-music-album 'aubry2004 'aubry 2004 
			'(cymbalum guitar mandolin violin) "Projection privée"
			15
			'("Antoine et Félicie"
			  "Tout le plaisir est pour moi" "Malabar Princess"))
	(mk-music-album
	 'malicorne1975 'malicorne 1975 
	 '(bass 
	   bouzouki crumhorn dulcimer spinet guitar harmonium hurdy-gurdy
	   mandolin psaltery violin)
	 "Le mariage anglais" 10
	 '(#t
	   "La fille aux chansons" "J'ai vu le loup, le renard et la belette"
	   "Marions les roses"))))

(define album-key car)

; 1 Preludio

(define (forall p1? l)
  (if (null? l)
      #f
      (if (p1? (car l))
          (forall p1? (cdr l))
          #t)))

(writeln/return (forall number? '(30 11 2017)))
(writeln/return (forall number? '(30 November 2017)))
(writeln/return (forall number? '()))

(define (subst x y l)
  (cond ((null? l) '())
        ((equal? x (car l))(cons y(subst x y (cdr l))))
        (else (cons(car l)(subst x y (cdr l))))))

(writeln/return (subst 29 30 '(29 11 2017 29 30 12 2017)))
(writeln/return (subst 30 29 '(29 11 2017 29 30 12 2017)))

(define (exchange x y l)
  (cond ((null? l) '())
        ((equal? x (car l))(cons y(subst x y (cdr l))))
        ((equal? y (car l))(cons x(subst y x (cdr l))))
        (else (cons(car l)(subst x y (cdr l))))))
(writeln/return (exchange 29 30 '(29 11 2017 29 30 12 2017)))


