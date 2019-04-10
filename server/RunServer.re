open Graphql_lwt;

let schema = Mxdb.Card.schema();

module Graphql_cohttp_lwt =
  Graphql_cohttp.Make(Schema, Cohttp_lwt_unix.IO, Cohttp_lwt.Body);

let on_exn =
  fun
  | Unix.Unix_error(error, func, arg) =>
    Logs.warn(m =>
      m(
        "Client connection error %s: %s(%S)",
        Unix.error_message(error),
        func,
        arg,
      )
    )
  | exn => Logs.err(m => m("Unhandled exception: %a", Fmt.exn, exn));

let callback =
  Graphql_cohttp_lwt.make_callback(_req => Mxdb.Ctx.make(), schema);
let server = Cohttp_lwt_unix.Server.make_response_action(~callback, ());
let mode = `TCP(`Port(8080));
let () =
  Cohttp_lwt_unix.Server.create(~on_exn, ~mode, server) |> Lwt_main.run;
