(print (length (remove #\-
		       (remove #\Space
			       (format nil "~{~A~}"
				       (loop for i from 1 to 1000 collect (format nil "~r" i)))))))
