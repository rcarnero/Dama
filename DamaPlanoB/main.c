#include <stdio.h>
#include <stdlib.h>
char tab[8][8];
char *nomeJogador1, *nomeJogador2;
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
                   tab[i][j]='B';
                }else if(i>4){
                    tab[i][j]='P';
                }
            }

    }
}
int verificarJogadas(int x, int y,int x1, int y1){
    if(x<0||x>=8||y<0||y>=8||x1<0||x1>=8||y1<0||y1>=8){
       printf("Jogada invalida\n");
       return 0;
    }
    if(!((x-x1)*(x-x1)==(y-y1)*(y-y1)&&((x-x1)<=2||(x-x1)>=-2))){
        printf("Jogada invalida\n");
        return 0;
    }
    if(tab[x1][y1]!=' '){
        printf("Jogada invalida\n");
        return 0;
    }
    return 1;
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
void jogar(){
    int x,y,x1,y1;
    int turno = 1;
    system("cls");
    iniciarTab();
    colocarPecas();
    printarTab();
    while(1){
            if(turno==1){
                printf("%s, Selecione a peca P pelas coordenadas: ",nomeJogador1);
                scanf("%d %d",&x,&y);
                printf("Mova a peca p selecionada: ",nomeJogador1);
                scanf("%d %d",&x1,&y1);
            }else{
                printf("%s, Selecione a peca B pelas coordenadas: ",nomeJogador2);
                scanf("%d %d",&x,&y);
                printf("Mova a peca B selecionada: ");
                scanf("%d %d",&x1,&y1);
            }


            while(!verificarJogadas(x,y,x1,y1)){
                printf("\nDigite coordenadas validas\n");
                scanf("%d %d",&x,&y);
                scanf("%d %d",&x1,&y1);
            }
            while(!(movimento(x,y,x1,y1,turno))){
              printf("Jogada invalida");
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
        }
}
int main()
{
    nomeJogador1 = (char*)malloc(50*sizeof(char));
    nomeJogador2 = (char*)malloc(50*sizeof(char));
    char menu;
    while(1){
        printf("Jogo de damas\n");
        printf("1-Jogar\n");
        printf("2-Instruções\n");
        printf("3-Ranking\n");
        printf("4-Sair\n");
        while(1){
            scanf("%c",&menu);
            if(menu=='1'){
                fflush(stdin);
                printf("Digite o nome do primeiro jogador\n");
                gets(nomeJogador1);
                fflush(stdin);
                printf("Digite o nome do segundo jogador\n");
                gets(nomeJogador2);
                jogar();
            }else if(menu=='2'){

            }else if(menu=='3'){

            }else if(menu=='4'){

            }
        }
    }
    return 0;
}
