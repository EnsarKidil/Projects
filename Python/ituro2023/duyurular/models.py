from django.db import models

# Create your models here.


class Duyurular(models.Model):

    turler = [
        ('primary', 'Onemli'),
        ('warning', 'Bilgilendirme'),
        ('danger', 'Acil'),

    ]


    objects = models.Manager()
    object = models.Manager()
    duyuru = models.TextField(max_length=250,default='',verbose_name='Duyuru')
    tur = models.CharField(choices=turler,verbose_name='Tür',default='',max_length=150)
    is_homepage = models.BooleanField(default=False,verbose_name='Paylaşılsın mı?')


    def __str__(self):
        return self.duyuru


