// uloha-10-2.c -- Tyzden 10 - Uloha 2
// Michal Kovacik, 27.11.2014 12:04:11

#include <stdio.h>
#include <string.h>

int main(){
char string[10];
int count, i, j;
while(scanf("%s", string)>0){
    count=i=0;
    j=strlen(string);
    while(i<j){
        while(i<j && string[i]!=string[j]){
            j--;
            count++;
        }
        i++; j--;
    }
    printf("%d\n", count-1);
}
return 0;
}
