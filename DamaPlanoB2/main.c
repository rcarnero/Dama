#include <stdio.h>
#include <stdlib.h>
char tab[8][8];

int dirP[2][2] = {{-1,-1},{-1,1}};
int dirB[2][2] = {{1,1},{1,-1}};
int dirD[4][2] = {{-1,-1},{1,-1},{1,1},{-1,1}};

void iniciarTab(){
    int i,j;
    for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(i%2==0 && j%2==0){
                    tab[i][j]=-79;
                }else if(i%2!=0 && j%2!=0){
                    tab[i][j]=-79;
                }else{
                    tab[i][j]=' ';
                }
            }

    }
}
void printarTab(){
    int i, j, count = 0;
	printf(" ");
    for(i = 0; i < 8; i++) printf("%d", count++);
    printf("\n");
    count = 0;
    for(i = 0; i < 8; i++) {
    	printf("%d", count++);
			for(j = 0; j < 8; j++) {
				printf("%c", tab[i][j]);
			}
			printf("\n");
		}
}
void colocarPecas(){
    int i,j;
    for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(tab[i][j]==-79){
                    continue;
                }
                if(i<3){
                 //  tab[i][j]='B';
                }else if(i>4){
                   // tab[i][j]='P';
                }
            }

    }
    tab[4][1] = 'B';
    tab[3][2] = 'P';

}
int verificarJogadas(int x, int y,int x1, int y1){
    if(x<0||x>=8||y<0||y>=8||x1<0||x1>=8||y1<0||y1>=8){
       printf("Jogada invalida");
       return 0;
    }
    if(!((x-x1)*(x-x1)==(y-y1)*(y-y1)&&((x-x1)<=2||(x-x1)>=-2))){
        printf("Jogada invalida");
        return 0;
    }
    if(tab[x1][y1]!=' '){
        printf("Jogada invalida");
        return 0;
    }
    return 1;
}
int passou = 0, vez = 0;
int movimentar(int i, int j, int jogador) {
    int w;
     for(w = 0; w < 4 && !vez; w++) {
        movimentar(i+dirD[w][0], j+dirD[w][1], jogador);
        if(w == 3) vez = 1;
    }

    if(jogador == 1) {
        if(passou && tab[i][j] == ' ') {
            return 1;
        }
        if(tab[i][j] == 'B' && !passou) {
            passou = 1;
            for(w = 0; w < 2; w++) {
                if(movimentar(i+dirP[w][0], j+dirD[w][1], jogador)) {
                    printf("Possivel comer nas coordenadas %d %d\n", i+dirP[w][0], j+dirD[w][1]);
                    break;    
                }
            }
        }
        passou = 0;
    } else {
        if(passou && tab[i][j] == ' ') {
            return 1;
        }
        if(tab[i][j] == 'P' && !passou) {
            passou = 1;
            for(w = 0; w < 2; w++) {
                if(movimentar(i+dirB[w][0], j+dirD[w][1], jogador)) {
                    printf("Possivel comer nas coordenadas %d %d\n", i+dirP[w][0], j+dirD[w][1]);
                    break;    
                }
            }
        }
        passou = 0;
    }
}

