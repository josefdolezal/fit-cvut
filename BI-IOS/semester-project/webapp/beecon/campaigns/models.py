from django.contrib.auth.models import User
from django.db import models

class App( models.Model ):
  name = models.CharField( max_length=60 )
  api_class = models.CharField( max_length=60 )

  def __str__( self ):
    return self.name


class AppConfig( models.Model ):
  name = models.CharField( max_length=60 )
  app = models.ForeignKey( App, on_delete=models.PROTECT )
  required = models.BooleanField( default=True )

  def __str__( self ):
    return self.name


class Campaign( models.Model ):
  name = models.CharField( max_length=200 )
  code = models.CharField( max_length=50, unique=True )
  beacon_uuid = models.CharField( 'Beacon UUID', max_length=200 )
  app = models.ForeignKey( App, on_delete=models.PROTECT )
  manager = models.ForeignKey( User, on_delete=models.CASCADE )

  def __str__( self ):
    return self.name


class AccessToken( models.Model ):
  description = models.CharField( max_length=50 )
  token = models.CharField( max_length=65 )
  date_added = models.DateTimeField()
  campaign = models.ForeignKey( Campaign, on_delete=models.CASCADE )


class Location( models.Model ):
  name = models.CharField( max_length=200 )
  beacon_major = models.CharField( max_length=10 )
  campaign = models.ForeignKey( Campaign, on_delete=models.CASCADE )

  def __str__( self ):
    return self.name


class Service( models.Model ):
  name = models.CharField( max_length=60 )
  beacon_minor = models.CharField( max_length=10 )
  location = models.ForeignKey( Location, on_delete=models.CASCADE )

  def __str__( self ):
    return self.name


class ServiceParams( models.Model ):
  key = models.ForeignKey( AppConfig, on_delete=models.PROTECT )
  value = models.CharField( max_length=60 )
  service = models.ForeignKey( Service, on_delete=models.PROTECT )

  def __str__( self ):
    return '{}'.format( self.key )
