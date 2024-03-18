from django.urls import path
from .views import *


app_name = 'eventapp'

urlpatterns = [

    path(r'^gorus-belirt/$', present_opinion, name='opinion'),
    path(r'^ani-birak/$', upload_photo, name='photo'),
    path(r'^kat-plani/$', plan_view, name='floors'),
    path(r'^gunler/$', days_choice, name='days_choice'),
    path(r'^gunler/konusmalar/$', days_view, name='days'),
    path(r'^gunler/yarismalar/$', days_competetion_view, name='days_competetions'),


]