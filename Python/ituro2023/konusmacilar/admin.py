from django.contrib import admin
from .models import Konusmacilar

class KonusmacilarAdmin(admin.ModelAdmin):


    list_display = ['konusmaci','pub_date']
    list_display_links = ['konusmaci','pub_date']

    list_filter = ['pub_date']
    search_fields = ['konusmaci','who']


    class Meta:
        model = Konusmacilar

admin.site.register(Konusmacilar,KonusmacilarAdmin)