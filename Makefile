infixe.o: infixe.c
	gcc infixe.c -o infixe.o

postfixe.o: postfixe.ml
	ocamlc postfixe.ml -o postfixe.o

clean:
	rm postfixe.cmi postfixe.cmo postfixe.o infixe.o