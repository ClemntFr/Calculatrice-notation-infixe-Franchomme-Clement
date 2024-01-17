all: infixe.o postfixe.o
	echo "./infixe.o -c < input.txt | ./postfixe.o -c" >> main.sh

infixe.o: infixe_2.c pile.c
	gcc infixe_2.c pile.c -o infixe.o

postfixe.o: postfixe.ml
	ocamlc postfixe.ml -o postfixe.o

clean:
	rm postfixe.cmi postfixe.cmo postfixe.o infixe.o main.sh
