# -*- coding: utf-8 -*-

from requests import Session
from bs4 import BeautifulSoup

class DataSource:
  BASE_REQUEST_DATA = {
    'format': 4,
    'JR': 'PID'
  }

  FIELD_NAMES = {
    'from': 'odkud',
    'to': 'kam',
    'time': 'cas',
    'date': 'den',
    'command': 'cmd',
    'session_key': 'znc',
    'line': 'linka'
  }

  PUBLIC_FIELDS = [
    'from',
    'to',
    'date',
    'time',
    'line'
  ]

  def __init__( self, url ):
    self.session = Session()
    self.url = url
    self._begin_session()

  def single_page( self, data ):
    return self.multi_page( data, limit = 1 )[0]

  def multi_page( self, usr_data, limit = 1 ):
    data = self._sanitize_input( usr_data )
    data = dict( self.BASE_REQUEST_DATA, ** data )
    pages = []

    for _ in range( 0, limit ):
      content = self._request_content( data )
      soup = BeautifulSoup( content, 'html.parser' )
      pages.append( str( soup.find_all( 'p' )[1] ) )

    return pages

  def _translate_field( self, field ):
    if field in self.FIELD_NAMES:
      return self.FIELD_NAMES[ field ]

    return 'undefined'

  def _begin_session( self ):
    content = self._request_content( self.BASE_REQUEST_DATA )

    self.session_key = self._session_key( content )

  def _session_key( self, html_content ):
    soup = BeautifulSoup( html_content, 'html.parser' )
    return soup.find( 'input', { 'type': "hidden", 'name': "znc" } )['value']

  def _request_content( self, data ):
    return self.session.get( self.url, params = data ).content

  def _sanitize_defaults( self, defaults ):
    san = {}

    for val in defaults:
      san[ self._translate_field( val ) ] = defaults[ val ]

    return san

  def _sanitize_input( self, data ):
    defaults = self._sanitize_defaults( {
      'command': 'search',
      'session_key': self.session_key
    } )

    for field in DataSource.PUBLIC_FIELDS:
      if field in data:
        defaults[ self._translate_field( field ) ] = data[field]
    return defaults
