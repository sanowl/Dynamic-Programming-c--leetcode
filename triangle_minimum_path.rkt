; Triangle Minimum Path Sum Solutions
; LeetCode Problem 120

; Main solution for LeetCode submission - O(n) space optimized
(define (minimum-total triangle)
  (let ([n (length triangle)])
    (cond
      [(= n 0) 0]
      [(= n 1) (car (car triangle))]
      [else (minimum-total-optimized triangle)])))

; O(n) space optimized solution using bottom-up DP
(define (minimum-total-optimized triangle)
  (let* ([rows (length triangle)]
         [last-row (list-ref triangle (- rows 1))]
         [dp (list->vector last-row)])
    ; Process from second-to-last row upwards
    (for ([row-idx (in-range (- rows 2) -1 -1)])
      (let ([current-row (list-ref triangle row-idx)])
        (for ([col-idx (in-range (length current-row))])
          (let ([current-val (list-ref current-row col-idx)]
                [below-left (vector-ref dp col-idx)]
                [below-right (vector-ref dp (+ col-idx 1))])
            (vector-set! dp col-idx 
                        (+ current-val (min below-left below-right)))))))
    (vector-ref dp 0)))

; Alternative O(n²) space solution for comparison
(define (minimum-total-2d triangle)
  (let* ([n (length triangle)]
         [dp (make-vector n)])
    ; Initialize dp with copies of triangle rows
    (for ([i (in-range n)])
      (vector-set! dp i (list->vector (list-ref triangle i))))
    
    ; Fill DP table from second row onwards
    (for ([i (in-range 1 n)])
      (let ([current-row (vector-ref dp i)]
            [prev-row (vector-ref dp (- i 1))])
        (for ([j (in-range (+ i 1))])
          (let ([current-val (vector-ref current-row j)]
                [left-parent (if (= j 0) +inf.0 (vector-ref prev-row (- j 1)))]
                [right-parent (if (= j i) +inf.0 (vector-ref prev-row j))])
            (vector-set! current-row j 
                        (+ current-val (min left-parent right-parent)))))))
    
    ; Find minimum in last row
    (let ([last-row (vector-ref dp (- n 1))])
      (apply min (vector->list last-row)))))

; Top-down recursive solution with memoization
(define (minimum-total-recursive triangle)
  (let ([memo (make-hash)])
    (define (helper row col)
      (let ([key (cons row col)])
        (cond
          [(hash-has-key? memo key) (hash-ref memo key)]
          [(= row (length triangle)) 0]
          [(>= col (length (list-ref triangle row))) +inf.0]
          [else
           (let* ([current-val (list-ref (list-ref triangle row) col)]
                  [down-left (helper (+ row 1) col)]
                  [down-right (helper (+ row 1) (+ col 1))]
                  [result (+ current-val (min down-left down-right))])
             (hash-set! memo key result)
             result)])))
    (helper 0 0)))

; In-place modification solution - modifies original triangle
(define (minimum-total-inplace triangle)
  (let ([n (length triangle)])
    (cond
      [(= n 0) 0]
      [(= n 1) (car (car triangle))]
      [else
       ; Convert to mutable structure for in-place modification
       (let ([tri-vec (list->vector (map list->vector triangle))])
         ; Process from second-to-last row upwards
         (for ([row-idx (in-range (- n 2) -1 -1)])
           (let ([current-row (vector-ref tri-vec row-idx)]
                 [below-row (vector-ref tri-vec (+ row-idx 1))])
             (for ([col-idx (in-range (vector-length current-row))])
               (let ([current-val (vector-ref current-row col-idx)]
                     [below-left (vector-ref below-row col-idx)]
                     [below-right (vector-ref below-row (+ col-idx 1))])
                 (vector-set! current-row col-idx 
                             (+ current-val (min below-left below-right)))))))
         (vector-ref (vector-ref tri-vec 0) 0))])))

; Test function
(define (run-tests)
  (displayln "Testing Triangle Minimum Path Sum Solutions:")
  (newline)
  
  ; Test case 1
  (let ([triangle1 '((2) (3 4) (6 5 7) (4 1 8 3))])
    (displayln "Test 1:")
    (displayln (format "Triangle: ~a" triangle1))
    (displayln (format "O(n) space optimized: ~a" (minimum-total triangle1)))
    (displayln (format "O(n²) space solution: ~a" (minimum-total-2d triangle1)))
    (displayln (format "Recursive with memo: ~a" (minimum-total-recursive triangle1)))
    (displayln (format "In-place solution: ~a" (minimum-total-inplace triangle1)))
    (displayln "Expected: 11")
    (newline))
  
  ; Test case 2
  (let ([triangle2 '((-10))])
    (displayln "Test 2:")
    (displayln (format "Triangle: ~a" triangle2))
    (displayln (format "O(n) space optimized: ~a" (minimum-total triangle2)))
    (displayln (format "O(n²) space solution: ~a" (minimum-total-2d triangle2)))
    (displayln (format "Recursive with memo: ~a" (minimum-total-recursive triangle2)))
    (displayln (format "In-place solution: ~a" (minimum-total-inplace triangle2)))
    (displayln "Expected: -10")
    (newline))
  
  ; Test case 3 - larger triangle
  (let ([triangle3 '((1) (2 3) (4 5 6) (7 8 9 10))])
    (displayln "Test 3:")
    (displayln (format "Triangle: ~a" triangle3))
    (displayln (format "O(n) space optimized: ~a" (minimum-total triangle3)))
    (displayln (format "O(n²) space solution: ~a" (minimum-total-2d triangle3)))
    (displayln (format "Recursive with memo: ~a" (minimum-total-recursive triangle3)))
    (displayln (format "In-place solution: ~a" (minimum-total-inplace triangle3)))
    (displayln "Minimum path: 1 + 2 + 4 + 7 = 14")
    (newline))
  
  ; Performance comparison
  (displayln "Performance Analysis:")
  (displayln "- O(n) space optimized: Best space complexity, good performance")
  (displayln "- O(n²) space solution: More space but conceptually clear")  
  (displayln "- Recursive with memo: Clean code, good for understanding")
  (displayln "- In-place solution: No extra space, modifies input"))

; Helper function to visualize triangle
(define (print-triangle triangle)
  (for ([row triangle]
        [level (in-range (length triangle))])
    (let ([spaces (make-string (* 2 (- (length triangle) level 1)) #\space)])
      (display spaces)
      (for ([val row])
        (display (format "~a " val)))
      (newline))))

; Example usage and visualization
(define (demo-triangle)
  (let ([triangle '((2) (3 4) (6 5 7) (4 1 8 3))])
    (displayln "Triangle visualization:")
    (print-triangle triangle)
    (newline)
    (displayln "Path visualization for minimum sum:")
    (displayln "   2")
    (displayln "  3 4      <- choose 3")
    (displayln " 6 5 7     <- choose 5") 
    (displayln "4 1 8 3    <- choose 1")
    (displayln "Minimum path sum: 2 + 3 + 5 + 1 = 11")))

; Run all tests
(run-tests)
(newline)
(demo-triangle)