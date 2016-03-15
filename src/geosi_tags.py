#!/usr/bin/python2.7

import xml.etree.ElementTree as ET
from abc import ABCMeta
from abc import abstractproperty
import datetime


class XMLTag(object):
    
    @staticmethod
    def create_tag_default(tag_name, tag_default=None):
        """
        
        :param tag_name: 
        :param tag_default: 
        :return: dict with "tag" and "default"
        :rtype: dict
        """
        return {"tag": tag_name, "default": tag_default}


class GeosiObject(object):

    """

    """

    __metaclass__ = ABCMeta

    OBJECT_COUNTER = 0

    def __init__(self, kwargs):
        self.id = self.OBJECT_COUNTER + 1
        GeosiObject.OBJECT_COUNTER += 1
        self.init_attributes(**kwargs)

    def get_xml(self):
        """
        :return: ET.Element of this class
        :rtype: ET.Element
        """
        et = ET.Element(tag=self.get_tag_name,
                        attrib={"ID": self.OBJECT_COUNTER})
        for child in self.get_children("child"):
            et.set(child, self.__getattribute__(child.lower()))
        return et

    @abstractproperty
    def get_tag_name(self):
        pass

    @abstractproperty
    def get_children(self):
        """
        contains tagname and default value as dict
        Example:
            {"child": [{
                            "tag": TAG_NAME_1,
                            "default" : DEFAULT_VALUE_1
                       },
                       {
                            "tag": TAG_NAME_2,
                            "default": DEFAULT_VALUE_2
                       }
            }
        :rtype: dict
        """
        pass

    def init_attributes(self, **kwargs):
        for attribute in self.get_children("child"):
            self.__setattr__(attribute.lower(),
                             kwargs.get(attribute, default=None))


class File(GeosiObject):
    """
    """
    def get_tag_name(self):
        return "FILE"

    def get_children(self):
        file_name = "geosi.xml"
        file_path = "./" + file_name
        return {"child": [
            XMLTag.create_tag_default("FILENAME_S", file_name),
            XMLTag.create_tag_default("FILEPATH_S", file_path),
        ]}


class Project(GeosiObject):
    """

    """
    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("KG_S"),
            XMLTag.create_tag_default("BEARBEITER_S", "JF"),
            XMLTag.create_tag_default("BEZ_S", "Geosi Project"),
        ]}

    def get_tag_name(self):
        return "PROJ"


class Instrument(GeosiObject):
    """

    """
    def get_children(self):
        theo_name = "Leica TPS"
        dist_name = theo_name
        theo_serial = "123456"
        dist_serial = theo_serial
        return {"child": [
            XMLTag.create_tag_default("THEO_S", theo_name),
            XMLTag.create_tag_default("DIST_S", dist_name),
            XMLTag.create_tag_default("THEO_SERIAL_S", theo_serial),
            XMLTag.create_tag_default("DIST_SERIAL_S", dist_serial),
        ]}

    def get_tag_name(self):
        return "INSTR"


class Standpunkt(GeosiObject):
    """

    """
    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("BEZ_S"),
            XMLTag.create_tag_default("CODE_S"),
            XMLTag.create_tag_default("IH_D", 0.0),
            XMLTag.create_tag_default("DRUCK_D", 1013.),
            XMLTag.create_tag_default("TEMPERATUR_D", 12.),
            XMLTag.create_tag_default("DATMESS_T", datetime.datetime.now().strftime("%y-%m-%d %H:%M")),            
        ]}

    def get_tag_name(self):
        return "SPKT"


class TachyObsRis(GeosiObject):
    """
    """
    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("GUID_S"),
            XMLTag.create_tag_default("RE_A_D"),
            XMLTag.create_tag_default("HO_A_D"),
            XMLTag.create_tag_default("H_A_D"),
            XMLTag.create_tag_default("RE_E_D"),
            XMLTag.create_tag_default("HO_E_D"),
            XMLTag.create_tag_default("H_E_D"),
        ]}

    def get_tag_name(self):
        return "TACHY_OBS_RIS"


class TachyTarget(GeosiObject):
    """
    """
    def __init__(self, **kwargs):
        self.tachy_obs_ris = kwargs.get("tachy_obs_ris", default=TachyObsRis())
        super(TachyTarget, self).__init__(**kwargs)
    
    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("NAME_S"),
        ]}
    

    def get_xml(self):
        et = super(TachyTarget, self).get_xml()
        et.append(self.tachy_obs_ris.get_xml())
        return et

    def get_tag_name(self):
        return "TACHY_TARGET"


