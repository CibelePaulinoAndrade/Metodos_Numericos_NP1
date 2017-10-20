# M-todos_N-mericos_NP1
#include<stdio.h>
#include<stdlib.h>

float convertBin(float n,int inteiro){
	int i;
	for(i=0;i<sizeof(int)*8;i++){
		printf("%d",((int )n>>sizeof(int)*8-1-i)&1);
	}
	n=n-inteiro;//pegando a parte fracioária do número;
	while(n!=1){
		printf("%d",(int)(n*2));
		n = n*2;
	}
}


 int main(){
	float n;
	int inteiro = (int)n;
	int i;
	
	scanf("%f",&n);
	
	convertBin(n,inteiro);
	
	return 0;

}
