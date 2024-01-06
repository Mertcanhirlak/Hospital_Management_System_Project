#include <stdio.h>
#include "fonksiyonlar.h"


int main() {
    while(1){//ana menü biz istemediğimiz sürece kapanmaması için döngüye aldım.
        printf("#####################################\n");
        printf("Sisteme hoş geldiniz.\n");
        printf("Lütfen yapmak istetdiğiniz işlemi seçiniz.\n");
        int secim;
        //ilk başta hastabilgileri.txt ve doktorbilgileri.txt dosyaları bulunmadığında sıkıntı olabildiğinden baştan oluşturuyorum.
        FILE *dosyaolustur1= fopen("hastabilgileri.txt","a");
        fclose(dosyaolustur1);
        FILE *dosyaolustur2= fopen("doktorbilgileri.txt","a");
        fclose(dosyaolustur2);
        printf("1)Doktor kayıt.\n");
        printf("2)Doktor giriş.\n");
        printf("3)Doktor listele.\n");
        printf("4)Hasta kayıt.\n");
        printf("5)Hasta listele.\n");
        printf("6)Hasta arşivi listele.\n");
        printf("7)Poliklinik listele.\n");
        printf("8)Kayıt silme işlemi.\n");
        printf("0)Çıkış yap.\n");
        printf("Seçiminiz: ");
        scanf("%d",&secim);


        if(secim==1)
            doktorKayit();


        else if(secim==2)
            doktorGiris();


        else if(secim==3)
            doktorListele();

        else if(secim==4)
            hastaKayit();

        else if(secim==5)
            hastaListele();

        else if(secim==6)
            hastaArsivListele();

        else if(secim==7)
            poliklinikListele();

        else if(secim==8)
            dosyasilme();

        else if(secim==0){//döngüden çıkıp programı kapatma şartı.
            printf("---program kapatılıyor---");
            break;
        }

        else
            printf("Hatalı bir giriş yaptınız.\n");



    }








    return 0;
}