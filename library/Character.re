module CharacterStats = {
  type stat = {
    type_: Stat.Type.t,
    rank: Stat.Rank.t,
    icon: Stat.Icon.t,
  };

  type t = list(stat);

  let dummy = [
    {type_: Strength, rank: 1, icon: "/path/to/strength-icon.png"},
  ];

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "stats";

    let doc = "Stats of a Character card.";

    let typ = () =>
      non_null(
        list(
          non_null(
            obj(
              "CharacterStat",
              ~doc="One stat of a Character card.",
              ~fields=_typ =>
              [
                Stat.Type.Schema.field((ctx, stat) => stat.type_),
                Stat.Rank.Schema.field((ctx, stat) => stat.rank),
                Stat.Icon.Schema.field((ctx, stat) => stat.icon),
              ]
            ),
          ),
        ),
      );

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

type t = {
  uid: UID.t,
  number: Number.t,
  rarity: Rarity.t,
  expansion: Expansion.t,
  type_: Type.t,
  title: Title.t,
  subtitle: Subtitle.t,
  trait: Trait.t,
  mp: MP.t,
  stats: CharacterStats.t,
  effect: Effect.t,
  image: Image.t,
  preview: Preview.t,
};

let dummy = {
  uid: "C1-JL",
  rarity: Common,
  number: 1,
  expansion: JL,
  type_: Character,
  title: "Alred",
  subtitle: "Butler",
  trait: Hero,
  mp: 1,
  stats: CharacterStats.dummy,
  effect: {
    symbol: Push,
    text: Some("Search for character"),
    icon: Some("/path/to/effect-icon.png"),
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

  let fieldName = "Character";

  let doc = "A Character Card.";

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
        // Subtitle.Schema.field((ctx, card) => card.subtitle),
        // Trait.Schema.field((ctx, card) => card.trait),
        // MP.Schema.field((ctx, card) => card.mp),
        // CharacterStats.Schema.field((ctx, card) => card.stats),
        // Effect.Schema.field((ctx, card) => card.effect),
        // Image.Schema.field((ctx, card) => card.image),
        // Preview.Schema.field((ctx, card) => card.preview),
      ]
    );
};
