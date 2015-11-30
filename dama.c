#include <stdio.h>
#include <stdlib.h>

typedef struct coord {
	int i;
	int j;
} coord;

char tabuleiro[8][8];
char aux[8][8];
int dirP[2][2] = {{-1,-1},{-1,1}};
int dirB[2][2] = {{1,1},{1,-1}};
coord all_pos[4*8*8];
void gerar_tabuleiro() {
	int i, j;
	for(i = 0; i < 8; i++) {
		if(i%2 == 0) j = 0;
		else j = 1;

		for(j; j < 8; j+=2) {
			tabuleiro[i][j] = '#';
			aux[i][j] = '#';
		}
	}
}

void colocar_pecas() {
	int i, j;
	for(i = 0; i < 8; i++) {
		if(i%2 == 0) j = 1;
		else j = 0;

		for(j; j < 8 && i < 3; j+= 2) {
			tabuleiro[i][j] = 'B';
			aux[i][j] = 'B';
		}
		for(j; j < 8 && i > 4; j+= 2) {
			tabuleiro[i][j] = 'P';
			aux[i][j] = 'P';
		}
	}
}

int movimentar(int jogador,int x1, int y1, int x2, int y2) {
	int k;
	int achou = 0, np = 0;
	if(x2 < 0 || x2 >= 8) return 0;
	if(y2 < 0 || y2 >= 8) return 0;
	if(tabuleiro[x2][y2] == '#' || tabuleiro[x2][y2] == 'B' || tabuleiro[x2][y2] == 'P') return 0;
	coord inicial;
	inicial.i = x1;
	inicial.j = y1;
	all_pos[np++] = inicial;

	for(k = 0;k < np; k++) {
		int i = all_pos[k].i;
		int j = all_pos[k].j;
		if(i < 0 || i >= 8) continue;
		if(j < 0 || j >= 8) continue;
		if(aux[i][j] == 'X') continue;
		if((i == x2 && j == y2) && jogador == 1) {
			tabuleiro[i][j] = 'P';
			tabuleiro[x1][y1] = ' ';
			return 1;
		} else if((i == x2 && j == y2) && jogador == 2) {
			tabuleiro[i][j] = 'B';
			tabuleiro[x1][y1] = ' ';
			return 1;
		}
		aux[i][j] = 'X';
		int w;
		for(w = 0; w < 2; w++) {
			coord mover;
		if(jogador == 1) {
			mover.i = i + dirP[0][w];
			mover.j = j + dirP[1][w];
		} else {
			mover.i = i + dirB[0][w];
			mover.j = j + dirB[1][w];
		}
		all_pos[np++] = mover;
		}
	}
}

int main() {
	gerar_tabuleiro();
	colocar_pecas();
	int i, j;
	int n = 3;
	int jogador = 1;
	int x1,y1,x2,y2;

	for(i = 0; i < 8; i++) {
			for(j = 0; j < 8; j++) {
				printf("%c", tabuleiro[i][j]);
			}
			printf("\n");
		}

	while(n--) {
		printf("Jogador %d:\n", jogador);
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		for(i = 0; i <8; i++) {
			for(j = 0; j < 8; j++) {
				aux[i][j] = tabuleiro[i][j];
			}
		}

		if(!movimentar(jogador, x1, y1, x2, y2)) printf("Posicao impossivel de ser acessada\n");

		for(i = 0; i < 8; i++) {
			for(j = 0; j < 8; j++) {
				printf("%c", tabuleiro[i][j]);
			}
			printf("\n");
		}
		if(n%2 == 1) jogador = 1;
		else jogador = 2;
	}
	return 0;
}
