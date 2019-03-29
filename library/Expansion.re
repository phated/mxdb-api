type t =
  | JL
  | GL
  | AT
  | BM
  | TT;

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "expansion";

  let doc = "The expansion the card belongs to.";

  let typ = () =>
    non_null(
      enum(
        "Expansion",
        ~doc="Expansions in MetaX.",
        ~values=[
          enum_value("JL", ~doc="Justice League (Set 1)", ~value=JL),
          enum_value("GL", ~doc="Green Lantern (Set 2)", ~value=GL),
          enum_value("AT", ~doc="Attack on Titan (Set 3)", ~value=AT),
          enum_value("BM", ~doc="Batman (Set 4)", ~value=BM),
          enum_value("TT", ~doc="Teen Titans Go (Set 5)", ~value=TT),
        ],
      ),
    );

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
