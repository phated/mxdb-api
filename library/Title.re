type t = string;

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "title";

  let doc = "The title of the card.";

  let typ = () => non_null(string);

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
