from django.db import models
from django.urls import reverse
from django.utils.text import slugify
from django.core.validators import MaxValueValidator, MinValueValidator

class Robotlar(models.Model):

    object = models.Manager()
    objects = models.Manager()
    robot = models.CharField(max_length=300 ,verbose_name='Robot')
    kategori = models.CharField(verbose_name='Kategori',max_length=300 ,default='',choices=[
                                        ('Çizgi İzleyen: Cumhuriyet Yolu', 'Çizgi İzleyen: Cumhuriyet Yolu'),
                                        ('Mini Sumo' , 'Mini Sumo'),
                                        ('Lojistik' , 'Lojistik'),
                                        ('Senaryo: Arama Kurtarma' ,'Senaryo: Arama Kurtarma'),
                                        ('AlgoLAB' , 'AlgoLAB '),
                                        ('Renk Seçen' , 'Renk Seçen'),
                                        ('Pul Toplayan' , 'Pul Toplayan'),
                                        ('Trafik' , 'Trafik'),
                                    ],)
    pub_date = models.DateTimeField(verbose_name='Paylaşma Tarihi',auto_now_add=True)
    slug = models.SlugField(unique=True,editable=False,max_length=130)
    order = models.PositiveIntegerField(default=1)

    def __str__(self):
        return self.robot


    def get_absolute_url(self):
        return reverse('konusmaciapp:detail',kwargs = {'slug' : self.slug})


    def get_unique_slug(self):
        slug = slugify(self.robot.replace('ı','i'))
        unique_slug = slug
        cntr  = 1
        while Robotlar.objects.filter(slug = unique_slug).exists():
            unique_slug = '{}-{}'.format(slug,cntr)
            cntr+=1
        return unique_slug

    def save(self,*args,**kwargs):
        if not self.slug:
            self.slug = self.get_unique_slug()
        return super(Robotlar,self).save(*args,**kwargs)


    class Meta:
        ordering = ['-pub_date']

class Siralar(models.Model):
    object = models.Manager()
    objects = models.Manager()
    sira = models.PositiveIntegerField(default=1,verbose_name='Robot Sırası',help_text='Futbol(a-b)\tMerdiven(c-d)\tSenaryo(f-e)\tİnşaat(a-b)\tDrone(c-d)\tRenk(f-e)\tMikro(a-b)\tTrafik(c-d)')
    current_ctgr = models.CharField(default='',
                                    verbose_name='Şu an oynanan kategori',
                                    choices=[
                                        ('Çizgi İzleyen: Cumhuriyet Yolu', 'Çizgi İzleyen: Cumhuriyet Yolu'),
                                        ('Mini Sumo', 'Mini Sumo'),
                                        ('Lojistik', 'Lojistik'),
                                        ('Senaryo: Arama Kurtarma', 'Senaryo: Arama Kurtarma'),
                                        ('AlgoLAB', 'AlgoLAB '),
                                        ('Renk Seçen', 'Renk Seçen'),
                                        ('Pul Toplayan', 'Pul Toplayan'),
                                        ('Trafik', 'Trafik'),
                                    ],
                                    max_length=250)
    is_live = models.BooleanField(default=False,verbose_name='Şu an oynanıyor mu?')

    def __str__(self):
        return self.current_ctgr

class Adimlar(models.Model):
    object = models.Manager()
    objects = models.Manager()
    adim = models.PositiveIntegerField(default=1,verbose_name='Adım Sırası')
    soru = models.TextField(default='',verbose_name='Soru')
    kisa_aciklama = models.TextField(default='',verbose_name='Açıklama')
