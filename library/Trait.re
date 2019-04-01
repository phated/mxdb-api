type t =
  | Hero
  | Villain
  | BlueLantern
  | GreenLantern
  | IndigoTribe
  | OrangeLantern
  | RedLantern
  | SinestroCorps
  | StarSapphire
  | WhiteLantern
  | BlackLantern
  | ScoutRegiment
  | GarrisonRegiment
  | MilitaryPoliceRegiment
  | Titan
  | CadetCorps
  | Human
  | BatFamily
  | ArkhamInmate
  | RoguesGallery
  | GCPD;

module Schema = {
  open Graphql_lwt.Schema;

  let fieldName = "trait";

  let doc = "The trait of a character.";

  let typ = () =>
    non_null(
      enum(
        "Trait",
        ~doc="All traits within MetaX",
        ~values=[
          enum_value("HERO", ~value=Hero),
          enum_value("VILLAIN", ~value=Villain),
          enum_value("BLUE_LANTERN", ~value=BlueLantern),
          enum_value("GREEN_LANTERN", ~value=GreenLantern),
          enum_value("INDIGO_TRIBE", ~value=IndigoTribe),
          enum_value("ORANGE_LANTERN", ~value=OrangeLantern),
          enum_value("RED_LANTERN", ~value=RedLantern),
          enum_value("SINESTRO_CORPS", ~value=SinestroCorps),
          enum_value("STAR_SAPPHIRE", ~value=StarSapphire),
          enum_value("WHITE_LANTERN", ~value=WhiteLantern),
          enum_value("BLACK_LANTERN", ~value=BlackLantern),
          enum_value("SCOUT_REGIMENT", ~value=ScoutRegiment),
          enum_value("GARRISON_REGIMENT", ~value=GarrisonRegiment),
          enum_value(
            "MILITARY_POLICE_REGIMENT",
            ~value=MilitaryPoliceRegiment,
          ),
          enum_value("TITAN", ~value=Titan),
          enum_value("CADET_CORPS", ~value=CadetCorps),
          enum_value("HUMAN", ~value=Human),
          enum_value("BAT_FAMILY", ~value=BatFamily),
          enum_value("ARKHAM_INMATE", ~value=ArkhamInmate),
          enum_value("ROGUES_GALLERY", ~value=RoguesGallery),
          enum_value("GCPD", ~value=GCPD),
        ],
      ),
    );

  let args = () => Arg.[];

  let field = resolve =>
    field(fieldName, ~doc, ~typ=typ(), ~args=args(), ~resolve);
};
