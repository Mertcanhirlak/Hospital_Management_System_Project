//
// Created by BATUHAN TÜRKYILMAZ on 2.01.2024.
//

#include "fonksiyonlar.h"
#include <stdio.h>
#include <string.h>

typedef struct hastaBilgi{
    char isim[20],soyisim[20];
    long kimlikNo;
    char doktorIsmi[20],doktorsoyIsmi[20];
    int yas;
    char cinsiyet[20];
    int klinik;
    char hastaGirisTarih[20];
    char hastaCikisTarih[20];
    char hastaDurum[10];
    char receteNo[20];
    char hastaTani[20];
};


typedef struct doktorBilgi{
    char kullaniciAdi[20],sifre[20];
    char doktorIsmi[20],doktorsoyIsmi[20];
    int Poliklinik;
};








void doktorKayit(){
    while(1){

        printf("##############################\n");
        printf("Doktor kayıt ekranına hoş geldiniz.\n");
        printf("Kaydedilecek doktorun bilgilerini giriniz.\n");
        struct doktorBilgi kayitDoktor;
        printf("Adı: ");
        scanf("%s",kayitDoktor.doktorIsmi);
        printf("Soyadı: ");
        scanf("%s",kayitDoktor.doktorsoyIsmi);


        printf("Kullanıcı adı: ");
        scanf("%s",kayitDoktor.kullaniciAdi);

        FILE *isimkontrolL= fopen("doktorbilgileri.txt","r");
        struct doktorBilgi isimkontrcigi;
        int mevcutmu=0;
        while(fread(&isimkontrcigi,sizeof(struct doktorBilgi),1,isimkontrolL)==1){//Bu döngü dosyanın içinde bu kullanıcı adına sahip herhangi birinin olup olmadığını kontrol eder
            if(strcmp(kayitDoktor.kullaniciAdi,isimkontrcigi.kullaniciAdi)==0){
                mevcutmu=1;//eğer kullanıcı adına sahip herhangi birisi varsa mevutmu değişkenine 1 ataması yapar
            }
        }
        if(mevcutmu==1){
            printf("Hata, böyle bir kullanıcı adı mevcut!\n");
            break;
        }
        fclose(isimkontrolL);



        printf("Şifresi: ");
        scanf("%s",kayitDoktor.sifre);
        printf("Polikliniğini giriniz[1-8]:");
        scanf("%d",&kayitDoktor.Poliklinik);
        if(kayitDoktor.Poliklinik<1|| kayitDoktor.Poliklinik>8 ) {
            printf("Hatalı bir değer girdiniz.\n");//poliklinik numaraları 1'den 8'e kadar sınırlıdır. Değiştirilebilir.
            break;
        }

        FILE *doktorkaydi= fopen("doktorbilgileri.txt","a");
        fwrite(&kayitDoktor,sizeof(struct doktorBilgi),1,doktorkaydi);
        fclose(doktorkaydi);
        printf("Doktor kaydı tamamlanmıştır!\n");
        printf("------------------------------\n");
        short sec;
        printf("Başka bir doktor kaydetmek için 0 haricinde bir değer giriniz. Ana menüye dönmek için 0'a basınız.\nSeçiminiz: ");
        scanf("%hd",&sec);


        if(sec==0){
            break;
        }

        else {
            continue;
        }
    }
}



