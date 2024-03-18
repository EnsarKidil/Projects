from django import forms
from .models import *
class PhotoForm(forms.ModelForm):
    image = forms.ImageField(required=True,label='Bizimle bir İTÜRO anını paylaş!')
    isimSoyisim = forms.CharField(required=True,label='İsim Soyisim')
    email = forms.EmailField(required=True,label='E-Posta')
    class Meta:
        model = PhotoModel
        fields = [
            'isimSoyisim',
            'email',
            'image',
        ]

class OpinionForm(forms.ModelForm):
    isimSoyisim = forms.CharField(required=True,label='İsim Soyisim')
    opinion = forms.CharField(required=True,label = 'Görüş Belirtiniz',widget=forms.Textarea)
    email = forms.EmailField(required=True,label='E-Posta')

    class Meta:
        model = Opinions
        fields = [
            'isimSoyisim',
            'email',
            'opinion',
        ]