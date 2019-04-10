type t = string;

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "uid";

  let doc = "The unique identifier of the card.";

  let typ = () => non_null(string);

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(
      fieldName,
      ~doc,
      // TODO: scalar?
      ~typ=typ(),
      ~args=args(),
    );

  let field = resolve =>
    io_field(
      fieldName,
      ~doc,
      // TODO: scalar?
      ~typ=typ(),
      ~args=args(),
      ~resolve,
    );
};

module Loader = {
  type t = Dataloader_lwt.t(int, string, string);

  let load = uids => {
    // TODO: Fix ordering
    let query =
      Caqti_request.collect(
        Database.Type.List.ofInt,
        Database.Type.string,
        "SELECT uid FROM cards WHERE id = ANY($1);",
      );
    Database.pool
    |> Caqti_lwt.Pool.use((module C: Caqti_lwt.CONNECTION) =>
         C.collect_list(query, uids)
       )
    |> Lwt_result.map_err(Caqti_error.show);
  };

  let make = () => Dataloader_lwt.create(~load);
};