void doktorGiris() {
    printf("############################################\n");
    printf("Doktor giriş ekranına hoş geldiniz.\n");
    printf("Lütfen giriş için kullanıcı adı ve şifrenizi giriniz.\n");
    char kullaniciAd[20], sifre[20];
    printf("Kullanıcı adı:");
    scanf("%s", kullaniciAd);
    printf("Şifre:");
    scanf("%s", sifre);
    while(1){


        FILE *doktorHosGeldin = fopen("doktorbilgileri.txt", "r");
        struct doktorBilgi doktorunGiris;

        if (doktorHosGeldin == NULL) {
            perror("Dosya açma hatası. Hata nedeni");
            return;
        }

        while (fread(&doktorunGiris, sizeof(struct doktorBilgi), 1, doktorHosGeldin) == 1) {//Bu döngü dosyanın açılıp aşağıdaki işlemlerin kontrolü için gereklidir.
            if (strcmp(kullaniciAd, doktorunGiris.kullaniciAdi) == 0 && strcmp(sifre, doktorunGiris.sifre) == 0) {//burada dosyanın içinde kullanıcı adı ve şifreyle eşleşen bir değer aranır.

                printf("########################################\n");
                printf("Hoş geldiniz Sn. Dr. %s %s \n", doktorunGiris.doktorIsmi, doktorunGiris.doktorsoyIsmi);
                printf("Sorumlu olduğunuz poliklinik: %d\n", doktorunGiris.Poliklinik);
                printf("Lütfen yapmak istediğiniz işlemi seçiniz.\n");
                printf("1)Hasta bilgileri.\n");
                printf("2)Hasta çıkışı gir.\n");
                printf("0)Ana menüye dön.\n");
                int a;
                scanf("%d", &a);
                if (a == 1){
                    printf("##########################\n");
                    FILE *hastaSecmek= fopen("hastabilgileri.txt","r");
                    struct hastaBilgi hastalarimiz;
                    while(fread(&hastalarimiz,sizeof(struct hastaBilgi),1,hastaSecmek)) {//dosyayı taramak için while döngüsü
                        if (strcmp(hastalarimiz.doktorIsmi, doktorunGiris.doktorIsmi) == 0 && strcmp(hastalarimiz.doktorsoyIsmi, doktorunGiris.doktorsoyIsmi) == 0) {//dosyanın içinde doktorun hastalarını listelemesi için kullanılan fonksiyon
                            if (strcmp(hastalarimiz.hastaDurum, "aktif") == 0) {//yalnızca aktif hastaların listelenmesini istediğim için kullanılan fonksiyon.
                                printf("Hastanın adı: %s\n", hastalarimiz.isim);
                                printf("Hastanın soyadı: %s\n", hastalarimiz.soyisim);
                                printf("Hastanın TC kimlik numarası: %ld\n", hastalarimiz.kimlikNo);
                                printf("Hastanın yaşı: %d\n", hastalarimiz.yas);
                                printf("Hastanın cinsiyeti: %s\n", hastalarimiz.cinsiyet);
                                printf("Hastanın giriş tarihi: %s\n", hastalarimiz.hastaGirisTarih);
                                printf("Hastadan sorumlu doktor: Dr. %s %s\n", hastalarimiz.doktorIsmi,
                                       hastalarimiz.doktorsoyIsmi);
                                printf("Poliklinik no.: %d\n", hastalarimiz.klinik);
                                printf("-------------------------\n");

                            }
                        }
                    }
                    fclose(hastaSecmek);
                }

                if (a == 2){
                    printf("##############################\n");
                    printf("Lütfen çıkışını yapacağınız hastanın TC kimlik numarasını giriniz.\n");
                    long kimlikNosu;
                    scanf("%ld",&kimlikNosu);
                    FILE *cikisTC= fopen("hastabilgileri.txt","r+");
                    struct hastaBilgi hastacikisi;
                    int tckimlikdogrumu=0;//eğer dosya içinde herhangi eşleşen bir TC değeri bulunamazsa çıkışı için gerekli değişken. 192. satırda kontrol edilir.
                    while(fread(&hastacikisi,sizeof(struct hastaBilgi),1,cikisTC)==1){
                        if(kimlikNosu==hastacikisi.kimlikNo){//çıkış yapılacak kişinin tc kimlik numarasını hasta listesinde arayan ve varsa çıkışı için alttaki bloğa geçen fonk.
                            if(strcmp(hastacikisi.hastaDurum,"aktif")!=0){//pasif bir hastanın çıkışı yapılamayacağına göre aktif hasta çıkışını yapacaktır. Aktif olup olmadığını kontrol eder. Pasif hastalara çıkış yapılmaz.
                                printf("Bu hasta aktif bir hasta değil.\n");
                                break;
                            }
                            tckimlikdogrumu=1;
                            printf("%s %s'nin çıkışını yapıyorsunuz.\n",hastacikisi.isim,hastacikisi.soyisim);
                            printf("Hastanın çıkış tarihini giriniz: ");
                            char cikisTarihimiz[20],recetemiz[20],hastaTanisi[20];
                            scanf("%s",cikisTarihimiz);
                            printf("Hastanın reçetesini giriniz: ");
                            scanf("%s",recetemiz);
                            printf("Hastanın tanısını giriniz: ");
                            scanf("%s",hastaTanisi);

                            strcpy(hastacikisi.hastaCikisTarih,cikisTarihimiz);
                            strcpy(hastacikisi.hastaDurum,"pasif");
                            strcpy(hastacikisi.receteNo,recetemiz);
                            strcpy(hastacikisi.hastaTani,hastaTanisi);

                            fseek(cikisTC, -sizeof(struct hastaBilgi), SEEK_CUR);
                            fwrite(&hastacikisi, sizeof(struct hastaBilgi), 1, cikisTC);

                            printf("Hasta çıkışı başarılı.\n");
                        }
                    }
                    fclose(cikisTC);
                    if(tckimlikdogrumu==0){
                        printf("Bu TC kimlik numarasına sahip bir hasta bulunmamaktadır.\n");
                        break;
                    }
                }

                if (a == 0)
                    break;

            }
        }
        printf("Ana menüye dönmek için 0, doktor girişine dönmek için herhangi bir sayıyı giriniz.\n");
        int cikis;
        scanf("%d",&cikis);
        if(cikis==0)
            break;

        fclose(doktorHosGeldin);
    }
}


