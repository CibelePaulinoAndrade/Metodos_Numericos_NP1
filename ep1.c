#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
//1º Exercício-programa de Métodos Numéricos
//Prof. Glauber Cintra
//Equipe: Cibele Paulino, Narcélio Lima, Gabriel, Raimundo.

//Começa tópico 1 - Conversão
void conversao(){
	printf("Conversão\n");
	esperar_comando();
	chamar_menu();
}
//Termina tópico 1 - Conversão

//Começa tópico 2 - Sistema Linear 
//FALTA COLOCAR O LANCE DAS LINHAS E COLUNAS (ATENÇÃO!!!!)
double gauss_seidel(int indice, int *multiplicadores, double *valores, int tamVal ){
	//Função que recebe o indice (variavél) a ser calculado(da), o endereço de um vetor com os valores de vetor[i], o endereço de um vetor 
	//com os valores atuais das variavéis e um inteiro com o número de variavéis. Calcula o valor das variavéis utilizando o método interativo 
	//para resolução de sistemas de equações lineares de Gauss-Seidel. Retorna o valor obtido.
	int i;
	double result;
	result = 0.0;
	for (i=0; i<tamVal; i++ ){
		if (indice != i){
			result = result - multiplicadores [i]*valores [i];
		}
	}
	result+=multiplicadores[i];
	result/=multiplicadores[indice];
	return result;
}

int controle_parada_sistema(int val, double *estAtual, double *estAnterior, int interacoes){
	//Função que recebe um inteiro referente ao número de variavéis do sistema, o endereço de um vetor com os valores atuais das variavéis,
	//o endereço de um vetor com os valores anteriores das variavéis e um inteiro com o número de interações que já foram executadas. Verifica se
	//a variação no valor das variavéis é menor que 10^(-8) ou se 1000 interações já foram executas. Retorna 1 (um) caso as uma das condições 
	//anteriores seja satisfeita e, 0 (zero), caso contrário.
	int i;
	int controle = 0;
	for(i=0;i<val;i++){
			if((estAtual[i]-estAnterior[i])< 0.00000001){
				controle++;
			}
		}
		if(controle==val || interacoes == 1000 ){
			return 1;
		}
		else{
			return 0;
		}
}

void imprime_resultado_sistema(double *estAtual ,int interacoes, int val){
	//Função que recebe o endereço de um vetor com os valores atuais das variavéis, um inteiro com o número de interações que foram 
	//executadas e um inteiro referente ao número de variavéis do sistema. Imprime na tela os valores obtidos para cada variavél e o
	//número de interações realizadas.
	int i;
	system("cls");
	printf("Resultado:\n");
	for (i=0;i<val;i++){
		printf("X%d: %.4Le\n", i+1, estAtual[i]);
	}
	printf("\n%d iteracoes realizadas\n\n", interacoes);
}
void sistema_linear(){
	//Função que lê um arquivo de texto contendo um sistema linear de n equações e n variavéis. Aloca os valores nas variavéis adequadas.
	//Chama a função para calcular o valor das váriavéis do sistema e a função para imprimir os valores obtidos na tela.
	FILE *arq;
	char arquivo[20];
	int interacoes = 0;
	int aux;
	int val;
	int i;
	int j;
	
	printf("Digite o nome do arquivo desejado: \n");
	scanf("%s", &arquivo);
	arq = fopen(arquivo, "r");
	
	fscanf(arq, " %d", &val);
	int vetor [val][val+1];
	
	for ( i = 0; i<val; i++){
		for ( j = 0; j<val+1; j++){
			fscanf(arq, " %d", &aux);
			vetor[i][j] = aux;
		}
	}
	
	double estAtual[val];
	double estAnterior [val];
	
	for (i=0; i<val; i++){
		estAtual[i]=0.0;
		estAnterior[i]=0.0;
	}
	
	while(1){
		double resultado;
		interacoes++;
		for (i=0;i<val;i++){
			resultado = gauss_seidel(i, vetor[i], estAtual, val);
			estAnterior[i] = estAtual[i];
			estAtual[i]= resultado;
		}
		if ((controle_parada_sistema(val, estAtual, estAnterior, interacoes)) == 1){
			break;
		}
	}
	
	imprime_resultado_sistema(estAtual, interacoes, val);
	
	esperar_comando();
	chamar_menu();
	
}
//Termina tópico 2 - Sistemas Lineares

//Começa tópico 3 - Equação algébrica
void equacao_algebrica(){
	printf("Equação Algebrica\n");
	
	esperar_comando();
	chamar_menu();
}
//Termina tópico 3 - Equação algébrica

void esperar_comando(){
	char entradaChr;
	printf("Digite qualquer letra para voltar ao menu inicial:\n");
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
