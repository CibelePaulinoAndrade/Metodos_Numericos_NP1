#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<locale.h>
//1º Exercicio-programa de Metodos Numericos
//Prof. Glauber Cintra
//Equipe: Cibele Paulino, Narcelio Lima, Gabriel Leal, Raimundo.

void esperar_comando(){
	char entradaChr;
	printf("Digite qualquer letra para voltar ao menu inicial:\n");
	scanf(" %c", &entradaChr);
	
}

//Comeca topico 1 - Conversao
void converter(double numero,int base){
	//Recebe um numero para converter, e uma base da qual sera convertida, de posse do primeiro valor 
	//resto da parte inteira, ele fara sucessivas divisôes pela base ate não ser mais possível dividir, depois, para
	//a parte fracionaria ele fara sucessivas multiplicaçoes pela base, até o valor fracionario ultrapassar
	//a 15° casa decinal (infinitas interações) ou o valor do fracionario ser 0.0.
	
	
	char vetorvalorhexa[6]={'A','B','C','D','E','F'}; 	//Vetor para conversão de int para hexa
	int vetorInt[32];						//Vetores para guardar posições dos bits
	int vetorFrac[32];	
	int aux;							//Variavel auxiliar
	int fimvetor1=0;					//Variaveis para definir o fim dos vetores
	int fimvetor2=0;
	int inteiro = abs((int)numero);					//Variavel guarda o módulo parte inteira
	double fracionaria = fabs(numero) - inteiro;	//Variavel guarda o módulo da parte fracionaria
	
	vetorInt[fimvetor1] = inteiro%base;			//Recolhe o ultimo valor base inteiro.
	fimvetor1++;
	while(inteiro>=base){						//Para recolher a parte inteira,
		inteiro /= base;						//faz sucessivas divisões ate preencher o vetor, e definindo um limite para varre-lo,
		vetorInt[fimvetor1] = inteiro%base;		//e para quando não houver mais como dividir.
		fimvetor1++;	
	}
	
	while(!(fracionaria==0.0)&&fimvetor2<15){
		fracionaria *= base;						//Para recolher a parte fracinária.
		vetorFrac[fimvetor2] = (int)fracionaria;	//faz sucessivas multiplicacoes ate preencher o vetor, e definindo um limite para varre-lo,
		fracionaria -= (int)fracionaria;			//e para quando não houver mais como multiplicar, ou quando o limite for igual a 15,
		fimvetor2++;
	}
	
	if(numero<0){
		printf("(1)");
	}
	for(aux=fimvetor1-1;aux>=0;aux--){							//Varre o vetor de fimvetor1-1 até 0
		if(vetorInt[aux]>9){									//Se houver numeros acima de 9, printa uma letra representante do numero
			printf("%c",vetorvalorhexa[vetorInt[aux]-10]);		//hexadecimal
		}
		else{
			printf("%d",vetorInt[aux]);
		}
	}
	if(numero-(int)numero!=0.0){								//Se houver valor fracionário varre de 0 ate fimvetor2-1
		printf(".");							
		for(aux=0;aux<=fimvetor2-1;aux++){
			if(vetorFrac[aux]>9){								//Se houver numeros acima de 9, printa uma letra representante do numero
				printf("%c",vetorvalorhexa[vetorFrac[aux]-10]); //hexadecimal
			}
			else{
				printf("%d",vetorFrac[aux]);
			}
		}
	}
	printf("\n");
}

void conversao(){
	double numero;
	
	printf("Conversao\n");
	printf("Digite um valor para converter (usar virgula caso não seja inteiro)\n");
	scanf(" %lf",&numero);
	
	system("cls");
	printf("Primeiro valor indicativo de sinal, se for 0 (positivo) nao imprime\n");
	printf("Binario: ");
	converter(numero,2);
	printf("Octal: ");
	converter(numero,8);
	printf("Hexadecimal: ");
	converter(numero,16);
	
	esperar_comando();
	chamar_menu();
}
//Termina topico 1 - Conversao

//Comeca topico 2 - Sistema Linear 
typedef struct sistema_linear {
	//Struct para guardar e agrupar os dados colhidos do arquivo.
	int val;
	double **sistema;
}Sistema;

