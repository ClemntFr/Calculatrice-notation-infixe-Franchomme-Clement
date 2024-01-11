# Projet-3-Info

Pour compiler:
  - exécuter la commande make

Pour effacer les fichiers .o .cmi .cmo et le .sh:
  - exécuter la commande make clean

Pour tester individuellement les fichiers ocaml et c:
  - exécuter la commande ./infixe.o pour le fichier c puis entrer une expression
    valide en notation infixe a convertir

  - exécuter la commande ./postfixe.o pour le fichier ocaml puis entrer une expression
    valide en notation postfixe a évaluer

Pour évaluer une ou plusieurs expressions en notation infixe:
  - Modifier le fichier input.txt avec les expressions a évaluer séparées par un retour a la ligne
  - Exécuter la commande sh main.sh pour toutes les évaluer
  - Le résultat de cette évaluation correspond a une expression par ligne

EX:
Si le fichier input.txt correspond le texte suivant:
4 + 6 * (5/8+1)
4 /(4+2)

le résultat sera de la forme:
résultat de 4 + 6 * (5/8+1)
résultat de 4 /(4+2)
