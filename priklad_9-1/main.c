// uloha-9-1.c -- Tyzden 9 - Uloha 1
// Michal Kovacik, 20.11.2014 11:55:27

#include <stdio.h>

int main()
{
  int pred2, pred1, max, kolko, akt, i, temp;
  while(scanf("%d", &kolko)>0){
      pred2=0;
      scanf("%d", &pred1);
      max=pred1;
      for(i=1; i<kolko; i++){
          scanf("%d", &akt);
          max=((pred2=pred2+akt)<pred1)? pred1:pred2;
          temp = pred1;
          pred1=max;
          pred2=temp;
      }
      printf("%d\n", max);
  }
  return 0;
}