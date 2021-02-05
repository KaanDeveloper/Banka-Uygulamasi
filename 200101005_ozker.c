//Kaan �zker 200101005
//Final projesi
//Banka uygulamas�

//K�t�phanelerimiz
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#define SIFRE_KAPASITE 6
#define MAX_MIKTAR 10000.00 //Kullan�c� 10000 TL'den fazla yat�ramaz, �ekemez ve limit belirleyemez. (Havale i�in ge�erli de�ildir.)

//Fonksiyonlar�m�z
void para_yatir(double hesap_bilgi_yatir_miktar[], int *yatir_durum, double *bakiye);
void para_cek(double hesap_bilgi_cek_miktar[], int *cek_durum, double *bakiye);
void hesap_bilgileri(char ad_soyad[], char sifre[], char kredi_karti[], double bakiye, int ad_uzunluk, int sifre_uzunluk);
void hesap_hareket(double hesap_bilgi_yatir_miktar[], double hesap_bilgi_cek_miktar[], double hesap_bilgi_havale_miktar[], long int hesap_bilgi_havale_hesap_no[], int yatir_durum, int cek_durum, int havale_durum);
void kredi_karti_ac(char kredi_karti[], int *kredi_karti_durum);
void kredi_karti_kapat(char kredi_karti[], int *kredi_karti_durum);
double komisyon_hesapla(double miktar, double miktar_kopya_komisyon);
void havale(long int hesap_bilgi_havale_hesap_no[], double hesap_bilgi_havale_miktar[], int *havale_durum, double *bakiye);
int sifre_karsilastirma(char sifre_giris[], char sifre[]);

