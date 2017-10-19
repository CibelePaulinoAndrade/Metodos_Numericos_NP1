#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<locale.h>

void conversao(){
	
}

void sistema_linear(){
	
}

void equacao_algebrica(){
	
}

void chamar_menu(){
	//Função chama o meu da aplicação, solicita a opção desejada, ler a opção escolhida pelo usuário e 
	//direciona para a opção desejada através do switch case.
	char menu ;
	
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	
	printf("Menu Principal\n");
	printf("C - Conversão\nS - Sistema Linear\nE - Equação Algébrica\nF - Finalizar\n");
	scanf ("%2c", &menu);
	
	while(menu != 'C' && menu != 'S' && menu != 'E' && menu != 'F'){
		printf("Alternativa inválida, tente novamente:\n");
		scanf ("%2c", &menu);
	}
	switch (menu){
		case 'C':
			conversao();
			break;
		case 'S':
			sistema_linear();
			break;
		case 'E':
			equacao_algebrica();
			break;
		case 'F': 
			printf("Até logo\n");
			break;
	}
}
int main (){
	
	chamar_menu();
	
	return 0; 
}
