(defun day-of-week (day month year)
    "Returns the day of the week as an integer.  Monday is 0."
    (nth-value
     6
     (decode-universal-time
      (encode-universal-time 0 0 0 day month year 0)
      0)))

(print (loop for y from 1901 to 2000 sum
	     (loop for m from 1 to 12 sum
		   (if (eq 6 (day-of-week 1 m y))
		       1
		     0))))


