# -*- coding: utf-8 -*-

from bs4 import BeautifulSoup
from datetime import datetime
import re

from .DataSource import CinemaCity

class MovieSchedule:
  @classmethod
  def entry_point( cls, args = {} ):
    url = 'http://www.cinemacity.cz/scheduleInfo?locationId=%s' % args['cinema_id']
    schedule = cls( url, '' )
    return schedule.closest_movies()

  def __init__( self, url, date ):
    self.url = url
    self._load_schedule()

  def closest_movies( self ):
    return [ m.to_dict() for m in self.movies ]

  def _load_schedule( self ):
    cc = CinemaCity( self.url )
    self._parse_schedule( cc.movie_schedule() )

  def _parse_schedule( self, html ):
    soup = BeautifulSoup( html, 'html.parser' )
    movies = soup.find_all( 'tr' )

    self.movies = [ Movie( movie ) for movie in movies if movie.td ]

class Movie:
  def __init__( self, soup ):
    self.showtimes = []
    self._remove_empty_elements( soup )
    self._parse_input( soup )

  def __str__( self ):
    return self.name

  def __repr__( self ):
    return self.name

  def to_dict( self ):
    return {
      'name': self.name,
      'pg': self.pg,
      'type': self.mtype,
      'language': self.language,
      'duration': self.duration,
      'showtimes': self.showtimes
    }

  def _parse_input( self, soup ):
    self.name = soup.td.extract().a.string
    self.pg = soup.td.extract().string
    self.mtype = soup.td.extract().string
    self.language = soup.td.extract().string
    self.duration = soup.td.extract().string
    self._setup_showtimes( soup )

  def _remove_empty_elements( self, soup ):
    for el in soup.find_all( 'td' ):
      if not el.contents:
        el.extract()

  def _setup_showtimes( self, soup ):
    self.showtimes = [ datetime.strptime( e.a.text.strip()[:5], '%H:%M' ).time() for e in soup.find_all( 'td' ) ]
