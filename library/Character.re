type t = {
  uid: string,
  rarity: Rarity.t,
  expansion: Expansion.t,
  title: string,
  subtitle: string,
};

let dummy = {
  uid: "123",
  rarity: Common,
  expansion: JL,
  title: "Alred",
  subtitle: "Butler",
};

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "Character";

  let doc = "A Character Card.";

  let typ = () =>
    obj(fieldName, ~doc, ~fields=_typ =>
      [
        UID.Schema.field((ctx, card) => card.uid),
        Rarity.Schema.field((ctx, card) => card.rarity),
        Expansion.Schema.field((ctx, card) => card.expansion),
        Title.Schema.field((ctx, card) => card.title),
        Subtitle.Schema.field((ctx, card) => card.subtitle),
      ]
    );
};
