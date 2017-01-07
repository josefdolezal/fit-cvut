from DataSource import CinemaCity
from bs4 import BeautifulSoup
from datetime import datetime
import re

class MovieSchedule:
  def __init__( self, url, date ):
    self.url = url
    self._load_schedule()

  def closest_movies( self ):
    print( self.movies )

  def _load_schedule( self ):
    cc = CinemaCity( self. url )
    self._parse_schedule( cc.movie_schedule() )

  def _parse_schedule( self, html ):
    soup = BeautifulSoup( html, 'html.parser' )
    movies = soup.find_all( 'tr' )

    self.movies = [ Movie( movie ) for movie in movies if movie.td ]

class Movie:
  def __init__( self, soup ):
    self._remove_empty_elements( soup )
    self._parse_input( soup )

  def __str__( self ):
    return self.to_json()

  def __repr__( self ):
    return self.to_json()

  def to_json( self ):
    js = '{'

    js += '"name":"{}", "pg":"{}", "type":"{}", '.format(
      self.name, self.pg, self.mtype )
    js += '"language":"{}", "duration":"{}", '.format(
      self.language, self.duration )
    js += '"showtimes":{}'.format( self._showtimes_to_json() )

    js += '}'
    return js

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
    self.showtimes = [ datetime.strptime( e.a.string.strip(), '%H:%M' ).time() for e in soup.find_all( 'td' ) ]

  def _showtimes_to_json( self ):
    js = '['

    for show in self.showtimes:
      if show is not self.showtimes[0]:
        js += ', '
      js += '"{}"'.format( show.strftime( '%H:%M' ) )

    js += ']'
    return js