int
main(void) 
{
	int uygulama = 1; //Uygulaman�n �al��mas�n� sa�lar.
	int giris_durum = 1; //Kay�t ve giri� b�l�m�n�n �al��mas�n� sa�lar.
	int menu_durum = 0; //��lemler b�l�m�n�n �al��mas�n� sa�lar.
	int kayit_durum = 0;
	char secim; //Yapt���m�z se�imleri tutan de�i�ken
	int secim_uzunluk;
	int yatir_durum = 0; //Para yat�rma say�m�z.
	int cek_durum = 0; //Para �ekme say�m�z.
	int havale_durum = 0; //Havale say�m�z.
	double *hesap_bilgi_yatir_miktar[1000]; //Yat�rd���m�z paralar.
	double *hesap_bilgi_cek_miktar[1000]; //�ekti�imiz paralar.
	double *hesap_bilgi_havale_miktar[1000]; //Havale etti�imiz paralar.
	long int *hesap_bilgi_havale_hesap_no[1000]; //Havale yapt���m�z ki�ilerin hesap numaralar�.
	int i, j;
	double bakiye = 0; //Bakiyemiz.
	int ad_uzunluk; //Kullan�c� ad� uzunlu�u.
	int ad_uzunluk2;
	int sifre_uzunluk; //�ifrenin uzunlu�u.
	int sifre_uzunluk2;
	int kredi_karti_durum = 0; 
	char kullanici_adi[500]; //Kullan�c� ad�n�z. Kullan�c� ad� ilk buraya depolan�r.
	char kullanici_adi2[500]; //E�er giri� yap�l�rsa kullan�c� ad� burada tutulur ve g�sterimler bu de�i�ken �zerinden yap�l�r.
	char sifre_guvenlik; //�ifre i�in g�venlik sorusu.
	char sifre[SIFRE_KAPASITE]; //�ifreniz. �ifre ilk buraya girilir. 
	char sifre2[SIFRE_KAPASITE]; //Kay�t ba�ar�l� ise �ifre buraya atan�r ve giri� i�lemlerinde bu de�i�ken �zerinden kar��la�t�r�lma yap�l�r.
	char sifre_giris[SIFRE_KAPASITE]; //Giri� yaparken kar��la�t�rmak i�in �ifre kopyas�
	int sifre_giris_uzunluk; //Giri�te girdi�imiz �ifrenin uzunlu�u.
	int sifre_dogruluk; //�ifrenin e�le�en karakter say�s�.
	int sifre_sistem_dogruluk; //Kay�tta ba�ka hesab�n ayn� �ifreyi girmemesi i�in yazd���m de�i�ken.
	char *sifre_sistem[1000][6]; //Kullan�lm�� �ifrelerin tutuldu�u yer.
	int sifre_durum = 0; //Kay�t olunan �ifre say�s�.
	char kredi_karti[7] = "Kapali"; //Kredi kart�n�n a��k veya kapal� olma durumu.
	
	//Dinamik bellek atamalar�.
	for (i = 0; i < 500; i++) 
	{
		kullanici_adi[i] = (char *) malloc(sizeof(char));
	}
	
	for (i = 0; i < 500; i++) 
	{
		kullanici_adi2[i] = (char *) malloc(sizeof(char));
	}

	for (i = 0; i < 1000; i++) 
	{
		hesap_bilgi_yatir_miktar[i] = (double *) malloc(sizeof(double));
	}

	for (i = 0; i < 1000; i++) 
	{
		hesap_bilgi_cek_miktar[i] = (double *) malloc(sizeof(double));
	}

	for (i = 0; i < 1000; i++) 
	{
		hesap_bilgi_havale_miktar[i] = (double *) malloc(sizeof(double));
	}

	for (i = 0; i < 1000; i++) 
	{
		hesap_bilgi_havale_hesap_no[i] = (long int *) malloc(sizeof(long int));
	}
	
	for (i = 0; i < 1000; i++) 
	{
		for (j = 0; j < 6; j++)
		{
			sifre_sistem[i][j] = (char *) malloc(sizeof(char));
		}
	}
	
	//Yaz� rengi de�i�tirme kodu.
	system("COLOR A");

	printf("***************************************\n\n");

	printf("Banka uygulamamiza hos geldiniz\n\n");

	printf("***************************************\n\n");
	
	printf("Uygulamada veritabani yoktur. Bu sebeple birinci kayittan sonraki kayitlarda onceden kayitli olan hesabin bilgileri silinir.\n\n");
	
	//Uygulamam�z �al���rken.
	while (uygulama != 0) 
	{
		//Kay�t veya giri� yap�l�rken.
		while (giris_durum != 0) 
		{
			//��lemi se�iyoruz.
			printf("\n1-Kayit ol\n\n2-Giris yap\n\n3-Uygulamadan cik\n\n");
			printf("\nBazi durumlarda eger giris yapacaksaniz iki defa 2'ye basin.\n\n");
			printf("\nBazi durumlarda kayit olmak istediginizde kullanici adi atlandigi zaman sifreyi istenen kosullarda girmeyerek giris menusune geri donebilirsiniz.\n\n");
			printf("Seciminiz(Lutfen 1-3 arasinda bir rakam giriniz.): ");
			secim = getche();

			printf("\n");
			
			switch (secim)
			{
				case '1':
					printf("\nKullanici adiniz(0 karakteri girisi sonlandirir): ");
					
					for (i = 0; i < 50; i++)
					{
						kullanici_adi[i] = getchar();
		
						if (kullanici_adi[i] == '0')
						{
							kullanici_adi[i] = '\0';
							break;
						}
					}

					ad_uzunluk = strlen(kullanici_adi);

					printf("\nSifrenizi belirleyiniz: ");
					scanf("%s", sifre);
					
					sifre_uzunluk = strlen(sifre);
				
					printf("\nNot:Guvenlik sorusunu yanitlarken dikkat edin cunku ilk karakteri degistirebilirsiniz.\n");	
					printf("\nNot:Ornegin sifreyi 050505 olarak belirleyip soruya 1 cevabini verirseniz sifre 150505 olur.\n");			
					printf("\nSifre guvenlik sorusu: Sifrenizin ilk karakteri: ");
					scanf(" %c", &sifre_guvenlik);
					
					sifre[0] = sifre_guvenlik;
					
					sifre[6] = '\0';
					
					sifre_uzunluk = strlen(sifre);
					
					//Bu listenin i�indeki herhangi bir �ifre ile kay�t olunmu� mu onu kontrol eder.
					for (i = 0; i < sifre_durum; i++)
					{
						if (sifre_karsilastirma(sifre, sifre_sistem[i]) == 6) //�ifre ayn� ise
						{
							sifre_sistem_dogruluk = sifre_karsilastirma(sifre, sifre_sistem[i]);
							break;
						}
						
						else if (sifre_karsilastirma(sifre, sifre_sistem[i]) != 6) //De�ilse
						{
							sifre_sistem_dogruluk = 0;
						}
					}
				
					//�ifre istenilen uzunlukta de�ilse.
					if (sifre_uzunluk != SIFRE_KAPASITE || sifre_sistem_dogruluk == 6)
					{
						system("CLS");
					
						printf("***************************************\n\n");
					
						printf("Sifreniz alti karakterden olusmalidir ve daha once kayit olunmus bir sifreyi kullanamazsiniz.\n\n");
					
						printf("***************************************\n\n");
					}
				
					else
					{
						//Ekran temizleme kodu.
						system("CLS");
						
						kayit_durum = 1;
						
						strcpy(&sifre2, sifre);
						
						sifre_uzunluk2 = strlen(sifre2);
						
						strcpy(&kullanici_adi2, kullanici_adi);
						
						ad_uzunluk2 = strlen(kullanici_adi2);
					
						printf("\n\nKayitiniz basarili bir sekilde yapilmistir.\n\n");

						printf("***************************************\n\n");

						printf("Hosgeldiniz \n");

						for (i = 0; i < ad_uzunluk2; i++) 
						{
							printf("%c", kullanici_adi2[i]);
						}

						printf("\n\n");

						printf("***************************************\n\n");
						
						strcpy(&sifre_sistem[sifre_durum], sifre2); //�ifreyi listeye ata.
						
						sifre_sistem[sifre_durum][6] = '\0';
						
						sifre_durum += 1; //Listenin uzunlu�u g�ncellenir.
						
						sifre_sistem_dogruluk = 0;
						
						//Yeni kullan�c� i�in s�f�rlamalar.
						bakiye = 0;
						yatir_durum = 0;
						cek_durum = 0;
						havale_durum = 0;
						strcpy(kredi_karti, "Kapali");
					
						giris_durum = 0;

						menu_durum = 1;
					}
					break;
					
				case '2':
					//Hesap olarak en son yap�lan kan�t baz al�n�r. Ona g�re �ifre girilir.
					//Daha kay�t olmam�� isek.
					if (kayit_durum == 0) 
					{
						system("CLS");
					
						printf("Once kayit olmalisiniz.\n\n");
					}
				
					//Olmu� isek.
					else 
					{	
						printf("\nSifrenizi giriniz: ");
						gets(sifre_giris);
						
						sifre_giris_uzunluk = strlen(sifre_giris);
						
						if (sifre_giris_uzunluk != SIFRE_KAPASITE)
						{
							system("CLS");
							
							printf("***************************************\n\n");
					
							printf("Lutfen alti karakterli bir sifre giriniz.\n\n");
					
							printf("***************************************\n\n");
						}
						
						else
						{
							printf("\nSifre guvenlik sorusu: Sifrenizin ilk karakteri: ");
							scanf(" %c", &sifre_guvenlik);
							
							sifre[0] = sifre_guvenlik;
							
							sifre[SIFRE_KAPASITE] = '\0';
								
							sifre_giris[0] = sifre_guvenlik;
							
							sifre_giris[SIFRE_KAPASITE] = '\0';
							
							sifre_dogruluk = sifre_karsilastirma(sifre_giris, sifre2);
					
							//Burada isim kay�tl� oldu�u i�in sadece �ifre ile giri� yapabiliyor(�ifrenin son 5 karakteri kontrol edilir).
							if (sifre_dogruluk == 6) 
							{
								system("CLS");
						
								printf("\nBasarili bir sekilde giris yaptiniz.\n");

								printf("\n***************************************\n\n");

								printf("Hosgeldiniz\n");

								for (i = 0; i < ad_uzunluk2; i++) 
								{
									printf("%c", kullanici_adi2[i]);
								}

								printf("\n\n***************************************\n\n");

								giris_durum = 0;

								menu_durum = 1;
							}
					
							//�ifre yanl�� girilmi� ise.
							else 
							{	
								system("CLS");
						
								printf("\nSifrenizi yanlis girdiniz.\n\n");

								printf("***************************************\n\n");
							}
						}
						
					}
					break;
					
				case '3':
					system("CLS");
				
					giris_durum = 0;
					uygulama = 0;
					break;
					
				default:
					system("CLS");
					printf("***************************************\n\n");
					printf("Gecersiz islem.\n\n");
					printf("***************************************\n\n");
					break;
			}
			
			
	}
		
		//��lem se�ilirken.
		while (menu_durum != 0) 
		{
			printf("1-Para yatir\n\n2-Para cek\n\n3-Hesap bilgileri\n\n4-Hesap hareketleri\n\n5-Kredi karti ac\n\n6-Kredi karti kapat\n\n7-Havale\n\n8-Giris ekranina git\n\n9-Cikis\n\n");
			printf("Lutfen 1-9 arasinda rakam seciniz.\n ");
			printf("\nSistemin duzgun calismasi icin once 1,2,5 veya 7'ye basip onay sorusuna h veya H cevabini veriniz.\n\n");
			printf("\nEger havale isleminde hata verirse onay sorusuna h veya H cevabini vererek ana menuye donun ve 7'ye tekrar basin.\n\n");
			printf("\nAyni durum 1,2 ve 5 icin de gecerlidir.\n\n");
			printf("\nSeciminiz: ");
			secim = getche();

			switch (secim) //Se�ilen i�leme g�re i�lem yapmak.
			{
				case '1':
					system("CLS");
					para_yatir(hesap_bilgi_yatir_miktar, &yatir_durum, &bakiye); //Para yat�rma.
					break;

				case '2':
					system("CLS");
					para_cek(hesap_bilgi_cek_miktar, &cek_durum, &bakiye); //Para �ekme.
					break;

				case '3':
					system("CLS");
					hesap_bilgileri(kullanici_adi2, sifre2, kredi_karti, bakiye, ad_uzunluk2, sifre_uzunluk2); //Hesap bilgileri.
					break;

				case '4':
					system("CLS");
					hesap_hareket(&hesap_bilgi_yatir_miktar, &hesap_bilgi_cek_miktar, &hesap_bilgi_havale_miktar, &hesap_bilgi_havale_hesap_no, yatir_durum, cek_durum, havale_durum); //Hesap hareketleri.
					break;

				case '5':
					system("CLS");
					kredi_karti_ac(kredi_karti, &kredi_karti_durum); //Kredi kart� a�.
					break;

				case '6':
					system("CLS");
					kredi_karti_kapat(kredi_karti, &kredi_karti_durum); //Kredi kart� kapat.
					break;

				case '7':
					system("CLS");
					havale(&hesap_bilgi_havale_hesap_no, &hesap_bilgi_havale_miktar, &havale_durum, &bakiye); //Havale yap.
					break;

				case '8':
					system("CLS"); 
					giris_durum = 1; //Giri� ekran�na geri d�n.
					menu_durum = 0;
					break;

				case '9':
					system("CLS"); 
					menu_durum = 0; //Uygulamadan ��k.
					uygulama = 0;
					break;

				default:
					system("CLS");
					printf("\nGecersiz islem.\n\n");
					break;
			}
		}
	}
	
	goto cikis;
	
	cikis:
		
		printf("\n***************************************\n\n");

		printf("Hos cakalin\n\n");

		printf("***************************************\n\n");
		
		//Haf�za bo�alt�m�.
		free(kullanici_adi);
		free(kullanici_adi2);
		free(hesap_bilgi_yatir_miktar);
		free(hesap_bilgi_cek_miktar);
		free(hesap_bilgi_havale_miktar);
		free(hesap_bilgi_havale_hesap_no);
		free(sifre_sistem);
	
		fflush(stdin);

	return (0);
}

