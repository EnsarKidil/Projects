import PyPDF2
import webbrowser
import os
import time
import sys

b = []
ablak=input("Hi! ")

if ablak != "4514":
    sys.exit()


def pdfkelimeokuma(a,k):

    x = PyPDF2.PdfFileReader('{}'.format(a))
    f = open("yazdir.txt", "a+",encoding="UTF-8")
    f.write("\n{}".format(a))
    f.close()
    for num_page in range(x.numPages):
        falan(num_page,a,x)



def falan(num_page, a, x):
    page_4_object = x.getPage(num_page)
    page_4_text = page_4_object.extractText()
    page_4_text = page_4_text.upper()
    page_4_text = page_4_text.replace(" ", "")
    page_4_text = page_4_text.replace("\n", "")
    f = open("yazdir.txt", "a+", encoding="UTF-8")
    f.write("{}:".format(num_page + 1) + page_4_text)
    f.close()


def dizinagaci():
    for root, dirs, files in os.walk(".", topdown=False):
        for name in files:
            if name.endswith('.pdf'):
                b.append(os.path.join(root, name))



def txtyazdir():
    dizinagaci()
    for i in b:
        pdfkelimeokuma(i,"k")

def txtdearat():
    f = open("yazdir.txt", "r+", encoding="UTF-8")
    fl = open("line.txt", "w", encoding="UTF-8")
    for i in f.readlines():
        if i.find(z) != -1:
            fl.write(i)
            continue
    f.close()
    fl.close()
    fl = open("line.txt", "r+", encoding="UTF-8")
    c = []

    for i in fl.readlines():
        data = ""
        start = 1
        end = 5
        for j in range(1, len(i)):
            if i[start:end] == '.pdf':
                break
            data = data + i[j]
            start += 1
            end += 1
        c.append(data)

    for i in c:
        print(i)
        """x = PyPDF2.PdfFileReader(".{}.pdf".format(i))
        for num_page in range(x.numPages):
            page_4_object = x.getPage(num_page)
            page_4_text = page_4_object.extractText()
            page_4_text = page_4_text.upper()
            page_4_text = page_4_text.replace(" ", "")
            page_4_text = page_4_text.replace("\n", "")
            if z in page_4_text:
                print("{} : {}".format(i, num_page))"""
    k=""
    if len(c)>=1:
        k = input("Dosyaları açmak ister misiniz? y/n")


    if k == "y":
        for i in c:
            os.startfile(".{}.pdf".format(i))
    else:
        print("Kod bulunamadı")
    fl.truncate(0)
    fl.close()


def dizinacik():
    dizinagaci()
    dizinacı = []
    cl = open("dizinagaci.txt", "a+", encoding="UTF-8")
    for i in cl.readlines():
        i = i[:-1]
        dizinacı.append(i)
    rtrn=[]
    if set(dizinacı) != set(b):
        for i in b:

            if dizinacı.count(i) == 0:
                print("Yeni pdf-ler bulundu taranıyor")
                pdfkelimeokuma(i, "k")
                rtrn.append(i)




        cl.close()
        print("\nYeni dosyalar tarandı:",rtrn,"\n")
        with open("dizinagaci.txt", "w", encoding="UTF-8") as dzn:
            dizinagaci()
            for i in b:
                dzn.write(i + "\n")
    else:
        print("\nYeni dosya bulunamadı\n")




while True:
    print("Python dosyasını pdf'leri arayacağınız klasörde çalıştırdığınızdan emin olun!")
    y = str(input("Yapmak istediniz işlemi seçiniz\nPdf'leri txt'ye aktarmak için 1'e basınız(Yalnızca 1 kez yapılması gerekir ve uzun sürecektir!)\nTxt'den kelime aratmak için 2'ye basınız\nYenilenen dosyaları check etmek için 3'e bas\nProgramı kapatmak için q'ya basınız:"))
    if y=="1":
        dzn=open("dizinagaci.txt", "w", encoding="UTF-8")
        dzn.close()
        txtyazdir()

    elif y=="2":
        z = str(input("Aranacak Kodu Giriniz (Büyük Harf): "))
        txtdearat()

    elif y== "q":
        break

    elif y== "3":
        dizinacik()








