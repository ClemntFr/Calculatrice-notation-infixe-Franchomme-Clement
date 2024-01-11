# Projet Calculatrice Notation Infixe Franchomme Clément #

# Pour compiler l'ensemble
  - Exécuter la commande `make`

# Pour effacer les fichiers .o .cmi .cmo et .sh
  - Exécuter la commande `make clean`

# Pour tester individuellement les fichiers ocaml et c
  - Exécuter la commande `./infixe.o` puis entrer une expression
    valide en notation infixe a convertir

  - Exécuter la commande `./postfixe.o` puis entrer une expression
    valide en notation postfixe a évaluer

# Pour évaluer une ou plusieurs expressions en notation infixe
  - Modifier le fichier input.txt avec les expressions à évaluer séparées par un retour a la ligne
  - Exécuter la commande `sh main.sh` pour toutes les évaluer

# Si le fichier input.txt correspond au texte suivant
4 + 6 * (5/8+1)\
4 /(4+2)

# Le résultat sera de la forme
résultat de 4 + 6 * (5/8+1)\
résultat de 4 /(4+2)
