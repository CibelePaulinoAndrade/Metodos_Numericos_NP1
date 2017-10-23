#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<locale.h>
//1º Exercicio-programa de Metodos Numericos
//Prof. Glauber Cintra

void esperar_comando(){
	//Funcao que espera comando do usuário
	char entradaChr;
	printf("Digite qualquer letra para voltar ao menu inicial:\n");
	scanf(" %c", &entradaChr);
	
}

//Comeca topico 1 - Conversao
void converter(double numero,int base){
	//Recebe um numero para converter, e uma base da qual sera convertida, de posse do primeiro valor 
	//resto da parte inteira, ele fara sucessivas divisoes pela base ate nao ser mais possivel dividir, depois, para
	//a parte fracionaria ele fara sucessivas multiplicacoes pela base, ate o valor fracionario ultrapassar
	//a 15° casa decinal (infinitas interacoes) ou o valor do fracionario ser 0.0.
	
	
	char vetorvalorhexa[6]={'A','B','C','D','E','F'}; 	                                     //Vetor para conversao de int para hexa
	int vetorInt[32];						                                                 //Vetores para guardar posicoes dos bits
	int vetorFrac[32];	
	int aux;							                                                    //Variavel auxiliar
	int fimvetor1=0;					                                                    //Variaveis para definir o fim dos vetores
	int fimvetor2=0;
	int inteiro = abs((int)numero);					                                        //Variavel guarda o modulo parte inteira
	double fracionaria = fabs(numero) - inteiro;	                                        //Variavel guarda o modulo da parte fracionaria
	
	vetorInt[fimvetor1] = inteiro%base;			                                            //Recolhe o ultimo valor base inteiro.
	fimvetor1++;
	while(inteiro>=base){						                                            //Para recolher a parte inteira,
		inteiro /= base;						        //faz sucessivas divisoes ate preencher o vetor, e definindo um limite para varre-lo,
		vetorInt[fimvetor1] = inteiro%base;		                                            //e para quando nao houver mais como dividir.
		fimvetor1++;	
	}
	
	while(!(fracionaria==0.0)&&fimvetor2<15){
		fracionaria *= base;					                                         	//Para recolher a parte fracinaria.
		vetorFrac[fimvetor2] = (int)fracionaria;     	//faz sucessivas multiplicacoes ate preencher o vetor, e definindo um limite para varre-lo,
		fracionaria -= (int)fracionaria;		    	//e para quando nao houver mais como multiplicar, ou quando o limite for igual a 15,
		fimvetor2++;
	}
	
	if(numero<0){
		printf("(1)");
	}
	for(aux=fimvetor1-1;aux>=0;aux--){							                          //Varre o vetor de fimvetor1-1 ate 0
		if(vetorInt[aux]>9){								            	//Se houver numeros acima de 9, printa uma letra representante do numero
			printf("%c",vetorvalorhexa[vetorInt[aux]-10]);	                             //hexadecimal
		}
		else{
			printf("%d",vetorInt[aux]);
		}
	}
	if(numero-(int)numero!=0.0){								                        //Se houver valor fracionario varre de 0 ate fimvetor2-1
		printf(".");							
		for(aux=0;aux<=fimvetor2-1;aux++){
			if(vetorFrac[aux]>9){								             //Se houver numeros acima de 9, printa uma letra representante do numero
				printf("%c",vetorvalorhexa[vetorFrac[aux]-10]);                        //hexadecimal
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
	printf("O primeiro digito é indicativo do sinal: 1 (negativo) e 0 (positivo - nesse caso o digito não é impresso).\n\n");
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
	//Funcao do tipo Sistema que nao recebe nenhum dado. Devera pedir o nome de um arquivo de texto contendo um sistema linear de n equaaces e n variaveis.
	//Caso o nome fornecido seja invalido, retorna uma mensagem de erro, caso contrario aloca os dados em seus respectivos locais. Retorna uma struct do 
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
		printf("\nDesculpe.\nArquivo não encontrado.\n\n");
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
				linha++;													 //Se prepara para a proxima interacao de linha.
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
				return 0;						                            // ele ja quebra o laco pois ja nao satisfaz o criterio das colunas.
			}
			else if(coluna==n-1){											//Se ele finalizar todas as interacoes, ele retorna o valor
				return 1;													//aprovando o criterio.
			}
			else{
				coluna++;												    //Se prepara para a proxima interacao de coluna.
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
	//a variacao nos ultimos dois valores das variaveis e menor que 10^(-8) ou se 1000 interacoes ja foram execudatas. Retorna 1 (um) caso as  
	//uma das condicoes anteriores seja satisfeita e, 0 (zero), caso contrario.
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
	printf("\n%d iteracões realizadas\n\n", interacoes);
}
void sistema_linear(){
	//Funcao que chama a funcao que le um arquivo de texto contendo um sistema linear de n equacoes e n variaveis e aloca os valores na matriz sistema.
	//Chama as funcoes para verificacao do criterio das linhas e do criterio das colunas. Caso o sistema satisfaÃ§a pelo menos um dos criterios ele continua e 
	//chama a funcao para calcular o valor das variaveis do sistema e a funcao para imprimir os valores obtidos na tela; e caso contrario retorna 
	//uma mensagem avisando que os criterios nÃ£o foram cumpridos. 
	
	int interacoes = 0;
	int i;
	int finalizar = 1;
	Sistema sis;
	
	sis = ler_entrada ();
	
	//Verifica se o sistema satisfaz o metodo da linha ou o da coluna.
	int criterioLinha = verifica_linha(sis.val,sis.sistema);
	int criterioColuna = verifica_coluna(sis.val,sis.sistema);
	
	if((criterioLinha == 0) && (criterioColuna == 0)){
		printf("O sistema não satisfaz nem o criterio das colunas nem o criterio das linhas.\n\n");
		esperar_comando();
		chamar_menu();
	}

	double estAtual[sis.val];                                                             //Guarda os valores atuais das variaveis
	double estAnterior [sis.val];                                                         //Guarda os valores das variaveis obtidos na iteracao anterior 
	
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
typedef struct polinomio{
	//Struct para guardar e agrupar os dados dos polinomio.
	int grau;
	double *polinomio;
}Polinomio;

Polinomio ler_polinomio (){
	//Funcao solicita o grau da equaÃ§Ã£o e os coeficientes an, an-1, ..., a0, nessa ordem. Retorna uma struct com os dados do polinomio lido.
	
	Polinomio pol;
	int grau_atual;
	
	printf("Digite o grau do polinomio: \n");
	scanf(" %d", &pol.grau );
	
	pol.polinomio = malloc(pol.grau * sizeof(double));
	
	for (grau_atual=pol.grau; grau_atual>=0; grau_atual--){
		printf("\nDigite o valor do coeficiente a%d: ", grau_atual);
		scanf(" %lf", &pol.polinomio[grau_atual]);
		if (grau_atual==pol.grau){
			while (pol.polinomio[grau_atual]<=0){
				printf("\nValor invalido. O valor de a%d deve ser maior que 0 (zero).\nDigite novamente:", grau_atual);
				scanf(" %lf", &pol.polinomio[grau_atual]);
			}
		}
		else if (grau_atual==0){
			while (pol.polinomio[grau_atual]==0){
				printf("\nValor invalido. O valor de a%d deve ser diferente de 0 (zero).\nDigite novamente:", grau_atual);
				scanf(" %lf", &pol.polinomio[grau_atual]);
			}
		}
	}
	
	return pol;
}
Polinomio inverte_polinomio (Polinomio pol){
	//Funcao recebe uma struct com os dados do polinomio base e o inverte. Retorna uma nova struct com os dados do vetor invertido
	
	int i;
	Polinomio pol_inv;
	pol_inv.grau = pol.grau;
	int grau = pol.grau;
	
	pol_inv.polinomio = malloc(pol_inv.grau * sizeof(double));
	
	for(i=grau; i>=0; i--){
		pol_inv.polinomio[pol.grau - i] = pol.polinomio[i];
	}	
	
	return pol_inv;
}

Polinomio muda_sinal_impar (Polinomio pol){
	//Funcao recebe uma struct com os dados do polinomio que deve ser alterado, multiplica os valores de grau impar por (-1)
	// e retorna uma nova struct com os novos dados do vetor
	
	int i;
	Polinomio pol_sinal;
	pol_sinal.grau = pol.grau;
	int grau = pol.grau;
	
	pol_sinal.polinomio = malloc(pol_sinal.grau * sizeof(double));
	
	for (i=0; i<=pol.grau; i++){
		if((i%2) != 0){
			pol_sinal.polinomio[i]=pol.polinomio[i]*(-1);
		}
		else{
			pol_sinal.polinomio[i]=pol.polinomio[i];
		}
	}
	
	return pol_sinal;
}

Polinomio inverte_polinomio_muda_sinal_impar (Polinomio pol){
	//Funcao recebe uma struct com os dados do polinomio que deve ser alterado, inverte a struct polinomio recebida
	//e depois multiplica por -1 os valores dos indices impares da struct nova e depois a retorna
	
	int i;
	Polinomio pol_inv_sinal;
	pol_inv_sinal.grau = pol.grau;
	int grau = pol.grau;
	
	pol_inv_sinal.polinomio = malloc(pol_inv_sinal.grau * sizeof(double));
	
	for(i=grau; i>=0; i--){
		pol_inv_sinal.polinomio[pol.grau - i] = pol.polinomio[i];
	}
	
	for (i=0; i<=pol.grau; i++){
		if((i%2) != 0){
			pol_inv_sinal.polinomio[i] *= -1;
		}
	}
	
	return pol_inv_sinal;
}

double lagrange (Polinomio pol){
	//Funcao recebe uma struct com os dados do polinomio e calcula o valor de L. Retorna o valor de L.
	
	int i;
	int n = pol.grau; 
	double an = pol.polinomio[pol.grau];
	int k=0;
	double b;
	double l;
	double coef_raiz;
	double div;
	
	for (i=pol.grau; i>=0; i--){
		if(pol.polinomio[i]<0&&k==0){
			k = i;
		}
		if(pol.polinomio[i]<b){
			b = pol.polinomio[i];
		}
	}
	
	b = fabs(b);
	coef_raiz = n-k;
	div = (b/an);
	l = pow(div,(1/coef_raiz));
	
	return l+1;
	
}

void calcular_limite_superior(double limite1,double limite2){
	//A funcao recebe o limite1 e o limite2 , apartir do limite2 ele calcula o alfa e depos o range entre alfa e limite1
	double alfa = 1/limite2;
	printf("Limite superior %lf <= x+ <= %lf\n",alfa,limite1);
}

void calcular_limite_inferior(double limite3,double limite4){
	//A funcao recebe o limite3 e o limite4 , apartir do limite4 ele calcula o alfa e depos o range entre limite3 e alfa
	double alfa = (1/limite4)*-1;
	limite3 *= -1;
	printf("Limite inferior %lf <= x+ <= %lf\n",limite3,alfa);
}

void metodo_newton(Polinomio pol,double limite1){
	//O mÃ©todo recebe o PolinÃ´mio base e o limite superior calculado na funÃ§Ã£o de lagrange, depois de alocado um novo polinomio
	//ele passa os valores da derivada do polinomio base para o novo, e entÃ£o apartir de uma variavel x0 que guarda
	//o limite superior, ele calcula f(x0) e f'(x0), que ficarÃ£o armazenadas nas variaveis soma e somaderivada
	//respectivamente, e depois divide a soma com a somaderivada e entÃ£o subtrai com x0, que serÃ¡ atribuido
	//a x1.
	
	int i;								//variavel auxilar
	Polinomio pol_derivado;
	pol_derivado.grau = pol.grau;
	int grau = pol.grau;				//guarda o grau limite dos polinomios
	double soma=0;
	double somaderivada=0;
	int interacoes = 0;
	double x0 = limite1;
	double x1 = 0;
	
	pol_derivado.polinomio = malloc(pol_derivado.grau * sizeof(double));
	i = grau;
	while(i>=1){			// passando a derivada do polinomio base para o polinomio de derivadas
		pol_derivado.polinomio[i] = pol.polinomio[i]*i;
		i--;
	}
	while(!(x0-x1<0.00000001)&&interacoes<1001){		//encerra quando for menor que a oitava casa decimal ou ocorrer as 1000 interacoes
		if(interacoes!=0){								//Evitar mudar o valor na primeira interaÃ§Ã£o.
			soma = 0;
			somaderivada = 0;
			x0 = x1;
		}
		for(i=grau; i>=0; i--){							//Calcula f(x0)
			soma += pol.polinomio[i]*pow(x0,i);
		}
		for(i=grau; i>=1; i--){							//Calcula f'(x0)
			somaderivada += pol_derivado.polinomio[i]*pow(x0,i-1);
		}
		x1 = x0 - (soma/somaderivada);					//Calcula a soluÃ§Ã£o
		interacoes++;
	}
	printf("Solucao do sistema: %9.8lf\n",x1);
	printf("Numero de interacoes: %d\n",interacoes);
}

void equacao_algebrica(){
	
	printf("Equação Algébrica\n");
	
	float pol_base;
	int grau_atual;
	Polinomio pol;
	Polinomio pol_inv;
	Polinomio pol_sinal;
	Polinomio pol_inv_sinal;
	
	pol = ler_polinomio();
	pol_inv = inverte_polinomio(pol);
	pol_sinal = muda_sinal_impar(pol);
	pol_inv_sinal = inverte_polinomio_muda_sinal_impar(pol);
	
	double limite1 = lagrange(pol);
	double limite2 = lagrange(pol_inv);
	double limite3 = lagrange(pol_sinal);
	double limite4 = lagrange(pol_inv_sinal);
	
	system("cls");
	
	calcular_limite_superior(limite1,limite2);
	calcular_limite_inferior(limite3,limite4);
	
	metodo_newton(pol,limite1);
	
	esperar_comando();
	chamar_menu();
}
//Termina topico 3 - Equacao algebrica

void chamar_menu(){
	//Funcao chama o menu da aplicacao, solicita a opcao desejada, ler a opcao escolhida pelo usuario e 
	//direciona para essa opcao atraves do switch case.
	char entradaChr;
	
	system("cls");	
	printf("Menu Principal\n");
	printf("C - Conversão\nS - Sistema Linear\nE - Equacao Algébrica\nF - Finalizar\n");
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
	
	setlocale(LC_ALL, "Portuguese");
	chamar_menu();
	
	return 0; 
}
