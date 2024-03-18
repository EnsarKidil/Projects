from django.urls import path
from .views import *


app_name = 'robotapp'

urlpatterns = [

    path(r'^index/$',robot_index,name='index'),
    path(r'^secenekler/$',robot_choice,name='robot_choice'),
    path(r'^ne-yapmaliyim/$',robot_what2do,name='what2do'),

]