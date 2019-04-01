module IsActive = {
  type t = bool;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "isActive";

    let doc = "Boolean indicating if the preview is active.";

    let typ = () => non_null(bool);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Previewer = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "previewer";

    let doc = "The person or site that previewed the card.";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Url = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "url";

    let doc = "The original URL where the card was previewed.";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

type preview = {
  isActive: IsActive.t,
  previewer: Previewer.t,
  url: Url.t,
};

type t = option(preview);

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "preview";

  let doc = "The preview for a card during spoiler season.";

  let typ = () =>
    obj("Preview", ~fields=_typ =>
      [
        IsActive.Schema.field((ctx, preview) => preview.isActive),
        Previewer.Schema.field((ctx, preview) => preview.previewer),
        Url.Schema.field((ctx, preview) => preview.url),
      ]
    );

  // TODO: isActive: true
  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
