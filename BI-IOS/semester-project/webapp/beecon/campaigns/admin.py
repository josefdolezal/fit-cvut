from django.contrib import admin

from .models import Campaign, App, Location, Service, ServiceParams, AppConfig


class ServiceParamsInline( admin.TabularInline ):
  model = ServiceParams
  extra = 3


class ServiceAdmin( admin.ModelAdmin ):
  list_display = ( 'name', 'beacon_minor' )
  search_fields = [ 'name' ]
  inlines = [ ServiceParamsInline ]


class AppConfigAdmin( admin.ModelAdmin ):
  list_display = ( 'app', 'name' )
  list_filter = [ 'app' ]


class CampaignAdmin( admin.ModelAdmin ):
  fieldsets = [
    ( None, { 'fields': [ 'name' ] } ),
    ( 'Campaign Details', { 'fields': [ 'beacon_uuid', 'app' ] } ),
    ( 'User Info', { 'fields': [ 'manager', 'code' ] } ),
  ]
  list_display = ( 'name', 'beacon_uuid' )

admin.site.register( App )
admin.site.register( AppConfig, AppConfigAdmin )
admin.site.register( Campaign, CampaignAdmin )
admin.site.register( Location )
admin.site.register( Service, ServiceAdmin )
