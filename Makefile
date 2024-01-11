all: infixe.o postfixe.o
	echo "./infixe.o < input.txt | ./postfixe.o" >> main.sh

infixe.o: infixe.c
	gcc infixe.c -o infixe.o

postfixe.o: postfixe.ml
	ocamlc postfixe.ml -o postfixe.o

clean:
	rm postfixe.cmi postfixe.cmo postfixe.o infixe.o main.sh