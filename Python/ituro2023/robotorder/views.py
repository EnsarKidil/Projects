from django.shortcuts import render,get_object_or_404, HttpResponseRedirect, redirect, Http404
from .models import Robotlar, Siralar,Adimlar
from django.contrib import messages
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.shortcuts import render
from django.db.models import Q
from django.core.exceptions import ObjectDoesNotExist

def robot_choice(request):
    return render(request,'robotorder/robot_choice.html',None)

def robot_what2do(request):
    adimlar = Adimlar.objects.all()
    args = {'adimlar' : adimlar}
    return render(request,'robotorder/what2do.html',args)


def robot_index(request):
    robot_list = Robotlar.object.all()

    query = request.GET.get('q')
    if (query):
        robot_list = robot_list.filter(Q(kategori__icontains=query)|
                                     Q(robot__icontains=query)|
                                     Q(order__icontains=query)
                                     ).distinct()

    paginator = Paginator(robot_list, 8)
    page = request.GET.get('page')

    try:
        robot_list = paginator.page(page)
    except PageNotAnInteger:
        robot_list = paginator.page(1)
    except EmptyPage:
        robot_list = paginator.page(paginator.num_pages)




    robot_listesi = Robotlar.object.all()

    if len(Siralar.objects.filter(is_live = True))>=2:
        robot_sirasi = Siralar.objects.filter(is_live = True)
    else:
        robot_sirasi = Siralar.objects.all()

    if len(robot_sirasi.filter(is_live=True))>=1:
        sira = robot_sirasi[len(robot_sirasi)-1].sira
        kategori = robot_sirasi[len(robot_sirasi)-1].current_ctgr
    else:
        sira = 1
        kategori = '-'

    if len(robot_sirasi.filter(is_live=True))>=2:
        sira2 = robot_sirasi[len(robot_sirasi)-2].sira
        kategori2 = robot_sirasi[len(robot_sirasi)-2].current_ctgr
    else:
        sira2 = 1
        kategori2 = '-'


    try:
        robot1 = robot_listesi.get(order=(sira + 1))
    except ObjectDoesNotExist:
        robot1 = None

    try:
        robot2 = robot_listesi.get(order=(sira + 2))
    except ObjectDoesNotExist:
        robot2 = None

    try:
        robot3 = robot_listesi.get(order=(sira + 3))
    except ObjectDoesNotExist:
        robot3 = None

    try:
        robot4 = robot_listesi.get(order=(sira2 + 1))
    except ObjectDoesNotExist:
        robot4 = None

    try:
        robot5 = robot_listesi.get(order=(sira2 + 2))
    except ObjectDoesNotExist:
        robot5 = None

    try:
        robot6 = robot_listesi.get(order=(sira2 + 3))
    except ObjectDoesNotExist:
        robot6 = None



    args = {'robots' : robot_list,

            'robot_sirasi' : sira,
            'kategori' : kategori,
            'robot_sirasi2': sira2,
            'kategori2': kategori2,
            'robot1' : robot1,
            'robot2': robot2,
            'robot3': robot3,
            'robot4': robot4,
            'robot5': robot5,
            'robot6': robot6,
            }
    return render(request, 'robotorder/index.html', args)