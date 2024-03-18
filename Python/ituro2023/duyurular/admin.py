from django.contrib import admin
from .models import Duyurular

class DuyurularAdmin(admin.ModelAdmin):


    list_display = ['duyuru','is_homepage']
    list_display_links = ['duyuru',]
    list_editable = ['is_homepage']


    search_fields = ['duyuru','tur']


    class Meta:
        model = Duyurular

admin.site.register(Duyurular,DuyurularAdmin)