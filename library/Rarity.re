type t =
  | Common
  | Uncommon
  | Rare
  | XRare
  | URare
  | Promo
  | Starter;

module Schema = {
  open Graphql_lwt.Schema;
  let fieldName = "rarity";

  let doc = "The rarity of the card.";

  let typ = () =>
    non_null(
      enum(
        "Rarity",
        ~doc="Rarity of MetaX cards.",
        ~values=[
          enum_value("COMMON", ~value=Common),
          enum_value("UNCOMMON", ~value=Uncommon),
          enum_value("RARE", ~value=Rare),
          enum_value("XRARE", ~value=XRare),
          enum_value("URARE", ~value=URare),
          enum_value("PROMO", ~value=Promo),
          enum_value("STARTER", ~value=Starter),
        ],
      ),
    );

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
