from django.urls import path
from .views import *


app_name = 'konusmaciapp'

urlpatterns = [

    path(r'^index/$',konusmaci_index,name='index'),
    path(r'^(?P<slug>[\w-]+)/$',konusmaci_detail,name='detail'),

]