void doktorListele() {
    printf("############################\n");
    struct doktorBilgi doktorlistemiz;

    FILE *listeleDoktor = fopen("doktorbilgileri.txt", "r");  //
    if (listeleDoktor == NULL) {
        perror("Dosya açma hatası. Hata nedeni");
        return;
    }

    int i = 1;

    while (fread(&doktorlistemiz, sizeof(struct doktorBilgi), 1, listeleDoktor) == 1) {//dosyanın içinde baştan sona tüm structları gezen ve istediğimiz sonuçları ekrana yazan döngü. Döngü olmazsa yalnızca bir adet yazar.
        printf("%d. Doktorun ismi: %s\n", i, doktorlistemiz.doktorIsmi);
        printf("%d. Doktorun soyismi: %s\n", i, doktorlistemiz.doktorsoyIsmi);
        printf("%d. doktorun polikliniği: %d\n", i, doktorlistemiz.Poliklinik);
        printf("----------------------------------\n");
        i++;
    }
    fclose(listeleDoktor);

    printf("Ana menüye dönmek için herhangi bir sayı giriniz.\n");
    int herhangibirsayi;
    scanf("%d", &herhangibirsayi);

}


void hastaKayit() {
    while (1) {
        printf("##############################\n");
        printf("Hasta kayıt ekranına hoş geldiniz.");
        printf("Kaydedilecek hastanın bilgilerini giriniz.\n");
        struct hastaBilgi hastakaydetme;
        printf("Hastanın ismini giriniz: ");
        scanf("%s", hastakaydetme.isim);
        printf("Hastanın soyismini giriniz:");
        scanf("%s", hastakaydetme.soyisim);

        printf("Hastanın TC kimlik numarasını giriniz:");
        scanf("%ld", &hastakaydetme.kimlikNo);

        if (hastakaydetme.kimlikNo > 99999999999 || hastakaydetme.kimlikNo < 10000000000) {//TC kimlik numaraları 11 haneli olmak zorundadır.
            printf("Hastanın kimlik numarası 11 haneli olmalıdır.\n");
            break;
        }

        int kimlikNoToplam = 0;
        long a = 10;
        for (int i = 1; i < 12; i++) {//tc kimlik numarasının baştan sona 10 hanesinin toplamının 10'a bölümünden kalan 11. hanesini verir.
            kimlikNoToplam = kimlikNoToplam + (hastakaydetme.kimlikNo / a) % 10;
            a = a * 10;
        }
        kimlikNoToplam %= 10;
        if (hastakaydetme.kimlikNo % 10 != kimlikNoToplam) {
            printf("Hatalı giriş(TC kimlik numaralarının ilk 10 hanesinin toplamının 10'a bölümünden kalan son haneyi verir.).\n");
            break;
        }
        FILE *hastatcKontrolu= fopen("hastabilgileri.txt","r+");
        struct hastaBilgi tckontroluyapma;
        int tckontrol=0,ikincigiriskontrol=0;//ikincigiriskontrol değişkeni, hastayı pasif durumdan aktife aldığımız durumda ilerleyen işlemler zaten yapıldığından programı sonlandırmamız için olan kontrol değişkenidir. tckontrol yine hata değişkeni. BKZ. satır 313/318
        while(fread(&tckontroluyapma,sizeof(struct hastaBilgi),1,hastatcKontrolu)){
            if(tckontroluyapma.kimlikNo==hastakaydetme.kimlikNo){//Burada girilen tc numarası ile dosyadaki tc numaraları karşılaştırılır. Eşitse bloğun içine girer.
                if(strcmp(tckontroluyapma.isim,hastakaydetme.isim)!=0 || strcmp(tckontroluyapma.soyisim,hastakaydetme.soyisim)!=0){
                    tckontrol=1;//TC kimlik numaraları uyuşurken isim ve soy isim uyuşmazlığı varsa tckontrol değişkenine 1 değeri atanır ve bloktan çıkılır.
                    break;
                }
                if(strcmp(tckontroluyapma.hastaDurum,"pasif")!=0){//aktif pasif durumunu kontrol eder. Eğer aktif bir hastayı girersek hata vermesi için buraya yazılmıştır.
                    tckontrol=1;
                }

                if(strcmp(tckontroluyapma.hastaDurum,"pasif")==0){//pasif hasta olması durumunda yeniden aktif hale gelmek için yapılan birtakım işlemler.
                    printf("Tekrar hastanemize uğradığınız için teşekkür ederiz Sn. %s %s\n",tckontroluyapma.isim,tckontroluyapma.soyisim);
                    strcpy(hastakaydetme.hastaCikisTarih,"---------------");
                    strcpy(hastakaydetme.hastaDurum,"aktif");
                    strcpy(hastakaydetme.receteNo,"---------------");
                    strcpy(hastakaydetme.hastaTani,"---------------");
                    strcpy(hastakaydetme.doktorIsmi,tckontroluyapma.doktorIsmi);
                    strcpy(hastakaydetme.doktorsoyIsmi,tckontroluyapma.doktorsoyIsmi);
                    hastakaydetme.klinik=tckontroluyapma.klinik;
                    strcpy(hastakaydetme.cinsiyet,tckontroluyapma.cinsiyet);
                    int tekrarGirisYas;
                    char girisTarihidegsitir[20];
                    printf("Hastanın yaşı: ");
                    scanf("%d",&tekrarGirisYas);
                    printf("Hasta giriş tarihi: ");
                    scanf("%s",girisTarihidegsitir);
                    strcpy(hastakaydetme.hastaGirisTarih,girisTarihidegsitir);
                    hastakaydetme.yas=tekrarGirisYas;
                    fseek(hastatcKontrolu,-sizeof(struct hastaBilgi),SEEK_CUR);
                    fwrite(&hastakaydetme,sizeof(struct hastaBilgi),1,hastatcKontrolu);
                    ikincigiriskontrol=1;
                    break;

                }
            }
        }
        fclose(hastatcKontrolu);

        if(ikincigiriskontrol==1){

            printf("Hasta kaydı tamamlanmıştır.\n");
            break;
        }
        if(tckontrol==1){
            printf("Girdiğiniz TC kimlik numarası başka birisine ait veya aktif bir hasta. Lütfen kendi TC kimlik numaranızı giriniz veya aktif girişinizin çıkışının yapılmasını bekleyiniz.\n");
            break;
        }


        printf("Hastanın yaşınız giriniz:");
        scanf("%d", &hastakaydetme.yas);

        if (hastakaydetme.yas > 130 || hastakaydetme.yas < 0) {
            printf("Hatalı giriş. Hastanın yaşı 130'dan büyük, 0'dan küçük olamaz.\n");
            break;
        }

        printf("Hastanın cinsiyetini giriniz:");
        scanf("%s", hastakaydetme.cinsiyet);

        int cinsiyetkontrol=0;

        if(strcmp(hastakaydetme.cinsiyet,"kadın")==0 || strcmp(hastakaydetme.cinsiyet,"erkek")==0){//cinsiyetin doğru girilip girilmediğini kontrol eder.
            cinsiyetkontrol=1;
        }
        if(strcmp(hastakaydetme.cinsiyet,"KADIN")==0 || strcmp(hastakaydetme.cinsiyet,"ERKEK")==0){
            cinsiyetkontrol=1;
        }

        if(cinsiyetkontrol==0){
            printf("Böyle bir cinsiyet yok.\n");
            break;
        }



        printf("Hastanın doktorunun adını giriniz:");
        scanf("%s", hastakaydetme.doktorIsmi);
        printf("Hastanın doktorunun soyadını giriniz:");
        scanf("%s", hastakaydetme.doktorsoyIsmi);
        FILE *doktorkontrol = fopen("doktorbilgileri.txt", "r");
        struct doktorBilgi kontrolet;
        int i = 0;//girilen isimde doktorun olmaması durumunda döngüyü durdurması için kontrol edilecek değişken.
        while (fread(&kontrolet, sizeof(struct doktorBilgi), 1, doktorkontrol) == 1) {//dosyanın içinde girilen doktorun isim ve soy isminde herhangi bir doktorun olup olmadığını kontrol eden döngü.
            if (strcmp(hastakaydetme.doktorIsmi, kontrolet.doktorIsmi) == 0 && strcmp(hastakaydetme.doktorsoyIsmi, kontrolet.doktorsoyIsmi) == 0) {
                hastakaydetme.klinik = kontrolet.Poliklinik;
                i = 1;
            }
        }
        if (i == 0) {
            printf("Bu isimde herhangi doktor yok!\n");
            break;
        }
        fclose(doktorkontrol);

        printf("Hasta giriş tarihi: ");
        scanf("%s", hastakaydetme.hastaGirisTarih);

        strcpy(hastakaydetme.hastaCikisTarih, "----------");
        strcpy(hastakaydetme.hastaDurum, "aktif");
        strcpy(hastakaydetme.receteNo, "----------");
        strcpy(hastakaydetme.hastaTani, "----------");

        FILE *hastakaydi = fopen("hastabilgileri.txt", "a");
        fwrite(&hastakaydetme, sizeof(struct hastaBilgi), 1, hastakaydi);
        printf("Hasta kaydı tamamlanmıştır!\n");
        printf("Hastanın polikliniği: %d\n", hastakaydetme.klinik);
        printf("------------------------------\n");
        fclose(hastakaydi);
        short secc;
        printf("Başka bir hasta kaydetmek için 0 haricinde bir değer giriniz. Ana menüye dönmek için 0'a basınız.\nSeçiminiz: ");
        scanf("%hd", &secc);


        if (secc == 0) {
            break;
        } else {
            continue;
        }
    }
}


