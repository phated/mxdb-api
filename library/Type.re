type t =
  | Character
  | Event
  | Battle;

let fromString = str =>
  switch (str) {
  | "CHARACTER" => Character
  | "EVENT" => Event
  | "BATTLE" => Battle
  // TODO: don't fail here, use Result?
  | _ => failwith("invalid card type")
  };

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "type";

  let doc = "The MetaX card type.";

  let typ = () =>
    non_null(
      enum(
        "CardType",
        ~doc="Card types in MetaX.",
        ~values=[
          enum_value("CHARACTER", ~value=Character),
          enum_value("EVENT", ~value=Event),
          enum_value("BATTLE", ~value=Battle),
        ],
      ),
    );

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
