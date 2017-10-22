#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>

typedef struct polinomio{
	//Struct para guardar e agrupar os dados dos polinomio.
	int grau;
	double *polinomio;
}Polinomio;

Polinomio ler_polinomio (){
	//Funcao solicita o grau da equação e os coeficientes an, an-1, ..., a0, nessa ordem. Retorna uma struct com os dados do polinomio lido.
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
	
	//Print de controle - devera sair da versao final
	printf("\nVetor inicial:\n");
	for (grau_atual = pol.grau; grau_atual>=0; grau_atual--){
		printf(" a%d = %lf", grau_atual, pol.polinomio[grau_atual]);
	}
	return pol;
}
Polinomio inverte_polinomio (Polinomio pol){
	//Funcao recebe uma struct com os dados do polinomio base e o inverte. Renorta uma nova struct com os dados do vetor invertido
	
	int i;
	Polinomio pol_inv;
	pol_inv.grau = pol.grau;
	int grau = pol.grau;
	
	pol_inv.polinomio = malloc(pol_inv.grau * sizeof(double));
	
	for(i=grau; i>=0; i--){
		pol_inv.polinomio[pol.grau - i] = pol.polinomio[i];
	}	
	
	//Print de controle - devera sair da versao final
	printf("\nVetor invertido:\n");
	for (i=grau; i>=0; i--){
		printf(" a%d = %lf", grau, pol_inv.polinomio[i]);
	}
	
	
	return pol_inv;
}

Polinomio muda_sinal_impar (Polinomio pol){
	//Funcao recebe uma struct com os dados do polinomio que deve ser alterado, multiplica os valores de grau impar por (-1)
	// e retorna uma nova struct com os novos dados do vetor
	int i;
	int j;
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
	
	//Print de controle - devera sair da versao final
	printf("\nVetor inicial com sinal invertido:\n");
	for (grau; grau>=0; grau--){
		printf(" a%d = %lf", grau, pol_sinal.polinomio[grau]);
	}
	
	return pol_sinal;
}

double lagrange (Polinomio pol){
	//Funcao recebe uma struct com os dados do polinomio e calcula o valor de L. Retorna o valor de L.
	
	int i;
	double controlador = 0.0;
	int n = pol.grau; 
	double an = pol.polinomio[0];
	int k;
	double b;
	double l;
	double coef_raiz;
	double div;
	
	for (i=pol.grau; i>=0; i--){
		if (pol.polinomio[i]<0){
			k = pol.polinomio[i]*(-1);                                  // ATENCAO: tratar excessao - o que acontece se n existir valores negativos?
		}		
	}
	
	for (i=pol.grau; i>=0, i--){
		if (pol.polinomio[i]<0){                                        // ATENCAO: tratar excessao - o que acontece se n existir valores negativos?
			if (pol.polinomio[i]<controlador){
				controlador = pol.polinomio[i];
			}
		}
	}
	
	b = controlador * (-1);
	coef_raiz = n-k;
	div = b/an
	
	//ver funcao para calcular a 'raiz' enesima de um valor 'div'.
	//raiz - tentem adaptar a funcao pow da biblioteca math.h pra isso. Ideia do elias.
	
	l = 1+ raiz;
	
	return l;
	
}
int main(){
	float pol_base;
	int grau_atual;
	Polinomio pol;
	Polinomio pol_inv;
	Polinomio pol_sinal;
	
	pol = ler_polinomio();
	pol_inv = inverte_polinomio(pol);
	pol_sinal = muda_sinal_impar(pol);
	
	return 0;
}
