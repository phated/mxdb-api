type t = {
  uid: UID.t,
  rarity: Rarity.t,
  number: Number.t,
  expansion: Expansion.t,
  type_: Type.t,
  title: Title.t,
  mp: MP.t,
  effect: Effect.t,
  image: Image.t,
  preview: Preview.t,
};

let dummy = {
  uid: "C66-JL",
  rarity: Common,
  number: 66,
  expansion: JL,
  type_: Event,
  title: "jokes on you",
  mp: (-1),
  effect: {
    symbol: None,
    text: Some("win the game."),
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

  let fieldName = "Event";

  let doc = "An Event Card.";

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
        // Image.Schema.field((ctx, card) => card.image),
        // Preview.Schema.field((ctx, card) => card.preview),
      ]
    );
};
