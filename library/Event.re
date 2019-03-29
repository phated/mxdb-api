type t = {
  uid: string,
  rarity: Rarity.t,
  expansion: Expansion.t,
  title: string,
};

let dummy = {
  uid: "456",
  rarity: Common,
  expansion: JL,
  title: "jokes on you",
};

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "Event";

  let doc = "An Event Card,";

  let typ = () =>
    obj(fieldName, ~doc, ~fields=_typ =>
      [
        UID.Schema.field((ctx, card) => card.uid),
        Rarity.Schema.field((ctx, card) => card.rarity),
        Expansion.Schema.field((ctx, card) => card.expansion),
        Title.Schema.field((ctx, card) => card.title),
      ]
    );
};
