#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Mustafa Güray Orhan 190201111
typedef struct komsu{
    int plakaKodu;
    struct komsu *ileri;
}komsu;

typedef struct sehir{
    char sehirAdi[20];
    char bolge[10];
    int plakaKodu;
    int komsuSayisi;
    struct komsu *komsular;
    struct sehir *ileri;
    struct sehir *geri;
}sehir;

int index = 0;
struct sehir* baslangic = NULL;

struct komsu* komsuOlustur(int plakakodu){
    struct komsu* yeniKomsu = (struct komsu*)malloc(sizeof(struct komsu));
    yeniKomsu->ileri = NULL;
    yeniKomsu->plakaKodu = plakakodu;
    return yeniKomsu;
}

int komsuEkle(int plakakodu,sehir *sehirBilgi){
    struct komsu *eklencek = komsuOlustur(plakakodu);
    struct komsu *kopyaBaslangic = sehirBilgi->komsular;
    struct komsu *gecici;

    if(kopyaBaslangic->ileri == NULL && kopyaBaslangic->plakaKodu < eklencek->plakaKodu){
        kopyaBaslangic->ileri = eklencek;
        return 1;
    }
    if(kopyaBaslangic->plakaKodu > eklencek->plakaKodu){
        eklencek->ileri = kopyaBaslangic;
        sehirBilgi->komsular = eklencek;
        return 1;
    }
    while(kopyaBaslangic->ileri->plakaKodu < eklencek->plakaKodu && kopyaBaslangic->ileri->ileri != NULL){
       kopyaBaslangic = kopyaBaslangic->ileri;
    }
    if(kopyaBaslangic->ileri->ileri == NULL && kopyaBaslangic->ileri->plakaKodu < eklencek->plakaKodu){
        kopyaBaslangic->ileri->ileri = eklencek;
        return 1;
    }

    gecici = kopyaBaslangic->ileri;
    kopyaBaslangic->ileri = eklencek;
    eklencek->ileri = gecici;
    return 1;
}

struct sehir* sehirOlustur(char sehirAdi[],char bolge[] ,int plakaKodu ,int komsuSayisi){
    struct sehir* yeniSehir = (struct sehir*)malloc(sizeof(struct sehir));
    strcpy(yeniSehir->bolge,bolge);
    strcpy(yeniSehir->sehirAdi,sehirAdi);
    yeniSehir->plakaKodu = plakaKodu;
    yeniSehir->komsuSayisi = komsuSayisi;
    yeniSehir->ileri = NULL;
    yeniSehir->geri = NULL;
    return yeniSehir;
}

int sehireKomsulariEkle(sehir *x,int plaka){
        if(x->komsuSayisi == 0){
            x->komsular = komsuOlustur(plaka);
            x->komsuSayisi++;
        }
        else{
            komsuEkle(plaka,x);
            x->komsuSayisi++;
        }
}


int sehirEkle(char sehirAdi[],char bolge[] ,int plakaKodu ,int komsuSayisi){
    struct sehir *eklencek = sehirOlustur(sehirAdi,bolge,plakaKodu,komsuSayisi);
    struct sehir *kopyaBaslangic;
    struct sehir *gecici;
    kopyaBaslangic = baslangic;
    //En Baþa Ekler
    if(index == 0 && kopyaBaslangic->plakaKodu < eklencek->plakaKodu ){
        kopyaBaslangic->ileri = eklencek;
        eklencek->geri = kopyaBaslangic;
        index++;
        return 1;
    }
    else if(kopyaBaslangic->plakaKodu > eklencek->plakaKodu){
        eklencek->ileri = kopyaBaslangic;
        kopyaBaslangic->geri = eklencek;
        baslangic = eklencek;
        index++;
        return 1;
    }
    while(kopyaBaslangic->ileri->plakaKodu < eklencek->plakaKodu && kopyaBaslangic->ileri->ileri != NULL){
        kopyaBaslangic = kopyaBaslangic->ileri;
    }

    if(kopyaBaslangic->ileri->ileri == NULL && eklencek->plakaKodu > kopyaBaslangic->ileri->plakaKodu){
        kopyaBaslangic->ileri->ileri = eklencek;
        eklencek->geri = kopyaBaslangic->ileri;
        eklencek->ileri = NULL;
        index++;
        return 1;
    }
    gecici = kopyaBaslangic->ileri;
    kopyaBaslangic->ileri = eklencek;
    eklencek->geri = kopyaBaslangic;
    eklencek->ileri = gecici;
    gecici->geri = eklencek;
    index++;
    return 1;
}

