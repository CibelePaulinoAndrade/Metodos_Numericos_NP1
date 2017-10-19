#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<locale.h>

void conversao(){
	printf("Conversão\n");
	esperar_comando();
	chamar_menu();
}

void sistema_linear(){
	
	printf("Sistema Linear\n");
	esperar_comando();
	chamar_menu();
	
}

void equacao_algebrica(){
	printf("Equação Algebrica\n");
	esperar_comando();
	chamar_menu();
}
void esperar_comando(){
	char entradaChr;
	printf("Digite qualquer letra para continuar:\n");
	scanf(" %c", &entradaChr);
}
void chamar_menu(){
	//Função chama o menu da aplicação, solicita a opção desejada, ler a opção escolhida pelo usuário e 
	//direciona para essa opção através do switch case.
	char entradaChr;
	
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	
	printf("Menu Principal\n");
	printf("C - Conversão\nS - Sistema Linear\nE - Equação Algébrica\nF - Finalizar\n");
	scanf (" %c", &entradaChr);                                                               

	switch (entradaChr){
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
		default:
			printf("Alternativa inválida.");
			esperar_comando();
			chamar_menu();
	}
}
int main (){
	
	chamar_menu();
	
	return 0; 
}
