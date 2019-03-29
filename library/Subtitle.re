type t = string;

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "subtitle";

  let doc = "The subtitle of a character.";

  let typ = () => non_null(string);

  let args = () => Arg.[];

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
