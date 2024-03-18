from django.shortcuts import get_object_or_404,render,HttpResponseRedirect ,redirect
from .forms import *
from .models import *
from django.contrib import messages


def plan_view(request):
    args = {
        'content' : 'katplani',
    }
    return render(request, 'ituro_event/soon.html',args)

def days_view(request):
    events = Event.objects.all()
    if events:
        event_name = events[0].event
    else:
        event_name = ''
    tuesday = ScheduleTuesday.objects.filter(is_competetion = False)
    wednesday = ScheduleWednesday.objects.filter(is_competetion = False)
    #saturdays = ScheduleSaturday.objects.filter(is_competetion = False)

    args = {
        'event_name' : event_name,
        'tuesday' : tuesday,
        'wednesday' : wednesday,
        #'saturdays' : saturdays,
    }
    return render(request, 'ituro_event/days.html',args)

def days_competetion_view(request):
    events = Event.objects.all()
    if events:
        event_name = events[0].event
    else:
        event_name = ''

    tuesday = ScheduleTuesday.objects.filter(is_competetion = True)
    wednesday = ScheduleWednesday.objects.filter(is_competetion = True)
    #saturdays = ScheduleSaturday.objects.filter(is_competetion = True)

    args = {
        'event_name' : event_name,
        'tuesday' : tuesday,
        'wednesday' : wednesday,
        #'saturdays' : saturdays,
    }
    return render(request, 'ituro_event/competetion_days.html',args)



def upload_photo(request):

    form = PhotoForm(request.POST or None, request.FILES or None)
    if (form.is_valid()):
        kaydedilenPhoto = form.save(commit=False)

        kaydedilenPhoto.save()
        messages.success(request, 'Başarıyla anınızı paylaştınız!')
        return redirect('home')

    args = {
        'form': form
    }
    return render(request, 'ituro_event/upload_photo.html', args)

def days_choice(request):
    return render(request, 'ituro_event/choice.html',None)

def present_opinion(request):

    form = OpinionForm(request.POST or None)
    if (form.is_valid()):
        kaydedilenOpinion = form.save(commit=False)
        messages.success(request, 'Başarıyla görüşünüzü paylaştınız!')
        kaydedilenOpinion.save()
        return redirect('home')

    args = {
        'form': form
    }
    return render(request, 'ituro_event/opinion.html', args)






