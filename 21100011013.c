#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAX_KISI_SAYISI 100
#define MAX_KITAP_SAYISI 100
//21100011013/Rabia/KIRATLI

typedef enum
{
    ogrenci=0,calisan=1
} YetkiSeviyeleri;


typedef struct
{
    char *Ad;
    char *kYazarAd;
    char *kYazarSoyad;
    char *yayinEvi;
    int sayfaSayisi;
    int kitapDurumu;
} kitapinfo;

typedef struct
{
    char *uyeAd;
    char *uyeSoyad;
    int sifre;
    int IDkutuphane;
    YetkiSeviyeleri kisiYetkisi;
} kisiinfo;

int kisiSorgula(kisiinfo *uyeListesi,int ID)
{
    int i;
    for(i=0; i<MAX_KISI_SAYISI; i++)
    {
        if(uyeListesi[i].IDkutuphane==ID)
        {
            return ID;//bu ID daha önce kullanýldý.
        }
    }
    return -1;//bu ID daha önce hiç kullanýlmadý.
}

int kayitOl(kisiinfo *uyeListesi)
{

    int i,kayitYapilacakIndex,ID;
    char uyeAd[20],uyeSoyad[20],ch;

    srand(time(NULL));//ID FARKLILIÐI ÝÇÝN
    for(i=0; i<MAX_KISI_SAYISI; i++)
    {
        if(uyeListesi[i].IDkutuphane==0)
        {
            kayitYapilacakIndex=i;
            break;
        }
    }
    ID=rand()%100000+1;//burdan son derse selamlar...
    if(kisiSorgula(uyeListesi,ID)!=-1)
    {
        printf("Bu ID degeri daha once kullanilmistir...Kayit yapilamiyor.\n");
        exit(1);
    }
    printf("ID numaraniz %d olarak belirlenmistir.",ID);
    uyeListesi[kayitYapilacakIndex].IDkutuphane=ID;

    printf("Lutfen sirasiyla ad-soyad bilginizi giriniz:");
    scanf("%s%s",&uyeAd,&uyeSoyad);

    uyeListesi[kayitYapilacakIndex].uyeAd=(char*)malloc(sizeof(char)*(strlen(uyeAd)+1));
    uyeListesi[kayitYapilacakIndex].uyeSoyad=(char*)malloc(sizeof(char)*(strlen(uyeSoyad)+1));
    strcpy(uyeListesi[kayitYapilacakIndex].uyeAd,uyeAd);
    strcpy(uyeListesi[kayitYapilacakIndex].uyeSoyad,uyeSoyad);

    printf("Lutfen ogrenciyseniz 'O' calisansaniz 'C' giriniz:");
    fflush(stdin);//bu komutu yazmadığımda benim derleyicimde kullanıcıdan almadı.o yüzden bu komutu yazdım
    ch=getchar();
    if(ch=='O')
    {
        uyeListesi[kayitYapilacakIndex].kisiYetkisi=ogrenci;
    }
    else
    {
        uyeListesi[kayitYapilacakIndex].kisiYetkisi=calisan;
    }

    printf("Lutfen sifrenizi giriniz:");
    scanf("%d",&uyeListesi[kayitYapilacakIndex].sifre);

    return uyeListesi[kayitYapilacakIndex].kisiYetkisi;
}


void kitaplariGoruntule(kitapinfo *kitaplik)
{
    int i;
    for(i=0; i<MAX_KITAP_SAYISI; i++)
    {
        if(kitaplik[i].sayfaSayisi!=0)
        {
            printf("Kitap Adi:%s\n",kitaplik[i].Ad);
            printf("Kitap Yazari:%s %s\n",kitaplik[i].kYazarAd,kitaplik[i].kYazarSoyad);
            printf("Kitap Yayinevi:%s\n",kitaplik[i].yayinEvi);
            printf("Kitap Sayfa Sayisi:%d\n",kitaplik[i].sayfaSayisi);
            if(kitaplik[i].kitapDurumu==0)
            {
                printf("Bu kitap raftadir.\n");
            }
            else
            {
                printf("Bu kitap alinmistir.\n");
            }
            printf("--------------------------------------------------------------------------------------\n");
        }
        else
        {
            return;
        }
    }
}

