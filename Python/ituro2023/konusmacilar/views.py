from django.shortcuts import render,get_object_or_404, HttpResponseRedirect, redirect, Http404
from .models import Konusmacilar
from django.contrib import messages
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.shortcuts import render
from django.db.models import Q


def konusmaci_index(request):
    konusmaci_list = Konusmacilar.object.all()

    query = request.GET.get('q')
    if (query):
        konusmaci_list = konusmaci_list.filter(Q(who__icontains=query)|
                                     Q(konusmaci__icontains=query)
                                     ).distinct()


    paginator = Paginator(konusmaci_list, 4)
    page = request.GET.get('page')

    try:
        konusmacilar = paginator.page(page)
    except PageNotAnInteger:
        konusmacilar = paginator.page(1)
    except EmptyPage:
        konusmacilar = paginator.page(paginator.num_pages)

    return render(request, 'konusmacilar/index.html', {'konusmacilar' : konusmacilar})

def konusmaci_detail(request,slug):
    konusmaci = get_object_or_404(Konusmacilar,slug = slug)

    context1 = {
            'konusmaci' : konusmaci,
        }
    return render(request,'post/detail.html',context1)