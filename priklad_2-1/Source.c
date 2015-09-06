#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct polia{
	char meno[1000];
	struct polia *dalsi;
}POLIA;

void vypis(char **obdlznik, int pocet, int i);
char **nahraj(POLIA *prvy, int pocet);

int main(){
	char **obdlznik, *buf, *empty;
	int i, pocet = 0;
	POLIA *novy_polia, *prvy_polia = NULL, *aktualny_polia, *predchadzajuci_polia;
	buf = (char*)malloc(1000 * sizeof(char));
	while (scanf("%100[^\n\r]", buf) > 0){
		getchar();
		//kym nemam cislo
		if (!strtol(buf, &empty, 10)){
			pocet++;
			//ukladanie prveho
			if (!prvy_polia){
				prvy_polia = (POLIA*)malloc(sizeof(POLIA));
				prvy_polia->dalsi = NULL;
				strcpy(prvy_polia->meno, buf);
			}
			//ukladanie dalsieho
			else{
				novy_polia = (POLIA*)malloc(sizeof(POLIA));
				novy_polia->dalsi = NULL;
				strcpy(novy_polia->meno, buf);
				aktualny_polia = prvy_polia;
				predchadzajuci_polia = prvy_polia;
				//insert sort
				//prechadzam zoznam kym nenajdem kam pridat dalsiu polozku
				while (aktualny_polia != NULL && strcmp(aktualny_polia->meno, novy_polia->meno)<0){
					aktualny_polia = aktualny_polia->dalsi;
					//skipnem prvy presun aktualneho, aby som bol o krok pozadu
					if (predchadzajuci_polia->dalsi != aktualny_polia){
						predchadzajuci_polia = predchadzajuci_polia->dalsi;
					}
				}
				//ak pridavam na prve miesto
				if (aktualny_polia == prvy_polia){
					novy_polia->dalsi = prvy_polia;
					prvy_polia = novy_polia;
				}
				else{
					novy_polia->dalsi = predchadzajuci_polia->dalsi;
					predchadzajuci_polia->dalsi = novy_polia;
				}
			}
		}
		//ked mam cislo
		else{
			//prekopirujem zoznam do obdlznika
			obdlznik = nahraj(prvy_polia, pocet);
			break;
		}
	}
	//vycistim posledný nacitany riadok s cislami
	while ((i = strtol(buf, &buf, 10)) != 0){
		vypis(obdlznik, pocet, i);
	}
	//uz len scanfujem do konca
	while (scanf("%d", &i) > 0){
		vypis(obdlznik, pocet, i);
	}
	return 0;
}

//vypis iteho riadku obdlznika
void vypis(char **obdlznik, int pocet, int i){
	if (pocet < i || i<1)
		printf("Vstup neobsahuje prvok %d\n", i);
	else
		printf("%s\n", *(obdlznik + i - 1));
}

//kopirovanie zoznamu do obdlznika
char **nahraj(POLIA *prvy, int pocet){
	int i;
	char **obdlznik;
	//aloc poctu riadkov
	obdlznik = (char**)malloc(sizeof(char*)*pocet);
	for (i = 0; i < pocet; i++){
		//aloc dlzky riadkov
		*(obdlznik + i) = (char*)malloc(sizeof(char)*strlen(prvy->meno));
		//kopirovanie
		strcpy(*(obdlznik + i), prvy->meno);
		//posun v zozname
		prvy = prvy->dalsi;
	}
	return obdlznik;
}