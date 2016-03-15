#include "StdAfx.h"
#include "XMetadata_Messdaten.h"
#include "xmetadata.h"

CXMetadata_Messdaten::CXMetadata_Messdaten(void)
{
}

CXMetadata_Messdaten::~CXMetadata_Messdaten(void)
{
}

void CXMetadata_Messdaten::Fill(CXMetadata *meta)
{
  meta->MetaID = _T("GMessdaten.xmeta");

  CXMetadataStruktObj *obj;

  const long createUnique = CXMetadataStruktObj::EDIT_FLAG_CREATE_UNIQUE;// rori, 02.06.2015 EDIT_FLAG_DEFAULT auf EDIT_FLAG_CREATE_UNIQUE geändert wegen messdaten-editor falls ih nicht in xml definiert ist

  // file, das root-objekt
  meta->SetRootTag(_T("FILE"));
  obj = meta->CreateStruktObj(_T("FILE"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("FILENAME_S"));// filename
    meta->StruktAddString(obj, _T("FILEPATH_S"));// pfad + filename

    meta->StruktAddObj(obj, _T("PROJ"));
    meta->StruktAddObj(obj, _T("INSTR"));
    meta->StruktAddObj(obj, _T("PKT"));
    meta->StruktAddObj(obj, _T("SPKT"));
    meta->StruktAddObj(obj, _T("WGSPKT"));
    meta->StruktAddObj(obj, _T("TRAFO_3D"));
    meta->StruktAddObj(obj, _T("TRAFO_2D"));
    meta->StruktAddObj(obj, _T("TRAFO_1D"));
    meta->StruktAddObj(obj, _T("STEUERCODE"));
    meta->StruktAddObj(obj, _T("FEHLER"));
    meta->StruktAddObj(obj, _T("WORKFLOW"));
    meta->StruktAddObj(obj, _T("APPLICATION"));
    meta->StruktAddObj(obj, _T("IMAGES"));
  }
  
  // projekt
  obj = meta->CreateStruktObj(_T("PROJ"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddString(obj, _T("KG_S"));        // KG-Nummer
    meta->StruktAddString(obj, _T("BEARBEITER_S")); // Bearbeiter
    meta->StruktAddDouble(obj, _T("HPROJ_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);      // mittlere projekthöhe
  }

  // instrument
  obj = meta->CreateStruktObj(_T("INSTR"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("INST_THEO_S"));
    meta->StruktAddString(obj, _T("INST_DIST_S"));
    meta->StruktAddString(obj, _T("INST_THEO_SERIAL_S"));
    meta->StruktAddString(obj, _T("INST_DIST_SERIAL_S"));
  }

  // punkt
  obj = meta->CreateStruktObj(_T("PKT"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddLong(obj, _T("ID_Z_L"));// id für zielung
    meta->StruktAddString(obj, _T("GUID_S"));// guid um mit berechnungen zu verknüpfen

    meta->StruktAddDouble(obj, _T("KOO_RE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KOO_HO_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KOO_H_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddString(obj, _T("CODE_S"));      // code
    meta->StruktAddString(obj, _T("STAB_S"));
    meta->StruktAddString(obj, _T("KOMM_S"));
    meta->StruktAddString(obj, _T("MS_S")); // meridianstreifen

    meta->StruktAddString(obj, _T("LC_TOPO_S"));   // topologie: liniencode für verbindung
    meta->StruktAddString(obj, _T("LC_THEM_S"));   // thematik: liniencode für layer

    meta->StruktAddDate(obj, _T("DATMESS_T"));   // messdatum
    meta->StruktAddEnum(obj, _T("FESTPUNKT_E")); // festpunkt-code
    meta->StruktAddEnum(obj, _T("BCODE_E"));     // berechnungscode

    meta->StruktAddObj(obj, _T("ATTRIBUT"));
    meta->StruktAddObj(obj, _T("INFOMESS"));
    meta->StruktAddObj(obj, _T("IMAGE_LINKS"));
  }

  // standpunkt
  obj = meta->CreateStruktObj(_T("SPKT"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddString(obj, _T("GUID_S"));// guid um mit berechnungen zu verknüpfen

    meta->StruktAddString(obj, _T("CODE_S"));      // code
    meta->StruktAddString(obj, _T("STAB_S"));
    meta->StruktAddString(obj, _T("KOMM_S"));

    meta->StruktAddDate(obj, _T("DATMESS_T"));   // messdatum

    //meta->StruktAddObj(obj, _T("SATZ"));
    meta->StruktAddObj(obj, _T("ZPKT"));
    meta->StruktAddObj(obj, _T("PKT"));
    meta->StruktAddObj(obj, _T("WGSPKT"));

    meta->StruktAddDouble(obj, _T("IH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
  	meta->StruktAddDouble(obj, _T("DRUCK_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_DRUCK);
    meta->StruktAddDouble(obj, _T("TEMPERATUR_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_TEMP);
    meta->StruktAddEnum(obj, _T("SATZMESSUNG_E"));// 0...nein (default), 1...ja
  }
/*
  // satz
  obj = meta->CreateStruktObj(_T("SATZ"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("CODE_S"));      // code
    meta->StruktAddString(obj, _T("STAB_S"));

    meta->StruktAddDouble(obj, _T("IH_D"));
  	meta->StruktAddDouble(obj, _T("DRUCK_D"));
	  meta->StruktAddDouble(obj, _T("TEMPERATUR_D"));

    meta->StruktAddDate(obj, _T("DATMESS_T"));   // messdatum

    meta->StruktAddObj(obj, _T("ZPKT"));
    meta->StruktAddObj(obj, _T("PKT"));
  }
*/
  // zielpunkt
  obj = meta->CreateStruktObj(_T("ZPKT"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddString(obj, _T("GUID_S"));// guid um mit berechnungen zu verknüpfen
    meta->StruktAddLong(obj, _T("ID_Z_L"));        // id für zielung, (z.B. zeile im messdatenfile oder zähler)
                                                   // wird verwendet, wenn aus einer zielung mehrere objekte entstehen (zpkt + pkt)

    meta->StruktAddString(obj, _T("CODE_S"));      // code
    meta->StruktAddString(obj, _T("STAB_S"));      // stabilisierung
    meta->StruktAddString(obj, _T("LC_TOPO_S"));   // topologie: liniencode für verbindung
    meta->StruktAddString(obj, _T("LC_THEM_S"));   // thematik: liniencode für layer


    meta->StruktAddDouble(obj, _T("ZH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("RI1_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);       // richtung kreislage 1
    meta->StruktAddDouble(obj, _T("RI2_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);       // richtung kreislage 2
    meta->StruktAddLong(obj, _T("RI1_CNT_L"));     // zähler bei mitteln ri kl1
    meta->StruktAddLong(obj, _T("RI2_CNT_L"));     // zähler bei mitteln ri kl2

    meta->StruktAddDouble(obj, _T("ZD1_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);       // zentiwinkel kreislage 1
    meta->StruktAddDouble(obj, _T("ZD2_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);       // zentiwinkel kreislage 2
    meta->StruktAddLong(obj, _T("ZD1_CNT_L"));     // zähler bei mitteln zd kl1
    meta->StruktAddLong(obj, _T("ZD2_CNT_L"));     // zähler bei mitteln zd kl2

    meta->StruktAddDouble(obj, _T("SS_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);        // schrägseite
    meta->StruktAddLong(obj, _T("SS_CNT_L"));      // zähler bei mitteln
    meta->StruktAddDouble(obj, _T("SH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);        // horizontalseite
    meta->StruktAddLong(obj, _T("SH_CNT_L"));      // zähler bei mitteln
    meta->StruktAddDouble(obj, _T("DH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);        // höhenunterschied
    meta->StruktAddLong(obj, _T("DH_CNT_L"));      // zähler bei mitteln

    meta->StruktAddDouble(obj, _T("IFE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);       // indexfehler
    meta->StruktAddDouble(obj, _T("ZFE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);       // zielachs-fehler
    meta->StruktAddDouble(obj, _T("EXZENTER_VH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("EXZENTER_LR_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("ADDREFL_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);   // Aditionskonstante Reflektor

  	meta->StruktAddDouble(obj, _T("DRUCK_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_DRUCK);
	  meta->StruktAddDouble(obj, _T("TEMPERATUR_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_TEMP);

    meta->StruktAddEnum(obj, _T("ORICODE_E"));
    meta->StruktAddFlags(obj, _T("EXZENTERCODE_F"));
    meta->StruktAddEnum(obj, _T("KONTROLLMESSUNG_E")); // kontrollmessung:  0...nein (default), 1...ja
    meta->StruktAddString(obj, _T("KOMM_S"));

    meta->StruktAddDate(obj, _T("DATMESS_T"));   // messdatum

    meta->StruktAddObj(obj, _T("ATTRIBUT"));
    meta->StruktAddObj(obj, _T("INFOMESS"));
    meta->StruktAddObj(obj, _T("IMAGE_LINKS"));
  }

  // wgs-punkt
  obj = meta->CreateStruktObj(_T("WGSPKT"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddString(obj, _T("GUID_S"));// guid um mit berechnungen zu verknüpfen
    
    meta->StruktAddDouble(obj, _T("KOO_PHI_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL_GEOGR);
    meta->StruktAddDouble(obj, _T("KOO_LAMDA_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL_GEOGR);// alte version mit schreibfehler
    meta->StruktAddDouble(obj, _T("KOO_LAMBDA_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL_GEOGR);

    meta->StruktAddDouble(obj, _T("KOO_H_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("KOO_X_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KOO_Y_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KOO_Z_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("ANT_H_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// ev durh "ZH_D" ersetzen, damit messdaten editor kein problem hat
    meta->StruktAddDouble(obj, _T("ANT_OFFSET_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("GEN_LAGE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL);// lage genauigkeit
    meta->StruktAddDouble(obj, _T("GEN_H_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL);// höhen-genauigkeit

    meta->StruktAddString(obj, _T("CODE_S"));      // code
    meta->StruktAddString(obj, _T("KOMM_S"));
    meta->StruktAddString(obj, _T("REF_FRAME_S"));

    meta->StruktAddEnum(obj, _T("BCODE_E"));     // berechnungscode
		meta->StruktAddEnum(obj, _T("REF_STATION_E"));// referenzstation
    meta->StruktAddEnum(obj, _T("POINTCLASS_E"));// punktklasse (

    meta->StruktAddDate(obj, _T("DATMESS_T"));   // messdatum

    meta->StruktAddObj(obj, _T("ATTRIBUT"));
    meta->StruktAddObj(obj, _T("WGSQUAL"));
    meta->StruktAddObj(obj, _T("INFOMESS"));
    meta->StruktAddObj(obj, _T("IMAGE_LINKS"));
  }

  // WGS Qualität
  obj = meta->CreateStruktObj(_T("WGSQUAL"));
  if (obj != NULL)
  {
    meta->StruktAddLong(obj, _T("NUM_SAT_L"));
    meta->StruktAddLong(obj, _T("NUM_POS_USED_L"));
    meta->StruktAddDouble(obj, _T("PDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    meta->StruktAddDouble(obj, _T("RDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    meta->StruktAddDouble(obj, _T("GDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    meta->StruktAddDouble(obj, _T("HDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    meta->StruktAddDouble(obj, _T("VDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    meta->StruktAddDouble(obj, _T("RMS_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);// Recorded in millicycles (to convert to metres divide by 1000 to get cycles and multiply by 0.19 - the L1 wavelength in metres)
    meta->StruktAddDouble(obj, _T("SIGMA_LAGE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL);
    meta->StruktAddDouble(obj, _T("SIGMA_HOEHE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL);
  }

  // Information über Messdaten
  obj = meta->CreateStruktObj(_T("INFOMESS"));
  if (obj != NULL)
  {
    meta->StruktAddDouble(obj, _T("KORR_ANT_H_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// ev durh "ZH_D" ersetzen, damit messdaten editor kein problem hat
    meta->StruktAddDouble(obj, _T("KORR_ANT_OFFSET_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddString(obj, _T("KORR_ANT_NAME_S"), createUnique);   // Name Antenne
    meta->StruktAddDouble(obj, _T("KORR_IH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KORR_ZH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KORR_OFFSET_LENGTH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KORR_OFFSET_RIGHT_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

  	meta->StruktAddDouble(obj, _T("KORR_DRUCK_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_DRUCK);
    meta->StruktAddDouble(obj, _T("KORR_TEMPERATUR_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_TEMP);
    meta->StruktAddDouble(obj, _T("KORR_TEMP_DRY_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_TEMP);
    meta->StruktAddDouble(obj, _T("KORR_TEMP_WET_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_TEMP);
    meta->StruktAddDouble(obj, _T("KORR_REFLADD_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL);   // Aditionskonstante Reflektor
    meta->StruktAddString(obj, _T("KORR_REFLNAME_S"), createUnique);   // Name Reflektor
    meta->StruktAddString(obj, _T("EDM_KIND_S"), createUnique);
    meta->StruktAddString(obj, _T("EDM_MODE_S"), createUnique);
    meta->StruktAddDouble(obj, _T("REF_RADIUS_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("REF_KOEFF_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    meta->StruktAddDouble(obj, _T("KORR_PPM_ATM_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_PPM);
    meta->StruktAddDouble(obj, _T("KORR_PPM_PROJ_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_PPM);
    meta->StruktAddDouble(obj, _T("KORR_PPM_HEIGHT_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_PPM);
    meta->StruktAddDouble(obj, _T("KORR_PPM_USER_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_PPM);


    //meta->StruktAddLong(obj, _T("NUM_SAT_L"));
    //meta->StruktAddLong(obj, _T("NUM_POS_USED_L"));
    //meta->StruktAddDouble(obj, _T("PDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    //meta->StruktAddDouble(obj, _T("RDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    //meta->StruktAddDouble(obj, _T("GDOP_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);
    //meta->StruktAddDouble(obj, _T("RMS_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_FAKTOR1);// Recorded in millicycles (to convert to metres divide by 1000 to get cycles and multiply by 0.19 - the L1 wavelength in metres)
    //meta->StruktAddDouble(obj, _T("SIGMA_LAGE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL);
    //meta->StruktAddDouble(obj, _T("SIGMA_HOEHE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL);
  }


  // trafo 3D
  obj = meta->CreateStruktObj(_T("TRAFO_3D"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddEnum(obj, _T("TYP_E"));// derzeit nicht verwendet

    meta->StruktAddDouble(obj, _T("X0_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE); // Drehpunkt
    meta->StruktAddDouble(obj, _T("Y0_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE); // Drehpunkt
    meta->StruktAddDouble(obj, _T("Z0_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE); // Drehpunkt
    
    meta->StruktAddDouble(obj, _T("ROTX_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL_SMALL_HP);// Rotation um X-Achse
    meta->StruktAddDouble(obj, _T("ROTY_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL_SMALL_HP);// Rotation um Y-Achse
    meta->StruktAddDouble(obj, _T("ROTZ_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL_SMALL_HP);// Rotation um Z-Achse

    meta->StruktAddDouble(obj, _T("DX_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// Verschiebung X
    meta->StruktAddDouble(obj, _T("DY_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// Verschiebung Y
    meta->StruktAddDouble(obj, _T("DZ_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// Verschiebung Z
    meta->StruktAddDouble(obj, _T("M_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_PPM); //Masstab

    meta->StruktAddString(obj, _T("REF_FRAME_S"));

    meta->StruktAddObj(obj, _T("PASSPUNKT"));
  }

  // trafo 2D
  obj = meta->CreateStruktObj(_T("TRAFO_2D"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddEnum(obj, _T("TYP_2D_E"));

    meta->StruktAddDouble(obj, _T("RE0_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// ursprung
    meta->StruktAddDouble(obj, _T("HO0_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// ursprung

    meta->StruktAddDouble(obj, _T("DRE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// verschiebung
    meta->StruktAddDouble(obj, _T("DHO_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// verschiebung

    meta->StruktAddDouble(obj, _T("ROT_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL_SMALL);// drehung um ursprung
    meta->StruktAddDouble(obj, _T("M_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_PPM);// masstab

    meta->StruktAddObj(obj, _T("PASSPUNKT"));
  }

  // trafo 1D
  obj = meta->CreateStruktObj(_T("TRAFO_1D"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddEnum(obj, _T("TYP_1D_E"));
    meta->StruktAddDouble(obj, _T("RE0_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// ursprung
    meta->StruktAddDouble(obj, _T("HO0_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// ursprung

    meta->StruktAddDouble(obj, _T("DH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// verschiebung

    // geneigte ebene für höhe
    meta->StruktAddDouble(obj, _T("SLOPE_HO_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// slope nord
    meta->StruktAddDouble(obj, _T("SLOPE_RE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);// slope ost

    meta->StruktAddObj(obj, _T("PASSPUNKT"));
  }

  obj = meta->CreateStruktObj(_T("PASSPUNKT"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_SOURCE_S"));// z.B. BezWgs;
    meta->StruktAddString(obj, _T("BEZ_TARGET_S"));// z.B. BezGk;
    
    meta->StruktAddEnum(obj, _T("DIM_E"));// 0, 1, 2, 3  0... nicht verwendet

    // klaffung 3D, nur bei DIM == 3
    meta->StruktAddDouble(obj, _T("KLAFF_X_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL); //3D: X
    meta->StruktAddDouble(obj, _T("KLAFF_Y_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL); //3D: Y
    meta->StruktAddDouble(obj, _T("KLAFF_Z_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL); //3D: Z

    // klaffung 2D, nur bei DIM == 2
    meta->StruktAddDouble(obj, _T("KLAFF_RE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL); //2D: Rechts
    meta->StruktAddDouble(obj, _T("KLAFF_HO_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL); //2D: Hoch

    // klaffung 1D, nur bei DIM == 1
    meta->StruktAddDouble(obj, _T("KLAFF_H_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE_SMALL); //1D: H
  }

  obj = meta->CreateStruktObj(_T("GPSVEK"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("BEZ_A_S"));
    meta->StruktAddString(obj, _T("BEZ_E_S"));
    
    meta->StruktAddString(obj, _T("CODE_A_S"));      // code
    meta->StruktAddString(obj, _T("CODE_E_S"));      // code

    meta->StruktAddDouble(obj, _T("ANT_H_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("ANT_OFFSET_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("ANT_H_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("ANT_OFFSET_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("DX_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("DY_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("DZ_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("KOO_X_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KOO_Y_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("KOO_Z_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("S0_D"));
    meta->StruktAddDouble(obj, _T("Q11_D"));
    meta->StruktAddDouble(obj, _T("Q12_D"));
    meta->StruktAddDouble(obj, _T("Q13_D"));
    meta->StruktAddDouble(obj, _T("Q22_D"));
    meta->StruktAddDouble(obj, _T("Q23_D"));
    meta->StruktAddDouble(obj, _T("Q33_D"));

    meta->StruktAddString(obj, _T("KOMM_S"));

    meta->StruktAddDate(obj, _T("DATMESS_T"));   // messdatum
  }

  // steuercode. z.b. "hochpunkt"
  obj = meta->CreateStruktObj(_T("STEUERCODE"));
  if (obj != NULL)
  {
    meta->StruktAddEnum(obj, _T("STEUERCODE1_E"));
    meta->StruktAddDouble(obj, _T("VALUE1_D"));
    meta->StruktAddLong(obj, _T("VALUE1_L"));
    meta->StruktAddString(obj, _T("VALUE1_S"));
  }

  obj = meta->CreateStruktObj(_T("ATTRIBUT"));
  if (obj != NULL)
  {
    meta->StruktAddLong(obj, _T("ID_L"));
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddString(obj, _T("WERT_S"));
  }

  obj = meta->CreateStruktObj(_T("FEHLER"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("TEXT_S"));
  }

  obj = meta->CreateStruktObj(_T("WORKFLOW"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("CMD_S"));
    meta->StruktAddString(obj, _T("BEZ_S"));
    meta->StruktAddEnum(obj, _T("CHECKLIST_FLAG_E"));
    meta->StruktAddString(obj, _T("TEXT_S"));
  }

  // Programm
  obj = meta->CreateStruktObj(_T("APPLICATION"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("NAME_S"), createUnique);
    meta->StruktAddString(obj, _T("INFO_S"), createUnique);

    meta->StruktAddObj(obj, _T("TACHY_STATION"));
    meta->StruktAddString(obj, _T("APP_CMD_S"), createUnique);
    meta->StruktAddString(obj, _T("SOURCE_S"), createUnique);
    meta->StruktAddDate(obj, _T("TIMESTAMP_T"), createUnique);
  }

  // TPS Aufstellung
  obj = meta->CreateStruktObj(_T("TACHY_STATION"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("NAME_S"), createUnique);
    meta->StruktAddDouble(obj, _T("ORI_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);
    meta->StruktAddDouble(obj, _T("MORI_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);

    meta->StruktAddDouble(obj, _T("RE_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("HO_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("H_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddObj(obj, _T("TACHY_TARGET"));
  }

  // TPS Zielpunkt
  obj = meta->CreateStruktObj(_T("TACHY_TARGET"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("NAME_S"));
    meta->StruktAddObj(obj, _T("TACHY_OBS_RI"));
    meta->StruktAddObj(obj, _T("TACHY_OBS_RIS"));
  }

  // TPS Observation
  obj = meta->CreateStruktObj(_T("TACHY_OBS_RI"));
  if (obj != NULL)
  {
    //meta->StruktAddString(obj, _T("NAME_S"));
    meta->StruktAddString(obj, _T("GUID_S"));

    meta->StruktAddDouble(obj, _T("T_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);
    meta->StruktAddDouble(obj, _T("SH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("DH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("RE_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("HO_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("H_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("RE_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("HO_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("H_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
  }

  // TPS Observation
  obj = meta->CreateStruktObj(_T("TACHY_OBS_RIS"));
  if (obj != NULL)
  {
    //meta->StruktAddString(obj, _T("NAME_S"));
    meta->StruktAddString(obj, _T("GUID_S"));

    meta->StruktAddDouble(obj, _T("T_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_WINKEL);
    meta->StruktAddDouble(obj, _T("SH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("DH_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);

    meta->StruktAddDouble(obj, _T("RE_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("HO_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("H_A_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("RE_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("HO_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
    meta->StruktAddDouble(obj, _T("H_E_D"), createUnique, CXMetadataStruktObj::TYPE_FLAG_D_STRECKE);
  }

  // Bilder
  obj = meta->CreateStruktObj(_T("IMAGES"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("IMAGEPATH_S"), createUnique);
    meta->StruktAddObj(obj, _T("IMAGE"));
  }

  // Bild
  obj = meta->CreateStruktObj(_T("IMAGE"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("KEY_S"), createUnique);// filename vermutlich besser als guid
    meta->StruktAddString(obj, _T("IMAGEFILE_S"), createUnique);
//    meta->StruktAddString(obj, _T("NAME_S"), createUnique);
    meta->StruktAddString(obj, _T("KOMM_S"), createUnique);
    meta->StruktAddDate(obj, _T("TIMESTAMP_T"), createUnique);

    //meta->StruktAddObj(obj, _T("LINKS"));// - doch nicht. verlinke nur obj->image aber nicht umgekehrt
  }

  // Links zu images ganz allgemein über GUID
  obj = meta->CreateStruktObj(_T("IMAGE_LINKS"));
  if (obj != NULL)
  {
    meta->StruktAddObj(obj, _T("LINK"));
  }

  // Link ganz allgemeint über GUID
  obj = meta->CreateStruktObj(_T("LINK"));
  if (obj != NULL)
  {
    meta->StruktAddString(obj, _T("KEY_S"), createUnique);
  }

  // festlegen enums, flags
  meta->ValuesSetListLong(_T("ORICODE_E"), GOC_NONE, GOC_ORI, GOC_EX, GOC_HOCH);
  meta->ValuesSetListLong(_T("EXZENTERCODE_F"), GEC_NONE, GEC_LINKS, GEC_RECHTS, GEC_VORNE, GEC_HINTEN);
  meta->ValuesSetListLong(_T("SATZMESSUNG_E"), 0, 1);// 0...nein (default), 1...ja
  meta->ValuesSetListLong(_T("STEUERCODE1_E"), SC_NONE, SC_HOCHPUNKT, SC_ZWEITPUNKT);
  meta->ValuesSetListLong(_T("USECOAXOFFSET_E"), 0, 1);// 1... ein
  meta->ValuesSetListLong(_T("FESTPUNKT_E"), FESTPUNKT_NONE, FESTPUNKT_LAGE, FESTPUNKT_HOEHE, FESTPUNKT_3D);
  meta->ValuesSetListLong(_T("CHECKLIST_FLAG_E"), GCHECK_TODO, GCHECK_OK, GCHECK_ERR, GCHECK_WARN); 

  // transformationen
  meta->ValuesSetListLong(_T("TYP_3D_E"), TRAFO3D_NONE, TRAFO3D_HELMERT/*, TRAFO3D_MOLODENSKY*/);
  meta->ValuesSetListLong(_T("TYP_2D_E"), TRAFO2D_NONE, TRAFO2D_HELMERT, TRAFO2D_FLAECHENTREU);
  meta->ValuesSetListLong(_T("TYP_1D_E"), TRAFO1D_NONE, TRAFO1D_VERSCHIEBUNG, TRAFO1D_EBENE);
  meta->ValuesSetListLong(_T("DIM_E"), 0, 1, 2, 3);

  // berechnungscodes
  meta->ValuesSetListLong(_T("BCODE_E"), BCODE_NONE, BCODE_INPUT, BCODE_TRAFO_AUS_WGS, BCODE_TRAFO_AUS_PS, BCODE_TACHY); 

  meta->ValuesSetListLong(_T("REF_STATION_E"), STATE_NONE, STATE_REF); 

  meta->ValuesSetListLong(_T("POINTCLASS_E"), PTCLASS_NONE, PTCLASS_FESTPUNKT, PTCLASS_FIXED_SOL, PTCLASS_FLOAT_SOL, PTCLASS_NAV_SOL); 
}