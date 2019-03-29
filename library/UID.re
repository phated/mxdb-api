type t = string;

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "uid";

  let doc = "The unique identifier of the card.";

  let typ = () => non_null(string);

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(
      fieldName,
      ~doc,
      // TODO: scalar?
      ~typ=typ(),
      ~args=args(),
    );

  let field = resolve =>
    field(
      fieldName,
      ~doc,
      // TODO: scalar?
      ~typ=typ(),
      ~args=args(),
      ~resolve,
    );
};
