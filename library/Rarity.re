type t =
  | Common
  | Uncommon
  | Rare
  | XRare
  | URare
  | Promo
  | Starter;

module Schema = {
  open Graphql_lwt.Schema;
  let fieldName = "rarity";

  let doc = "The rarity of the card.";

  let typ = () =>
    non_null(
      enum(
        "Rarity",
        ~doc="Rarity of MetaX cards.",
        ~values=[
          enum_value("COMMON", ~value=Common),
          enum_value("UNCOMMON", ~value=Uncommon),
          enum_value("RARE", ~value=Rare),
          enum_value("XRARE", ~value=XRare),
          enum_value("URARE", ~value=URare),
          enum_value("PROMO", ~value=Promo),
          enum_value("STARTER", ~value=Starter),
        ],
      ),
    );

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    io_field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};

module Loader = {
  type rarity = t;
  type t = Dataloader_lwt.t(int, rarity, string);

  let load = uids => {
    Console.log("rarity loader");
    // TODO: Fix ordering
    let query =
      Caqti_request.collect(
        Database.Type.List.ofInt,
        Database.Type.string,
        "SELECT rarity FROM cards WHERE id = ANY($1);",
      );
    Database.pool
    |> Caqti_lwt.Pool.use((module C: Caqti_lwt.CONNECTION) =>
         C.fold(
           query,
           (rarity, result) =>
             switch (rarity) {
             | "COMMON" => [Common, ...result]
             | "UNCOMMON" => [Uncommon, ...result]
             | "RARE" => [Rare, ...result]
             | "XRARE" => [XRare, ...result]
             | "URARE" => [URare, ...result]
             | "PROMO" => [Promo, ...result]
             | "STARTER" => [Starter, ...result]
             | _ => result
             },
           uids,
           [],
         )
       )
    |> Lwt_result.map_err(Caqti_error.show);
  };

  let make = () => Dataloader_lwt.create(~load);
};