void hastaListele() {
    printf("###########################\n");
    printf("-----Mevcut hastalar-----\n");
    struct hastaBilgi hastalistemiz;
    FILE *hastayiListeleme = fopen("hastabilgileri.txt", "r");

    if (hastayiListeleme == NULL) {
        perror("Dosya açma hatası. Hata nedeni");
        return;
    }

    while (fread(&hastalistemiz, sizeof(struct hastaBilgi), 1, hastayiListeleme) == 1) {//dosyayı baştan sonra tarıyoruz.
        if (strcmp(hastalistemiz.hastaDurum, "aktif") == 0) {//aktif hastaları listelemesi için kontrol kısmı.
            printf("Hastanın adı: %s\n", hastalistemiz.isim);
            printf("Hastanın soyadı: %s\n", hastalistemiz.soyisim);
            printf("Hastanın TC kimlik numarası: %ld\n", hastalistemiz.kimlikNo);
            printf("Hastanın yaşı: %d\n", hastalistemiz.yas);
            printf("Hastanın cinsiyeti: %s\n", hastalistemiz.cinsiyet);
            printf("Hastanın giriş tarihi: %s\n", hastalistemiz.hastaGirisTarih);
            printf("Hastadan sorumlu doktor: Dr. %s %s\n", hastalistemiz.doktorIsmi, hastalistemiz.doktorsoyIsmi);
            printf("Poliklinik no.: %d\n", hastalistemiz.klinik);
            printf("-------------------------\n");

        }


    }
    fclose(hastayiListeleme);
    printf("Ana menüye dönmek için herhangi bir sayı giriniz:");
    int sayicik;
    scanf("%d", &sayicik);

}


