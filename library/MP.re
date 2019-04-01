type t = int;

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "mp";

  let doc = "The MetaPoint the card gains or costs.";

  let typ = () => non_null(int);

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
