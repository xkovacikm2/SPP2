// uloha-9-2.c -- Tyzden 9 - Uloha 2
// Michal Kovacik, 20.11.2014 08:20:55

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct zoznam{
    int start;
    int stop;
    struct zoznam *dalsi;
}ZOZNAM;

void quickSort(double **arr, int from, int to);
ZOZNAM *vytvorZoznam(double **mem, double speed, int n);
char stiham(double *villagerPosition, double *applePosition, double speed);
void vypis(double **mem, int i);
void vyhodnot(double **mem, int n, ZOZNAM *zoznam, double speed);
char posunStart(ZOZNAM *zaznam);
char posunStop(ZOZNAM *zaznam);

int main(){
    int pocet, i;
    double speed, **pamat;
    ZOZNAM *zoznam;
    while(scanf("%d %lf", &pocet, &speed)>0){
        pamat = (double**)malloc(pocet*sizeof(double*));
        for(i=0; i<pocet; i++){
            pamat[i]=(double*)malloc(3*sizeof(double));
            scanf("%lf %lf %lf", &pamat[i][0], &pamat[i][1], &pamat[i][2]);
        }
        quickSort(pamat, 0, i-1);
        zoznam = vytvorZoznam(pamat, speed, i);
        vyhodnot(pamat, i, zoznam, i);
    }
    return 0;
}

void quickSort(double **arr, int from, int to){
    int i = from, j = to;
    double *pivot = arr[from], *pom;
    if (to - from>0){
        while (i < j){
            while (i<=to && arr[i][2] <= pivot[2])
                i++;
            while (j>=from && arr[j][2] > pivot[2])
                j--;
            if (i < j){
                pom = arr[i];
                arr[i] = arr[j];
                arr[j] = pom;
            }
        }
        pom = arr[from];
        arr[from] = arr[j];
        arr[j] = pom;
        quickSort(arr, from, j - 1);
        quickSort(arr, i, to);
    }
}

ZOZNAM *vytvorZoznam(double **mem, double speed, int n){
    int i=0;
    double *villagerPosition;
    ZOZNAM *novy=NULL, *akt=NULL, *prvy=NULL;
    while(i<n){
        novy=(ZOZNAM*)calloc(1, sizeof(ZOZNAM));
        villagerPosition=(double*)calloc(3, sizeof(double));
        novy->start=i;
        while(i<n && stiham(villagerPosition, mem[i], speed)){
            villagerPosition=mem[i];
            novy->stop=i;
            i++;
        }
        if(novy->stop){
            if(akt==NULL)
                prvy=novy;
            else
                akt->dalsi=novy;
            akt=novy;
        }
        else{
            free(novy);
            i++;
        }
    }
    return prvy;
}

char stiham(double *villagerPosition, double *applePosition, double speed){
    double x,y,vektor,mozne;
    x=villagerPosition[0]-applePosition[0];
    y=villagerPosition[1]-applePosition[1];
    vektor=sqrt(pow(x,2)+pow(y,2));
    mozne = speed*(applePosition[2]-villagerPosition[2]);
    if(mozne>=vektor)
        return 1;
    return 0;
}

void vyhodnot(double **mem, int n, ZOZNAM *zoznam, double speed){
    ZOZNAM *akt, *pred;
    int pocet=0;
    pred=zoznam;
    akt=pred->dalsi;
    while(akt!=NULL){
        if(!stiham(mem[pred->stop], mem[akt->start], speed)){
            if(posunStart(akt) && !stiham(mem[pred->stop], mem[akt->start], speed)){
                akt->start--;
                if(posunStop(pred)){
                    continue;
                }
            }
        }
        pred=akt;
        akt=akt->dalsi;
    }
    while(zoznam!=NULL){
        pocet+=(zoznam->start-zoznam->stop);
    }
    printf("%d\n", pocet);
}

void vypis(double **mem, int i){
    int j;
    for (j=0; j<=i; j++)
        printf("%lf %lf %lf\n", mem[j][0], mem[j][1], mem[j][2]);
}

char posunStart(ZOZNAM *zaznam){
    if((zaznam->start - zaznam->stop)>0)
        zaznam->start++;
    if((zaznam->start - zaznam->stop)>0)
        return 1;
    return 0;
}

char posunStop(ZOZNAM *zaznam){
    if((zaznam->start - zaznam->stop)>0)
        zaznam->stop--;
    if((zaznam->start - zaznam->stop)>0)
        return 1;
    return 0;
}