int sehirSil(int plakaKodu){
    struct sehir *kopyaBaslangic = baslangic;
    struct sehir *gecici;
    if(kopyaBaslangic->plakaKodu == plakaKodu){
        baslangic = kopyaBaslangic->ileri;
        baslangic->geri = NULL;
        return 1;
    }
    while(kopyaBaslangic->ileri->plakaKodu != plakaKodu && kopyaBaslangic->ileri->ileri != NULL){
       kopyaBaslangic = kopyaBaslangic->ileri;
    }
    if(kopyaBaslangic->ileri->ileri == NULL && kopyaBaslangic->ileri->plakaKodu == plakaKodu){
        kopyaBaslangic->ileri = NULL;
        return 1;
    }
    if(kopyaBaslangic->ileri->plakaKodu == plakaKodu){
        gecici = kopyaBaslangic->ileri->ileri;
        kopyaBaslangic->ileri = gecici;
        gecici->geri = kopyaBaslangic->ileri;
        return 1;
    }
    printf("Silinicek Deger Sehir Listesinde Bulunmamaktadir.\n");
    return 0;
}

int komsuSil(int plakaKodu,sehir *gelenSehir){
    struct komsu *kopyaBaslangic = gelenSehir->komsular;
    struct komsu *gecici;
    if(kopyaBaslangic->plakaKodu == plakaKodu){
        gelenSehir->komsular = kopyaBaslangic->ileri;
        return 1;
    }
    while(kopyaBaslangic->ileri->plakaKodu != plakaKodu && kopyaBaslangic->ileri->ileri != NULL){
       kopyaBaslangic = kopyaBaslangic->ileri;
    }
    if(kopyaBaslangic->ileri->ileri == NULL && kopyaBaslangic->ileri->plakaKodu == plakaKodu){
        kopyaBaslangic->ileri = NULL;
        return 1;
    }
    if(kopyaBaslangic->ileri->plakaKodu == plakaKodu){
        kopyaBaslangic->ileri = kopyaBaslangic->ileri->ileri;
        return 1;
    }

    printf("Silinicek Deger Komsu Listesinde Bulunmamaktadir.\n");
    return 0;
}

// varsa sehiri getirir yoksa gecici olarak plaka kodu 0 olan bos bir sehir getirir
struct sehir* sehirAra(int plakaKodu){
    struct sehir *kopyaBaslangic = baslangic;

    if(kopyaBaslangic->plakaKodu == plakaKodu){
        return kopyaBaslangic;
    }
    while(kopyaBaslangic->ileri->plakaKodu != plakaKodu && kopyaBaslangic->ileri->ileri != NULL){
        kopyaBaslangic = kopyaBaslangic->ileri;
    }
    if(kopyaBaslangic->ileri->ileri == NULL && kopyaBaslangic->ileri->plakaKodu == plakaKodu){
        return kopyaBaslangic->ileri;
    }
    else if(kopyaBaslangic->ileri->ileri != NULL && kopyaBaslangic->ileri->plakaKodu == plakaKodu){
        return kopyaBaslangic->ileri;
    }
    struct sehir *gecici = (struct sehir*)malloc(sizeof(struct sehir));
    gecici->plakaKodu = 0;
    return gecici;
}

struct sehir* sehirAraAdGore(char ad[]){
    struct sehir *kopyaBaslangic = baslangic;
    if(strcmp(ad,kopyaBaslangic->sehirAdi) == 0){
        return kopyaBaslangic;
    }
    while(strcmp(ad,kopyaBaslangic->ileri->sehirAdi) != 0 && kopyaBaslangic->ileri->ileri != NULL){
        kopyaBaslangic = kopyaBaslangic->ileri;
    }
    if(kopyaBaslangic->ileri->ileri == NULL && strcmp(ad,kopyaBaslangic->ileri->sehirAdi) == 0){
        return kopyaBaslangic->ileri;
    }
    else if(kopyaBaslangic->ileri->ileri != NULL && strcmp(ad,kopyaBaslangic->ileri->sehirAdi) == 0){
        return kopyaBaslangic->ileri;
    }
    struct sehir *gecici = (struct sehir*)malloc(sizeof(struct sehir));
    strcpy(gecici->sehirAdi,"Bos");
    return gecici;
}