void kitapAra(kitapinfo *kitaplik)
{
    int i=0;
    char kitapAdi[30];

    printf("Lutfen aramak istediginiz kitabin adini giriniz:");
    scanf("%s",&kitapAdi);

    while(i<MAX_KITAP_SAYISI && kitaplik[i].sayfaSayisi!=0)
    {
        if(strcmp(kitaplik[i].Ad,kitapAdi)==0)
        {
            printf("Kitap Adi:%s\n",kitaplik[i].Ad);
            printf("Kitap Yazari:%s %s\n",kitaplik[i].kYazarAd,kitaplik[i].kYazarSoyad);
            printf("Kitap Yayinevi:%s\n",kitaplik[i].yayinEvi);
            printf("Kitap Sayfa Sayisi:%d\n",kitaplik[i].sayfaSayisi);
            return;
        }
        i++;
    }
    printf("Maalesef...Aradiginiz kitap kutuphanemizde bulunmuyor.\n");
}

void kitapEkle(kitapinfo *kitaplik)
{
    int sayfaSayisi,i;
    char Ad[30],yayinEvi[30],yazarAdi[30],yazarSoyadi[30];
    printf("Lutfen kitap adini giriniz:");
    scanf("%s",&Ad);
    printf("Lutfen kitap yayinevi bilgisini giriniz:");
    scanf("%s",&yayinEvi);
    printf("Lutfen kitabin yazar adini ve soyadini sirasiyla giriniz:");
    scanf("%s %s",&yazarAdi,&yazarSoyadi);
    printf("Lutfen kitabin sayfa sayisini giriniz:");
    scanf("%d",&sayfaSayisi);

    for(i=0; i<MAX_KITAP_SAYISI; i++)
    {
        if(kitaplik[i].sayfaSayisi==0)
        {
            kitaplik[i].Ad=(char*)malloc(sizeof(char)*(strlen(Ad)+1));
            kitaplik[i].yayinEvi=(char*)malloc(sizeof(char)*(strlen(yayinEvi)+1));
            kitaplik[i].kYazarAd=(char*)malloc(sizeof(char)*(strlen(yazarAdi)+1));
            kitaplik[i].kYazarSoyad=(char*)malloc(sizeof(char)*(strlen(yazarSoyadi)+1));
            strcpy(kitaplik[i].Ad,Ad);
            strcpy(kitaplik[i].kYazarAd,yazarAdi);
            strcpy(kitaplik[i].kYazarSoyad,yazarSoyadi);
            strcpy(kitaplik[i].yayinEvi,yayinEvi);
            kitaplik[i].sayfaSayisi=sayfaSayisi;
            break;
        }
    }
}

void uyeleriGoruntule(kisiinfo *uyeListesi)
{
    int i=0;
    while(i<MAX_KISI_SAYISI && uyeListesi[i].IDkutuphane!=0)
    {
        printf("Uye Adi-Soyadi:%s %s\n",uyeListesi[i].uyeAd,uyeListesi[i].uyeSoyad);
        printf("Uye ID Bilgisi:%d\n",uyeListesi[i].IDkutuphane);
        if(uyeListesi[i].kisiYetkisi==1)
        {
            printf("Uye Durumu: Calisan\n");
        }
        else
        {
            printf("Uye Durumu: Ogrenci\n");
        }
        printf("--------------------------------------------------------------------------------------\n");
        i++;
    }
}





int girisYap(kisiinfo *uyeListesi)
{
    int ID,sifre,i;
    printf("Lutfen kutuphane ID bilginizi giriniz:");
    scanf("%d",&ID);
    printf("Lutfen kutuphane sifre bilginizi giriniz:");
    scanf("%d",&sifre);
    for(i=0; i<MAX_KISI_SAYISI; i++)
    {
        if(uyeListesi[i].IDkutuphane==ID)
        {
            if(uyeListesi[i].sifre==sifre)
            {
                printf("ID-Sifre dogru...Giris Basarili.\n");
                return uyeListesi[i].kisiYetkisi;
            }
            return -1;//sifre yanlis girildi.giris basarisiz.
        }
    }
    return -2;//O ID DEÐERÝNE AÝT KÝMSE BULUNAMADI.
}

