#pragma once

class CXMetadata;
class CXMetadata_Messdaten
{
public:
  CXMetadata_Messdaten(void);
  ~CXMetadata_Messdaten(void);

  enum EnumBerechnungscode:long{BCODE_NONE
                         , BCODE_INPUT          // eingegeben
                         , BCODE_TRAFO_AUS_WGS  // aus wgs-punkt transformiert
                         , BCODE_TRAFO_AUS_PS   // aus projektionssystem transformiert
                         , BCODE_TACHY};        // aus tachymeterdaten

  enum EnumFestpunkt:long{FESTPUNKT_NONE=0, FESTPUNKT_LAGE=1, FESTPUNKT_HOEHE=2, FESTPUNKT_3D=3};

  enum FlagsExzenterCodes:long{GEC_NONE=0, GEC_LINKS=1, GEC_RECHTS=2, GEC_VORNE=4, GEC_HINTEN=8};
  enum EnumOrientierungscodes:long{GOC_NONE, GOC_ORI=1, GOC_EX=2, GOC_HOCH=3};

  enum EnumTrafo3D:long{TRAFO3D_NONE, TRAFO3D_HELMERT/*, TRAFO3D_MOLODENSKY*/};
  enum EnumTrafo2D:long{TRAFO2D_NONE, TRAFO2D_HELMERT, TRAFO2D_FLAECHENTREU, TRAFO2D_VERSCHIEBUNG, TRAFO2D_VERSCHIEBUNG_MASSTAB};
  enum EnumTrafo1D:long{TRAFO1D_NONE, TRAFO1D_VERSCHIEBUNG, TRAFO1D_EBENE};
  enum EnumCheckListFlags:long{GCHECK_TODO = 1, GCHECK_OK = 2, GCHECK_WARN = 3, GCHECK_ERR = 4};

	enum EnumRefStation:long{STATE_NONE, STATE_REF}; // referenzstation

  enum EnumSolution:long{PTCLASS_NONE, PTCLASS_FESTPUNKT, PTCLASS_FIXED_SOL, PTCLASS_FLOAT_SOL, PTCLASS_NAV_SOL}; // festpunkte bzw. koordinatenlösung

  enum  EnumSteuercode:long
  {
    SC_NONE = 0
    ,SC_HOCHPUNKT=1  // hochpunkt: punkt über 2 messungen bestimmt: zd, lage basispunkt
    ,SC_ZWEITPUNKT=2 // code mit zweiter zielhöhe für zweitpunkt, siehe leica, Werte.TiefeZweitLast
  };

  // hochpunkt: 1)basispunkt messen, 2) code hochpunkt setzen, 3) winkel zu hochpunkt messen
  //            es sind beliebig viele hochpunkte zu einem basispunkt möglich
  //            aus strecke zu basispunkt und zenitdistanz zu hochpunkt wird strecke zu hochpunkt zurückgerechnet und gesetzt
  //            hochpunkt flag: 0 ... nix spezielles (75)
  //                            1 ... basispunkt löschen (15)
  //                            2 ... hochpunkt bekommt nummer des basispunkte + i*10000

  // zweitpunkt: 1) punkt messen, 2) code zweitpunkt setzen, offset zielhöhe übergeben
  //            gemessener zielpunkt wird als kopie nochmals eingetragen, bezeichnung wird ergänzt, zielhöhe wird geändert

/*
  enum EnumAppType:long{APP_NONE     // nicht gesetzt
                        ,APP_UNKNOWN  // unbekannte applikation
                        ,APP_ORI
                        ,APP_FS
                        ,APP_TRAVERSE // polygonzug
                        };
*/

  void Fill(CXMetadata *meta);
};
