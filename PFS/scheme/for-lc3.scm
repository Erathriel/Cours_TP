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
(define (publishers l0) (car (cddddr l0))) ;;(list-ref(l0 4)))
(define (cds l0) (list-ref l0 5)) ;;(cadr(cddddr l0)))


(writeln/return (key (car miles-davis-r)))
(writeln/return (cds (car miles-davis-r)))
(writeln/return (cons key cds))

;(define (unique-keys l)
  ;(define (all-different l)
    ;(let ((premier (car l))
     ;   (suite (cdr l)))
    ;(or (null? suite)
   ;     (and (not(member premier suite))
  ;          (all-different suite)))))
 ; (all-different (map key l)))

;(writeln/return (unique-keys (map key miles-davis-r)))

(define (unique-keys-v1 l)
  (let ((premier (car l))
        (suite (cdr l)))
    (if (null? suite)
        #t
        (if (member premier suite)
            #f
            (unique-keys-v1 suite)))))

(writeln/return (unique-keys-v1 (map key miles-davis-r)))


(define (get-information-e key0 sel0 list0)
  (if (null? list0)
      #f
      (let ((premier (car list0))
            (suite (cdr list0)))
        (if(equal? (key premier) key0)
           (sel0 premier)
           (get-information-e key0 sel0 suite)))))

(writeln/return (get-information-e 'd14 title miles-davis-r ))
(writeln/return (get-information-e 'd13 authors miles-davis-r ))
(writeln/return (get-information-e 'g30 year stan-getz-r))
;(writeln/return (get-information-e 'd14 publishers miles-davis-r ))

(define (get-key x0 sel0 list0)
  (if (null? list0)
      #f
      (let ((premier (car list0))
            (suite (cdr list0)))
        (if(equal? (sel0 premier) x0)
           (key premier)
           (get-key x0 sel0 suite)))))

(writeln/return (get-key "Kelo" title miles-davis-r ))
(writeln/return (get-key "Blue Moon" title stan-getz-r ))

(define (those-that? p1? list f1)
  (if (null? list)
      '()
      (let ((premier (car list))
            (suite (cdr list)))
        (if(p1? premier)
           (cons (f1 premier) (those-that? p1? suite f1))
           (those-that? p1? suite f1)))))

(define (those-that2? p1? list f1)
  (if (null? list)
      '()
      (let* ((premier (car list))
            (suite (cdr list))
            (recursion (those-that? p1? suite f1)))
        (if(p1? premier)
           (cons (f1 premier) recursion)
           recursion))))
           
(writeln/return (those-that?
                 (lambda (x) (= (year x) 1972))
                 miles-davis-r title))

(writeln/return (those-that2?
                 (lambda (x) (= (year x) 1972))
                 miles-davis-r title))

(writeln/return (those-that2?
                 (lambda (x)
                   (let ((authors0 (authors x)))
                     (and (not (unknown? authors0))
                          (pair? (cdr authors0)))))
                 stan-getz-r key))

(writeln/return (those-that2?
                 (lambda (x)
                   (let ((authors0 (authors x)))
                     (and (not (unknown? authors0))
                          (null?(cdr authors0)))))
                 miles-davis-r key))

(writeln/return (those-that2?
                 (lambda (x)
                   (unknown? (publishers x)))
                 (append miles-davis-r stan-getz-r) title))

(writeln/return (those-that2?
                 (lambda (x)
                   (equal? (publishers x) 'EMI))
                 miles-davis-r key))

(writeln/return (those-that2?
                 (lambda (x)
                   (let ((authors0 (authors x)))
                     (and (not (unknown? authors0))
                          (member 'Miles-Davis authors0))))
                 miles-davis-r title))

(writeln/return (those-that2?
                 (lambda (x)
                   (let ((cds0 (cds x)))
                     (and (not (unknown? cds0))
                          (pair? (cdr cds0)))))
                 stan-getz-r key))

(define (update annee l l0)
  (cond ((null? l) (cons (cons annee 1) l0))
        ((= annee (caar l)) (cons (cons annee (+ 1 (cdar l))) l0))
        (else (update annee (cdr l) l0))))

(writeln/return (update 1956
                        '((1972 . 1) (1956 . 2))
                        '((1972 . 1) (1956 . 2))))
(define (annee l)
  (if (null? l)
      '()
      (let ((premier (car l))
            (suivant (cdr l))
            (ajoute (annee suivant)))
        (update premier ajoute ajoute))))

(writeln/return (annee '(1980 1972 1972 1954 1954 1972 1958)))

(define (top-years j-list)
  ;; JAZZ-MBD -> LIST-of[INTEGER]
  (define (find-top-years alist)
    (let thru ((alist-0 alist)
               (current-maximum 0)
               (current-year-list '()))
      (if null? alist-0)
      current-year-list
      (let* ((first-association (car alist-0))
             (occ-nb (cdr first-association))
             (alist-1 (cdr alist-0)))
        (if (< occ-nb current-maximum)
            (thru alist-1 current-maximum current-year-list)
            (let ((new-year (car first-association)))
              (if (> occ-nb current-maximum)
                  (thru alist-1 occ-nb (list new-year))
                  (thru alist-1 current-maximum
                        (cons new-year current-year))))))))

  (define (update-alist alist year-0)
    (if (null? alist)
        (list (cons year-0 1))
        (let ((first (car alist))
              (rest (cdr alist)))
          (if (= (car first) year-0)
              (cons (cons year-0 (+ (cdr first) 1)) rest)
              (cons first (update-alist rest year-0))))))
  
  (let loop ((j-list-0 j-list)
             (alist-accumulator '()))
    (if (null? j-list-0)
        (find-top-years alist-accumulator)
        (loop (cdr j-list-0)
              (update-alist alist-accumulator (year (car j-list-0)))))))


(define (mergesort 1 rel-2?)
  ;; la cloture lexicale permet aux fonctions locales d'acceder à la relation d'ordre
  ;;
  (define (merge-2-groups g0 g1)
    (cond ((null? g0) g1)
          ((null? g1) g0)
          (else (let ((first-0 (car g0))
                      (first-1 (car g1)))
                  (if (rel-2? first-0 first-1)
                      (cons first-0 (merge-2-groups (cdr g0) g1))
                      (cons first-1 (merge-2-groups g0 (cdr g1 ))))))))
  ;;
  (define (merge-groups group-list)
    (if (or (null? group-list) (null? (cdr group-list)))
        group-list
        (cons (merge-2-groups (car group-list) (cadr group-list))
              (merge-groups (cddr group-list)))))
  ;;
  (define (make-groups 10)
    ;; 10 est une liste linéaire non vide
    (let ((first (car 10))
          (rest (cdr 10)))
      (if (null? rest)
          (list (list first))
          (let ((next-groups (make-groups rest)))
            (if (rel-2? first(car rest))
                (cons (cons first (car next-groups)) (cdr next-groups))
                (cons (list first) next-groups))))))
  ;;
  (if (null? 1)
      '()
      (let iter-merge-groups ((group-list (make-groups 1)))
        (if (null? (cdr group-list))
            (car group-list)
            (iter-merge-groups (merge-groups group-list))))))

(define cp-list-example '((5 . 5) (6 . 0) (3 . 3) (6 . 1) (7 . 1) (1 . 1) (6 . 2)))




                        
