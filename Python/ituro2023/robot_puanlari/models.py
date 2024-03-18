from django.db import models

# Create your models here.
from django.db import models

class Competition(models.Model):
    name = models.CharField(max_length=255)

    def __str__(self):
        return self.name

class Robot(models.Model):
    competition = models.ForeignKey(Competition, on_delete=models.CASCADE)
    name = models.CharField(max_length=255)
    robot_id = models.CharField(max_length=255)
    time = models.FloatField()
    score = models.IntegerField()
    class Meta:
        ordering = ['-score', 'time']

    def __str__(self):
        return self.name
