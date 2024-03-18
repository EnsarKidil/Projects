from django.contrib import admin
from .models import *

class PhotoAdmin(admin.ModelAdmin):

    list_display = ['image','pub_date','isimSoyisim']
    list_display_links = ['image','pub_date']
    fields = ['isimSoyisim']
    list_filter = ['pub_date']
    search_fields = ['image']

    class Meta:
        model = PhotoModel

class OpinionAdmin(admin.ModelAdmin):

    list_display = ['isimSoyisim','opinion','pub_date']



    class Meta:
        model = Opinions


#***************************************************************************

class ScheduleTuesdayInLineAdmin(admin.TabularInline):
    model = ScheduleTuesday
    extra = 0


class ScheduleTuesdayAdmin(admin.ModelAdmin):
    list_display = ["title","created_at","related_with"]
    search_fields = ["title"]

class ScheduleTuesdayAdmin(admin.ModelAdmin):
    list_display = ['title','related_with']
    readonly_fields =  ['title','related_with','hour_slice']

    class Meta:

        model = ScheduleTuesday
        verbose_name_plural = 'Sali'


#***************************************************************************

class ScheduleWednesdayInlineAdmin(admin.TabularInline):
    model = ScheduleWednesday
    extra = 0


class ScheduleWednesdayAdmin(admin.ModelAdmin):
    list_display = ["title","created_at","related_with"]
    search_fields = ["title"]

class ScheduleWednesdayAdmin(admin.ModelAdmin):
    list_display = ['title','related_with']
    readonly_fields =  ['title','related_with','hour_slice']

    class Meta:

        model = ScheduleWednesday
        verbose_name_plural = 'Carsamba'



class EventAdmin(admin.ModelAdmin):

    list_display = ['event']
    inlines = [ScheduleTuesdayInLineAdmin,ScheduleWednesdayInlineAdmin]

    class Meta:
        model = Event


admin.site.register(ScheduleTuesday,ScheduleTuesdayAdmin)
admin.site.register(ScheduleWednesday,ScheduleWednesdayAdmin)
admin.site.register(Event,EventAdmin)
admin.site.register(PhotoModel,PhotoAdmin)
admin.site.register(Opinions,OpinionAdmin)
