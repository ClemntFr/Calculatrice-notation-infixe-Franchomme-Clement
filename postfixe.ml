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

let match_typed_op = function 
    "sqrt" -> Unary_op sqrt
  | "exp" -> Unary_op exp
  | "+" -> Binary_op ( +. )
  | "-" -> Binary_op ( -. )
  | "*" -> Binary_op ( *. )
  | "/" -> Binary_op ( /. )
  |  _  -> assert false;;

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
  let rec aux l res = match l with
      [] -> res
    | h :: t ->
      if is_unary h || is_binary h then 
        let operator = match_typed_op h in
        let new_res = res @ [operator] in
        aux t new_res
      else
        let operand = Number (float_of_string h) in
        let new_res = res @ [operand] in
        aux t new_res 
  in
  aux pre_l [];;

let eval_h str = (* Evalue une expression postfixe entrée sur une ligne *)
  let lst = precompute str in
  let stack = Stack.create () in

  let rec aux = function
      [] -> Stack.pop stack
    | (Number a) :: t -> Stack.push a stack; aux t

    | (Binary_op f) :: t -> 
      let a =  Stack.pop stack in
      let b = Stack.pop stack in
      Stack.push (f b a) stack;
      aux t

    | (Unary_op f) :: t ->  
      let a = Stack.pop stack in
      Stack.push (f a) stack;
      aux t
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
    let x = 
      if line.[String.length line - 1] = ' ' then
        String.sub line 0 (String.length line - 1)
      else line in
    
    print_float (eval_h x);      
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
    de caractère lue en entrée
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
  (* Evalue une expression en notation postfixe ordinateur *)
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

let mod_selection str =
  if str = "-h" then
    listen ()
  else if str = "-c" then
    eval_c ()
  else
    begin
      print_string "Veuillez sélectionner un mode d'entrée valide : \n";
      print_string "\t-h Pour entrer des expressions en notation postfixe usuelle,\n";
      print_string "\t appuyez simplement sur entrée pour évaluer\n";
      print_string "\t-c Pour entrer des expressions en notation ordinateur,\n";
      print_string "\t entrez ';' puis appuyez sur entrée pour évaluer\n"
    end;;


let () =
  try
    if Array.length Sys.argv < 2 then
      mod_selection "-c"
    else
      mod_selection Sys.argv.(1)
  with _ -> print_string "Expression invalide, impossible de l'évaluer\n";;
