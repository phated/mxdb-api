open Graphql_lwt;

type character = {
  title: string,
  subtitle: string,
};

type event = {title: string};

let alfred = {title: "Alred", subtitle: "Butler"};
let jokes = {title: "jokes on you"};

let character =
  Schema.(
    obj("Character", ~doc="A Character Card", ~fields=a =>
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
    obj("Event", ~doc="An Event Card", ~fields=a =>
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
        "cards",
        ~doc="List of all cards",
        ~typ=non_null(list(non_null(card))),
        ~args=Arg.[],
        ~resolve=(_info, _src) =>
        [characterAsCard(alfred), eventAsCard(jokes)]
      ),
    ])
  );
