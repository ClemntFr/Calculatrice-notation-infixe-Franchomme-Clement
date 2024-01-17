open Queue;;
open Stack;;

(* -- Type definitions -- *)
type my_type =
    Number of float
  | Binary_op of (float->float->float)
  | Unary_op of (float->float);;


(* -- Vérification opérateurs -- *)
let is_binary = function
  "+" | "-" | "*" | "/" | "^" -> true
  | _ -> false;;

let is_unary = function
    "sqrt" | "exp" -> true
  | _ -> false;;


(* -- Calculs -- *)
let precompute str =
  (*
    Prend en paramètre une chaine de caractères
    sous forme d'expression postfixe.
    Ex : "4 3 + 2 *"
    Puis stocke chaque nombre et opérateur
    dans une file (lst : my_type t) 
  *)
  let pre_l = String.split_on_char ' ' str in
  let lst = Queue.create () in

  for i = 0 to List.length pre_l - 1 do
    let tmp = List.nth pre_l i in
    if is_unary tmp || is_binary tmp then 
      match tmp with
          "sqrt" -> Queue.push (Unary_op sqrt) lst
        | "exp" -> Queue.push (Unary_op exp) lst
        | "+" -> Queue.push (Binary_op (fun a b -> a +. b)) lst
        | "-" -> Queue.push (Binary_op (fun a b -> a -. b)) lst
        | "*" -> Queue.push (Binary_op (fun a b -> a *. b)) lst
        | "/" -> Queue.push (Binary_op (fun a b -> a /. b)) lst
        |  _  -> (assert false)
    else
      Queue.push (Number (float_of_string tmp)) lst
  done;
  lst;;

let check_compute q =
  (*
    Utilisé pour vérifier que la file était bien complétée
    dans la fonction precompute 
  *)
  while not (Queue.is_empty q) do
    match Queue.pop q with
        (Number x) -> print_float x; print_newline ()
      | (Binary_op f) -> print_string "Binary_op\n"
      | (Unary_op f) -> print_string "Unary_op\n"
  done;;

let eval_h str = (* Evalue une expression postfixe entrée sur une ligne *)
  let lst = precompute str in
  let stack = Stack.create () in
  let rec aux file =
    if Queue.is_empty file then Stack.pop stack
    else
      match Queue.pop file with
          (Number a) -> Stack.push a stack; aux file
        | (Binary_op f) -> let a = Stack.pop stack in
                            let b = Stack.pop stack in
                            Stack.push (f b a) stack;
                            aux file
        | (Unary_op f) ->  let a = Stack.pop stack in
                            Stack.push (f a) stack;
                            aux file
    in
  aux lst;;

let rec listen () =
  (*
    Ecoute l'entrée standard en attente d'expression a évaluer,
    une fois trouvée, l'évalue et renvoie le résultat sur la
    sortie standard
  *)
  try
    let line = read_line () in
    print_float (eval_h (String.sub line 0 (String.length line - 1)));
    print_newline ();
    listen ()
  with End_of_file -> ();;


let match_op_un (op : string) (a : float) = match op with
(* 
  Effectue l'opération associée a l'opérateur 
  unaire 'op' si possible et renvoie le résultat, 
  lève une erreur sinon 
*)
  "sqrt" -> sqrt a
| "exp"  -> exp a
|   _    -> assert false;;

let match_op_bin (op : string) (a : float) (b : float) = match op with
  (* 
    Effectue l'opération associée a l'opérateur 
    binaire 'op' si possible et renvoie le résultat, 
    lève une erreur sinon 
  *)
    "+" -> b +. a
  | "-" -> b -. a
  | "*" -> b *. a
  | "/" -> b /. a
  |  _  -> assert false;;

let manage_line line stack =
  (*
    Effectue l'opération adéquate a la chaine
    de caractère lue en entrée :
    
    - Si line est un opérateur binaire, effectue 
    l'opération sur les deux éléments du haut 
    de la pile puis rempile le résultat.
    
    - Si line est un opérateur unaire, effectue 
    l'opération sur l'élément du haut de la pile
    puis rempile le résultat.

    - Si line est une opérande, empile la valeur
    de cette dernière en nombre flottant

    - Si line = ";", on est arrivé a la fin de
    l'expression a évaluer, écrit le résultat
    sur l'entrée standard
  *)
  if line = ";" then
    begin
      print_float (Stack.pop stack);
      print_newline ();
    end
  else
    if is_binary line then
      let a = Stack.pop stack in
      let b = Stack.pop stack in
      let x = match_op_bin line a b in
      Stack.push x stack;
    else if is_unary line then
      let a = Stack.pop stack in
      let x = match_op_un line a in
      Stack.push x stack;
    else
      Stack.push (float_of_string line) stack;;

let eval_c () =
  (*
    Evalue une expression en notation postfixe entrée
    en plusieurs lignes terminée par le caractère ';'. EX:
    eval2 ();;
    3
    exp
    2
    +
    ;
    renverra le même résultat que eval "3 exp 2 + "
  *)
  let stack = Stack.create () in
  let rec aux () =
    try
      let line = read_line () in
      begin
        manage_line line stack;
        aux ()
      end
    with End_of_file -> () in
  aux ();;


let () = eval_c ();;