void sopro(int jogador) {
    int i, j, w;
    if(jogador == 1) {
        for(i = 0; i < 8; i++) {
            for(j =0; j < 8; j++) {
                if(tab[i][j] == 'P') {
                    movimentar(i, j, jogador);
                }
            }
        }
    } else {
        for(i = 0; i < 8; i++) {
            for(j =0; j < 8; j++) {
                if(tab[i][j] == 'B') {
                    movimentar(i, j, jogador);
                }
            }
        }
    }
}
int movimento(int x, int y,int x1, int y1, int jogador){
    int w;
    if(jogador==1){
        if(tab[x][y]=='P'){
            for(w=0;w<2;w++){
                if(tab[x+dirP[w][0]][y+dirP[w][1]]=='B'){
                    if(tab[x+dirP[w][0]+dirP[w][0]][y+dirP[w][1]+dirP[w][1]]==' '){
                        if(x+dirP[w][0]+dirP[w][0]==x1 && y+dirP[w][1]+dirP[w][1]==y1){
                            tab[x][y]=' ';
                            tab[x+dirP[w][0]][y+dirP[w][1]]=' ';
                            tab[x1][y1]='P';
                            if(x1==0){
                                tab[x1][y1]='D';
                            }
                            return 1;
                        }
                    }
                }else if(x+dirP[w][0]==x1 && y+dirP[w][1]==y1){
                    tab[x][y]=' ';
                    tab[x1][y1]='P';
                    if(x1==0){
                        tab[x1][y1]='D';
                    }
                    return 1;
                }
            }
        }else if(tab[x][y]=='D'){
            for(w=0;w<4;w++){
                if(tab[x+dirD[w][0]][y+dirD[w][1]]=='B'||tab[x+dirB[w][0]][y+dirB[w][1]]=='d'){
                    if(tab[x+dirD[w][0]+dirD[w][0]][y+dirD[w][1]+dirD[w][1]]==' '){
                        if(x+dirD[w][0]+dirD[w][0]==x1 && y+dirD[w][1]+dirD[w][1]==y1){
                            tab[x][y]=' ';
                            tab[x+dirD[w][0]][y+dirD[w][1]]=' ';
                            tab[x1][y1]='D';
                            return 1;
                        }
                    }
                }else if(x+dirD[w][0]==x1 && y+dirD[w][1]==y1){
                    tab[x][y]=' ';
                    tab[x1][y1]='D';
                    return 1;
                }
            }
        }

    }else{
        if(tab[x][y]=='B'){
            for(w=0;w<2;w++){
                if(tab[x+dirB[w][0]][y+dirB[w][1]]=='P'||tab[x+dirB[w][0]][y+dirB[w][1]]=='D'){
                    if(tab[x+dirB[w][0]+dirB[w][0]][y+dirB[w][1]+dirB[w][1]]==' '){
                        if(x+dirB[w][0]+dirB[w][0]==x1 && y+dirB[w][1]+dirB[w][1]==y1){
                            tab[x][y]=' ';
                            tab[x+dirB[w][0]][y+dirB[w][1]]=' ';
                            tab[x1][y1]='B';
                            if(x1==7){
                                tab[x1][y1]='d';
                            }
                            return 1;
                        }
                    }
                }else if(x+dirB[w][0]==x1 && y+dirB[w][1]==y1 && tab[x1][y1]==' '){
                    tab[x][y]=' ';
                    tab[x1][y1]='B';
                    if(x1==7){
                        tab[x1][y1]='d';
                    }
                    return 1;
                }
            }
        }else if(tab[x][y]=='d'){
            for(w=0;w<4;w++){
                if(tab[x+dirD[w][0]][y+dirD[w][1]]=='P'){
                    if(tab[x+dirD[w][0]+dirD[w][0]][y+dirD[w][1]+dirD[w][1]]==' '){
                        if(x+dirD[w][0]+dirD[w][0]==x1 && y+dirD[w][1]+dirD[w][1]==y1){
                            tab[x][y]=' ';
                            tab[x+dirD[w][0]][y+dirD[w][1]]=' ';
                            tab[x1][y1]='d';
                            return 1;
                        }
                    }
                }else if(x+dirD[w][0]==x1 && y+dirD[w][1]==y1){
                    tab[x][y]=' ';
                    tab[x1][y1]='d';
                    return 1;
                }
            }
        }
    }
    return 0;
}
int main()
{
    int turno = 1;
    iniciarTab();
    colocarPecas();
    printarTab();
    int x,y,x1,y1;
    int n=5;
    sopro(1);
   /* while(1){
        printf("Jogador %d:\n", turno);
        scanf("%d %d",&x,&y);
        scanf("%d %d",&x1,&y1);
        if(x == 0 && y == 0) break;
        while(!verificarJogadas(x,y,x1,y1)){
            printf("\nDigite coordenadas validas\n");
            scanf("%d %d",&x,&y);
            scanf("%d %d",&x1,&y1);
        }
        while(!(movimento(x,y,x1,y1,turno))){
          printf("Jogad invalida");
          printf("\nDigite coordenadas validas\n");
          scanf("%d %d",&x,&y);
          scanf("%d %d",&x1,&y1);
        }
        system("cls");
        printarTab();
        if(turno==1){
            turno=2;
        }else{
            turno=1;
        }
    }*/
    return 0;
}
