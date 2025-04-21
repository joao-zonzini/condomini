// condomini.c 
// simulação da questão 5 da 40a Olimpíada de Matemática da Unicamp
// jaz 21/04/25

#include <stdlib.h>
#include <stdio.h>

#define LINHAS 3    // Número de linhas da matriz
#define COLUNAS 3   // Número de colunas da matriz

void printar_condo(int matriz[LINHAS][COLUNAS]); void inserir_perrengues(int matriz[LINHAS][COLUNAS]);
int condo_deboa(int matriz[LINHAS][COLUNAS]); void troca_perrengues(int matriz[LINHAS][COLUNAS]);

int main(void){
	
	// inicializando a matriz condominio com zeros
	int condo[LINHAS][COLUNAS] = {0};
	int noite = 0;
	int deboa = 0;

	puts("Bem-vindo ao Condominio Planolandia! No Condomínio cada casa tem um número:");

	for(int i = 0; i < LINHAS; i++) {
		for(int j = 0; j < COLUNAS; j++) {
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

void printar_condo(int matriz[LINHAS][COLUNAS]){
	for(int i = 0; i < LINHAS; i++) {
		for(int j = 0; j < COLUNAS; j++) {
			printf("\t%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

void inserir_perrengues(int matriz[LINHAS][COLUNAS]) {
	int input;
	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			while (1) {
				input = 0;
				printf("Dê perrengues para a casa %d%d: ", i+1, j+1);
				scanf("%d", &input);

				// verificar se input positivo
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

int condo_deboa(int matriz[LINHAS][COLUNAS]) {
	for(int i = 0; i < LINHAS; i++) {
		for(int j = 0; j < COLUNAS; j++) {
			if(matriz[i][j] >= 4) {
				return 0;
			}
		}
	}

	return 1;
}

void troca_perrengues(int matriz[LINHAS][COLUNAS]) {
	int matriz_despejo[LINHAS][COLUNAS] = {0};

	// Matriz como os deslocamentos para os vizinhos diretamente adjacentes
    int deslocamentos[4][2] = {
        {-1, 0}, // cima
        {1, 0},  // baixo
        {0, -1}, // esquerda
        {0, 1},  // direita
    };

	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			if (matriz[i][j] >= 4) { // se a casa tem perrengues, ela despeja 4
				matriz_despejo[i][j] = matriz_despejo[i][j] - 4;
				for (int k = 0; k < 4; k++) { // joga os perrengues nos vizinhos adjacentes
					int linha_viz = i + deslocamentos[k][0];
					int coluna_viz = j + deslocamentos[k][1];

					// Verificar se a posição está dentro dos limites da matriz
					if (linha_viz >= 0 && linha_viz < LINHAS && coluna_viz >= 0 && coluna_viz < COLUNAS) {
						matriz_despejo[linha_viz][coluna_viz]++;
					}
				}	
			} 
		}
	}

	// gera nova configuração do condominio
	for(int i = 0; i < LINHAS; i++) {
		for(int j = 0; j < COLUNAS; j++) {
			matriz[i][j] = matriz[i][j] + matriz_despejo[i][j];
		}
	}
}