//bolgeye gore arama yapma bolumu
void bolgeyeGoreGetir(char bolge[]){
    struct sehir *kopyaBaslangic = baslangic;
    int sayi = 0;
    while(kopyaBaslangic->ileri != NULL){
        int deger = strcmp(kopyaBaslangic->bolge, bolge);
        if(deger == 0){
            printf("Sehir Adi: %s - Sehir Plaka Kodu: %d - Sehir Komsu Sayisi: %d\n",kopyaBaslangic->sehirAdi,kopyaBaslangic->plakaKodu,kopyaBaslangic->komsuSayisi);
            sayi++;
        }
        kopyaBaslangic = kopyaBaslangic->ileri;
    }
    if(sayi == 0){
        printf("Kritere Gore Kayit Bulunmamaktadir.\n");
        sayi = 0;
    }
}

//komsu sayisina gore arama yapma bolumu
void komsuSayisinaGoreGetir(int komsuSayisiKriteri,int ustKomsuSayisi){
    struct sehir *kopyaBaslangic = baslangic;
    int sayi = 0;
    while(kopyaBaslangic->ileri != NULL){
        if(kopyaBaslangic->komsuSayisi >= komsuSayisiKriteri && kopyaBaslangic->komsuSayisi <= ustKomsuSayisi){
            printf("Sehir Adi: %s - Sehir Plaka Kodu: %d - Sehir Komsu Sayisi: %d\n",kopyaBaslangic->sehirAdi,kopyaBaslangic->plakaKodu,kopyaBaslangic->komsuSayisi);
            sayi++;
        }
        kopyaBaslangic = kopyaBaslangic->ileri;
    }
    if(sayi == 0){
        printf("Kritere Gore Kayit Bulunmamaktadir.\n");
        sayi = 0;
    }
}
void dosyayaAktar(){
    struct sehir *kopyaBaslangic = baslangic;
    struct sehir *gecici;
    struct komsu *kopyaKomsuBaslangic;
    FILE *dosya;

    dosya = fopen("cikti.txt", "w+");
    fprintf(dosya,"Sehir Plaka Kodu: %d - Adi: %s - Bolge: %s - Komsular: --> ",kopyaBaslangic->plakaKodu,kopyaBaslangic->sehirAdi,kopyaBaslangic->bolge);
    if(kopyaBaslangic->komsuSayisi > 0 ){
            kopyaKomsuBaslangic = kopyaBaslangic->komsular;
        while(kopyaKomsuBaslangic->ileri != NULL && kopyaBaslangic->komsuSayisi != 0){
            gecici = sehirAra(kopyaKomsuBaslangic->plakaKodu);
            fprintf(dosya,"Sehir Plaka Kodu: %d - Adi: %s - Bolge: %s --> ",gecici->plakaKodu,gecici->sehirAdi,gecici->bolge);
            kopyaKomsuBaslangic = kopyaKomsuBaslangic->ileri;
        }
        if(kopyaBaslangic->komsuSayisi != 0){
                gecici = sehirAra(kopyaKomsuBaslangic->plakaKodu);
            fprintf(dosya,"Sehir Plaka Kodu: %d - Adi: %s - Bolge: %s \n",gecici->plakaKodu,gecici->sehirAdi,gecici->bolge);
                fprintf(dosya,"   /\\ \n");
                fprintf(dosya,"   II\n");
                fprintf(dosya,"   \\/ \n");
        }
    }
    else{
        fprintf(dosya,"\n\n");
        fprintf(dosya,"   /\\ \n");
        fprintf(dosya,"   II\n");
        fprintf(dosya,"   \\/ \n\n");
    }

    while(kopyaBaslangic->ileri != NULL && kopyaBaslangic->ileri->komsuSayisi != 82){
        kopyaBaslangic = kopyaBaslangic->ileri;
        if(kopyaBaslangic->plakaKodu != 82){
            fprintf(dosya,"Sehir Plaka Kodu: %d - Adi: %s - Bolge: %s - Komsular: --> ",kopyaBaslangic->plakaKodu,kopyaBaslangic->sehirAdi,kopyaBaslangic->bolge);
        }
        if(kopyaBaslangic->komsuSayisi > 0){
        kopyaKomsuBaslangic = kopyaBaslangic->komsular;
        while(kopyaKomsuBaslangic->ileri != NULL && kopyaBaslangic->ileri->komsuSayisi != 0){
            gecici = sehirAra(kopyaKomsuBaslangic->plakaKodu);
            fprintf(dosya,"Sehir Plaka Kodu: %d - Adi: %s - Bolge: %s --> ",gecici->plakaKodu,gecici->sehirAdi,gecici->bolge);
            kopyaKomsuBaslangic = kopyaKomsuBaslangic->ileri;
        }
        gecici = sehirAra(kopyaKomsuBaslangic->plakaKodu);
        fprintf(dosya,"Sehir Plaka Kodu: %d - Adi: %s - Bolge: %s \n",gecici->plakaKodu,gecici->sehirAdi,gecici->bolge);
            fprintf(dosya,"   /\\ \n");
            fprintf(dosya,"   II\n");
            fprintf(dosya,"   \\/ \n");
        }
        else{
            if(kopyaBaslangic->plakaKodu != 82){
                fprintf(dosya,"\n \n");
                fprintf(dosya,"   /\\ \n");
                fprintf(dosya,"   II\n");
                fprintf(dosya,"   \\/ \n \n");
            }
        }
    }
    fclose(dosya);
}