//Bu fonksiyon para yat�rmak i�indir.
void para_yatir(double hesap_bilgi_yatir_miktar[], int *yatir_durum, double *bakiye) 
{
	double miktar_yatir;
	char miktar[20];
	int miktar_uzunluk;
	int i;
	char onay;

	printf("\n***************************************\n\n");

	printf("\nKac TL yatirmak istiyorsunuz(En fazla 10000 TL yatirabilirsiniz): ");
	fgets(miktar, 20, stdin); //Yat�r�alcak miktar.
	
	//Kullan�c� onay�
	onay_soru:
		printf("\nNot: Ornegin eger 200ksds gibi bir deger girdiyseniz isleminiz 200 TL uzerinden yapilir.\n");
		printf("\nDevam etmek istediginize emin misiniz?(E/H): ");
		onay = getche();
		
	switch (onay)
	{
		case 'E':
			break;
			
		case 'e':
			break;
			
		case 'H':
			goto menu_donus;
			break;
			
		case 'h':
			goto menu_donus;
			break;
			
		default:
			goto onay_soru;
			break;
	}
	
	miktar_uzunluk = strlen(miktar);
	
	miktar_yatir = atof(miktar);

	//Miktar 0 veya negatif ise.
	if (miktar_yatir <= 0 || miktar_yatir > MAX_MIKTAR) 
	{
		printf("\nGecersiz miktar.\n\n");
	}

	else 
	{
		*bakiye += miktar_yatir; //Bakiyeyi g�ncelle.

		hesap_bilgi_yatir_miktar[*yatir_durum] = miktar_yatir; //Listeyi g�ncelle.

		*yatir_durum += 1; //Yat�r�m say�s�n� g�ncelle.

		printf("\nHesabiniza basarili bir sekilde %.2f TL yatirildi.\n\n", miktar_yatir);
	}
	
	miktar_yatir = 0.0;

	printf("\n***************************************\n\n");
	
	menu_donus:
		printf("\nAna menuye donuluyor...\n\n");
		printf("\n***************************************\n\n");
}