void hastaArsivListele() {

    printf("###########################\n");
    printf("-----HASTA ARŞİVİ-----\n");
    struct hastaBilgi arsivlistemiz;
    FILE *hastamizarsiv = fopen("hastabilgileri.txt", "r");

    if (hastamizarsiv == NULL) {
        perror("Dosya açma hatası. Hata nedeni");
        return;
    }

    while (fread(&arsivlistemiz, sizeof(struct hastaBilgi), 1, hastamizarsiv) == 1) {
        if (strcmp(arsivlistemiz.hastaDurum, "pasif") == 0) {//pasif olan, çıkışı yapılmış hastaları listeler.
            printf("Hastanın adı: %s\n", arsivlistemiz.isim);
            printf("Hastanın soyadı: %s\n", arsivlistemiz.soyisim);
            printf("Hastanın TC kimlik numarası: %ld\n", arsivlistemiz.kimlikNo);
            printf("Hastanın yaşı: %d\n", arsivlistemiz.yas);
            printf("Hastanın cinsiyeti: %s\n", arsivlistemiz.cinsiyet);
            printf("Hastanın giriş tarihi: %s\n", arsivlistemiz.hastaGirisTarih);
            printf("Hastanın çıkış tarihi: %s\n", arsivlistemiz.hastaCikisTarih);
            printf("Hasta durumu: %s\n", arsivlistemiz.hastaDurum);
            printf("Hasta reçete no.:%s\n", arsivlistemiz.receteNo);
            printf("Hasta tanısı: %s\n", arsivlistemiz.hastaTani);
            printf("Hastadan sorumlu doktor: Dr. %s %s\n", arsivlistemiz.doktorIsmi, arsivlistemiz.doktorsoyIsmi);
            printf("Poliklinik no.: %d\n", arsivlistemiz.klinik);
            printf("-------------------------\n");

        }


    }
    fclose(hastamizarsiv);
    printf("Ana menüye dönmek için herhangi bir sayı giriniz:");
    int sayi;
    scanf("%d", &sayi);

}



