#include <stdio.h>

char isPrime[1300000];
int prime[100000];

int main(){
	int position;
	long unsigned int i, j, k;
	i = 0;
	j = 2;
	//erastotenovo sito
	while (i < 100000){
		//ak najdem prvocislo
		if (!isPrime[j]){
			//zapisem si ho
			prime[i++] = j;
			for (k = j; k < 1300000; k+=j){
				//vyplieskam jeho nasobky z pola
				isPrime[k] = 1;
			}
		}
		j++;
	}
	while(scanf("%d", &position)>0)
		printf("%d\n", prime[position - 1]);
	return 0;
}