//Bu fonksiyon para �ekmek i�indir.
void para_cek(double hesap_bilgi_cek_miktar[], int *cek_durum, double *bakiye) 
{
	double miktar_cek;
	char miktar[20];
	char onay;

	printf("\n***************************************\n\n");

	printf("\nKac TL cekmek istiyorsunuz(En fazla 10000 TL yatirabilirsiniz): ");
	fgets(miktar, 20, stdin); //�ekilecek miktar.
	
	//Kullan�c� onay�
	onay_soru:
		printf("\nNot: Ornegin eger 200ksds gibi bir deger girdiyseniz isleminiz 200 TL uzerinden yapilir.\n");
		printf("\nDevam etmek istediginize emin misiniz?(E/H): ");
		onay = getche();
		
	switch (onay)
	{
		case 'E':
			break;
			
		case 'e':
			break;
			
		case 'H':
			goto menu_donus;
			break;
			
		case 'h':
			goto menu_donus;
			break;
			
		default:
			goto onay_soru;
			break;
	}
	
	miktar_cek = atof(miktar);
	
	//Miktar 0 veya negatif ise.
	if (miktar_cek <= 0 || miktar_cek > MAX_MIKTAR) 
	{
		printf("\nGecersiz miktar.\n\n");
	}

	//Hesapta para var ve �ekilmek istenen miktar bakiyeden k���k veya e�it ise.
	else if (*bakiye > 0 && miktar_cek <= *bakiye) 
	{
		*bakiye -= miktar_cek; //Bakiyeyi g�ncelle.

		hesap_bilgi_cek_miktar[*cek_durum] = miktar_cek; //Listeyi g�ncelle.

		*cek_durum += 1; //�ekim say�s�n� g�ncelle.

		printf("\nHesabinizdan basarili bir sekilde %.2f TL cekildi.\n\n", miktar_cek);
	}

	//Hesapta para yoksa.
	else if (*bakiye <= 0) 
	{
		printf("\nYetersiz bakiye.\n\n");
	}

	//Hesapta �ekilmek istenen miktar yoksa.
	else if (miktar_cek > *bakiye) 
	{
		printf("\nHesabinizda %.2f TL bulunmamaktadir.\n\n", miktar_cek);
	}
	
	miktar_cek = 0.0;

	printf("\n***************************************\n\n");
	
	menu_donus:
		printf("\nAna menuye donuluyor...\n\n");
		printf("\n***************************************\n\n");
}

