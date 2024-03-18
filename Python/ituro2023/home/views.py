from django.shortcuts import get_object_or_404,render,HttpResponseRedirect ,redirect
from django.contrib.auth.decorators import login_required
from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger
from django.db.models import Q
from itertools import chain
from django.contrib import messages
from duyurular.models import Duyurular


def home_view(request):
    if Duyurular.objects.filter(is_homepage = True):
        length = len(Duyurular.objects.filter(is_homepage = True))
        duyurular = Duyurular.objects.filter(is_homepage = True)[length-1]

        args = {
            'duyuru' : duyurular,
        }
        return render(request,'home.html',args)
    else:
        return render(request, 'home.html', None)

def fourofour_handler(request, exception):
    # Set the response status code to 404
    response = render(request, '404.html')
    response.status_code = 404
    return response