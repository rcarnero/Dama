#include <stdio.h>
#include <stdlib.h>
char tab[8][8];
char *nomeJogador1, *nomeJogador2;
int dirP[2][2] = {{-1,-1},{-1,1}};
int dirB[2][2] = {{1,1},{1,-1}};
int dirD[4][2] = {{-1,-1},{1,-1},{1,1},{-1,1}};
int contador=0;
int countP = 0, countB = 0;
int pecaP = 12, pecaB = 12;
struct jogada{
    int x,y,x1,y1,x2,y2;
    char tipo;
};
struct jogada jogadas[1000];
int indexJogadas=0;

void iniciarTab(){
    int i,j;
    //Inicializando o tabuleiro com marcas brancas e espa�os vazios
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
    printf(" ");//Printando o tabuleiro e coordenadas
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
//Insere num arquivo txt o vencedor da partida
void inserir(int pontuacao, char *nome) {
    freopen("Ranking.out", "a+", stdout);
    printf("%s - %d\n", nome, pontuacao);
}
void inserir_vencedor() {//Calcula quem foi o vencedor, pega sua pontuacao e nome
    int pontuacao;
    char *nome;
    if(!pecaB) {pontuacao = countP - countB; nome = nomeJogador1;}
    else if(!pecaP) {pontuacao = countB - countP; nome = nomeJogador2;}
    else return;

    inserir(pontuacao, nome);
}
//Le o arquivo txt e imprime no console os nomes e as pontuacoes contidas
void mostrar_vencedor() {
    system("cls");
    char *nome = (char*)malloc(sizeof(char));
    FILE *file;
    int i = 0;
    int vezes = 4;
    file = freopen("Ranking.out", "r", stdin);
    if(file == NULL) perror("Error opening de file");
    else {
        //Executa enquanto houver coisa para ler
        while(gets(nome)) {
            printf("%s\n", nome);
        }
    }
}

int sopro(int i, int j, int jogador,int dir,char tipo){
    if(i>7 || i<0 || j>7 || j<0){//verificando se i e j n�o passam do limite do tabuleiro
        return 1;
    }
    if(tipo=='P'){//tipo do jogador P ou B
        //se o tipo do jogador for 1 e a casa atual for do tipo 2=Boud ent�o eu verifico se a proxima casa na mesma dire��o � vazia se for isso � uma jogada obrigatoria
          if(jogador==1 && (tab[i][j]=='B'||tab[i][j]=='d')){
            if(tab[i+dirP[dir][0]][j+dirP[dir][1]]==' '){//verificando proxima casa na mesma dire��o
                //guardando a jogada obrigatoria
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
            return 1;
          }
          int w;
          for(w=0;w<2;w++){//Casa do tipo P eu verifico os arredores e se for B ou d eu entro e entro no caso acima pela recurs�o
            if(tab[i+dirP[w][0]][j+dirP[w][1]]=='B'||tab[i+dirP[w][0]][j+dirP[w][1]]=='d'){
                sopro(i+dirP[w][0], j+dirP[w][1],1,w,tipo);
            }
          }
    //Os proximo else if e else s�o iguais ao anterior s� muda o tipo de pe�a B D ou d
    }else if(tipo=='B'){
        if(jogador==2 && (tab[i][j]=='P'||tab[i][j]=='D')){
            if(tab[i+dirB[dir][0]][j+dirB[dir][1]]==' '){
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
            return 1;
        }
        int w;
          for(w=0;w<2;w++){
            if(tab[i+dirB[w][0]][j+dirB[w][1]]=='P'||tab[i+dirB[w][0]][j+dirB[w][1]]=='D'){
                sopro(i+dirB[w][0], j+dirB[w][1],2,w,tipo);
            }
          }
    }else if(tipo=='D'){
         if(jogador==1 && (tab[i][j]=='B'||tab[i][j]=='d')){
            if(tab[i+dirD[dir][0]][j+dirD[dir][1]]==' '){
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
            if(tab[i+dirD[dir][0]][j+dirD[dir][1]]==' '){
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
            return 1;
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
    //colocando as pe�as B ou P no tabuleiro
    for(i=0;i<8;i++){
            for(j=0;j<8;j++){
                    //Se for diferente de marcas brancas eu boto B ou P depedendo das linhas
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
    //Verificando se as posi��es n�o saem do tabuleiro
    if(x<0||x>=8||y<0||y>=8||x1<0||x1>=8||y1<0||y1>=8){
       printf("Jogada invalida\n");
       return 0;
    }
    //verificando se a distancia de uma posi��o pra outra n�o � maior do que 2
    if(!((x-x1)*(x-x1)==(y-y1)*(y-y1)&&((x-x1)<=2||(x-x1)>=-2))){
        printf("Jogada invalida\n");
        return 0;
    }
    //verificando se a posi��o destino n�o � uma casa ocupada
    if(tab[x1][y1]!=' '){
        printf("Jogada invalida\n");
        return 0;
    }
    return 1;
}
int movimento(int x, int y,int x1, int y1, int jogador){
    int w;
    //Verificando qual jogador esta jogando
    if(jogador==1){
        if(tab[x][y]=='P'){//Caso pe�a P
            for(w=0;w<2;w++){//Verifico todas as jogadas validas pra essa pe�a e vejo se alguma � igual ao destino x1 e y1
                if(tab[x+dirP[w][0]][y+dirP[w][1]]=='B'){//caso as casas vizinhas sejam uma pe�a oposta eu verifico se tem uam espa� vazio dps se tiver e essa for a posi��o desejada a pe�a vai ser comida
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
            }//Mesma coisa do caso anterior so que vai ter 4 op��es de jogada pq � uma dama
        }else if(tab[x][y]=='D'){
            for(w=0;w<4;w++){
                if(tab[x+dirD[w][0]][y+dirD[w][1]]=='B'||tab[x+dirD[w][0]][y+dirD[w][1]]=='d'){
                    if(tab[x+dirD[w][0]+dirD[w][0]][y+dirD[w][1]+dirD[w][1]]==' '){
                        if(x+dirD[w][0]+dirD[w][0]==x1 && y+dirD[w][1]+dirD[w][1]==y1){
                            tab[x][y]=' ';
                            tab[x+dirD[w][0]][y+dirD[w][1]]=' ';
                            tab[x1][y1]='D';
                            countP++;
                            pecaB--;
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

    }else{//Mesma coisa do primeiro caso
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
            }//mesma coisa do caso da D
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
    //varrendo todos o tabuleiro e verificando se naquela pe�a existe jogada obrigatoria
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
    //turno inicial � com as pe�as p
    int turno = 1;
    //limpando a tela
    system("cls");
    //inicializando o tabuleiro e colocando pe�as
    iniciarTab();
    colocarPecas();
    printarTab();
    int i,j;
    int nextTurno = 0;
    //chamarSopro(1);
    //printf(" ");
    //o jogo s� acaba quando acabar as pe�as de algum jogador
    while(pecaP && pecaB){
            //verificando se tem sopro
            chamarSopro(turno);
            //Mostra quantas e onde possui jogadas obrigatorias
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
                //Movimenta a pela do local original pro escolhido
                tab[jogadas[escolha].x][jogadas[escolha].y]=' ';
                tab[jogadas[escolha].x1][jogadas[escolha].y1]=' ';
                tab[jogadas[escolha].x2][jogadas[escolha].y2]=jogadas[escolha].tipo;
                //Come uma pe�a adversaria e incrementa os pontos do jogador
                if(jogadas[escolha].tipo == 'P' || jogadas[escolha].tipo == 'D') {
                    countP++;
                    pecaB--;
                } else {
                    countB++;
                    pecaP--;
                }
                //Forma dama
                if(jogadas[escolha].x2==0&&jogadas[escolha].tipo=='P'){
                    tab[jogadas[escolha].x2][jogadas[escolha].y2]='D';
                }else if(jogadas[escolha].x2==7&&jogadas[escolha].tipo=='B'){
                    tab[jogadas[escolha].x2][jogadas[escolha].y2]='d';
                }
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
                    break;
                }
            }
            if(nextTurno){
                nextTurno=0;
                continue;
            }
            printf("%d\n", pecaP);
            printf("%d\n", pecaB);
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
        inserir_vencedor();
}
int main()
{
    //Alocando espa� pro nomes dos jogadores
    nomeJogador1 = (char*)malloc(50*sizeof(char));
    nomeJogador2 = (char*)malloc(50*sizeof(char));
    char menu;
    //menu
    while(1){
        system("cls");
        printf("Jogo de damas\n");
        printf("1-Jogar\n");
        printf("2-Instrucoes\n");
        printf("3-Ranking\n");
        printf("4-Sair\n");
        scanf(" %c",&menu);
        //op��es do menu que iram se repetir at� ser alguma valida
        if(menu=='1'){
            //pegando nome dos jogadores
            fflush(stdin);
            printf("Digite o nome do primeiro jogador\n");
            gets(nomeJogador1);
            fflush(stdin);
            printf("Digite o nome do segundo jogador\n");
            gets(nomeJogador2);
            //entrando na fun��o jogar

            jogar();
        }else if(menu=='2'){//Como jogar
            system("cls");
            printf("Escolha a sua peca, de enter e em seguida o local para onde ela ira se mover.\nEx: 5 0 enter 4 1\n");
            break;
        }else if(menu=='3'){//Imprime uma lista de todos os vencedores
            mostrar_vencedor();
            break;
        }else if(menu=='4'){//Sai do programa
            break;
        }
    }
    return 0;
}