void uyeleriAktar(kisiinfo *uyeListesi)
{
    FILE *uyeKayitlari;
    int i;
    char ad[20],soyad[20];

    uyeKayitlari=fopen("uyeListesi.txt","r");
    if(uyeKayitlari==NULL)
    {
        fprintf(stderr,"Uye listesine ulasilirken bir hata meydana geldi.\n");
        exit(1);
    }

    while(!feof(uyeKayitlari))
    {
        for(i=0; i<MAX_KISI_SAYISI; i++)
        {
            if(uyeListesi[i].IDkutuphane==0)
            {
                fscanf(uyeKayitlari,"%s\t%s\t%d\t%d\t%d\n",ad,soyad,&uyeListesi[i].kisiYetkisi,&uyeListesi[i].IDkutuphane,&uyeListesi[i].sifre);
                uyeListesi[i].uyeAd=(char*)malloc(sizeof(char)*(strlen(ad)+1));
                uyeListesi[i].uyeSoyad=(char*)malloc(sizeof(char)*(strlen(soyad)+1));
                strcpy(uyeListesi[i].uyeAd,ad);
                strcpy(uyeListesi[i].uyeSoyad,soyad);
                break;
            }

        }
    }
    fclose(uyeKayitlari);
}

void kitaplariAktar(kitapinfo *kitaplik)
{
    char Ad[30],yazarAdi[30],yayinEvi[30],yazarSoyadi[30];
    FILE *kitapKayitlari;
    int i;

    kitapKayitlari=fopen("kitapListesi.txt","r");
    if(kitapKayitlari==NULL)
    {
        fprintf(stderr,"Kitap listesine ulasilirken bir hata meydana geldi.\n");
        exit(1);
    }

    while(!feof(kitapKayitlari))
    {
        for(i=0; i<MAX_KITAP_SAYISI; i++)
        {
            if(kitaplik[i].sayfaSayisi==0)
            {
                fscanf(kitapKayitlari,"%s\t%s\t%s\t%s\t%d\t%d\n",Ad,yayinEvi,yazarAdi,yazarSoyadi,&kitaplik[i].kitapDurumu,&kitaplik[i].sayfaSayisi);
                kitaplik[i].Ad=(char*)malloc(sizeof(char)*(strlen(Ad)+1));
                kitaplik[i].kYazarAd=(char*)malloc(sizeof(char)*(strlen(yazarAdi)+1));
                kitaplik[i].kYazarSoyad=(char*)malloc(sizeof(char)*(strlen(yazarSoyadi)+1));
                kitaplik[i].yayinEvi=(char*)malloc(sizeof(char)*(strlen(yayinEvi)+1));
                strcpy(kitaplik[i].Ad,Ad);
                strcpy(kitaplik[i].kYazarAd,yazarAdi);
                strcpy(kitaplik[i].kYazarSoyad,yazarSoyadi);
                strcpy(kitaplik[i].yayinEvi,yayinEvi);
                break;

            }
        }
    }
    fclose(kitapKayitlari);
}
void kitaplariYedekle(kitapinfo *kitaplik)
{
    FILE *kitapKayitlari;
    int i=0;

    kitapKayitlari=fopen("kitapListesi.txt","w");
    if(kitapKayitlari==NULL)
    {
        fprintf(stderr,"Kitap listesine ulasilirken bir hata meydana geldi.\n");
        exit(1);
    }

    while(i<MAX_KITAP_SAYISI && kitaplik[i].sayfaSayisi!=0)
    {
        fprintf(kitapKayitlari,"%s\t%s\t%s\t%s\t%d\t%d\n",kitaplik[i].Ad,kitaplik[i].yayinEvi,kitaplik[i].kYazarAd,kitaplik[i].kYazarSoyad,kitaplik[i].kitapDurumu,kitaplik[i].sayfaSayisi);
        i++;
    }
    fclose(kitapKayitlari);
}
void uyeleriYedekle(kisiinfo *uyeListesi)
{
    FILE *uyeKayitlari;
    int i=0;

    uyeKayitlari=fopen("uyeListesi.txt","w");
    if(uyeKayitlari==NULL)
    {
        fprintf(stderr,"Uye listesine ulasilirken bir hata meydana geldi.\n");
        exit(1);
    }
    while(i<MAX_KISI_SAYISI&& uyeListesi[i].IDkutuphane!=0)
    {
        fprintf(uyeKayitlari,"%s\t%s\t%d\t%d\t%d\n",uyeListesi[i].uyeAd,uyeListesi[i].uyeSoyad,uyeListesi[i].kisiYetkisi,uyeListesi[i].IDkutuphane,uyeListesi[i].sifre);
        i++;
    }
    fclose(uyeKayitlari);
}

