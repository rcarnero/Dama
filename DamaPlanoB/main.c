#include <stdio.h>
#include <stdlib.h>
char tab[8][8];
char *nomeJogador1, *nomeJogador2;
int dirP[2][2] = {{-1,-1},{-1,1}};
int dirB[2][2] = {{1,1},{1,-1}};
int dirD[4][2] = {{-1,-1},{1,-1},{1,1},{-1,1}};
int contador=0;
int countP = 0, countB = 0;
int pecaP = 12; pecaB = 12;
struct jogada{
    int x,y,x1,y1,x2,y2;
    char tipo;
};
struct jogada jogadas[1000];
int indexJogadas=0;
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
int sopro(int i, int j, int jogador,int dir,char tipo){
    if(i>7 || i<0 || j>7 || j<0){
        return 1;
    }
    if(tipo=='P'){

          if(jogador==1 && (tab[i][j]=='B'||tab[i][j]=='d')){
            if(tab[i+dirP[dir][0]][j+dirP[dir][1]]==' '){
                jogadas[indexJogadas].tipo = tipo;
                jogadas[indexJogadas].x2=i+dirP[dir][0];
                jogadas[indexJogadas].y2=j+dirP[dir][1];
                jogadas[indexJogadas].x1=i;
                jogadas[indexJogadas].y1=j;
                jogadas[indexJogadas].x=i-dirP[dir][0];
                jogadas[indexJogadas++].y=j-dirP[dir][1];
                contador++;
                return 1;
            }
          }
          int w;
          for(w=0;w<2;w++){
            if(tab[i+dirP[w][0]][j+dirP[w][1]]=='B'||tab[i+dirP[w][0]][j+dirP[w][1]]=='d'){
                sopro(i+dirP[w][0], j+dirP[w][1],1,w,tipo);
            }
          }

    }else if(tipo=='B'){
        if(jogador==2 && (tab[i][j]=='P'||tab[i][j]=='D')){
            if(tab[i+dirB[dir][0]][j+dirB[dir][0]]==' '){
                    jogadas[indexJogadas].tipo = tipo;
                jogadas[indexJogadas].x2=i+dirB[dir][0];
                jogadas[indexJogadas].y2=j+dirB[dir][1];
                jogadas[indexJogadas].x1=i;
                jogadas[indexJogadas].y1=j;
                jogadas[indexJogadas].x=i-dirB[dir][0];
                jogadas[indexJogadas++].y=j-dirB[dir][1];
                contador++;
                return 1;
            }
        }
        int w;
          for(w=0;w<2;w++){
            if(tab[i+dirB[w][0]][j+dirB[w][1]]=='P'||tab[i+dirB[w][0]][j+dirB[w][1]]=='D'){
                sopro(i+dirB[w][0], j+dirB[w][1],2,w,tipo);
            }
          }
    }else if(tipo=='D'){
         if(jogador==1 && (tab[i][j]=='B'||tab[i][j]=='d')){
            if(tab[i+dirD[dir][0]][j+dirD[dir][0]]==' '){
                    jogadas[indexJogadas].tipo = tipo;
                jogadas[indexJogadas].x2=i+dirD[dir][0];
                jogadas[indexJogadas].y2=j+dirD[dir][1];
                jogadas[indexJogadas].x1=i;
                jogadas[indexJogadas].y1=j;
                jogadas[indexJogadas].x=i-dirD[dir][0];
                jogadas[indexJogadas++].y=j-dirD[dir][1];
                contador++;
                return 1;
            }
        }
        int w;
          for(w=0;w<4;w++){
            if(tab[i+dirD[w][0]][j+dirD[w][1]]=='B'||tab[i+dirD[w][0]][j+dirD[w][1]]=='d'){
                sopro(i+dirD[w][0], j+dirD[w][1],1,w,tipo);
            }
          }
    }else{
        if(jogador==2 && (tab[i][j]=='P'||tab[i][j]=='D')){
            if(tab[i+dirD[dir][0]][j+dirD[dir][0]]==' '){
                    jogadas[indexJogadas].tipo = tipo;
                jogadas[indexJogadas].x2=i+dirD[dir][0];
                jogadas[indexJogadas].y2=j+dirD[dir][1];
                jogadas[indexJogadas].x1=i;
                jogadas[indexJogadas].y1=j;
                jogadas[indexJogadas].x=i-dirD[dir][0];
                jogadas[indexJogadas++].y=j-dirD[dir][1];
                contador++;
                return 1;
            }
        }
        int w;
          for(w=0;w<4;w++){
            if(tab[i+dirD[w][0]][j+dirD[w][1]]=='P'||tab[i+dirD[w][0]][j+dirD[w][1]]=='D'){
                sopro(i+dirD[w][0], j+dirD[w][1],2,w,tipo);
            }
          }
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
                    //tab[i][j]='B';
                }else if(i>4){
                    //tab[i][j]='P';
                }
            }
        tab[6][1]='P';
        tab[5][0]='B';
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
                            countP++;
                            pecaB--;
                            if(x1==0){
                                tab[x1][y1]='D';
                            } else {
                                tab[x1][y1]='P';
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
                if(tab[x+dirD[w][0]][y+dirD[w][1]]=='B'||tab[x+dirD[w][0]][y+dirD[w][1]]=='d'){
                    if(tab[x+dirD[w][0]+dirD[w][0]][y+dirD[w][1]+dirD[w][1]]==' '){
                        if(x+dirD[w][0]+dirD[w][0]==x1 && y+dirD[w][1]+dirD[w][1]==y1){
                            tab[x][y]=' ';
                            tab[x+dirD[w][0]][y+dirD[w][1]]=' ';
                            tab[x1][y1]='D';
                            countP++;
                            pecaB
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
                            countB++;
                            pecaP--;
                            if(x1==7){
                                tab[x1][y1]='d';
                            } else {
                                tab[x1][y1]='B';
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
                            countB++;
                            pecaP--;
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
void chamarSopro(int turno){
    indexJogadas=0;
    int i,j;
    if(turno==1){
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(tab[i][j]=='D'||tab[i][j]=='P'){
                    sopro(i,j,1,0,tab[i][j]);
                }
            }
        }
    }else{
        for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                if(tab[i][j]=='B'||tab[i][j]=='d'){
                    sopro(i,j,2,0,tab[i][j]);
                }
            }
        }
    }
}
void jogar(){
    int x,y,x1,y1;
    int turno = 2;
    system("cls");
    iniciarTab();
    colocarPecas();
    printarTab();
    int i,j;
    int nextTurno = 0;
    //chamarSopro(1);
    //printf(" ");
    while(1){
            chamarSopro(turno);
            while(indexJogadas>0){
                if(turno==1){
                    printf("%s tem %d jogadas obrigatorias\n",nomeJogador1,indexJogadas);
                }else{
                    printf("%s tem %d jogadas obrigatorias\n",nomeJogador2,indexJogadas);
                }

                int w;
                printf("Escolha uma jogada: \n");
                for(w=0;w<indexJogadas;w++){
                    printf("%d- Sua peca: %d %d Destino: %d %d\n",w,jogadas[w].x,jogadas[w].y,jogadas[w].x2,jogadas[w].y2);
                }
                int escolha=-1;
                scanf("%d",&escolha);
                while(escolha<0 || escolha>=indexJogadas){
                    scanf("%d",&escolha);
                }
                tab[jogadas[escolha].x][jogadas[escolha].y]=' ';
                tab[jogadas[escolha].x1][jogadas[escolha].y1]=' ';
                tab[jogadas[escolha].x2][jogadas[escolha].y2]=jogadas[escolha].tipo;
                if(jogadas[escolha].tipo == 'P' || jogadas[escolha].tipo == 'D') {
                    countP++;
                    pecaB--;
                } else {
                    countB++;
                    pecaP--;
                }
                if(jogadas[escolha].x2==0&&jogadas[escolha].tipo=='P'){
                    tab[jogadas[escolha].x2][jogadas[escolha].y2]='D';
                }else if(jogadas[escolha].x2==7&&jogadas[escolha].tipo=='B'){
                    tab[jogadas[escolha].x2][jogadas[escolha].y2]='d';
                }
                indexJogadas=0;
                system("cls");
                printarTab();
                indexJogadas=0;

                sopro(jogadas[escolha].x2,jogadas[escolha].y2,turno,0,jogadas[escolha].tipo);
                if(indexJogadas==0){
                    if(turno==1){
                       turno=2;
                    }else{
                       turno=1;
                    }
                    nextTurno=1;
                }
            }
            if(nextTurno){
                nextTurno=0;
                continue;
            }
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
                printf("\nDigite coordenadas1 validas\n");
                scanf("%d %d",&x,&y);
                scanf("%d %d",&x1,&y1);
            }
            while(!(movimento(x,y,x1,y1,turno))){
              printf("Jogada invalida");
              printf("\nDigite coordenadas2 validas\n");
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
        while(pecaP && pecaB){
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