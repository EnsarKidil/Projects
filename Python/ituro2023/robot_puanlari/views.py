from django.shortcuts import render
from .models import Competition, Robot


def home(request):
    competitions = Competition.objects.all()
    context = {'competitions': competitions}
    return render(request, 'robot_puanlari_home.html', context)

def competition_detail(request, competition_id):
    competition = Competition.objects.get(id=competition_id)
    robots = competition.robot_set.all()
    context = {'competition': competition, 'robots': robots}
    return render(request, 'competition_detail.html', context)
