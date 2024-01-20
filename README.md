# Projet Calculatrice Notation Infixe Franchomme Clément #

Avant toute chose je tient a préciser qu'il est uniquement possible d'évaluer des expressions valides.
Toute tentative d'évaluation d'une expression invalide
risque de causer une erreur.

# Différentes notations et opérateurs

Lors de la compilation, l'utilisateur sera interrogé quand au mode de retour \
du fichier infixe.o et au mode d'entrée du fichier postfixe.o.

Ces derniers correspondent a deux notations disponnibles a l'utilisateur quand a l'affichage des expressions postfixe.

Le premier est le mode `-h` (i.e human). Chaque opérande et opérateur est séparé par
un espace et chaque expression par un retour a la ligne. \
Le second est le mode `-c` (i.e computer). Chaque opérande et opérateur est séparé par un retour à la ligne et la fin d'une expression est marquée par un `;`. 

Cette notation permet d'évaluer les expressions en une unique passe sur la
chaine de caractère, elle a cependant le désaventage d'être moins lisible pour un humain. C'est à cet effet que le mode humain est implémenté.

Si cela est nécessaire il est possible de récupérer les expressions en notation postfixe usuelle en compilant avec le flag `-h`, cela ajoute cependant une complexité spatiale non négligeable sur de grandes entrées.

Les opérateurs supportés en notation infixe sont : '+'; '-'; '*'; '/'; 'e'; 's'; '('; ')' \
ou 'e' et 's' correspondent respectivement à la fonction exponentielle et racine carrée.

Les opérateurs supportés en notation postfixe sont : '+'; '-'; '*'; '/'; 'exp'; 'sqrt'

# Pour compiler l'ensemble
  - Exécuter la commande `make`
  - Il est possible de spécifier le mode d'évaluation avec `make h` ou `make c`, en l'absence de flag le mode sera mis a `-c` par défaut.

# Pour effacer les fichiers .o .cmi .cmo et .sh
  - Exécuter la commande `make clean`

# Pour tester individuellement les fichiers ocaml et c
  - Exécuter la commande `./infixe.o -h` puis entrer une expression pour avoir un résultat en notation postfixe lisible par un humain
  - Exécuter la commande `./infixe.o -c` puis entrer une expression pour avoir un résultat en notation postfixe optimisé pour une évaluation faite par l'ordinateur
  - Exécuter la commande `./postfixe.o -h` puis entrer une expression en notation postfixe usuelle pour l'évaluer
  - Exécuter la commande `./postfixe.o -c` puis entrer une expression en notation postfixe "ordinateur" pour l'évaluer
  - En l'absence de précision quand au mode, ce dernier sera mis automatiquement a `-c` sur le fichier concerné

# Pour évaluer une ou plusieurs expressions directement depuis leur notation infixe
  - Modifier le fichier input.txt avec les expressions à évaluer séparées par un retour a la ligne
  - Exécuter la commande `sh main.sh` pour toutes les évaluer
  - Il est possible de spécifier le mode d'évaluation avant la compilation uniquement, le fichier `main.sh` utilisera le mode choisit par l'utilisateur lors de la compilation pour évaluer les expressions du fichier `input.txt`

Si le fichier input.txt correspond au texte suivant :
$$
\begin{align*}
&4 + 6 * (5/8+1) \\
&4 /(4+2)
\end{align*}
$$

Le résultat sera de la forme :
$$
\begin{align*}
&\text{résultat de } 4 + 6 * (5/8+1) \\
&\text{résultat de } 4 /(4+2)
\end{align*}
$$
