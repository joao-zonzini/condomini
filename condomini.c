// Programa: condomini.c 
// Objetivo: simular a questão 5 da 40a Olimpíada de Matemática da Unicamp
// Autor: João Pedro de Azevedo Zonzini @ 21/04/25

// importação das bibliotecas padrões de C
#include <stdlib.h>
#include <stdio.h>

// generalização do tamanho do condominio
#define LINHAS 3    // linhas da matriz que representa o condominio
#define COLUNAS LINHAS
// o condominio é quadrado
// o numero de casas no condominio é LINHAS * COLUNAS

//declaração das funções
void printar_condo(int matriz[LINHAS][COLUNAS]); void inserir_perrengues(int matriz[LINHAS][COLUNAS]);
int condo_deboa(int matriz[LINHAS][COLUNAS]); void troca_perrengues(int matriz[LINHAS][COLUNAS]);

int main(void){
	// inicialização da matriz condominio com zeros perrengues
	int condo[LINHAS][COLUNAS] = {0};

	// inicialização das variaveis noite e deboa
	int noite = 0; // conta o # de noites
	int deboa = 0; // variavel de estado do condominio

	puts("Bem-vindo ao Condominio Planolandia! No Condomínio cada casa tem um número:");

	// imprimir na tela os numeros das casas
	for(int i = 0; i < LINHAS; i++) {
		for(int j = 0; j < COLUNAS; j++) {
			printf("\t%d%d ", i+1, j+1);
		}
		printf("\n");
	}
	
	puts("Aqui tem vários perrengues. No momento, cada casa tem zero perrengues.");

	printar_condo(condo);

	printf("Dê perrengues para cada casa. Lembre-se que o número de perrengues deve ser positivo.\n");
	
	// chama função que recebe o numero de perrengues em cada casa
	inserir_perrengues(condo);

	// mostra de volta os perrengues para o usuario
	printf("Os perrengues ficaram assim:\n\n");
	printar_condo(condo);
	puts("");

	// analiza o estado do condominio antes da trocação de perrengues
	if (condo_deboa(condo)) {
		printf("O Condominio está de boa.\n"); // não precisa fazer a troca de perrengues
	} else {
		printf("O Condomínio está em pé de guerra! Vamos ver a troca de perrengues:\n");
	}

	// executa código enquanto o condominio não fica de boa
	while(!condo_deboa(condo)) {
		// simula uma noite --> adiciona no contador
		noite++;
		printf("----------- Noite #%d -----------\n", noite);
		
		// executa a troca de perrengues
		troca_perrengues(condo);

		// imprime a nova configuraçao do condominio
		printar_condo(condo);
	}	// saiu do loop --> condominio ficou de boa
 
	if (noite > 0) {
		puts("-----------> de boa <-----------");
		printf("Foram necessárias %d noites para o condomínio ficar de boa.\n", noite);
	}

	return 0;
}

void printar_condo(int matriz[LINHAS][COLUNAS]){
	// para imprimir a configuração do condominio, é preciso percorrer cada posição da matriz
	for(int i = 0; i < LINHAS; i++) {
		for(int j = 0; j < COLUNAS; j++) {
			printf("\t%d ", matriz[i][j]);
		}
		printf("\n");
	}
}

void inserir_perrengues(int matriz[LINHAS][COLUNAS]) {
	// inicialização de variavel de input do usuario
	int input;

	// para cada casa do condominio, inserir um número de perrengues
	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			while (1) {
				// se livrando de possível lixo na variavel input
				input = 0;

				// recebendo do usuario
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
	// verificar se o condominio está de boa significa se verificar se existe alguma casa com 4 perrengues ou mais
	for(int i = 0; i < LINHAS; i++) {
		for(int j = 0; j < COLUNAS; j++) {
			if(matriz[i][j] >= 4) {
				return 0; // zero significa que o condominio não está de boa
			}
		}
	}
	return 1; // um significa que o condominio está de boa
}

void troca_perrengues(int matriz[LINHAS][COLUNAS]) {
	// inicialização de uma matriz temporária que vai registrar qual a diferença de perrengues
	// entre a configuração atual e a configuração nova do condominio
	int matriz_despejo[LINHAS][COLUNAS] = {0};

	// matriz como os deslocamentos para os vizinhos diretamente adjacentes
    int deslocamentos[4][2] = {
        {-1, 0}, // cima
        {1, 0},  // baixo
        {0, -1}, // esquerda
        {0, 1},  // direita
    };

	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			if (matriz[i][j] >= 4) { // se a casa tem perrengues, ela sempre despeja 4
				matriz_despejo[i][j] = matriz_despejo[i][j] - 4;
				for (int k = 0; k < 4; k++) { // determinar vizinhos adjacentes
					int linha_viz = i + deslocamentos[k][0];
					int coluna_viz = j + deslocamentos[k][1];

					// verificar se o vizinho está dentro dos limites da matriz
					if (linha_viz >= 0 && linha_viz < LINHAS && coluna_viz >= 0 && coluna_viz < COLUNAS) {
						// poderiamos tirar um perrengue de matriz_despejo[i][j] para cada vizinho
						// mas já fizemos acima e assim não precisamos considerar as janelas
						//vizinho válido --> despeja perrengue nele
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
