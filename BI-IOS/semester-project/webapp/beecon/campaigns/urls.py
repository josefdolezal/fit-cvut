from django.conf.urls import url

from . import views


app_name = 'campaigns'
urlpatterns = [
  url( r'^$', views.JsonView.response, name='index' ),
  url( r'^(?P<app_code>[a-zA-Z0-9]+)/info/$', views.info, name='info' ),
  url( r'^(?P<app_code>[a-zA-Z0-9]+)/services/$', views.services, name='services' ),
]
