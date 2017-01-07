# -*- coding: utf-8 -*-

from .DataSource import DataSource
import re


class Connections:
  @classmethod
  def entry_point( cls, args ):
    url = 'http://m.jizdnirady.cz/ConnMHD.aspx'
    departure = args['departure']
    connections = cls( url )

    return connections.upcoming_departures( departure )

  def __init__( self, url ):
    self.url = url

  def upcoming_departures( self, departure ):
    upcoming = self._load_upcoming( { 'from': departure } )
    return self._parse_upcoming( upcoming, departure )

  def _load_upcoming( self, data ):
    ds = DataSource( self.url )
    return ds.single_page( data )

  def _parse_upcoming( self, html, departure ):
    regex = re.compile( r'[^:]*: (?P<line>[^ ]+)[\D]*(?P<time>[\d]+:[\d]+)[^,]*, (?P<termstation>[^<]+)' )

    conn = []
    for con in regex.finditer( html ):
      c = con.groupdict()
      c['departure'] = departure

      conn.append( Connection( c ).as_dict() )

    return conn


class Connection:
  ATTRIBUTES = [
    'line',
    'departure',
    'termstation',
    'time',
    'transfers'
  ]

  def __init__( self, data ):
    self._sanitize_input( data )

  def __repr__( self ):
    return self.to_json()

  def __str__( self ):
    return self.to_json()

  def _sanitize_input( self, data ):
    for attr in Connection.ATTRIBUTES:
      if attr in data:
        setattr( self, attr, data[ attr ] )

  def as_dict( self ):
    movie = {}

    for attr in Connection.ATTRIBUTES:
      i = getattr( self, attr, '' )
      movie[attr] = i

    return movie

