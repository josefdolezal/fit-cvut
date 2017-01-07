from django.shortcuts import render, get_object_or_404
from django.http import JsonResponse
from django.conf import settings
from importlib import import_module
import imp, json
from os import path
import sys

from .models import App, Campaign, ServiceParams, Service

def api( request ):
  app = get_object_or_404( Campaign, code=request.GET['app_code'] )



  return render( request, 'campaigns/test.html', { 'app': app } )

class JsonView:
  @classmethod
  def response( cls, request ):
    app_code = request.GET['app_code']
    location = request.GET['location']
    service = request.GET['service']
    data = []
    response = {}

    try:
      campaign = get_object_or_404( Campaign, code=app_code )
      library = campaign.app.api_class
      service = Service.objects.get(
        beacon_minor=service,
        location__beacon_major=location,
        location__campaign__code=app_code
      )

      config = ServiceParams.objects.filter( service__pk=service.pk )

      response['app'] = campaign.name
      response['uuid'] = campaign.beacon_uuid
      response['service'] = service.name
      response['location'] = service.location.name

      api = cls.import_api( library )
      response["data"] = api.entry_point( cls.campaing_configuration( config ) )
    except:
      return JsonResponse( cls.empty_response() )

    return JsonResponse( cls.base_response( response ) )

  @classmethod
  def empty_response( cls ):
    return cls.base_response( { 'status': 500, 'status_text': 'Bad request format.' } )

  @classmethod
  def base_response( cls, args = {} ):
    body = {
      'status': 200,
      'status_text': 'OK',
      'app': 'Unknow',
      'location': 'Unknown',
      'service': 'Unknow',
      'data': {},
      'uuid': 'Unknown',
      'prefered_view': 'app.default',
    }

    for key, val in args.items():
      if key in body:
        body[key] = val

    return body

  @classmethod
  def import_api( cls, mod ):
    mod = mod.split('.')
    m = import_module( '..libs.' + mod[0], __name__ )
    return getattr( m, mod[1] )

  @classmethod
  def campaing_configuration( cls, configs ):
    configuration = {}

    for c in configs:
      configuration[ '%s' % c.key] = c.value

    return configuration

def info( request, app_code ):
  try:
    campaign = Campaign.objects.get( code=app_code )
  except:
    return JsonResponse( JsonView.empty_response() )

  return JsonResponse( JsonView.base_response( { 'app': campaign.name, 'uuid': campaign.beacon_uuid } ) )

def services( request, app_code ):
  data = {}
  try:
    services = Service.objects.filter( location__campaign__code=app_code )
    campaign = Campaign.objects.get( code=app_code )
    data['app'] = campaign.name
    data['uuid'] = campaign.beacon_uuid
    data = JsonView.base_response( data )
  except:
    return JsonResponse( JsonView.empty_response() )

  data = JsonView.base_response( data )
  data['services'] = [ {
    "name": service.name,
    "major": service.location.beacon_major,
    "minor": service.beacon_minor,
  } for service in services ]

  return JsonResponse( data )