class TachyStation(GeosiObject):
    """
    """
    def __init__(self, **kwargs):
        super(TachyStation, self).__init__(**kwargs)
        self.tachy_target_list = []

    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("NAME_S"),
            XMLTag.create_tag_default("MORI_D", 0.0),
            XMLTag.create_tag_default("ORI_D", 0.0),
            XMLTag.create_tag_default("RE_D"),
            XMLTag.create_tag_default("HO_D"),
            XMLTag.create_tag_default("H_D"),
        ]}

    def add_tachy_target(self, tachy_target):
        self.tachy_target_list.append(tachy_target)

    def get_xml(self):
        et = super(TachyStation, self).get_xml()
        for tachy_target in self.tachy_target_list:
            et.append(tachy_target.get_xml())
        return et

    def get_tag_name(self):
        return "TACHY_STATION"


class Application(GeosiObject):
    """
    """
    def __init__(self, **kwargs):
        super(Application, self).__init__(**kwargs)
        self.tachy_station = None
        self.project = None
        self.geosi_file = None
        self.instrument = []
        self.standpunkt = []

    def add_tachy_station(self, tachy_station):
        """
        :type tachy_station: TachyStation
        """
        self.tachy_station = tachy_station

    def add_tachy_target(self, tachy_target):
        """
        :type tachy_target: TachyTarget
        """
        self.tachy_station.add_tachy_target(tachy_target)

    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("TIMESTAMP_T", datetime.datetime.now().strftime("%y-%m-%d %H:%M")),
            XMLTag.create_tag_default("NAME_S"),
            XMLTag.create_tag_default("INFO_S"),
            XMLTag.create_tag_default("APP_CMD_S"),
        ]}

    def get_tag_name(self):
        return "APPLICATION"

    def get_xml(self):
        et = super(Application, self).get_xml()
        et.append(self.tachy_station.get_xml())
        return et


class InfoMess(GeosiObject):
    """
    """
    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("KORR_REFLADD_D"),
            XMLTag.create_tag_default("KORR_REFLNAME_S"),
            XMLTag.create_tag_default("EDM_KIND_S"),
            XMLTag.create_tag_default("EDM_MODE_S"),
            XMLTag.create_tag_default("REF_RADIUS_D"),
            XMLTag.create_tag_default("KORR_TEMP_DRY_D"),
            XMLTag.create_tag_default("KORR_TEMP_WET_D"),
            XMLTag.create_tag_default("KORR_DRUCK_D"),
            XMLTag.create_tag_default("REF_KOEFF_D"),
            XMLTag.create_tag_default("KORR_PPM_ATM_D"),
            XMLTag.create_tag_default("KORR_PPM_PROJ_D"),
            XMLTag.create_tag_default("KORR_PPM_HEIGHT_D"),
            XMLTag.create_tag_default("KORR_PPM_USER_D"),
        ]}

    def get_tag_name(self):
        return "INFOMESS"


class Zielpunkt(GeosiObject):
    """
    """
    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("BEZ_S"),
            XMLTag.create_tag_default("CODE_S"),
            XMLTag.create_tag_default("GUID_S"),
            XMLTag.create_tag_default("ZH_D", 0.0),
            XMLTag.create_tag_default("DATMESS_T", datetime.datetime.now().strftime("%y-%m-%d %H:%M")),
            XMLTag.create_tag_default("SS_D"),
            XMLTag.create_tag_default("ZH_D"),
            XMLTag.create_tag_default("RI1_D"),
            XMLTag.create_tag_default("ZD1_D"),
            XMLTag.create_tag_default("RI2_D"),
            XMLTag.create_tag_default("ZD2_D"),
            XMLTag.create_tag_default("ID_Z_L"),
            XMLTag.create_tag_default("ORICODE_E")
        ]}

    def get_tag_name(self):
        return "ZPKT"


class Punkt(GeosiObject):
    """
    """
    BCODE = (
        ("BCODE_NONE", 0),           # kein Berechnungscode
        ("BCODE_INPUT", 1),          # eingegeben
        ("BCODE_TRAFO_AUS_WGS", 2),  # aus wgs-punkt transformiert
        ("BCODE_TRAFO_AUS_PS", 3),   # aus projektionssystem transformiert
        ("BCODE_TACHY", 4),          # aus tachymeterdaten
    )

    def get_children(self):
        return {"child": [
            XMLTag.create_tag_default("KOO_RE_D"),
            XMLTag.create_tag_default("KOO_HO_D"),
            XMLTag.create_tag_default("KOO_H_D"),
            XMLTag.create_tag_default("CODE_S"),
            XMLTag.create_tag_default("DATMESS_T", datetime.datetime.now().strftime("%y-%m-%d %H:%M")),
            XMLTag.create_tag_default("BEZ_S"),
            XMLTag.create_tag_default("ID_Z_L"),
            XMLTag.create_tag_default("BCODE_E", Punkt.BCODE["BCODE_NONE"])
        ]}

    def get_tag_name(self):
        return "PKT"