//Bu fonksiyon hesap bilgilerini g�sterir.
void hesap_bilgileri(char ad_soyad[], char sifre[], char kredi_karti[], double bakiye, int ad_uzunluk, int sifre_uzunluk) 
{
	int i;
	int kredi_karti_uzunluk;

	kredi_karti_uzunluk = strlen(kredi_karti);

	printf("\n***************************************\n\n");
	
	//Kullan�c� ad�.
	printf("\nKullanici adi:\n");

	printf("\n");

	for (i = 0; i < ad_uzunluk - 1; i++) 
	{
		printf("%c", ad_soyad[i]);
	}

	printf("\n\n");

	//�ifre uzunlu�u kadar y�ld�z.
	printf("\nSifre:\n\n");

	for (i = 0; i < sifre_uzunluk; i++) 
	{
		printf("*");
	}

	printf("\n\n");
	
	//Hesaptaki para.
	printf("\nBakiye:\n");

	printf("\n%.2f TL\n", bakiye);

	//Kredi kart� aktif mi?
	printf("\nKredi karti durumu:\n");

	printf("\n");

	for (i = 0; i < kredi_karti_uzunluk; i++) 
	{
		printf("%c", kredi_karti[i]);
	}

	printf("\n\n");

	printf("\n***************************************\n\n");
}

