import requests


class CinemaCity:
  def __init__( self, url ):
    self._compile_url( url )

  def movie_schedule( self ):
    content = requests.get( self.url ).content

    return content

  def _compile_url( self, url ):
    self.url = url
