type t;

open Graphql_lwt;

let card: Schema.abstract_typ(Ctx.t, t) =
  Schema.(
    interface(
      "Card", ~doc="Interface which all cards must conform to", ~fields=_typ =>
      [
        UID.Schema.abstract_field(),
        Rarity.Schema.abstract_field(),
        // Number.Schema.abstract_field(),
        // Expansion.Schema.abstract_field(),
        Type.Schema.abstract_field(),
        // Title.Schema.abstract_field(),
        // MP.Schema.abstract_field(),
        // Effect.Schema.abstract_field(),
        // Image.Schema.abstract_field(),
        // Preview.Schema.abstract_field(),
      ]
    )
  );

let characterAsCard = Schema.add_type(card, Character.Schema.typ());
let eventAsCard = Schema.add_type(card, Event.Schema.typ());
let battleAsCard = Schema.add_type(card, Battle.Schema.typ());

let schema = () =>
  Schema.(
    schema([
      io_field(
        "cards",
        ~doc="List of all cards",
        ~typ=non_null(list(non_null(card))),
        ~args=Arg.[],
        ~resolve=(info, src) => {
          let selectCards =
            Caqti_request.collect(
              Caqti_type.unit,
              Caqti_type.(tup2(int, string)),
              "SELECT id, type FROM cards;",
            );

          Database.pool
          |> Caqti_lwt.Pool.use((module C: Caqti_lwt.CONNECTION) =>
               C.collect_list(selectCards, ())
             )
          |> Lwt_result.map(rows =>
               List.fold_left(
                 (result, (id, type_)) => {
                   let card =
                     switch (Type.fromString(type_)) {
                     | Character => characterAsCard((id, Character))
                     | Event => eventAsCard((id, Event))
                     | Battle => battleAsCard((id, Battle))
                     };
                   [card, ...result];
                 },
                 [],
                 rows,
               )
             )
          |> Lwt_result.map_err(Caqti_error.show);
        },
      ),
    ])
  );