Sistema ler_entrada (){
	//Funcao do tipo Sistema que não recebe nenhum dado. Devera pedir o nome de um arquivo de texto contendo um sistema linear de n equações e n variáveis.
	//Caso o nome fornecido seja inválido, retorna uma mensagem de erro, caso contrário aloca os dados em seus respectivos locais. Retorna uma struct do 
	//tipo Sistema contendo a matriz estendida correspondente ao sistema e um inteiro com o numero de variaveis.
	FILE *arq;
	Sistema sis;
	char arquivo[20];
	int linha;
	int coluna;
	
	printf("Digite o nome do arquivo desejado: \n");
	scanf("%s", &arquivo);
	arq = fopen(arquivo, "r");
	
	if(arq == NULL){
		printf("\nDesculpe.\nArquivo nao encontrado.\n\n");
		esperar_comando();
		chamar_menu();
	}
	
	fscanf(arq, " %d", &sis.val);
	
	sis.sistema = malloc(sis.val * sizeof(double*));

	for ( linha = 0; linha<sis.val; linha++){
		sis.sistema[linha] = malloc((sis.val+1) * sizeof(double));
		for ( coluna = 0; coluna<sis.val+1; coluna++){
			fscanf(arq, " %lf", &sis.sistema[linha][coluna]);
		}
	}
	
	fclose(arq);
	return sis;
}

int verifica_linha(int n, double **sistema){
	//O metodo soma |a[linha][coluna]| se linha!=coluna, caso seja igual ele pula para a proxima interacao, ao final do programa 
	//ele retorna um valor 1 caso o criterio das linhas seja satisfeito, e 0 caso nao haja satisfacao do criterio.
	int linha=0;
	int coluna=0;
	
	double somatorio = 0;                                                      // variavel para acumular os valores de |a[linha][coluna]|
	
	while(1){
		if(linha!=coluna){
			somatorio += abs(sistema[linha][coluna]);
		}
		if(coluna==n-1){
			if(abs(sistema[linha][linha])<=somatorio){                        //Verifica se o |a[linha][linha]|<=somatorio, caso ele seja em algumas das  
				return 0;		                                              //linhas ele ja quebra o laco pois ja nao satisfaz o criterio das linhas.
			}
			else if(linha==n-1){											  //Se ele finalizar todas as interacoes, ele retorna o valor
				return 1;													  //aprovando o criterio.
			}
			else{
				linha++;													//Se prepara para a proxima interacao de linha.
				somatorio = 0;
				coluna=0;
			}
		}
		else{
			coluna++;
		}
	}
}//fim verifica_linha
	
int verifica_coluna(int n, double **sistema){
	//O metodo soma |a[linha][coluna]| se linha!=coluna, caso seja igual ele pula para a proxima interacao, ao final do programa 
	//ele retorna um valor 1 caso o criterio das colunas seja satisfeito, e 0 caso nao haja satisfacao do criterio.
	int linha=0;
	int coluna=0;
	
	double somatorio = 0;                                                  // variavel para acumular os valores de |a[linha][coluna]|
	
	while(1){
		if(linha!=coluna){
			somatorio += abs(sistema[linha][coluna]);
		}
		if(linha==n-1){
			if(abs(sistema[coluna][coluna])<=somatorio){		            //Verifica se o |a[coluna][coluna]|>somatorio, caso nao seja em algumas das  
				return 0;						                           // ele ja quebra o laco pois ja nao satisfaz o criterio das colunas.
			}
			else if(coluna==n-1){											//Se ele finalizar todas as interacoes, ele retorna o valor
				return 1;													//aprovando o criterio.
			}
			else{
				coluna++;												   //Se prepara para a proxima interacao de coluna.
				somatorio = 0;
				linha=0;
			}
		}
		else{
			linha++;
		}
	}
}//fim verifica_coluna

