#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int key;
	struct no *next;
} no;

no *head, *aux;

char tabuleiro[8][8];
int dirP[2][2] = {{-1,-1},{-1,1}};
int dirB[2][2] = {{1,1},{1,-1}};
int dirD[4][2] = {{1, 1},{1,-1},{-1,-1},{-1,1}};
int x,y;
int pecaP = 12, pecaB = 12;
int countP = 0;
int countB = 0;
int tamanho = 0;

no *procurar(int key) {
    no *temp;
    for(temp = head; temp; temp = temp->next) {
        if(temp->next->key > key) return temp;
    }
    return NULL;
}


void inserir(int key) {
    no *node = (no*)procurar(key);
    if(!node) node = aux;
    no *novo = (no*)malloc(sizeof(no));
    novo->key = key;
    novo->next = node->next;
    node->next = novo;
    if(!aux->next) aux = novo;

}

void remover() {
    if(!head) return;
    no *temp = head->next;
    head->next = temp->next;
    tamanho--;
    free(temp);

}

void ranking(int countP, int countB) {
	int pontuacao;
	if(!pecaB) pontuacao = countP - countB;
	else if(!pecaP) pontuacao = countB - countP;
	else return;

	inserir(pontuacao);
	if(tamanho > 10) remover();
}




void imprimir_mapa() {
	int i, j, count = 1;
	printf(" ");
    for(i = 0; i < 8; i++) printf("%d", count++);
    printf("\n");
    count = 1;
    for(i = 0; i < 8; i++) {
    	printf("%d", count++);
			for(j = 0; j < 8; j++) {
				printf("%c", tabuleiro[i][j]);
			}
			printf("\n");
	}
}


void gerar_tabuleiro() {
	int i, j;
	for(i = 0; i < 8; i++) {
		if(i%2 == 0) j = 0;
		else j = 1;

		for(j; j < 8; j+=2) {
			tabuleiro[i][j] = 177;
		}
	}
}

void colocar_pecas() {
	int i, j;
	//coloca as peças pulando uma casa para que todas fiquem em casas pretas
	for(i = 0; i < 8; i++) {
		//se a linha for par ou 0 a primeira casa é branca
		if(i%2 == 0) j = 1;
		//senão a primeira casa é preta
		else j = 0;
		//Coloca as peças nas casas pretas
		for(j; j < 8 && i < 3; j+= 2) {
			tabuleiro[i][j] = 'B';
		}
		for(j; j < 8 && i > 4; j+= 2) {
			tabuleiro[i][j] = 'P';
		}
	}
}

int movimentar(int jogador,int i, int j, int x2, int y2) {
	
	if(x2 < 0 || x2 == 8) return 0;
	if(y2 < 0 || y2 == 8) return 0;
	//se o destino for uma casa branca ou em cima de alguma peça, retorna 0
	if(tabuleiro[x2][y2] == 177 || tabuleiro[x2][y2] == 'B' || tabuleiro[x2][y2] == 'P') return 0;
	
		if(i < 0 || i == 8) return 0;
		if(j < 0 || j == 8) return 0;

		//se chegou ao destino e estiver na vez do jogador um, movimenta a peça se ela for do jogador 1
		//x e y são as coordenadas iniciais e, x2 e y2 são as coordenadas do destino
		if(i == x2 && j == y2 && (tabuleiro[x][y] == 'P' || tabuleiro[x][y] == 'D') && jogador == 1) {
			if(x2 == 0) {
				tabuleiro[x2][y2] = 'D';
				tabuleiro[x][y] = ' ';
			} else if(tabuleiro[x][y] == 'D') {
				tabuleiro[x2][y2] = 'D';
				tabuleiro[x][y] = ' ';
			} else {
				tabuleiro[x2][y2] = 'P';
				tabuleiro[x][y] = ' ';
			}
			return 1;
		//se chegou ao destino e estiver na vez do jogador um, movimenta a peça se ela for do jogador 2
		} else if(i == x2 && j == y2 && (tabuleiro[x][y] == 'B' || tabuleiro[x][y] == 'd') && jogador == 2) {
			if(x2 == 7) {
				tabuleiro[x2][y2] = 'd';
				tabuleiro[x][y] = ' ';
			} else if(tabuleiro[x][y] == 'd') {
				tabuleiro[x2][y2] = 'd';
				tabuleiro[x][y] = ' ';
			} else {
				tabuleiro[x2][y2] = 'B';
				tabuleiro[x][y] = ' ';
			}
			return 1;
		}
		
		int w;
		//Se a vez for do jogador 1 faz uma busca em profundidade para encontrar o destino
		if(jogador == 1) {
			//Se a peça escolhida for uma dama, ela se movimenta em 4 direções
			if(tabuleiro[x][y] == 'D') {
				for(w = 0; w < 4; w++) {
					//Se houver possibilidade de comer uma peça inimiga, come
					if(movimentar(1, i+dirD[w][0], j+dirD[w][1], x2, y2) && tabuleiro[i][j] == 'B') {
						countP++;
						pecaB--;
						tabuleiro[i][j] = ' ';
					}
				}
			//se for uma peça normal, ela se movimenta apenas em 2 direções	
			} else {
				for(w = 0; w < 2; w++) {
					//Se houver possibilidade de comer uma peça inimiga, come
					if(movimentar(1, i+dirP[w][0], j+dirP[w][1], x2, y2) && tabuleiro[i][j] == 'B') {
						countP++;
						pecaB--;
						tabuleiro[i][j] = ' ';
					}
				}
			}
		//Se a vez for do jogador 2 faz uma busca em profundidade para encontrar o destino
		} else {
			//Se a peça escolhida for uma dama, ela se movimenta em 4 direções
			if(tabuleiro[x][y] == 'd') {
				for(w = 0; w < 4; w++) {
					//Se houver possibilidade de comer uma peça inimiga, come
					if(movimentar(2, i+dirD[w][0], j+dirD[w][1], x2, y2) && tabuleiro[i][j] == 'P') {
						countB++;
						pecaP--;
						tabuleiro[i][j] = ' ';
					}
				}
			//se for uma peça normal, ela se movimenta apenas em 2 direções	
			} else {
				for(w = 0; w < 2; w++) {
					//Se houver possibilidade de comer uma peça inimiga, come
					if(movimentar(2, i+dirB[w][0], j+dirB[w][1], x2, y2) && tabuleiro[i][j] == 'P') {
						countB++;
						pecaP--;
						tabuleiro[i][j] = ' ';
					}
				}
			}
		}

}

int main() {
	
	gerar_tabuleiro();
	
	colocar_pecas();
	
	int i, j, x2, y2;
	int n = 14;
	int jogador = 1;
	
	do {

		imprimir_mapa();

		printf("Jogador %d:\n", jogador);
		scanf("%d%d%d%d", &x, &y, &x2, &y2);


		movimentar(jogador, x, y, x2, y2);
		 	//printf("Posicao impossivel de ser acessada\n");

			
			if(n%2 == 1) jogador = 2;
			else jogador = 1;

			n++;
	} while(!pecaP || !pecaB);
	return 0;
}
