#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char x, y, z[50];
	int l, mod, i, dlugosc, moddlugosci, ilosc_wierszy, nacos;
	FILE*tekst = fopen("tekst_vigenere2.txt", "r");
	FILE*szyfr = fopen("szyfr_Vigenere.txt", "w");
	FILE*szyfrr = fopen("szyfr_Vigenere.txt", "r");

	scanf("%s", z);
	l = strlen(z);
	printf("Dlugosc kodu to: %i\n", l);

	i = 0;
	dlugosc = 0;
	x = 0;
	y = 0;


	//-------------------------------------------------------------------------------\\


	while (!feof(tekst))
	{
		x = fgetc(tekst);
		mod = i % l;
		i++;
		x = x + z[mod] - 194;
		y = x % 26;
		y = y + 97;
		printf("%c", y);
		fputc(y, szyfr);
		dlugosc++;
	}
	dlugosc = dlugosc - 1;

	//-------------------------------------------------------------------------------\\

	printf("\n\nDlugosc tekstu to: %i\n", dlugosc);

	moddlugosci = dlugosc % l;
	nacos = 0;
	nacos = dlugosc / l;

	if (moddlugosci>0)
	{
		ilosc_wierszy = nacos + 1;
	}
	else
		ilosc_wierszy = nacos;


	printf("\n\nIloœæ wierszy to: %i\n", ilosc_wierszy);
	printf("\n\nReszta dlugosci tekstu to: %i\n\n", moddlugosci);


	//-------------------------------------------------------------------------------\\

	int tablica_abc[26];//zgodnosc

	rewind(szyfr);

	for (i = 0; i<26; i++)
	{
		tablica_abc[i] = i;
		//       printf("\n\nZnak to: %i\n",tablica_abc[i]);//97-122

	}

	//-------------------------------------------------------------------------------\\

	int s = l;
	int tablica_znak[l][26], c, n, v[s], r;//liczenie
	int k = 0;

	for (k = 0; k<s; k++)
	{
		v[k] = 0;
	}



	for (c = 0; c<26; c++)
	{
		for (n = 0; n<l; n++)
		{
			tablica_znak[n][c] = 0;
			//printf("Tablica %i %i: %i\n",c,n,tablica_znak[n][c]);
		}
	}




	while (!feof(szyfrr))
	{
		for (n = 0; n<l; n++)
		{
			v[n] = fgetc(szyfrr) - 97;
			for (s = 0; s<26; s++)
			{
				if (v[n] == tablica_abc[s])
				{
					tablica_znak[n][s]++;
					//  printf("Tablica nr %i %i ma wartosc: %i \n",n, s,tablica_znak[n][s]);
				}
			}
		}

	}

	//-------------------------------------------------------------------------------\\


	int sumy_znakow[l];


	for (n = 0; n<l; n++)
	{
		sumy_znakow[n] = 0;
		for (s = 0; s<26; s++)
		{
			sumy_znakow[n] = sumy_znakow[n] + tablica_znak[n][s];

		}
		//  printf("Dla n = %i jest %i \n",n ,sumy_znakow[n]); // OBLICZENIE SUM KOLUMN
	}




	int wsp_koin_pom[l][26];
	float suma_liter[l];


	for (n = 0; n<l; n++)
	{
		suma_liter[n] = 0;
		for (s = 0; s<26; s++)//Zerowanie tablic
		{

			wsp_koin_pom[n][s] = 0;
		}
	}

	for (n = 0; n<l; n++)
	{

		for (s = 0; s<26; s++)
		{
			wsp_koin_pom[n][s] = tablica_znak[n][s] * (tablica_znak[n][s] - 1);//czesc gorna wzoru
																			   // printf("COS n = %i %i jest %i \n",n , s,wsp_koin_pom[n][s]);

		}


	}


	//-------------------------------------------------------------------------------\\

	for (n = 0; n<l; n++)
	{
		for (s = 0; s<26; s++)
		{
			suma_liter[n] = (float)suma_liter[n] + (float)wsp_koin_pom[n][s];//suma gornej czesci
																			 //printf("Suma kolumnowa kol %i to % \n",n, wsp_koin_pom[n][s]);
		}
		printf("\n Suma kolumnowa kol %i to %f \n", n, suma_liter[n]);
	}

	float koin_wszo[l];

	for (n = 0; n<l; n++)
	{
		koin_wszo[n] = suma_liter[n] / (sumy_znakow[n] * (sumy_znakow[n] - 1));//calosc
		printf("\nWynik dla n=%i to %f\n", n, koin_wszo[n]);

	}

	//-------------------------------------------------------------------------------\\


	float koin_wzgl[l];
	float sumy_znakow_ko[l], sumy_dlugosci_ko[l];
	int a;
	a = 0;
	for (n = 0; n<l - 1; n++)
	{
		sumy_znakow_ko[n] = 0;
		koin_wzgl[n] = 0;



		for (a = 1; a<l; a++)
		{
			if (a != n)
			{
				sumy_znakow_ko[n] = 0;

				for (s = 0; s<26; s++)
				{
					sumy_znakow_ko[n] = sumy_znakow_ko[n] + (tablica_znak[n][s] * tablica_znak[a][s]);
				}

				koin_wzgl[n] = sumy_znakow_ko[n] / (sumy_znakow[n] * sumy_znakow[a]);
				printf("\nWynik dla kolumn: n %i oraz a %i to %f\n", a, n, koin_wzgl[n]);
			}
		}
	}


	return 0;
}
