// uloha-8-1.c -- Tyzden 8 - Uloha 1
// Michal Kovacik, 12.11.2014 08:53:28

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define isnum(x) (((x)>='0' && (x)<='9')? 1:0)

typedef struct number{
    int array[1000];
    int count;
}NUMBER;

NUMBER *nacitajCinitel();
char vyhodnotOperaciu(char *operacia);
void scitaj(NUMBER *cinenec, NUMBER *cinitel);
NUMBER *nasob(NUMBER *cinenec, NUMBER *cinitel);
void vypis(NUMBER *cislo);

int main(){
    NUMBER *cinitel, *cislo;
    char operacia[10], prepinac;
    cislo = (NUMBER*)calloc(1, sizeof(NUMBER));
    while(scanf("%s", operacia)>0){
        cinitel=nacitajCinitel();
        prepinac = vyhodnotOperaciu(operacia);
        switch(prepinac){
            case 1: scitaj(cislo, cinitel); break;
            case 2: cislo=nasob(cislo, cinitel); break;
            default: printf("Neplatna operacia!"); break;
        }
        vypis(cislo);
    }
    return 0;
}

NUMBER *nacitajCinitel(){
    NUMBER *cinitel = (NUMBER*)calloc(1, sizeof(NUMBER));
    char buf[1000];
    int pocet, i;
    scanf("%s", buf);
    pocet = strlen(buf);
    cinitel->count=pocet-1;
    for(pocet--, i=0 ;pocet>=0; pocet--, i++)
        cinitel->array[pocet] = buf[i] - '0';
    return cinitel;
}

char vyhodnotOperaciu(char *operacia){
    if(!strcmp(operacia, "plus"))
        return 1;
    if(!strcmp(operacia, "krat"))
        return 2;
    return 0;
}

void scitaj(NUMBER *cinenec, NUMBER *cinitel){
    int prechod=0, i=0, temp;
    while(i<=cinitel->count || prechod!=0){
        temp = cinenec->array[i] + cinitel->array[i] + prechod;
        prechod = temp/10;
        if(prechod)
            temp%=10;
        cinenec->array[i]=temp;
        if(cinenec->count<i)
            cinenec->count=i;
        i++;
    }
}

void vypis(NUMBER *cislo){
    int i=cislo->count;
    for(; i>=0; i--)
        printf("%d", cislo->array[i]);
    putchar('\n');
}

NUMBER *nasob(NUMBER *cinenec, NUMBER *cinitel){
    NUMBER *medzi, *temp;
    int i, j, prechod, pom;
    medzi = (NUMBER*)calloc(1, sizeof(NUMBER));
    for(i=0; i<=cinitel->count; i++){
        prechod=0;
        j=0;
        temp = (NUMBER*)calloc(1,sizeof(NUMBER));
        while (prechod!=0 || j<=cinenec->count){
            pom = prechod + (cinitel->array[i]*cinenec->array[j]);
            prechod=pom/10;
            if (prechod)
                pom%=10;
            temp->array[j+i]=pom;
            if(j+i>temp->count)
                temp->count=j+i;
            j++;
        }
        scitaj(medzi, temp);
        free(temp);
    }
    return medzi;
}
