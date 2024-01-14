open Queue;;
open Stack;;

(* -- Type definitions -- *)
type my_type =
    Number of float
  | Binary_op of (float->float->float)
  | Unary_op of (float->float);;


(* -- Operator checks -- *)
let is_binary = function
  "+" | "-" | "*" | "/" | "^" -> true
  | _ -> false;;

let is_unary = function
    "sqrt" | "exp" -> true
  | _ -> false;;


(* -- Computations -- *)
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

let eval str =
  let lst = precompute str in
  let pile = Stack.create () in
  let rec aux file =
    if Queue.is_empty file then Stack.pop pile
    else
      match Queue.pop file with
          (Number a) -> Stack.push a pile; aux file
        | (Binary_op f) -> let a = Stack.pop pile in
                            let b = Stack.pop pile in
                            Stack.push (f b a) pile;
                            aux file
        | (Unary_op f) ->  let a = Stack.pop pile in
                            Stack.push (f a) pile;
                            aux file
    in
  aux lst;;


(* -- A few of the tests -- *)
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


let rec listen () =
  try
    let line = read_line () in
    print_float (eval (String.sub line 0 (String.length line - 1)));
    print_newline ();
    listen ()
  with End_of_file -> ();;

let () = listen ();;