void poliklinikListele() {

    printf("############################\n");
    struct doktorBilgi poliklinik;

    FILE *listelepoliklinik = fopen("doktorbilgileri.txt", "r");  //
    if (listelepoliklinik == NULL) {
        perror("Dosya açma hatası. Hata nedeni");
        return;
    }

    while (fread(&poliklinik, sizeof(struct doktorBilgi), 1, listelepoliklinik) == 1) {//klinikleri ve doktorları listeler.
        printf("%d numaralı poliklinikten sorumlu doktor\n", poliklinik.Poliklinik);
        printf("Sorunmlu doktorun ismi: %s\n", poliklinik.doktorIsmi);
        printf("Sorumlu doktorun soyismi: %s\n", poliklinik.doktorsoyIsmi);
        printf("----------------------------------\n");
    }

    fclose(listelepoliklinik);

    printf("Ana menüye dönmek için herhangi bir sayı giriniz:");
    int sayii;
    scanf("%d", &sayii);
}



void dosyasilme(){
    printf("############################\n");
    printf("Lütfen yapmak istediğiniz işlemi seçiniz.\n");
    printf("1)Hasta bilgileri dosyasını temizle.\n");
    printf("2)Doktor bilgileri dosyasını temizle.\n");
    printf("0)Ana menüye dön.\n");
    int dosyasilsecim;
    scanf("%d",&dosyasilsecim);
    if(dosyasilsecim==1){
        char hastab[]="hastabilgileri.txt";
        if (remove(hastab) == 0) {
            printf("%s dosyasi basariyla silindi.\n", hastab);
        } else {
            perror("Dosya silme hatasi");
        }

    }

    else if(dosyasilsecim==2){
        FILE *doktorhastak= fopen("hastabilgileri.txt","r");
        FILE *doktork= fopen("doktorbilgileri.txt","r");

        struct doktorBilgi drkontrol;
        struct hastaBilgi hstkontrol;

        int kontroldegiskeni=0;

        while(fread(&drkontrol,sizeof(struct doktorBilgi),1,doktork)==1){//bu döngüde doktorun hastasının olup olmadığı kontrol edilir. Aktif hasta varken doktor kayıt dosyası silinemez.
            while(fread(&hstkontrol,sizeof(struct hastaBilgi),1,doktorhastak)==1){
                if(strcmp(hstkontrol.hastaDurum,"aktif")==0){
                    if(strcmp(drkontrol.doktorIsmi,hstkontrol.doktorIsmi)==0 && strcmp(drkontrol.doktorsoyIsmi,hstkontrol.doktorsoyIsmi)==0){
                        kontroldegiskeni=1;//bu döngü çok önemli. Eğer aktif hasta bir doktora atanmışsa dosyanın silinmesine izin vermeyecek.
                    }
                }
            }
        }


        fclose(doktorhastak);
        fclose(doktork);

        if(kontroldegiskeni==0){
            char doktorr[]="doktorbilgileri.txt";
            if (remove(doktorr) == 0) {
                printf("%s dosyasi basariyla silindi.\n", doktorr);
            } else {
                perror("Dosya silme hatasi");
            }

        }

        if(kontroldegiskeni==1){
            printf("Aktif hasta bulunmakta. Silme işlemi yapılamaz.\n");


        }


    }





}



