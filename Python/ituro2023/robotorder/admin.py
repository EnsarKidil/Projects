from django.contrib import admin
from .models import *

class RobotlarAdmin(admin.ModelAdmin):


    list_display = ['robot','pub_date','order']
    list_display_links = ['robot','pub_date']

    list_filter = ['pub_date']
    search_fields = ['robot','kategori']


    class Meta:
        model = Robotlar

admin.site.register(Robotlar,RobotlarAdmin)

class SiralarAdmin(admin.ModelAdmin):

    list_display = ['current_ctgr', 'sira','is_live']
    list_editable = ['is_live']
    fields = ['sira','current_ctgr','is_live']

    class Meta:
        model = Siralar

admin.site.register(Siralar,SiralarAdmin)

class AdimlarAdmin(admin.ModelAdmin):

    list_display = ['soru','adim']


    class Meta:
        model = Adimlar

admin.site.register(Adimlar,AdimlarAdmin)