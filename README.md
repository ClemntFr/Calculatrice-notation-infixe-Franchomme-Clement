# Projet Calculatrice Notation Infixe Franchomme Clément #

Pour l'instant il est uniquement possible de convertir et
évaluer des expressions valides.

Les opérateurs supportés en notation infixe sont : '+'; '-'; '*'; '/'; 'e'; 's'; '('; ')' \
ou 'e' et 's' correspondent respectivement aux fonctions exponentielles et racine carrée.

Les opérateurs supportés en notation postfixe sont : '+'; '-'; '*'; '/'; 'exp'; 'sqrt'

# Pour compiler l'ensemble
  - Exécuter la commande `make`
  - Il est possible de spécifier le mode d'évaluation en ajoutant un `h` ou un `c` à la suite du `make`

# Pour effacer les fichiers .o .cmi .cmo et .sh
  - Exécuter la commande `make clean`

# Pour tester individuellement les fichiers ocaml et c
  - Exécuter la commande `./infixe.o -h` puis entrer une expression pour avoir un résultat en notation postfixe lisible par un humain
  - Exécuter la commande `./infime.o -c` puis entrer une expression pour avoir un résultat en notation postface optimisé pour une évaluation faite par l'ordinateur
  - Exécuter la commande `./postfixe.o -h` puis entrer une expression en notation postfixe usuelle pour l'évaluer
  - Exécuter la commande `./postfixe.o -c` puis entrer une expression en notation postfixe "ordinateur" pour l'évaluer

# Pour évaluer une ou plusieurs expressions directement depuis leur notation infixe
  - Modifier le fichier input.txt avec les expressions à évaluer séparées par un retour a la ligne
  - Exécuter la commande `sh main.sh` pour toutes les évaluer
  - Il est possible de spécifier le mode d'évaluation avant la compilation uniquement, le fichier `main.sh` utilisera le mode choisit par l'utilisateur lors de la compilation pour évaluer les expressions du fichier `input.txt`

# Si le fichier input.txt correspond au texte suivant
4 + 6 * (5/8+1)\
4 /(4+2)

# Le résultat sera de la forme
résultat de 4 + 6 * (5/8+1)\
résultat de 4 /(4+2)
