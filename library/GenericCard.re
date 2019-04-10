type t = {
  uid: string,
  rarity: string,
  number: int,
  expansion: string,
  type_: string,
};

let make = {
  let encode = ({uid, rarity, number, expansion, type_}) =>
    Ok((uid, (rarity, (number, (expansion, type_)))));
  let decode = ((uid, (rarity, (number, (expansion, type_))))) =>
    Ok({uid, rarity, number, expansion, type_});

  let rep = {
    open Caqti_type;
    let (&) = tup2;
    string & string & int & string & string;
  };
  Caqti_type.custom(~encode, ~decode, rep);
};