int bonusSehir(int x,int y,char ilkSehir[],char ikinciSehir[]){
    struct sehir *kopyaBaslangic = baslangic;
    struct komsu *kopyaKomsuBaslangic = baslangic->komsular;
    struct sehir *xSehir = sehirAraAdGore(ilkSehir);
    struct sehir *ySehir = sehirAraAdGore(ikinciSehir);
    int sehirler = 0,kacDeger = 0;
    if(strcmp(xSehir->sehirAdi,"Bos") == 0 || strcmp(ySehir->sehirAdi,"Bos") == 0){
            printf("Girilen Sehir Isimleri Bulunmamaktadir.\n");
            return 0;
    }
    if(kopyaBaslangic->komsuSayisi > x && kopyaBaslangic->komsuSayisi < y){
            if(kopyaKomsuBaslangic->plakaKodu == xSehir->plakaKodu){
                        sehirler++;
            }else if(kopyaKomsuBaslangic->plakaKodu == ySehir->plakaKodu){
                        sehirler++;
            }
            while(kopyaKomsuBaslangic->ileri != NULL){
                kopyaKomsuBaslangic = kopyaKomsuBaslangic->ileri;

                if(kopyaKomsuBaslangic->plakaKodu == xSehir->plakaKodu){
                        sehirler++;
                }
                if(kopyaKomsuBaslangic->plakaKodu == ySehir->plakaKodu){
                        sehirler++;
                }
            }
    }
    if(sehirler > 1){
        printf("Hem %s hem de %s `ya komsu olan sehirler: %s - ",xSehir->sehirAdi,ySehir->sehirAdi,kopyaBaslangic->sehirAdi);
        kacDeger++;
        sehirler = 0;
    }
    else{
        sehirler = 0;
        printf("Hem %s hem de %s `ya komsu olan sehirler: ",xSehir->sehirAdi,ySehir->sehirAdi);
    }
    while(kopyaBaslangic->ileri != NULL && kopyaBaslangic->ileri->komsuSayisi != 82){
        kopyaBaslangic = kopyaBaslangic->ileri;
        if(kopyaBaslangic->komsuSayisi > x && kopyaBaslangic->komsuSayisi < y){
            kopyaKomsuBaslangic = kopyaBaslangic->komsular;
            if(kopyaKomsuBaslangic->plakaKodu == xSehir->plakaKodu || kopyaKomsuBaslangic->plakaKodu == ySehir->plakaKodu){
                        sehirler++;
            }
            while(kopyaKomsuBaslangic->ileri != NULL){
                kopyaKomsuBaslangic = kopyaKomsuBaslangic->ileri;
                if(kopyaKomsuBaslangic->plakaKodu == xSehir->plakaKodu){
                        sehirler++;
                }
                else if(kopyaKomsuBaslangic->plakaKodu == ySehir->plakaKodu){
                        sehirler++;
                }
            }
        }
    if(sehirler > 1){
        printf(" %s  ",kopyaBaslangic->sehirAdi);
        kacDeger++;
        sehirler = 0;
    }
    else{
        sehirler = 0;
    }
    }
    if(kacDeger < 1 ){
       printf("Eslesen Hic Bir Deger Bulunamadi.");
    }
    printf("\n");
}