//Bu fonksiyon hesaptaki t�m hareketleri g�sterir.(Para yat�rma, �ekme ve havale)
void hesap_hareket(double hesap_bilgi_yatir_miktar[], double hesap_bilgi_cek_miktar[], double hesap_bilgi_havale_miktar[], long int hesap_bilgi_havale_hesap_no[], int yatir_durum, int cek_durum, int havale_durum) 
{
	int i;

	printf("\n***************************************\n\n");

	printf("\nPara yatirma hareketleri:\n");

	if (yatir_durum == 0) 
	{
		printf("\nBu hesaba hic para yatirilmadi.\n\n");
	}

	else 
	{
		for (i = 0; i < yatir_durum; i++) 
		{
			printf("\nBu hesaba %.2f TL para yatirdiniz.\n\n", hesap_bilgi_yatir_miktar[i]);
		}
	}

	printf("\nPara cekme hareketleri:\n");

	if (cek_durum == 0) 
	{
		printf("\nBu hesaptan hic para cekilmedi.\n\n");
	}

	else 
	{
		for (i = 0; i < cek_durum; i++) 
		{
			printf("\nBu hesaptan %.2f TL para cektiniz.\n\n", hesap_bilgi_cek_miktar[i]);
		}
	}

	printf("\nHavale hareketleri:\n");

	if (havale_durum == 0) 
	{
		printf("\nBu hesaptan hic havale yapilmadi.\n\n");
	}

	else 
	{
		for (i = 0; i < havale_durum; i++) 
		{	
			printf("\nBu hesaptan %ld numarali hesaba %.2f TL havale edildi.\n\n", hesap_bilgi_havale_hesap_no[i], hesap_bilgi_havale_miktar[i]);	
		}
	}

	printf("\n***************************************\n\n");
}

