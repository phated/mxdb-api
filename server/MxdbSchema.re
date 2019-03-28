open Graphql_lwt;
// let card: Schema.abstract_typ(unit, [ | `Card]) =
//   Schema.union(~doc="The union of a card type", "card");

type character = {
  title: string,
  subtitle: string,
};

type event = {title: string};

let alfred = {title: "Alred", subtitle: "Butler"};
let jokes = {title: "jokes on you"};

let card_type =
  Schema.(
    Arg.enum(
      "card_type",
      ~values=[
        enum_value("CHARACTER", ~value=`Character),
        enum_value("EVENT", ~value=`Event),
      ],
    )
  );

let character =
  Schema.(
    obj(~doc="A Character Card", "Character", ~fields=a =>
      [
        field(
          "title",
          ~doc="The title!",
          ~typ=non_null(string),
          ~args=Arg.[],
          ~resolve=(ctx, character) =>
          alfred.title
        ),
        field(
          "subtitle",
          ~doc="The subtitle!",
          ~typ=non_null(string),
          ~args=Arg.[],
          ~resolve=(ctx, character) =>
          alfred.subtitle
        ),
      ]
    )
  );

let event =
  Schema.(
    obj(~doc="An Event Card", "Event", ~fields=a =>
      [
        field(
          "title",
          ~doc="The title!",
          ~typ=non_null(string),
          ~args=Arg.[],
          ~resolve=(ctx, event) => {
            Console.log("event title resolver");
            jokes.title;
          },
        ),
      ]
    )
  );

let card: Schema.abstract_typ(unit, [ | `Card]) =
  Schema.(
    interface(
      "Card", ~doc="Interface which all cards must conform to", ~fields=_typ =>
      [
        abstract_field(
          "title",
          ~doc="The title of the card",
          ~typ=non_null(string),
          ~args=Arg.[],
        ),
      ]
    )
  );

let characterAsCard = Schema.(add_type(card, character));
let eventAsCard = Schema.(add_type(card, event));

let make = () =>
  Schema.(
    schema([
      field(
        "card",
        ~typ=non_null(card),
        ~args=Arg.[arg("type", ~typ=non_null(card_type))],
        ~resolve=(ctx, (), card_type) =>
        switch (card_type) {
        | `Character => characterAsCard(alfred)
        | `Event => eventAsCard(jokes)
        }
      ),
      field(
        "cards",
        ~doc="A card",
        ~typ=non_null(list(non_null(card))),
        ~args=Arg.[],
        ~resolve=(_info, _src) =>
        [characterAsCard(alfred), eventAsCard(jokes)]
      ),
    ])
  );

// Console.log(ctx);
// let {alias, name, arguments, directives, selection_set}: Graphql_parser.field = field;
// Console.log(alias);
// Console.log(name);
// Console.log(arguments);
// Console.log(directives);
// Console.log(selection_set);
// Console.log(fragments);
// Console.log(variables);
// Console.log(src);
// selection_set
// |> List.map(selection =>
//      switch (selection) {
//      | Graphql_parser.Field(field) => Console.log("field")
//      | FragmentSpread(fragment_spread) =>
//        Console.log("fragment spread")
//      | InlineFragment(inline_fragment) =>
//        Console.log("Inline fragment");
//        Console.log(inline_fragment);
//      //  if (inline_fragment.type_condition === Some)
//      }
//    )
// |> ignore;
