module Type = {
  type t =
    | Strength
    | Intelligence
    | Special;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "type";

    let doc = "The type of a stat.";

    let typ = () =>
      non_null(
        enum(
          "StatType",
          ~doc="Stat types that are valid for a Character card.",
          ~values=[
            enum_value("STRENGTH", ~value=Strength),
            enum_value("INTELLIGENCE", ~value=Intelligence),
            enum_value("SPECIAL", ~value=Special),
          ],
        ),
      );

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Rank = {
  type t = int;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "rank";

    let doc = "The rank of a stat.";

    let typ = () => non_null(int);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Icon = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "icon";

    let doc = "The icon of for a stat. Currently only shows stat type but might include rank later";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

type t = {
  type_: Type.t,
  rank: Rank.t,
  icon: Icon.t,
};

let dummy = {type_: Strength, rank: 1, icon: "/path/to/strength-icon.png"};

module Schema = {
  open Graphql_lwt.Schema;

  let typ = () =>
    non_null(
      obj("Stat", ~doc="One stat of a Character card.", ~fields=_typ =>
        [
          Type.Schema.field((ctx, stat) => stat.type_),
          Rank.Schema.field((ctx, stat) => stat.rank),
          Icon.Schema.field((ctx, stat) => stat.icon),
        ]
      ),
    );
};
