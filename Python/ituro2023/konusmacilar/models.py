from django.db import models
from django.urls import reverse
from django.utils.text import slugify
from ckeditor.fields import RichTextField


class Konusmacilar(models.Model):

    object = models.Manager()
    objects = models.Manager()
    user = models.ForeignKey('auth.user', verbose_name='Yazar',related_name='posts', on_delete=models.CASCADE)
    konusmaci = models.CharField(max_length=300 ,verbose_name='Isim/Soyisim')
    who = RichTextField(verbose_name='hakkinda')
    pub_date = models.DateTimeField(verbose_name='Paylaşma Tarihi',auto_now_add=True)
    image = models.ImageField(null=True, blank=True,verbose_name='Kapak Fotoğrafı')
    slug = models.SlugField(unique=True,editable=False,max_length=130)

    def __str__(self):
        return self.konusmaci


    def get_absolute_url(self):
        return reverse('konusmaciapp:detail',kwargs = {'slug' : self.slug})


    def get_unique_slug(self):
        slug = slugify(self.konusmaci.replace('ı','i'))
        unique_slug = slug
        cntr  = 1
        while Konusmacilar.objects.filter(slug = unique_slug).exists():
            unique_slug = '{}-{}'.format(slug,cntr)
            cntr+=1
        return unique_slug

    def save(self,*args,**kwargs):
        if not self.slug:
            self.slug = self.get_unique_slug()
        return super(Konusmacilar,self).save(*args,**kwargs)


    class Meta:
        ordering = ['-pub_date']