void sehirEkleFonk(){
    int komsuSayisi = 0,plaka;
    char ad[20],bolge1[5];
    printf("Sehir Adi:");scanf("%s",ad);
    printf("Bolge:");scanf("%s",bolge1);
    printf("Plaka kodu:");scanf("%d",&plaka);
    char ek[20];
    struct sehir *w,*y;
    w = sehirAra(plaka);
    y = sehirAraAdGore(ad);
    if(w->plakaKodu != 0 || strcmp(y->sehirAdi,"Bos") != 0){
        printf("Sehir Bilgileri Ayni Olan Kayit Bulunmaktadir.\n");
    }else{
        sehirEkle(ad,bolge1,plaka,komsuSayisi);
        for(int i = 0; ; i++){
            printf("Komsu Ismi giriniz(Cikis: Bitti):");scanf("%s",ek);
            if(strcmp(ek,"Bitti")==0){
                break;
            }
            struct sehir *g,*u;
            g = sehirAraAdGore(ek);
            u = sehirAraAdGore(ad);
            if(strcmp(u->sehirAdi,"Bos") == 0 || strcmp(g->sehirAdi,"Bos")==0){
                printf("Sehir Ismi Bulunmamaktadir.\n");
            }else{
                sehireKomsulariEkle(u,g->plakaKodu);
            }
        }
    }
}

