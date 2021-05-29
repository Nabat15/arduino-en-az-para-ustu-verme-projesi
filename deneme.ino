#include <Wire.h>
#include <LiquidCrystal_SR.h>
#include <SPI.h>
#include <SD.h>

File myFile;
LiquidCrystal_SR lcd(6,7,5);
int clockPin1=9;   // ardunionun 9 pinine baglanır
int latctPin1=3;   // ardunionun 3 pinine baglanır
int dataPin1= 2;   // ardunionun 2 pinine baglanır
int kasa[5]; // 5,10,20,50,100 tl adet sayısı 
int KalanHizmet[4]; //kalan hizmet adeti
int sayac5tl=0,sayac10tl=0,sayac20tl=0,sayac50tl=0,sayac100tl=0,bakiye =0;
String metin;
int kirmizi=10;
int yesil=8;
int sayac_kopukleme=0,sayac_yikama=0,sayac_kurulama=0,sayac_cila=0;
int hizmetBedeli;


void setup() 
{
  char dosya1[100];
int eleman;
char* parcala;
  // dosya işlemleri
  Serial.begin(9600);
  while (!Serial) {
    ;
  }


  if (!SD.begin(4)) 
  {
    Serial.println("Baglanma Hatası");
    while (1);
  }

  SD.remove("test.txt"); //Eski dosyayi siler
 
  myFile = SD.open("test.txt", FILE_WRITE); //yeni dosya oluşturur
//dosyaya veri yazdirma
  if (myFile) 
  {
    // dosyaya satir satir yazdirma
    Serial.println("test.txt dosyasina yazdiriliyor");
    myFile.println("20,20,10,30,5,");
    myFile.println("1,kopukleme,3,15tl,");
    myFile.println("2,yikama,50,10tl,");
    myFile.println("3,kurulama,100,5tl,");
    myFile.println("4,cilalama,20,50tl,");
    // dosyayi kapatır
    myFile.close();
  } 
  else 
  {

    Serial.println("test.txt acilirken hata olustu");
  }

  // dosya okuma için açılır
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available())
    { // veri sonuna kadar calisir
      dosya1[eleman]=myFile.read(); //veriyi bit bit dosya1 dizisine aktarir
      eleman++;
      
      
    }
    // dosya kapatılır
    myFile.close();
    // okuma işlemi konsol ekranına yazdirilir.
     for(int i=0;i<=eleman;i++)
     {
      Serial.write(dosya1[i]);
    }
    //dosya1 dizisindeki virgule kadar parcalarve strtok parcala,atoi chari integere cevirir
    //strtok parçalama işlemi yapar
       parcala=strtok(dosya1,",");
       kasa[0] =atoi(parcala);
       Serial.write(parcala);
    for(int i=1;i<21;i++)
    {
        parcala=strtok(NULL,",");
     if(i==1)
     {
      //atio char tipinden int tipine çevirir.
     kasa[i] =atoi(parcala);
   }
    else if(i==2)
    {
    kasa[i] =atoi(parcala);
    }
    else if(i==3)
    {
    kasa[i] =atoi(parcala);
    }
    else if(i==4)
    {
    kasa[i] =atoi(parcala);
}
   else if(i==7)
   {
    KalanHizmet[0] =atoi(parcala);
}
   else if(i==11)
   {
   KalanHizmet[1] =atoi(parcala);
}
   else if(i==15)
   {
    KalanHizmet[2] =atoi(parcala);
}
   else if(i==19)
   {
   KalanHizmet[3] =atoi(parcala);
}
// virgülü kaldırılmiş şekilde ekrana yazdırır
  Serial.write(parcala);
   
    }

   
  } else 
  {
 
    Serial.println("acilirken hata olustu test.txt");
  }
  

  pinMode(dataPin1,INPUT);  // veri1 pini giriş olarak ayarlanır
  pinMode(latctPin1,OUTPUT); // led1 bacağı çıkış olarak ayarlanır
  pinMode(clockPin1,OUTPUT);  // saat1 bacagı çıkış olarak ayarlanır
  pinMode(kirmizi,OUTPUT);     // kirmiz led cikis olarak ayarlanir
  pinMode(yesil,OUTPUT);      //   yesil led cikis oalrak ayarlanir
  digitalWrite(kirmizi,LOW);    
   lcd.begin(16,2);
 
}


