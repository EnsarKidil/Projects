from django.db import models
from django.urls import reverse
from django.utils.text import slugify


class PhotoModel(models.Model):

    object = models.Manager()
    objects = models.Manager()
    pub_date = models.DateTimeField(verbose_name='Paylaşma Tarihi',auto_now_add=True)
    isimSoyisim = models.CharField(default='',verbose_name='isim - soyisim',max_length=150)
    image = models.ImageField(null=True, blank=True,verbose_name='ani')
    slug = models.SlugField(unique=True, editable=False, max_length=130,default='')
    email = models.EmailField(null=False,blank=False, verbose_name='E-Posta',default='')

    def __str__(self):
        return self.isimSoyisim

    def get_unique_slug(self):
        slug = slugify(self.image.url.replace('ı','i'))
        unique_slug = slug
        cntr  = 1
        while PhotoModel.objects.filter(slug = unique_slug).exists():
            unique_slug = '{}-{}'.format(slug,cntr)
            cntr+=1
        return unique_slug

    def save(self,*args,**kwargs):
        if not self.slug:
            self.slug = self.get_unique_slug()
            return super(PhotoModel, self).save(*args, **kwargs)

class Event(models.Model):
    object = models.Manager()
    objects = models.Manager()

    event = models.CharField(max_length=250,verbose_name='Etkinlik Adı')

    def __str__(self):
        return self.event

class ScheduleTuesday(models.Model):

    object = models.Manager()
    objects = models.Manager()
    title = models.CharField(max_length=400,verbose_name='Başlık')
    speaker = models.CharField(max_length=150, verbose_name='Konuşmacı/KAT(?)',null=True, blank=True)
    hour_slice = models.CharField(max_length=100, verbose_name='Saat Dilimi')
    related_with = models.ForeignKey(Event, null=True, blank=True, on_delete=models.CASCADE)
    created_at = models.DateTimeField(auto_now_add=True)
    is_competetion = models.BooleanField(default=False, verbose_name='Yarışma mı?')

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name_plural = 'Sali'

    def __str__(self):
        return self.title

class ScheduleWednesday(models.Model):

    object = models.Manager()
    objects = models.Manager()
    title = models.CharField(max_length=400,verbose_name='Başlık')
    speaker = models.CharField(max_length=150, verbose_name='Konuşmacı/KAT(?)',null=True, blank=True)
    hour_slice = models.CharField(max_length=100, verbose_name='Saat Dilimi')
    related_with = models.ForeignKey(Event, null=True, blank=True, on_delete=models.CASCADE)
    created_at = models.DateTimeField(auto_now_add=True)
    is_competetion = models.BooleanField(default=False, verbose_name='Yarışma mı?')

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name_plural = 'Carsamba'

    def __str__(self):
        return self.title

"""class ScheduleSaturday(models.Model):

    object = models.Manager()
    objects = models.Manager()
    title = models.CharField(max_length=400,verbose_name='Başlık')
    speaker = models.CharField(max_length=150, verbose_name='Konuşmacı/KAT(?)',null=True, blank=True)
    hour_slice = models.CharField(max_length=100, verbose_name='Saat Dilimi')
    related_with = models.ForeignKey(Event, null=True, blank=True, on_delete=models.CASCADE)
    created_at = models.DateTimeField(auto_now_add=True)
    is_competetion = models.BooleanField(default=False, verbose_name='Yarışma mı?')

    def __unicode__(self):
        return self.title

    class Meta:
        verbose_name_plural = 'Cumartesiler'

    def __str__(self):
        return self.title"""

class Opinions(models.Model):
    object = models.Manager()
    objects = models.Manager()
    pub_date = models.DateTimeField(verbose_name='Paylaşma Tarihi', auto_now_add=True)
    isimSoyisim = models.CharField(default='', verbose_name='isim - soyisim', max_length=150)
    opinion = models.TextField(max_length=750, verbose_name='Görüş', null=True, blank=True)
    email = models.EmailField(null=False, blank=False, verbose_name='E-Posta', default='')

    def __str__(self):
        return '{} : {}...'.format(self.isimSoyisim,self.opinion)





