type loaders = {
  uid: UID.Loader.t,
  rarity: Rarity.Loader.t,
};

type t = {loaders};

let make = () => {
  loaders: {
    uid: UID.Loader.make(),
    rarity: Rarity.Loader.make(),
  },
};
