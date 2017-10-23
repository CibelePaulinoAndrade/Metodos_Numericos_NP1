#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<math.h>

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
	
	int i;
	Polinomio pol_derivado;
	pol_derivado.grau = pol.grau-1;
	int grau = pol.grau;
	double x=limite1;
	double soma=0;
	double somaderivada=0;
	int interacoes = 0;
	
	pol_derivado.polinomio = malloc(pol_derivado.grau * sizeof(double));

	for(i=grau; i>=1; i--){
		pol_derivado.polinomio[i-1] = pol.polinomio[i]*i;
	}
	//remover do codigo final
	for(i=pol_derivado.grau;i>=0;i--){
		printf("a%d: %lf ",i,pol_derivado.polinomio[i]);
	}
	
	for(i=grau; i>=0; i--){
		soma += pol.polinomio[i]*pow(limite1,i);
	}
	for(i=pol_derivado.grau; i>=0; i--){
		somaderivada += pol_derivado.polinomio[i]*pow(limite1,i);
	}
	x = x - (soma/somaderivada);
	printf("\n%lf",x); //deletar depois
	/*while(interacoes<1001){
		for(i=grau; i>=0; i--){
			soma += pol.polinomio[i]*pow(x,i);
		}
		for(i=pol_derivado.grau; i>=0; i--){
			somaderivada += pol_derivado.polinomio[i]*pow(x,i);
		}
		x = x - (soma/somaderivada);
		printf("\n%lf",x);
		interacoes++;
	}*/
}

int main(){
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
	
	calcular_limite_superior(limite1,limite2);
	calcular_limite_inferior(limite3,limite4);
	
	metodo_newton(pol,limite1);
	
	return 0;
}
