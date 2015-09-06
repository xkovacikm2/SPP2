// uloha-8-2.c -- Tyzden 8 - Uloha 2
// Michal Kovacik, 12.11.2014 08:57:12

#include <stdio.h>

// vypocita x^n
double xn(double x, int n)
{
    double pom=x, vysledok=1;
    while(n>0){
        if(n&1)
            vysledok*=pom;
        pom*=pom;
        n>>=1;
    }
    return vysledok;
}

// ukazkovy test
int main(void)
{
  int i;
  for (i = 0; i < 32; i++)
    printf("2^%d = %lf\n", i, xn(2.0, i));
  return 0;
}
