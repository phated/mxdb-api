module Thumbnail = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "thumbnail";

    let doc = "The url to the thumbnail size of a card's image.";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Small = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "small";

    let doc = "The url to the small size of a card's image.";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Medium = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "medium";

    let doc = "The url to the medium size of a card's image.";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Large = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "large";

    let doc = "The url to the large size of a card's image.";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

module Original = {
  type t = string;

  module Schema = {
    open Graphql_lwt.Schema;

    let fieldName = "original";

    let doc = "The url to the original location of a card's image.";

    let typ = () => non_null(string);

    let args = () => Arg.[];

    let field = resolve =>
      field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
  };
};

type t = {
  thumbnail: Thumbnail.t,
  small: Small.t,
  medium: Medium.t,
  large: Large.t,
  original: Original.t,
};

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "image";

  let doc = "Urls to the different sizes of a card's image.";

  let typ = () =>
    non_null(
      obj("Image", ~fields=_typ =>
        [
          Thumbnail.Schema.field((ctx, image) => image.thumbnail),
          Small.Schema.field((ctx, image) => image.small),
          Medium.Schema.field((ctx, image) => image.medium),
          Large.Schema.field((ctx, image) => image.large),
          Original.Schema.field((ctx, image) => image.original),
        ]
      ),
    );

  let args = () => Arg.[];

  let abstract_field = () =>
    abstract_field(fieldName, ~doc, ~typ=typ(), ~args=args());

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