void loop() 
{
  
ParaYukle ();   
  hizmetSec();


 


}
//lcd ekrana yazdırma metodu
void ekranaYazdir (String metin , int deger)
{
  String deger_str=String(deger);
  lcd.clear();
  lcd.setCursor(0,0);  // ilk satir
  lcd.print(metin);
  lcd.setCursor(0,1);  // ikinci satir
  lcd.print(deger_str);
  delay(1000);
  
  
}
// para yukleme metodu
void ParaYukle ()
{
//metin= String(kasa[0])+","+String(kasa[1])+","+String(kasa[2])+","+String(kasa[3])+","+String(kasa[4]);
//ekranaYazdir(metin,0);  
int butonlar;
int buton;
    digitalWrite(latctPin1,0); //  register 
  digitalWrite(clockPin1,0);   //        bacakları 
   digitalWrite(clockPin1,1);  //            ayarlama 
  digitalWrite(latctPin1,1);   //                 işlemi

  for(buton =0; buton<6; buton++){
    // butonun aktif olmasını belirler
     butonlar=digitalRead(dataPin1);
    // hangi  buton aktif oldugunu belirler
 if(butonlar==1){
      if(buton==0){
         metin ="5Tl adeti:";
      sayac5tl++;
      
       ekranaYazdir(metin,sayac5tl);

      }
      else if(buton==1){
       metin ="10Tl adeti:";
      sayac10tl++;
     
       ekranaYazdir(metin,sayac10tl);
      }
       else if(buton==2){
       metin ="20Tl adeti:";
      sayac20tl++;
  
       ekranaYazdir(metin,sayac20tl);
      }
            else if(buton==3){
      metin ="50Tl adeti:";
      sayac50tl++;
      
       ekranaYazdir(metin,sayac50tl);
      }      else if(buton==4){
      metin ="100Tl adeti:";
      sayac100tl++;
    
       ekranaYazdir(metin,sayac100tl);
      }      else if(buton==5){
        // toplam bakiye hesaplama işlemi
      bakiye= (sayac5tl*5)+(sayac10tl*10)+(sayac20tl*20)+(sayac50tl*50)+(sayac100tl*100);
     metin ="Bitti , Bakiye:";
   ekranaYazdir(metin,bakiye);
   // kasaya para birimi eklenir
     kasa[0]=kasa[0]+sayac5tl;
  kasa[1]=kasa[1]+sayac10tl;
  kasa[2]=kasa[2]+sayac20tl;
  kasa[3]= kasa[3]+sayac50tl;
  kasa[4]=kasa[4]+sayac100tl;

      }
 }

 digitalWrite(clockPin1, LOW);
    digitalWrite(clockPin1,HIGH);
      
    }
  
  }
 
  
  void hizmetSec()
  { 
    
    int hizmetler;
    int hizmet;
    int sayac=1; 
    
    digitalWrite(latctPin1,0); 
  digitalWrite(clockPin1,0);
   digitalWrite(clockPin1,1);
  digitalWrite(latctPin1,1);
 
// i register kullanıldıgından 8+8=16 pin oldugunda for dongusu 16  ayarlanmıştır
  for(hizmet =0; hizmet<16; hizmet++)
  {
     hizmetler=digitalRead(dataPin1);
//hizmet butonlarının aktif olma durumu
     if(hizmetler==1)
     {
// hangi butona basıldıgını gosterir
      if(hizmet==15)
      {
      //  kalan hizmet 0 esit olmadıgı surece çalısır
        if(KalanHizmet[0]>0){
         sayac_kopukleme++;
         metin ="Kopukleme 15 Tl:";
         ekranaYazdir(metin,sayac_kopukleme);
          KalanHizmet[0]=KalanHizmet[0]-1;
        }
        else
        {
          metin= "Kopukleme bitti";
           ekranaYazdir(metin,sayac_kopukleme);
        }

 }
      if(hizmet==14)
      {
       if(KalanHizmet[1]>0)
       { 
      metin ="Yikama 10Tl:";
      sayac_yikama++;
      ekranaYazdir(metin,sayac_yikama);
       KalanHizmet[1]=KalanHizmet[1]-1;
       }
       else
       {
       metin= "Yikama bitti";
       ekranaYazdir(metin,sayac_yikama);
       }
      }
        if(hizmet==13)
        {
          if(KalanHizmet[2]>0)
          {
       metin ="Kurulama 5Tl:";
      sayac_kurulama++;
      ekranaYazdir(metin,sayac_kurulama);
       KalanHizmet[2]=KalanHizmet[2]-1;
          }
          else
        {
          metin= "Kurulama bitti";
          ekranaYazdir(metin,sayac_kurulama);
        }
      }
        if(hizmet==12)
      {
          if(KalanHizmet[2]>0)
      {
      metin ="Cilamama 50Tl:";
      sayac_cila++;
      ekranaYazdir(metin,sayac_cila);
       KalanHizmet[3]=KalanHizmet[3]-1;
      }
      else
      {
            metin= "Cilalama bitti";
             ekranaYazdir(metin,sayac_cila);
          }
      }
     if(hizmet==11)
    {
           // bittirme butonu 
           //hizmet bedeli hesaplanir 
      hizmetBedeli=hizmetBedeli+(sayac_kopukleme*15);
      hizmetBedeli=hizmetBedeli+(sayac_yikama*10);
      hizmetBedeli=hizmetBedeli+(sayac_kurulama*5);
      hizmetBedeli=hizmetBedeli+(sayac_cila*50);
      // secilen hizmet bedeli bakiyeden az ise
     if(bakiye<hizmetBedeli)
     {
           metin ="H_Bedeli Asti:";
          ekranaYazdir(metin,hizmetBedeli);
          
     }
     else
     {
        //secilen hizmet bedeli bakiyeden az degilse rasgele sayı uret
        int rasgele=2; //rand()%4+1;
        // rasgele sayi 2 ise problemvar
     if(rasgele==2)
     {
                          //kirmizi işik yanar
       digitalWrite(kirmizi,HIGH);
      delay(2000);
     // para sıkışması var para iade edilir
      metin ="Iade Yapiliyor";
      ekranaYazdir(metin,rasgele);
      metin="Toplam Iade:";
      ekranaYazdir(metin,bakiye);
      // kalan hizmet hesaplanir 
      KalanHizmet[0]=KalanHizmet[0]+sayac_kopukleme;
      KalanHizmet[1]=KalanHizmet[1]+sayac_yikama;
      KalanHizmet[2]=KalanHizmet[2]+sayac_kurulama;
      KalanHizmet[2]=KalanHizmet[3]+sayac_cila;
      // kasadan para iadesi yapılır
  kasa[0]=kasa[0]-sayac5tl;
  kasa[1]=kasa[1]-sayac10tl;
  kasa[2]=kasa[2]-sayac20tl;
  kasa[3]=kasa[3]-sayac50tl;
  kasa[4]=kasa[4]-sayac100tl;
  sayac5tl=0,sayac10tl=0,sayac20tl=0,sayac50tl=0,sayac100tl=0,bakiye =0;
      //  metin= String(kasa[0])+","+String(kasa[1])+","+String(kasa[2])+","+String(kasa[3])+","+String(kasa[4]);
     //ekranaYazdir(metin,0);
      sayac_kopukleme=0;
      sayac_yikama=0;
      sayac_kurulama=0;
      sayac_cila=0;
       digitalWrite(kirmizi,LOW);
     }
     else if(rasgele==1 ||rasgele==3 || rasgele==4)
     {
      // problem yok yesil işik yanar
      digitalWrite(yesil,HIGH);
     // delay(2000);
      
            metin ="Basarili";
            ekranaYazdir(metin,rasgele);
            // para ustu verme metodu çagırılır
            ParaUstu();
 
  digitalWrite(yesil,LOW);
         }
       }  
  }
     if(hizmet==10)
     {
      // resetle butonu seçimi sıfırlar
      metin ="Rsetleniyor:";
  KalanHizmet[0]=KalanHizmet[0]+sayac_kopukleme;
  KalanHizmet[1]=KalanHizmet[1]+sayac_yikama;
  KalanHizmet[2]= KalanHizmet[2]+sayac_kurulama;
  KalanHizmet[3]=KalanHizmet[3]+sayac_cila;
      hizmetBedeli=0;
      sayac_kopukleme=0;
      sayac_yikama=0;
      sayac_kurulama=0;
      sayac_cila=0;
       ekranaYazdir(metin,0);
      }
     }
      digitalWrite(clockPin1, LOW);
    digitalWrite(clockPin1,HIGH);
  }
}


 void ParaUstu()
 {
  int paraustu,kalan,adet100,adet50,adet20,adet10,adet5;
 paraustu=bakiye-hizmetBedeli;
 kalan=paraustu;
  //paraustu istenilen birimden buyukse 
  if(paraustu>=100)
  {
  //kasadaki para 0 esit degilse
  if(kasa[4]!=0)
  {
         adet100=(paraustu/100);
      kasa[4]=kasa[4]-adet100;
      paraustu=paraustu-(adet100*100);
       if(paraustu==0)
       {
        metin=String(adet5)+","+String(adet10)+","+String(adet20)+","+String(adet50)+","+String(adet100);
    ekranaYazdir(metin,kalan);
    ///dosyaGuncelle();  
       }
      }
     }
     if(paraustu>=50)
     {
     if(kasa[3]!=0)
     {
      adet50=(paraustu/50);
      kasa[3]=kasa[3]-adet50;
     paraustu=paraustu-(adet50*50);
   
     if(paraustu==0)
     {
     metin=String(adet5)+","+String(adet10)+","+String(adet20)+","+String(adet50)+","+String(adet100);
    ekranaYazdir(metin,kalan);
    }
   }
  }
  if(paraustu>=20)
  {
  if(kasa[2]!=0)
  {
       adet20=(paraustu/20);   
          kasa[2]=kasa[2]-adet20;  
      paraustu=paraustu-(adet20*20);
      if(paraustu==0)
      {
    metin=String(adet5)+","+String(adet10)+","+String(adet20)+","+String(adet50)+","+String(adet100);
    ekranaYazdir(metin,kalan);
// dosyaGuncelle();
    }
   }  
  }
  if(paraustu>=10)
  {
  if(kasa[1]!=0)
  {
      adet10=(paraustu/10);
      paraustu=paraustu-(adet10*10);
      kasa[1]=kasa[1]-adet10;
      if(paraustu==0)
      {
     metin=String(adet5)+","+String(adet10)+","+String(adet20)+","+String(adet50)+","+String(adet100);
    ekranaYazdir(metin,kalan);
  //dosyaGuncelle();
     }
    }
  }
  if(paraustu>=5)
  {
   if(kasa[0]!=0)
   {
       adet5=(paraustu/5);
       paraustu=paraustu-(adet5*5);
       kasa[0]=kasa[0]-adet5;
       if(paraustu==0)
       {
     metin=String(adet5)+","+String(adet10)+","+String(adet20)+","+String(adet50)+","+String(adet100);
    ekranaYazdir(metin,kalan);
 //dosyaGuncelle();
    }
   }
  }
 else if(paraustu!=0)
 {
  // yukardaki işlemlerden biri eksik kalırsa ve hala para ustu tamamlanmaz ise bakiye yetersizdir
  metin ="bakiye yetersiz";
  ekranaYazdir(metin,paraustu);

 }

 }


  