//Bu fonksiyon kredi kart� aktif eder.
void kredi_karti_ac(char kredi_karti[], int *kredi_karti_durum) 
{
	int limit;
	char limit_s[20];
	char onay;

	printf("\n***************************************\n\n");

	//Kredi kart� a��ksa.
	if (*kredi_karti_durum == 1) 
	{
		printf("\nZaten kredi kartiniz var.\n\n");
	}

	else 
	{
		printf("\nLimitiniz ne kadar olacak(En fazla 10000 TL limit koyabilirsiniz): ");
		fgets(limit_s, 20, stdin);
		
		//Kullan�c� onay�
		onay_soru:
			printf("\nNot: Ornegin eger 200ksds gibi bir deger girdiyseniz isleminiz 200 TL uzerinden yapilir.\n");
			printf("\nDevam etmek istediginize emin misiniz?(E/H): ");
			onay = getche();
			
		switch (onay)
	{
		case 'E':
			break;
			
		case 'e':
			break;
			
		case 'H':
			goto menu_donus;
			break;
			
		case 'h':
			goto menu_donus;
			break;
			
		default:
			goto onay_soru;
			break;
	}
		
		limit = atoi(limit_s);
		
		if (limit <= 0 || limit > MAX_MIKTAR)
		{
			printf("\nGecersiz limit.\n\n");
		}
		
		else
		{
			strcpy(kredi_karti, "Acik");

			*kredi_karti_durum = 1;

			printf("\n%d TL limitli kredi kartiniz aktif edilmistir.\n\n", limit);
		}
	}

	printf("\n***************************************\n\n");
	
	menu_donus:
		printf("\nAna menuye donuluyor...\n\n");
		printf("\n***************************************\n\n");
}

//Bu fonksiyon kredi kart� kapat�r.
void kredi_karti_kapat(char kredi_karti[], int *kredi_karti_durum) {

	printf("\n***************************************\n\n");
	
	//Kredi kart� kapal� ise.
	if (*kredi_karti_durum == 0) 
	{
		printf("\nHerhangi bir kredi kartiniz bulunmamaktadir.\n\n");
	}

	else 
	{
		strcpy(kredi_karti, "Kapali");

		*kredi_karti_durum = 0;

		printf("\nKredi kartiniz inaktif edilmistir.\n\n");
	}

	printf("\n***************************************\n\n");
}

//Bu fonksiyon havale i�in kesilecek komisyonu hesaplar.(Recursion olarak)
double komisyon_hesapla(double miktar, double miktar_kopya_komisyon) 
{
	double komisyon;

	if ((double) (miktar) == miktar_kopya_komisyon * (double)(1) / (100)) 
	{
		komisyon = (double) (miktar);
	}

	else 
	{
		komisyon = komisyon_hesapla(miktar - (double)(miktar_kopya_komisyon) / (100), miktar_kopya_komisyon);
	}

	return (komisyon);
}

