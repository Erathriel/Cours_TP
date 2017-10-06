#!r7rs

(import (scheme base) (scheme case-lambda) (scheme cxr) (scheme write))

(define (writeln/return x)
  ;;  Fonction très utile pour pouvoir afficher un résultat suivi d'un passage
  ;;  à la ligne, tout en pouvant récupérer ce résultat dans une variable. Les
  ;;  trois expressions suivantes sont évaluées en séquence et la valeur de la
  ;;  dernière est retournée.
  (write x)
  (newline)
  x)

;;;  ==========================================================================
;;;  Start

(writeln/return (cons 0 1))
(writeln/return (cons 0.1 0.1))
(writeln/return (cons (cons 0.1 0.1) 1))
(writeln/return (cons 0.1 '()))
(writeln/return (cons '() 0.1))
(writeln/return (cons '() '()))

(define current-year 2017)
(define next-year (+ current-year 1))
(define academic-year (cons current-year next-year))
(define academic-year-0 (cons current-year 'next-year))
(define academic-year-1 (cons 'current-year 'next-year))
(define operations (cons + -))
(define symbols (cons '+ '-))
(define two-numbers (cons 0 1))
(define something (cons (cons 0.1 0.1) 1))

(writeln/return academic-year)
(writeln/return (quote academic-year))
(writeln/return 'academic-year)
(writeln/return 'undefined)
;; (writeln/return undefined)
(writeln/return +)
(writeln/return '+)
;; (writeln/return (0 . 1))
(writeln/return '(0 . 1))
;; (writeln/return (+ . 1))
(writeln/return '(+ . 1))

(writeln/return (car academic-year))
(writeln/return (cdr academic-year))
;; (writeln/return (car next-year))
(writeln/return academic-year-0)
(writeln/return (cdr academic-year-0))
(writeln/return academic-year-1)

(writeln/return ((car operations) (car two-numbers) (cdr two-numbers)))
;; (writeln/return ((cdr symbols) (cdr two-numbers) (car two-numbers)))
(writeln/return (cons (cdr symbols) (car two-numbers)))
(writeln/return (cons (cdr operations) (cdr two-numbers)))
(writeln/return ((cdr operations) (cdr two-numbers)))
(writeln/return (car something))
(writeln/return (cdr (car something)))
;;(writeln/return (car (cdr something)))

;;;  ==========================================================================
;;;  From Pairs to Lists

;  ****

;;;  ==========================================================================
;;;  Lists

(writeln/return '(Sometime . ((to . ()) . ((() . miss) . (now . ())))))
;;(writeln/return '(Everybody . ()) . (() . wants) . (somebody . ())))

  (writeln/return
   '((Thats . ((() . ()) . why)) . ((() . I) . ((need . (you . baby)) . ()))))

  (writeln/return
   (cons (list 'Aint 'nobody 'else 'around) '()))

(writeln/return (list 'Someone (cons 'to '(squeeze))))

(writeln/return (list (list 'I 'need 'you)
  			       (cons 'you (cons 'you '()))))

(writeln/return (append (list 'And 'I) 
			       (append '(need) '(you))
                               (cons 'you '(you))))

(writeln/return
 (cons 'I-m
                  (append '((so glad))
  			       (list 'to 'be 'here 'tonight))))

;;;  ==========================================================================
;;;  Mini data bases

(define unknown '??)

(define (unknown? x)
  (eq? x unknown))

(define (mk-recording key-0 title-0 author-list-0 year-0 publisher-0 
		      key-list-0)
  ;;  SYMBOL,STRING,LIST-of[SYMBOL}^,INTEGER,SYMBOL^,LIST-of[SYMBOL]^ -> JAZZ-R
  (list key-0 title-0 author-list-0 year-0 publisher-0 key-list-0))

(define miles-davis-r
  (list (mk-recording 'd0 "On the Corner" unknown 1972 unknown '(c40))
	(mk-recording 'd1 "New-York Girl" unknown 1972 unknown '(c40))
	(mk-recording 'd2 "Thinkin' One Thing and Doin' Another" unknown 1972
		      unknown '(c40))
	(mk-recording 'd3 "One and One" unknown 1972 unknown '(c40))
	(mk-recording 'd4 "Well You Needn't" '(Thelonius-Monk) 1954
		      'Blue-Ribbon-Music '(c41))
	(mk-recording 'd5 "Love for Sale" '(Cole-Porter) 1958 'Chappell '(c41))
	(mk-recording 'd6 "Something Else" '(Miles-Davis) 1958 'EMI '(c41))
	(mk-recording 'd7 "Dear Old Stockholm" '(Stan-Getz P-Golly) 1952
		      'Windswept-Pacific-Music '(c41))
	(mk-recording 'd8 "Black Satin" unknown 1972 unknown '(c40))
	(mk-recording 'd9 "Mr. Freedom X" unknown 1972 unknown '(c40))
	(mk-recording 'd10 "Helen Butte" unknown 1972 unknown '(c40))
	(mk-recording 'd11 "Boplicity" '(Cleo-Henry) 1949 'Campbell '(c40))
	(mk-recording 'd12 "Ray's Idea" '(Ray-Bonner W-G-Fuller) 1953 
		      'Bosworth '(c41))
	(mk-recording 'd13 "Yesterdays" '(Kern Harbach) 1952 'Universal '(c42))
	(mk-recording 'd14 "Vote for Miles" unknown 1972 unknown '(c40))
	(mk-recording 'd15 "Deception" '(Miles-Davis) 1950 'Sony '(c41))
	(mk-recording 'd16 "Israel" '(John-Carisi) 1949 'EMI '(c41))
	(mk-recording 'd17 "How Deep is the Ocean" '(Irving-Berlin) 1952 'EMI
		      '(c41))
	(mk-recording 'd18 "Kelo" '(Jay-Jay-Johnson) 1953 'Kensington-Music
		      '(c41))
	(mk-recording 'd19 "Woody 'n' You" '(Dizzy-Gillepsie) 1952 'Chappell
		      '(c41))
	(mk-recording 'd20 "Chance It" '(Oscar-Petitford) 1952 'Orpheus-Music
		      '(c41))))

(define stan-getz-r
  (list (mk-recording 'g30 "Autumn Leaves" '(Kosma Prevert) 1980
		      'Peter-Maurice-Co-Ltd '(c44))
	(mk-recording 'g31 "Nature Boy" '(Abbon) 1980 'Chappell '(c44))))

;  ****

;;;  ==========================================================================
;;;  Operations on mini data bases

(writeln/return (map (lambda (x) (+ x 1)) '(26 9 2017)))

;;  (writeln/return (unique-keys? miles-davis-r))
;;  (writeln/return (unique-keys? stan-getz-r))

;;;  ==========================================================================
;;;  Merge Sort

(define (mergesort l rel-2?)
  ;;  La clôture lexicale permet aux fonctions locales d'accéder à la relation
  ;;  d'ordre "rel-2?".
  ;;
  (define (merge-2-groups g0 g1)
    (cond ((null? g0) g1)
	  ((null? g1) g0)
	  (else (let ((first-0 (car g0))
		      (first-1 (car g1)))
		  (if (rel-2? first-0 first-1) 
		      (cons first-0 (merge-2-groups (cdr g0) g1))
		      (cons first-1 (merge-2-groups g0 (cdr g1))))))))
  ;;
  (define (merge-groups group-list)
    (if (or (null? group-list) (null? (cdr group-list)))
	group-list
	(cons (merge-2-groups (car group-list) (cadr group-list))
	      (merge-groups (cddr group-list)))))
  ;;
  (define (make-groups l0)
    ;;  "l0" est une liste linéaire non vide.
    (let ((first (car l0))
	  (rest (cdr l0)))
      (if (null? rest)
	  (list (list first))
	  (let ((next-groups (make-groups rest)))
	    (if (rel-2? first (car rest))
		(cons (cons first (car next-groups)) (cdr next-groups))
		(cons (list first) next-groups))))))
  ;;
  (if (null? l)
      '()
      (let iter-merge-groups ((group-list (make-groups l)))
	(if (null? (cdr group-list))
	    (car group-list)
	    (iter-merge-groups (merge-groups group-list))))))

(define cp-list-example
  '((5 . 5) (6 . 0) (3 . 3) (6 . 1) (7 . 7) (1 . 1) (6 . 2)))

(define (pretty-writeln/return x)
  ;;  Writes "x", followed by an end-of-line character, and returns "x".  If
  ;;  "x" is a linear list, successive lines are used for successive elements.
  (if (and (pair? x) (list? x))
      (begin
	(write-char #\()
	(write (car x))
	(for-each (lambda (x0)
		    (newline)
		    (write-char #\space)
		    (write x0))
		  (cdr x))
	(write-char #\)))
      (write x))
  (newline)
  x)

;;;  ==========================================================================
;;;  Apotheosis

(define (position x l)
  (let thru ((l0 l)
	     (current-position 0))
    (cond ((null? l0) #f)
	  ((equal? (car l0) x) current-position)
	  (else (thru (cdr l0) (+ current-position 1))))))

(define add-something
  (case-lambda
   ((x) (+ x 1))
   ((x y) (+ x y))))

;;(define free-family
  ;;(lambda (v w)
    ;;))

(define key car)
(define title cadr)
(define authors caddr)
(define (year l0) (car(cdddr l0)))
(define (publishers l0) (car (cddddr l0))) ;;(car (cddddr l0)
(define (cds l0) (list-ref l0 5)) ;;(cadr(cddddr l0)))


(writeln/return (key (car miles-davis-r)))
(writeln/return (cds (car miles-davis-r)))
(writeln/return (cons key cds))

(define (unique-keys-v1 l)
  (let ((premier (car l))
        (suite (cdr l)))
    (if (null? suite)
        #t
        (if (member premier suite)
            #f
            (unique-keys-v1 suite)))))

(writeln/return (unique-keys-v1 (map key miles-davis-r)))


;;(define (unique-keys l)
;;  (define (all-different l)
;;    (let ((premier (car l))
;;        (suite (cdr l)))
;;    (or (null? suite)
;;        (and (not(member premier suite))
;;            (all-different suite)))))
;;  (all-different (map key l)))

;;(writeln/return (unique-keys (map key miles-davis-r)))

(define (get-information-e key0 sel0 j-list)
  (if (null? j-list)
      #f
      (let ((premier (car j-list))
            (suite (cdr j-list)))
        (if (equal? (key premier) key0)
            (sel0 premier)
            (get-information-e key0 sel0 suite)))))

(writeln/return (get-information-e 'd14 title miles-davis-r))

(define (get-key x0 sel0 j-list)
  (if (null? j-list)
      #f
      (let ((premier (car j-list))
            (suite (cdr j-list)))
        (if (equal? (sel0 premier) x0)
            (key premier)
            (get-key x0 sel0 suite)))))

(writeln/return (get-key "Kelo" title miles-davis-r))

(define (those-that p1? j-list f1)
  (if (null? j-list)
      '()
      (let* ((premier (car j-list))
            (suite (cdr j-list))
            (recursion (those-that p1? suite f1)))
        (if (p1? premier)
            (cons (f1 premier) recursion)
            recursion))))

(writeln/return (those-that
                 (lambda (x) (= (year x) 1972))
                 miles-davis-r
                 title))

(writeln/return (those-that
                 (lambda (x)
                   (let ((authors0 (authors x)))
                   (and (not (unknown? authors0))
                        (pair? authors0))))
                 miles-davis-r
                 key))

(writeln/return (those-that
                 (lambda (x)
                   (let ((authors0 (authors x)))
                   (and (not (unknown? authors0))
                        (null? (cdr authors0)))))
                 miles-davis-r
                 title))

(writeln/return (those-that
                 (lambda (x) (unknown? (publishers x)))
                 (append miles-davis-r stan-getz-r)
                 title))

(writeln/return (those-that
                 (lambda (x) (equal? (publishers x) 'EMI))
                 miles-davis-r 
                 title))

(writeln/return (those-that
                 (lambda (x)
                   (let ((authors0 (authors x)))
                   (and (not (unknown? authors0))
                        (member 'Miles-Davis authors0))))
                 miles-davis-r
                 title))


(writeln/return (those-that
                 (lambda (x)
                   (let ((cds0 (cds x)))
                   (and (not (unknown? cds0))
                        (pair? (cdr cds0)))))
                 stan-getz-r
                 key))



