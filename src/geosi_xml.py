#!/usr/bin/python2.7

import geosi_tags as GT


class GeosiXML(object):
    """
    """
    def __init__(self, **kwargs):
        self.geosi_file = GT.File(**kwargs)
        self.project = GT.Project(**kwargs)
        self.instruments = []
        if kwargs.has_key("instrument"):
            pass

    def add_file(self, geosi_file):
        """
        :type geosi_file: File
        """
        self.geosi_file = geosi_file

    def add_project(self, project):
        """
        :type project: Project
        """
        self.project = project

    def add_instrument(self, instrument):
        """
        :type instrument: Instrument
        """
        self.instrument.append(instrument)

    def add_standpunkt(self, standpunkt):
        """
        :type standpunkt: Standpunkt
        """
        self.standpunkt.append(standpunkt)