int main()
{
    baslangic = sehirOlustur("default","default",82,0);
    char okunanVeri[100];
    FILE *sehirDosya;
    char * gecici;
    char ad[20],bolge[5];
    int komsuSayisi=0,plaka,konum=0,seksenbir= 0;
    sehirDosya = fopen("sehirler.txt", "r");
    while(!feof(sehirDosya)){
        fgets(okunanVeri,100,sehirDosya);
        gecici = strtok (okunanVeri,",");
        while (gecici != NULL){
            if(konum == 0){
                int t = atoi(gecici);
                plaka = t;
                gecici = strtok (NULL, ",");
                if(plaka  == 81){
                    seksenbir++;
                }
                konum++;
            }else if(konum == 1){
                strcpy(ad,gecici);
                gecici = strtok (NULL, ",");
                konum++;
            }else if(konum == 2){
                strcpy(bolge,gecici);

                konum++;
            }else{
                gecici = strtok (NULL, ", \n");
            }

        }

        if((ad,"null") != 0 && strcmp(bolge,"null") != 0){
            sehirEkle(ad,bolge,plaka,komsuSayisi);
        }
        strcpy(ad,"null");
        strcpy(bolge,"null");
        komsuSayisi = 0;
        komsuSayisi=0;
        konum = 0;
    }
    close(sehirDosya);
    sehirDosya = fopen("sehirler.txt", "r");
    int a=0;
    while(!feof(sehirDosya)){
        struct sehir *x,*y;
        fgets(okunanVeri,100,sehirDosya);
        gecici = strtok (okunanVeri,",");
        int t = atoi(gecici);
        if(t == 81){
           a++;
        }
        if(a != 2){
            gecici = strtok (NULL, ",");
            strcpy(ad,gecici);
            x = sehirAraAdGore(ad);
            gecici = strtok (NULL, ",");
            while (gecici != NULL)
            {
                gecici = strtok (NULL, ",\n");
                if(gecici != NULL){
                    strcpy(ad,gecici);
                    y = sehirAraAdGore(ad);
                    if(strcmp(y->sehirAdi,"Bos") != 0){
                        sehireKomsulariEkle(x,y->plakaKodu);
                    }
                }
            }
        }
    }
    close(sehirDosya);
    dosyayaAktar();

    while(1 == 1){
        bas:
        printf("----------------------------------------------------------------------\n");
        printf("1. Yeni Sehir Ekle veya Kosmuluk Ekle\n");
        printf("2. Sehir Ismi veya Plaka Kodu ile Sehir ve Komsu Sehirleri Goster.\n");
        printf("3. Sehir veya Sehrin Komsuluk Kaydi Silme\n");
        printf("4. Komsu Sayisina Gore Ara\n");
        printf("5. Bolge Adina Gore Ara\n");
        printf("6. Bonus - Iki Ile Komsu Ve Komsu Sayisi Araligina Gore Arama\n");
        printf("7. Cikti.txt Dosyasini Yaz\n");
        printf("0. Cikis\n");
        printf("----------------------------------------------------------------------\n");
        printf("Seciminiz: ");
        int islem;
        scanf("%d",&islem);
        printf("----------------------------------------------------------------------\n");
        if(islem == 1){
            printf("1. Yeni sehir ekle\n");
            printf("2. Yeni kosmuluk ekle\n");
            printf("0. Basa Don.\n");
            printf("----------------------------------------------------------------------\n");
            int altIslem;
            printf("Isleminiz: ");scanf("%d",&altIslem);
            printf("----------------------------------------------------------------------\n");
            if(altIslem == 0){
                goto bas;
            }
            if(altIslem == 1){
                sehirEkleFonk();
            }else if(altIslem == 2){
                int sehirPlaka;
                char eklcekKomsuPlaka[20];
                Tekrar1:
                printf("Ekliceniz Komsunun Sehir Plakasini Giriniz:");
                scanf("%d",&sehirPlaka);
                struct sehir *gecici = sehirAra(sehirPlaka);
                struct sehir *g;
                if(gecici->plakaKodu == 0){
                    printf("Boyle Bir Kayit Bulunmamaktadir.\n");
                    goto Tekrar1;
                }
                else{
                    Tekrar4:
                    printf("Ekliceniz Komsunun Adini Giriniz:");
                    scanf("%s",eklcekKomsuPlaka);
                    g = sehirAraAdGore(eklcekKomsuPlaka);
                    if(strcmp(g->sehirAdi,"Bos") == 0){
                        printf("Sehir Ismi Bulunmamaktadir.\n");
                        goto Tekrar4;
                    }
                    else{
                        komsuEkle(g->plakaKodu,gecici);
                        gecici->komsuSayisi++;
                    }
                }
            }
        }else if(islem == 2){
            printf("1. Sehir Ismi Ile Sehir Ve Komsu Sehirleri Goster\n");
            printf("2. Plaka Kodu Ile Sehir Ve Komsu Sehirleri Goster\n");
            printf("0. Basa Don.\n");
            printf("----------------------------------------------------------------------\n");
            int ek5,plaka1;
            char ad1[20];
            printf("Seciminiz: ");
            scanf("%d",&ek5);
            printf("----------------------------------------------------------------------\n");
            if(ek5 == 0){
                goto bas;
            }
            struct sehir *x,*p;
            struct komsu *y;
            if(ek5 == 1){
                printf("Sehir Ismi Giriniz: ");
                scanf("%s",ad1);
                x = sehirAraAdGore(ad1);
                if(strcmp(x->sehirAdi,"Bos") == 0){
                    printf("Boyle Bir Sehir Bulunmamaktadir. Sehiri Eklemek Istermisiniz : ? (1-Evet/2-Hayir): ");
                    int a = 0;
                    scanf("%d",&a);
                    if(a == 1){
                        sehirEkleFonk();
                    }else{
                        printf("Sehir Eklemesi Iptal Edildi.\n");
                    }
                }
                else{
                    y = x->komsular;
                    printf("Sehir Adi: %s , Sehir Plaka Kodu: %d ,Sehir Bolgesi: %s ,Komsu Sayisi: %d\n - Komsulari - \n",x->sehirAdi,x->plakaKodu,x->bolge,x->komsuSayisi);
                    for(int i = 0;i < x->komsuSayisi ; i++){
                        p=sehirAra(y->plakaKodu);
                        printf("Sehir Adi: %s , Sehir Plaka Kodu: %d ,Sehir Bolgesi: %s ,Komsu Sayisi: %d \n",p->sehirAdi,p->plakaKodu,p->bolge,p->komsuSayisi);
                        y = y->ileri;
                    }
                }
            }
            else if(ek5 == 2){
                printf("Sehir Plakasi Giriniz: ");
                scanf("%d",&plaka1);
                x = sehirAra(plaka1);
                if(x->plakaKodu == 0){
                    printf("Boyle Bir Plaka Bulunmamaktadir.Sehiri Eklemek Istermisiniz : ? (1-Evet/2-Hayir): ");
                    int a = 0;
                    scanf("%d",&a);
                    if(a == 1){
                        sehirEkleFonk();
                    }else{
                        printf("Sehir Eklemesi Iptal Edildi.\n");
                    }
                }
                else{
                    y = x->komsular;
                    printf("Sehir Adi: %s , Sehir Plaka Kodu: %d ,Sehir Bolgesi: %s ,Komsu Sayisi: %d\n - Komsulari - \n",x->sehirAdi,x->plakaKodu,x->bolge,x->komsuSayisi);
                    for(int i = 0;i < x->komsuSayisi ; i++){
                        p=sehirAra(y->plakaKodu);
                        printf("Sehir Adi: %s , Sehir Plaka Kodu: %d ,Sehir Bolgesi: %s ,Komsu Sayisi: %d \n",p->sehirAdi,p->plakaKodu,p->bolge,p->komsuSayisi);
                        y = y->ileri;
                    }
                }
            }
        }else if(islem == 3){
            printf("1. Sehir Sil\n");
            printf("2. Kosmuluk Sil\n");
            printf("0. Basa Don.\n");
            printf("----------------------------------------------------------------------\n");
            int altIslem;
            printf("Isleminiz: ");scanf("%d",&altIslem);
            printf("----------------------------------------------------------------------\n");
            if(altIslem == 0){
                goto bas;
            }
            if(altIslem == 1){
                int plaka;
                printf("Silincek Sehrin Plaka Kodu:");scanf("%d",&plaka);
                sehirSil(plaka);
            }else if(altIslem == 2){
                int sehirPlaka,silincekKomsuPlaka;
                Tekrar2:
                printf("Siliceniz Komsunun Ait Oldugu Sehir Plakasini Giriniz:");
                scanf("%d",&sehirPlaka);
                struct sehir *gecici = sehirAra(sehirPlaka);
                if(gecici->plakaKodu == 0){
                    printf("Boyle Bir Kayit Bulunmamaktadir.\n");
                    goto Tekrar2;
                }
                else{
                    printf("Siliceniz Komsunun Plaka Kodu:");
                    scanf("%d",&silincekKomsuPlaka);
                    int a = komsuSil(silincekKomsuPlaka,gecici);
                    if(a == 1){
                        gecici->komsuSayisi--;
                    }
                }
            }
        }else if(islem == 4){;
            int komsuSayisiAlt,komsuSayisiUst;
            printf("Alt Komsu Sayisi Giriniz:");
            scanf("%d",&komsuSayisiAlt);
            printf("Ust Komsu Sayisi Giriniz:");
            scanf("%d",&komsuSayisiUst);
            komsuSayisinaGoreGetir(komsuSayisiAlt,komsuSayisiUst);
        }else if(islem == 5){
            printf("----------------------------------------------------------------------\n");
            char bolge[10];
            printf("Bolge Giriniz:");
            scanf("%s",bolge);
            bolgeyeGoreGetir(bolge);
        }else if(islem == 6){
            int x,y;
            char bir[20],iki[20];
            printf("Alt Komsu Sayisi Giriniz:");scanf("%d",&x);
            printf("Ust Komsu Sayisi Giriniz:");scanf("%d",&y);
            printf("Komsu Adi Giriniz:");scanf("%s",bir);
            printf("Komsu Adi Giriniz:");scanf("%s",iki);
            bonusSehir(x,y,bir,iki);
            printf("----------------------------------------------------------------------\n");
        }
        else if(islem == 7){
            dosyayaAktar();
            printf("----------------------------------------------------------------------\n");
        }else if(islem == 0){
            break;
        }
    }
    return 0;
}
