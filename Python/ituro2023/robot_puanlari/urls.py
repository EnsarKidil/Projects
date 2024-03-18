from django.urls import path
from . import views

app_name='robot_puanlari'

urlpatterns = [
    path('cumhuriyet-yolu/', views.competition_detail, {'competition_name': 'Çizgi İzleyen: Cumhuriyet Yolu'}),
    path('competition/<int:competition_id>/', views.competition_detail, name='competition_detail'),
    path('', views.home, name='home'),
    # ... add paths for the other competitions
]
