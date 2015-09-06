// uloha-10-1.c -- Tyzden 10 - Uloha 1
// Michal Kovacik, 26.11.2014 21:19:20

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int zisti_pocet(char *vzorka, char (read)());
char vzor_a();
char vzor_aaabca();
int hashString(char *string);
int rollHash(char *megapole, int prevHash, int i, int j);

// ukazkovy test
int main(void)
{
  printf("zisti_pocet(\"aaa\", vzor_a) = %d\n", zisti_pocet("aaa", vzor_a));
  printf("zisti_pocet(\"aaa\", vzor_aaabca) = %d\n", zisti_pocet("abc", vzor_aaabca));
  return 0;
}

// urci pocet vyskytov vzorky v datach, ktore prichadzaju z funkcie read. Funkcia read vrati 0, ked je koniec vstupu.
int zisti_pocet(char *vzorka, char (read)())
{
    int vzorkaLenght=0, count=0, actHash=0, vzorkaHash, i=0, j=0;
    char c, flag=1, *megapole;
    megapole= (char*)calloc(20, sizeof(char));
    vzorkaLenght=strlen(vzorka);
    vzorkaHash = hashString(vzorka);
    while((c=read())!=0){
        megapole[j++]=c;
        if(j-i<vzorkaLenght)
            continue;
        if(flag){
            actHash=hashString(megapole);
            flag=0;
        }
        else
            actHash=rollHash(megapole, actHash, i++, j);
        if(actHash==vzorkaHash){
            if(!strcmp(vzorka, &megapole[i]))
                count++;
        }
    }
    return count;
}

int hashString(char *string){
    int hash=0, i;
    for(i=0; string[i]!='\0'; i++)
        hash=(hash<<1)+string[i];
    return hash;
}

int rollHash(char *megapole, int prevHash, int i, int j){
    prevHash-=(megapole[i]<<(j-i-2));
    prevHash=(prevHash<<1)+megapole[j-1];
    return prevHash;
}

// 10x a
char vzor_a(){
  static int len = 0;
  if (++len <= 10)
    return 'a';
  return 0;
}

// 5x aabca
char vzor_aaabca(){
  static int len = 0, i = 0, n = 6;
  static char *s = "aaabca";
  
  if (i == n)
  {
    if (++len >= 6)
      return 0;
    i = 0;
  }
  return s[i++];
}