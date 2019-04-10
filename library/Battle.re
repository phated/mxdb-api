module StatType = {
  type t =
    | Strength
    | Intelligence
    | Special
    | Multi;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "type";

    let doc = "The type of a Battle card. Includes all Mono-types and Multi.";

    let typ = () =>
      non_null(
        enum(
          "BattleStatType",
          ~doc="The types of a Battle card.",
          ~values=[
            enum_value("STRENGTH", ~value=Strength),
            enum_value("INTELLIGENCE", ~value=Intelligence),
            enum_value("SPECIAL", ~value=Special),
            enum_value("MULTI", ~value=Multi),
          ],
        ),
      );

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module OfTypes = {
  type t = list(Stat.Type.t);

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "ofTypes";

    let doc = "Stat types that make up a Battle card.";

    let typ = () => non_null(list(Stat.Type.Schema.typ()));

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module BattleStat = {
  type t = {
    type_: StatType.t,
    rank: Stat.Rank.t,
    icon: Stat.Icon.t,
    ofTypes: OfTypes.t,
  };

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "stat";

    let doc = "The stat of a Battle card.";

    let typ = () =>
      non_null(
        obj("BattleStat", ~fields=_typ =>
          [
            StatType.Schema.field((ctx, stat) => stat.type_),
            Stat.Rank.Schema.field((ctx, stat) => stat.rank),
            Stat.Icon.Schema.field((ctx, stat) => stat.icon),
            OfTypes.Schema.field((ctx, stat) => stat.ofTypes),
          ]
        ),
      );

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

type t = {
  uid: UID.t,
  rarity: Rarity.t,
  number: Number.t,
  expansion: Expansion.t,
  type_: Type.t,
  title: Title.t,
  mp: MP.t,
  effect: Effect.t,
  stat: BattleStat.t,
  image: Image.t,
  preview: Preview.t,
};

let dummy = {
  uid: "U100-JL",
  rarity: Uncommon,
  number: 100,
  expansion: JL,
  type_: Battle,
  title: "Strength / Intelligence / Special",
  mp: 2,
  stat: {
    type_: Multi,
    rank: 4,
    icon: "/path/to/multi-icon.png",
    ofTypes: [Strength, Intelligence, Special],
  },
  effect: {
    symbol: None,
    text: None,
    icon: None,
  },
  image: {
    thumbnail: "/path/to/thumbnail.png",
    small: "/path/to/small.png",
    medium: "/path/to/medium.png",
    large: "/path/to/large.png",
    original: "/path/to/original.png",
  },
  preview: None,
};

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "Battle";

  let doc = "A Battle Card.";

  let typ = () =>
    obj(fieldName, ~doc, ~fields=_typ =>
      [
        UID.Schema.field(({ctx}: resolve_info(Ctx.t), (id, _type)) =>
          Dataloader_lwt.load(ctx.loaders.uid, id)
        ),
        Rarity.Schema.field(({ctx}: resolve_info(Ctx.t), (id, _type)) =>
          Dataloader_lwt.load(ctx.loaders.rarity, id)
        ),
        // Number.Schema.field((ctx, card) => card.number),
        // Expansion.Schema.field((ctx, card) => card.expansion),
        Type.Schema.field((info, (_id, type_)) => type_),
        // Title.Schema.field((ctx, card) => card.title),
        // MP.Schema.field((ctx, card) => card.mp),
        // Effect.Schema.field((ctx, card) => card.effect),
        // BattleStat.Schema.field((ctx, card) => card.stat),
        // Image.Schema.field((ctx, card) => card.image),
        // Preview.Schema.field((ctx, card) => card.preview),
      ]
    );
};
