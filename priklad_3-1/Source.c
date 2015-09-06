#include <stdio.h>
#include <stdlib.h>

typedef struct hrana{
	int kam;
	int velkost;
	struct hrana *dalsi;
}HRANA;

typedef struct vrchol{
	char marker;
	HRANA *prva_hrana;
	HRANA *posledna_hrana;
}VRCHOL;

VRCHOL *alokuj_vrcholy(); 
void vytvor_hrany(int buf2, int buf1, int value, VRCHOL ***vrcholy);
int najdi(VRCHOL ***vrcholy, int akt, int target, int value);

int main(){
	VRCHOL **vrcholy;
	int n, m, a, b, i, buf1, buf2, value;
	scanf("%d %d %d %d", &n, &m, &a, &b);
	//alokujem pole struktur
	vrcholy = (VRCHOL**)malloc((n+1)*sizeof(VRCHOL*));
	//alokujem samotne struktury
	for (i = 1; i <= n; i++){
		*(vrcholy + i) = alokuj_vrcholy();
	}
	for (i = 0; i < m; i++){
		scanf("%d %d %d", &buf1, &buf2, &value);
		//vytvorim si novu hranu
		vytvor_hrany(buf2, buf1, value, &vrcholy);
		vytvor_hrany(buf1, buf2, value, &vrcholy);
	}
	printf("%d\n", najdi(&vrcholy, a, b, 0));
	return 0;
}

VRCHOL *alokuj_vrcholy(){
	VRCHOL *vrcholy;
	vrcholy= (VRCHOL*)malloc(sizeof(VRCHOL));
	vrcholy->marker = 0;
	vrcholy->prva_hrana = vrcholy->posledna_hrana = NULL;
	return vrcholy;
}

void vytvor_hrany(int buf2, int buf1, int value, VRCHOL ***vrcholy){
	HRANA *hrana_pom;
	hrana_pom = (HRANA*)malloc(sizeof(HRANA));
	hrana_pom->dalsi = NULL;
	hrana_pom->kam = buf2;
	hrana_pom->velkost = value;
	//ukladam do vrcholy[buf1] hodnotu buf2
	//ak este nemam vytvoreny zoznam
	if ((*vrcholy)[buf1]->prva_hrana == NULL){
		//ulozim
		(*vrcholy)[buf1]->prva_hrana = hrana_pom;
		(*vrcholy)[buf1]->posledna_hrana = hrana_pom;
	}
	//ak uz nieco mam tak to priplacnem na koniec
	else{
		(*vrcholy)[buf1]->posledna_hrana->dalsi = hrana_pom;
		(*vrcholy)[buf1]->posledna_hrana = hrana_pom;
	}
}

int najdi(VRCHOL ***vrcholy, int akt,  int target, int value){
	int i = 0;
	//ak som nasiel, vratim hodnotu hrany
	if (akt == target)
		return value;
	//poznacim si, ze na tomto bode som uz bol
	(*vrcholy)[akt]->marker = 1;
	//pomozem si
	(*vrcholy)[akt]->posledna_hrana = (*vrcholy)[akt]->prva_hrana;
	//budem sa vetvit kym bude kam
	while ((*vrcholy)[akt]->posledna_hrana != NULL){
		//ak by hrana na ktorej som viedla do vrcholu kde som uz bol
		if ((*vrcholy)[(*vrcholy)[akt]->posledna_hrana->kam]->marker){
			//posuniem sa na inu hranu
			(*vrcholy)[akt]->posledna_hrana = (*vrcholy)[akt]->posledna_hrana->dalsi;
			continue;
		}
		//tu bude rekurzia
		//pytam sa ci funkcia mi nahodou nevrati nenulovu odpoved, ak ano tak scitam navratovu hodnotu s vlastnou value a vratim
		if ((i = najdi(vrcholy, (*vrcholy)[akt]->posledna_hrana->kam, target, (*vrcholy)[akt]->posledna_hrana->velkost))!=0)
			return (i + value);
		(*vrcholy)[akt]->posledna_hrana = (*vrcholy)[akt]->posledna_hrana->dalsi;
	}
	return 0;
}