double gauss_seidel(int indice, double *multiplicadores, double *valores, int tamVal ){
	//Funcao que recebe o indice (variavel) a ser calculado(da), o endereco de um vetor com os valores de vetor[i], o endereco de um vetor 
	//com os valores atuais das variaveis e um inteiro com o numero de variaveis. Calcula o valor das variaveis utilizando o metodo interativo 
	//para resolucao de sistemas de equacoes lineares de Gauss-Seidel. Retorna o valor obtido.
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
	//Funcao que recebe um inteiro referente ao numero de variaveis do sistema, o endereco de um vetor com os valores atuais das variaveis,
	//o endereco de um vetor com os valores anteriores das variaveis e um inteiro com o numero de interacoes que ja foram executadas. Verifica se
	//a variacao no valor das variaveis e menor que 10^(-8) ou se 1000 interacoes ja foram execudatas. Retorna 1 (um) caso as uma das condicoes 
	//anteriores seja satisfeita e, 0 (zero), caso contrario.
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
	//Funcao que recebe o endereco de um vetor com os valores atuais das variaveis, um inteiro com o numero de interacoes que foram 
	//executadas e um inteiro referente ao numero de variaveis do sistema. Imprime na tela os valores obtidos para cada variavel e o
	//numero de interacoes realizadas.
	int i;
	system("cls");
	printf("Resultado:\n");
	for (i=0;i<val;i++){
		printf("X%d: %9.3lf\n", i+1, estAtual[i]);
	}
	printf("\n%d iteracoes realizadas\n\n", interacoes);
}
void sistema_linear(){
	//Funcao que chama a funcao que le um arquivo de texto contendo um sistema linear de n equacoes e n variaveis e aloca os valores na matriz sistema.
	//Chama as funcoes para verificacao do critio das linhas e do criterio das colunas. Caso o sistema satisfaça pelo menos um dos criterios ele continua e 
	//chama a funcao para calcular o valor das variaveis do sistema e a funcao para imprimir os valores obtidos na tela; e caso contrario retorna 
	//uma mensagem avisando que os criterios não foram cumpridos. 
	
	
	int interacoes = 0;
	int i;
	int finalizar = 1;
	Sistema sis;
	
	sis = ler_entrada ();
	
	int criterioLinha = verifica_linha(sis.val,sis.sistema);
	int criterioColuna = verifica_coluna(sis.val,sis.sistema);
	
	if((criterioLinha == 0) && (criterioColuna == 0)){
		printf("O sistema não satisfaz nem o criterio das colunas nem o criterio das linhas.\n\n");
		esperar_comando();
		chamar_menu();
	}

	double estAtual[sis.val];
	double estAnterior [sis.val];
	
	for (i=0; i<sis.val; i++){
		estAtual[i]= 0.0;
		estAnterior[i]= 0.0;
	}
	
	while(finalizar){
		double resultado;
		interacoes++;
		for (i=0;i<sis.val;i++){
			resultado = gauss_seidel(i, sis.sistema[i], estAtual, sis.val);
			estAnterior[i] = estAtual[i];
			estAtual[i]= resultado;
		}
		if ((controle_parada_sistema(sis.val, estAtual, estAnterior, interacoes)) == 1){
			finalizar = 0;
		}
	}
	
	imprime_resultado_sistema(estAtual, interacoes, sis.val);
	
	esperar_comando();
	chamar_menu();
	
}
//Termina topico 2 - Sistemas Lineares

//Comeca topico 3 - Equacao algebrica
void equacao_algebrica(){
	printf("Equação Algebrica\n");
	
	esperar_comando();
	chamar_menu();
}
//Termina topico 3 - Equacao algebrica

void chamar_menu(){
	//Funcao chama o menu da aplicacao, solicita a opcao desejada, ler a opcao escolhida pelo usuario e 
	//direciona para essa opcao atraves do switch case.
	char entradaChr;
	
	system("cls");
	setlocale(LC_ALL, "Portuguese");
	
	printf("Menu Principal\n");
	printf("C - Conversao\nS - Sistema Linear\nE - Equacao Algebrica\nF - Finalizar\n");
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
			printf("Ate logo\n");
			break;
		default:
			printf("Alternativa invalida.");
			esperar_comando();
			chamar_menu();
	}
}
int main (){
	
	chamar_menu();
	
	return 0; 
}
