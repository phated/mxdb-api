type t =
  | Card;

open Graphql_lwt;

let card: Schema.abstract_typ(unit, t) =
  Schema.(
    interface(
      "Card", ~doc="Interface which all cards must conform to", ~fields=_typ =>
      [
        UID.Schema.abstract_field(),
        Rarity.Schema.abstract_field(),
        Expansion.Schema.abstract_field(),
        Title.Schema.abstract_field(),
      ]
    )
  );

let characterAsCard = Schema.add_type(card, Character.Schema.typ());
let eventAsCard = Schema.add_type(card, Event.Schema.typ());

let schema = () =>
  Schema.(
    schema([
      field(
        "cards",
        ~doc="List of all cards",
        ~typ=non_null(list(non_null(card))),
        ~args=Arg.[],
        ~resolve=(_info, _src) =>
        [characterAsCard(Character.dummy), eventAsCard(Event.dummy)]
      ),
    ])
  );