//Bu fonksiyon havale yapar.
void havale(long int hesap_bilgi_havale_hesap_no[], double hesap_bilgi_havale_miktar[], int *havale_durum, double *bakiye) 
{
	double toplam_miktar;
	double miktar_havale;
	char miktar[20];
	int miktar_komisyon_kopya;
	double komisyon;
	int hesap_no;
	char hesap_no_s[10];
	char onay_miktar;
	char onay_hesap_no;
	
	printf("\n***************************************\n\n");
	printf("\nNe kadar gondermek istiyorsunuz(25'nin katlari kadar havale yapabilirsiniz ve kusuratlar sayilmayacaktir(25'in katlari icin)): ");
	fgets(miktar, 20, stdin); //Havale edilecek miktar.
	
	//Kullan�c� onay�
	onay_soru_miktar:
			printf("\nNot: Ornegin eger 200ksds gibi bir deger girdiyseniz isleminiz 200 TL uzerinden yapilir.\n");
			printf("\nDevam etmek istediginize emin misiniz?(E/H): ");
			onay_miktar = getche();
			
	switch (onay_miktar)
	{
		case 'E':
			break;
			
		case 'e':
			break;
			
		case 'H':
			goto menu_donus;
			break;
			
		case 'h':
			goto menu_donus;
			break;
			
		default:
			goto onay_soru_miktar;
			break;
	}
	
	miktar_havale = atof(miktar);
	
	if ((int) (miktar_havale) % 25 != 0)
	{
		printf("\n***************************************\n\n");
		
		printf("\nGondereceginiz miktar 25'in kati olmali.\n\n");
		
		printf("\n***************************************\n\n");
	}
	
	else
	{
		miktar_havale = floor(miktar_havale);
		
		miktar_komisyon_kopya = miktar_havale;
	
		komisyon = komisyon_hesapla(miktar_havale, miktar_komisyon_kopya); //Komisyon kes.

		//Hesaptan �ekilecek toplam miktar.
		toplam_miktar = miktar_havale + komisyon;

		printf("\n***************************************\n\n");

		//E�er girilen miktar 0 veya negatif ise.
		if (miktar_havale <= 0) 
		{
			printf("\n%.2f TL havale edemezsiniz.\n\n", miktar_havale);
		}

		//E�er toplam miktar bakiyeden k��k veya e�it ise.
		else if (toplam_miktar <= *bakiye) 
		{
			printf("Alici'nin hesap numarasini giriniz(En fazla 10 karakterli olmali): ");
			fgets(hesap_no_s, 10, stdin); //Al�c�n�n hesap numaras�.
			
			//Kullan�c� onay�
			onay_soru_hesap_no:
				printf("Not: Ornegin eger 200ksds gibi bir deger girdiyseniz isleminiz 200 hesap nosu uzerinden yapilir.\n");
				printf("\nDevam etmek istediginize emin misiniz?(E/H): ");
				onay_hesap_no = getche();
			
			switch (onay_hesap_no)
			{
				case 'E':
					break;
			
				case 'e':
					break;
			
				case 'H':
					goto menu_donus;
					break;
			
				case 'h':
					goto menu_donus;
					break;
			
				default:
					goto onay_soru_hesap_no;
					break;
			}
	
			hesap_no = atoi(hesap_no_s);
	
			//Hesap numaras� 0 veya negatif ise.(Onlar�n d���nda herhangi bir say� olabilir.)	
			if (hesap_no <= 0)
			{
				printf("\nGecersiz hesap numarasi.\n\n");
			}
		
			else
			{
				*bakiye -= toplam_miktar; //Bakiyeyi g�ncelle.

				hesap_bilgi_havale_miktar[*havale_durum] = miktar_havale; //Havale miktar�.

				hesap_bilgi_havale_hesap_no[*havale_durum] = hesap_no; //Havale hesap numaras�.

				*havale_durum += 1; //Yap�lan havale miktar�.

				printf("\nHavale isleminiz basarili bir sekilde gerceklesmistir.\n\n");
			}
		}

		//Di�er durumlarda.
		else 
		{
			printf("\nBakiyeniz yetersiz.\n\n");
		}

		printf("\n***************************************\n\n");	
	}
	
	miktar_havale = 0.0;
	
	menu_donus:
		printf("\nAna menuye donuluyor...\n\n");
		printf("\n***************************************\n\n");
}

//Bu fonksiyon giri� ekran�nda �ifreleri kar��la�t�r�r.
int sifre_karsilastirma(char sifre_giris[], char sifre[])
{
	int sayac = 0;
	int i;
	
	for (i = 0; i < SIFRE_KAPASITE; i++)
	{
		sayac += (sifre_giris[i] == sifre[i]);
	}
	
	return sayac;
}

int karakter_uzunluk(char secim[])
{
	int sayac = 0;
	int i;
	
	for (i = 0; i < 20; i++)
	{
		if (secim[i] != ' ')
		{
			sayac += 1;
		}
	}
	
	return sayac;
}
