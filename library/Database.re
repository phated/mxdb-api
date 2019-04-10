let connection_url = "postgresql://localhost:5432/metax";

let uri = Uri.of_string(connection_url);

// This is the connection pool we will use for executing DB operations.
let pool =
  switch (Caqti_lwt.connect_pool(~max_size=10, uri)) {
  | Ok(pool) => pool
  | Error(err) => failwith(Caqti_error.show(err))
  };

module Type = {
  include Caqti_type;

  type field(_) +=
    | StringList: field(list(string))
    | IntList: field(list(int));

  module List = {
    open Field;
    let get_coding: type a. (_, t(a)) => coding(a) =
      (_driverInfo, fieldType) =>
        switch (fieldType) {
        | StringList =>
          let encode = list => {
            Console.log(list);
            let str = "{" ++ String.concat(",", list) ++ "}";
            Console.log(str);
            Ok(str);
          };
          let decode = str =>
            try (
              Ok(
                String.split_on_char(
                  ',',
                  String.sub(str, 1, String.length(str) - 1),
                ),
              )
            ) {
            | _ => Error("Could not decode List")
            };
          Coding({rep: Caqti_type.String, encode, decode});
        | IntList =>
          let encode = list => {
            Console.log(list);
            let str =
              "{" ++ String.concat(",", List.map(string_of_int, list)) ++ "}";
            Console.log(str);
            Ok(str);
          };
          let decode = str =>
            try (
              Ok(
                List.map(
                  int_of_string,
                  String.split_on_char(
                    ',',
                    String.sub(str, 1, String.length(str) - 1),
                  ),
                ),
              )
            ) {
            | _ => Error("Could not decode List")
            };
          Coding({rep: Caqti_type.String, encode, decode});
        | _ => assert(false)
        };

    define_coding(IntList, {get_coding: get_coding});
    define_coding(StringList, {get_coding: get_coding});

    let ofInt = Caqti_type.field(IntList);
    let ofString = Caqti_type.field(StringList);
  };
};