int main(void)
{
    kitapinfo *kitaplik;
    kisiinfo *uyeListesi;
    YetkiSeviyeleri uyeYetkisi;
    int girisDurumu;
    char ch;

    kitaplik=(kitapinfo*)calloc(MAX_KITAP_SAYISI,sizeof(kitapinfo));
    uyeListesi=(kisiinfo*)calloc(MAX_KISI_SAYISI,sizeof(kisiinfo));

    uyeleriAktar(uyeListesi);//kitaplik ve üyelistesi arraylerine aktarým saðlandý.
    kitaplariAktar(kitaplik);

    ///KAYIT OL-GÝRÝÞ YAP
    printf("\t\t\tMerhaba,Kutuphane sistemimize hosgeldiniz\n");
    printf("1.Sisteme kayit  olmak istiyorsaniz 'K'\n2.Sisteme giris yapmak istiyorsaniz 'G' tuslayiniz:");
    fflush(stdin);
    ch=getchar();
    if(ch=='K'||ch=='k')
    {
        girisDurumu=kayitOl(uyeListesi);//ogrenci mi,yoksa calisan mi.
    }
    else if(ch=='G'||ch=='g')
    {
        girisDurumu=girisYap(uyeListesi);//ogrenci mi,yoksa calisan mi.
        if(girisDurumu==-1)
        {
            printf("Sifrenizi yanlis girdiniz...Giris yapilamiyor.\n");
                  (1);
        }
        else if(girisDurumu==-2)
        {
            printf("Boyle bir ID degeri sistemde kayitli degil...Giris yapilamiyor.\n");
            exit(1);
        }
    }
    else
    {
        printf("Yanlis bir tuslama yaptiniz...Sistemden cikiliyor.\n");
        exit(1);
    }

    /////UYENIN YETKÝSÝNÝ BELÝRLEME
    if(girisDurumu==1)
    {
        uyeYetkisi=calisan;
    }
    else
    {
        uyeYetkisi=ogrenci;
    }

    if(uyeYetkisi==ogrenci)
    {
        do
        {
            printf("1.Tum kitaplari goruntulemek icin 'G' tuslayiniz\n2.Kitap aramak icin 'A' tuslayiniz\n3.Cikis yapmak icin 'Q' tuslayiniz:");
            fflush(stdin);
            ch=getchar();
            switch(ch)
            {
            case 'G':
            case 'g':
                kitaplariGoruntule(kitaplik);
                break;
            case 'A':
            case 'a':
                kitapAra(kitaplik);
                break;
            case 'Q':
            case 'q':
                kitaplariYedekle(kitaplik);//cikis yapilirken, tüm kitaplar ve üye bilgileri dosyaya kaydediliyor.
                uyeleriYedekle(uyeListesi);
                printf("Cikis yapiliyor...");
                break;
            default:
                printf("Hatali bir tuslama yaptiniz");
                break;
            }
        }
        while(ch!='Q');
    }
    else
    {
        do
        {
            printf("1.Kitap eklemek istiyorsaniz 'E' tuslayiniz\n2.Tum uyeleri goruntulemek istiyorsaniz 'U' tuslayiniz\n3.Cikis yapmak istiyorsaniz 'Q' tuslayiniz:");
            fflush(stdin);
            ch=getchar();
            switch(ch)
            {
            case 'E':
            case 'e':
                kitapEkle(kitaplik);
                break;
            case 'U':
            case 'u':
                uyeleriGoruntule(uyeListesi);
                break;
            case 'Q':
            case 'q':
                uyeleriYedekle(uyeListesi);
                kitaplariYedekle(kitaplik);
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Yanlis bir tuslama yaptiniz.\n");
                break;
            }

        }
        while(ch!='Q');
    }
    return 0;
}
