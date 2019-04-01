module Symbol = {
  type t =
    | Constant
    | Play
    | Push
    | Attack
    | Defend
    | None;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "symbol";

    let typ = () =>
      non_null(
        enum(
          "Symbol",
          ~values=[
            enum_value("CONSTANT", ~value=Constant),
            enum_value("PLAY", ~value=Play),
            enum_value("PUSH", ~value=Push),
            enum_value("ATTACK", ~value=Attack),
            enum_value("DEFEND", ~value=Defend),
            enum_value("NONE", ~value=None),
          ],
        ),
      );

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Text = {
  type t = option(string);

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "text";

    let typ = () => string;

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Icon = {
  type t = option(string);

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "icon";

    let typ = () => string;

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~typ=typ(), ~args=args(), ~resolve);
  };
};

type t = {
  symbol: Symbol.t,
  text: Text.t,
  icon: Icon.t,
};

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "effect";

  let doc = "The effect of the card, including symbol and text.";

  let typ = () =>
    non_null(
      obj("Effect", ~fields=_typ =>
        [
          Symbol.Schema.field((ctx, effect) => effect.symbol),
          Text.Schema.field((ctx, effect) => effect.text),
          Icon.Schema.field((ctx, effect) => effect.icon),
        ]
      ),
    );

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
