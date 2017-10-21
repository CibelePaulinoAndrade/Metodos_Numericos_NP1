#include<stdio.h>
#include<stdlib.h>
 
//Entrando com o valor 12.5;
void convertBin(float n){
	/*Recebe um numero float n, depois fragmenta em 2 partes, uma será a parte inteira do float recebido
	que irá para a variavel "inteiro", o outro será a parte fracinária que será a variavel "fracionaria"
	em posse desses valores, se inicia 2 vetores inteiros, um guardará o binário inteiro e o outro o 
	binário fracionário. No vetor inteiro "binInt" preechemos com valores apartir do deslocamento de bits
	de um numero inteiro. Já no vetor da parte fracionaria "binDec" a gente faz multiplicaçoes sucessivas
	até a 15° casa decimal, no caso truncando o numero se ele houver infinitos processos.Caso o inteiro ou
	a fração seja 0, define 0 na posição inicial.*/
	int binInt[32];
	int binDec[32];				
	int i;			//contador auxiliar;
	int fimvetor1=0;
	int fimvetor2=0;
	int inteiro = (int)n;
	float fracionaria = n - inteiro;
	
	if(inteiro!=0){
		for(i=0;i<sizeof(int)*8;i++){
			if(((int )inteiro>>sizeof(int)*8-1-i)&1==1||fimvetor1>0){
				binInt[fimvetor1] = ((int )inteiro>>sizeof(int)*8-1-i)&1;
				fimvetor1++;
			}
		}
	}
	else{
		binInt[fimvetor1] = 0;
	}
	
	if(fracionaria!=0.0){
		while(!((int)fracionaria==1&&(fracionaria-1)==0)&&fimvetor2<15){
			if((int)fracionaria==1){
				fracionaria -= 1;
		}
		else{
				fracionaria *= 2;
				binDec[fimvetor2] = (int)fracionaria;
				fimvetor2++;
			}
		}
	}
	else{
		binDec[fimvetor2] = 0;
	}
	
	for(i=0;i<fimvetor1;i++){
			printf("%d",binInt[i]); //Atenção nesse detalhe, eu to printando de maneira
		}				//certa, mas não sei se isso é aceitável.
	printf(",");				//No caso só faltaria concatenar os vetores..
	for(i=0;i<=fimvetor2-1;i++){
			printf("%d",binDec[i]);
		}
}

 int main(){
 	
	float n;
	
	scanf("%f",&n);

	convertBin(n);
	
	return 0;

}
