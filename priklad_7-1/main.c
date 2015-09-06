// uloha-7-1.c -- Tyzden 7 - Uloha 1
// Michal Kovacik, 4.11.2014 16:52:02

#include <stdio.h>
#include <stdlib.h>

unsigned long long int factorial_memory[21];

typedef struct zoznam{
    int hodnota;
    struct zoznam *dalsi;
}ZOZNAM;

// Urci k-tu permutaciu cisel 1,2,...,n a zapise ju do pola vysledok.
void kperm(int n, unsigned long long int k, int vysledok[]);
// urci najblizsi nizsi faktorial
unsigned long long factorial(int n);
// Urci k-tu permutaciu cisel 1,2,...,n a zapise ju do pola vysledok.
void calculate(int n, unsigned long long int k, int vysledok[], int depth, ZOZNAM *options);
// urci cislo na pouzitie
int chooseOption(int i, ZOZNAM **options);
// ukazkovy test
int main(void)
{
  int j, n = 19, p[19];
  unsigned long long i;
  for (i = factorial(18); i <= factorial(19); i++)
  {
    kperm(n, i, p);
    printf("%d:", i);
    for (j = 0; j < n; j++)
      printf(" %d", p[j]);
    printf("\n");
  }
  return 0;
}

void kperm(int n, unsigned long long int k, int vysledok[]){
    ZOZNAM *options=NULL, *novy, *dalsi;
    int i;
    for (i=1; i<=n; i++){
        novy = (ZOZNAM*)malloc(sizeof(ZOZNAM));
        novy->hodnota=i;
        novy->dalsi=NULL;
        if(options==NULL){
            options=dalsi=novy;
        }
        else{
            dalsi->dalsi=novy;
            dalsi=novy;
        }
    }
    calculate(n, k, vysledok, 0, options);
}

void calculate(int n, unsigned long long int k, int vysledok[], int depth, ZOZNAM *options){
    int i, count = n-depth;
    unsigned long long int fact, nfact;
    nfact = fact = factorial(count-1);
    for(i=1; i<=n; i++){
        if(i>1)
            nfact+=fact;
        if(nfact>=k){
            k=k-(nfact-fact);
            i=chooseOption(i, &options);
            vysledok[depth++]=i;
            if(depth<n)
                calculate(n, k, vysledok, depth, options);
            break;
        }
    }
}

unsigned long long int factorial(int n){
    if (factorial_memory[n])
        return factorial_memory[n];
    if (n>1)
        return factorial_memory[n]=n*factorial(n-1);
    return 1;
}

int chooseOption(int i, ZOZNAM **options){
    int count=1, value;
    ZOZNAM *akt, *pred;
    akt=pred=*options;
    while(count!=i){
        akt=akt->dalsi;
        if(pred->dalsi!=akt)
            pred=pred->dalsi;
        count++;
    }
    value=akt->hodnota;
    if(akt!=*options)
        pred->dalsi=akt->dalsi;
    else
        *options=(*options)->dalsi;
    return value;
}