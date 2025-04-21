// condomini.c 
// simulacao da questao 5 da 40a Olimpiada de Matematica da UNICAMP
// jaz 20/04/25

#include <stdlib.h>
#include <stdio.h>

void printar_condo(int matriz[3][3]); void inserir_perrengues(int matriz[3][3]);
int condo_deboa(int matriz[3][3]); void troca_perrengues(int matriz[3][3]);

int main(void){
	
	// inicializando a matriz condominio com zeros
	int condo[3][3] = {0};
	int noite = 0;
	int deboa = 0;

	puts("Bem-vindo ao Condominio Planolandia! No Condomínio cada casa tem um número:");

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			printf("\t%d%d ", i+1, j+1);
		}
		printf("\n");
	}
	
	puts("Aqui tem vários perrengues. No momento, cada casa tem zero perrengues.");

	printar_condo(condo);

	printf("Dê perrengues para cada casa. Lembre-se que o número de perrengues deve ser positivo.\n");
	
	inserir_perrengues(condo);

	printf("Os perrengues ficaram assim:\n\n");
	printar_condo(condo);
	puts("");

	if (condo_deboa(condo)) {
		printf("O Condominio está de boa.\n");
	} else {
		printf("O Condomínio está em pé de guerra! Vamos ver a troca de perrengues:\n");
	}

	while(!condo_deboa(condo)) {
		noite++;
		printf("----------- Noite #%d -----------\n", noite);
		troca_perrengues(condo);

		printar_condo(condo);
	}

	if (noite > 0) {
		puts("-----------> de boa <-----------");
		printf("Foram necessárias %d noites para o condomínio ficar de boa.\n", noite);
	}

	return 0;
}

void printar_condo(int matriz[3][3]){
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			printf("\t%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

void inserir_perrengues(int matriz[3][3]) {
	int input;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			while (1) {
				input = 0;
				printf("Dê perrengues para a casa %d%d: ", i+1, j+1);
				scanf("%d", &input);

				// verificar se teste positivo
				if(input >= 0) { // positivo
					matriz[i][j] = input;
					break; // sai do while
				} else {
					printf("O número de perrengues deve ser positivo. Tente novamente.\n");
				}
			}
		}
	}
}

int condo_deboa(int matriz[3][3]) {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if(matriz[i][j] >= 4) {
				return 0;
			}
		}
	}

	return 1;
}

void troca_perrengues(int matriz[3][3]) {
	int matriz_despejo[3][3] = {0};

	// casa 00 --> canto: 2 j e 2 v
	if (matriz[0][0] >= 4) {
		matriz_despejo[0][0] = matriz_despejo[0][0] - 4;
		// despeja no vizinho da direita
		matriz_despejo[0][1]++;
		// desepeja no vizinho debaixo
		matriz_despejo[1][0]++;  
	}

	// casa 01 --> meio: 1 j e 3 v
	if (matriz[0][1] >= 4) {
		matriz_despejo[0][1] = matriz_despejo[0][1] - 4;
		// despeja no vizinho da esquerda
		matriz_despejo[0][0]++;
		// despeja no vizinho da direita
		matriz_despejo[0][2]++;
		// desepeja no vizinho debaixo
		matriz_despejo[1][1]++;  
	}

	// casa 02 --> canto: 2 j e 2 v
	if (matriz[0][2] >= 4) {
		matriz_despejo[0][2] = matriz_despejo[0][2] - 4;
		// despeja no vizinho da esquerda
		matriz_despejo[0][1]++;
		// desepeja no vizinho debaixo
		matriz_despejo[1][2]++;  
	}

	// casa 10 --> meio: 1 j e 3 v
	if (matriz[1][0] >= 4) {
		matriz_despejo[1][0] = matriz_despejo[1][0] - 4;
		// despeja no vizinho de cima
		matriz_despejo[0][0]++;
		// despeja no vizinho da direita
		matriz_despejo[1][1]++;
		// desepeja no vizinho debaixo
		matriz_despejo[2][0]++;  
	}

	// casa 11 --> sindico: 0 j e 4 v
	if (matriz[1][1] >= 4) {
		matriz_despejo[1][1] = matriz_despejo[1][1] - 4;
		// despeja no vizinho de cima
		matriz_despejo[0][1]++;
		// despeja no vizinho da esquerda
		matriz_despejo[1][0]++;
		// despeja no vizinho da direita
		matriz_despejo[1][2]++;
		// desepeja no vizinho debaixo
		matriz_despejo[2][1]++;  
	}

	// casa 12 --> meio: 1 j e 3 v
	if (matriz[1][2] >= 4) {
		matriz_despejo[1][2] = matriz_despejo[1][2] - 4;
		// despeja no vizinho de cima
		matriz_despejo[0][2]++;
		// despeja no vizinho da esquerda
		matriz_despejo[1][1]++;
		// desepeja no vizinho debaixo
		matriz_despejo[2][2]++;  
	}

	// casa 20 --> canto: 2 j e 2 v
	if (matriz[2][0] >= 4) {
		matriz_despejo[2][0] = matriz_despejo[2][0] - 4;
		// despeja no vizinho de cima
		matriz_despejo[1][0]++;
		// despeja no vizinho da direita
		matriz_despejo[2][1]++;  
	}

	// casa 21 --> meio: 1 j e 3 v
	if (matriz[2][1] >= 4) {
		matriz_despejo[2][1] = matriz_despejo[2][1] - 4;
		// despeja no vizinho de cima
		matriz_despejo[1][1]++;
		// despeja no vizinho da esquerda
		matriz_despejo[2][0]++;
		// despeja no vizinho da direita
		matriz_despejo[2][2]++;  
	}

	// casa 22 --> canto: 1 j e 3 v
	if (matriz[2][2] >= 4) {
		matriz_despejo[2][2] = matriz_despejo[2][2] - 4;
		// despeja no vizinho de cima
		matriz_despejo[1][2]++;
		// despeja no vizinho da esquerda
		matriz_despejo[2][1]++;  
	}

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			matriz[i][j] = matriz[i][j] + matriz_despejo[i][j];
		}
	}
}
