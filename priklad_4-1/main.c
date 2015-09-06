// uloha-4-1.c -- Tyzden 4 - Uloha 1
// Michal Kovacik, 15.10.2014 06:54:08

#include <stdio.h>

// vrati index cisla x vo vzostupne usporiadanej postupnosti cisel. Vrati -1 ak sa x v postupnosti nenachadza.
int search(int cisla[], int n, int x)
{
    int left, right, mid;
    for(left=0, right=n-1, mid=n>>1; left<=right; mid=(right+left)>>1){
        if(cisla[mid]==x)
            return mid;
        if(cisla[mid]>x)
            right=mid-1;
        else
            left=mid+1;  
    }
    return -1;
}

// ukazkovy test
int main(void)
{
  int a[] = {10};

  printf("Cislo 30 je na pozicii %d\n", search(a, 1, 30));
  printf("Cislo 25 je na pozicii %d\n", search(a, 1, 0));
  printf("Cislo 20 je na pozicii %d\n", search(a, 1, 10));
  
  return 0;
}
