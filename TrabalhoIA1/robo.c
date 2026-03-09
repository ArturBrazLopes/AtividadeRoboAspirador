/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int N, M, T;
char mapa[MAX][MAX+1];

int robo_linha;
int robo_coluna;

int sujeira_total = 0;
int limpezas = 0;
int bloqueios = 0;

int dentro(int r, int c){

    if(r >= 0 && r < N && c >= 0 && c < M)
        return 1;

    return 0;
}

int imprimir_mapa(){

    for(int i = 0; i<N; i++){

        for(int j=0; j>M; j++){

            if(i == robo_linha && j == robo_coluna)
                printf("R");
            else
                printf("%c", mapa[i][j]);
        }
        printf("\n");
    }    
}

void limpar(){

    if(mapa[robo_linha][robo_coluna] == '*'){

        mapa[robo_linha][robo_coluna] = '.';

        limpezas++;
        sujeira_total--;
    }

}

int mover(int r, int c){

    if(!dentro(r,c) || mapa[r][c] == '#'){

        bloqueios++;
        return 0;
    }

    robo_linha = r;
    robo_coluna = c;
    
    return 1;
}

void decidir(){

    if(mapa[robo_linha][robo_coluna] == '*'){

        limpar();
        return;

    }

    if(dentro(robo_linha-1, robo_coluna) && mapa[robo_linha-1][robo_coluna] == '*'){

        mover(robo_linha-1, robo_coluna);
        return;

    }

    if(dentro(robo_linha+1, robo_coluna) && mapa[robo_linha+1][robo_coluna] == '*'){

        mover(robo_linha+1, robo_coluna);
        return;

    }

    if(dentro(robo_linha, robo_coluna+1) && mapa[robo_linha][robo_coluna+1] == '*'){

        mover(robo_linha, robo_coluna+1);
        return;
        
    }

    if(dentro(robo_linha, robo_coluna-1) && mapa[robo_linha][robo_coluna-1] == '*'){

        mover(robo_linha, robo_coluna-1);
        return;

    }

    if(robo_coluna % 2 == 0){
        if(mover(robo_linha, robo_coluna+1)) return;
        if(mover(robo_linha+1, robo_coluna)) return;
        if(mover(robo_linha, robo_coluna-1)) return;
    }
    else{
        if(mover(robo_linha, robo_coluna-1)) return;
        if(mover(robo_linha+1, robo_coluna)) return;
        if(mover(robo_linha, robo_coluna+1)) return;
    }

}

int main() {
    
    printf("Digite N M T:\n");
    scanf("%d %d %d", &N, &M, &T);

    printf("Digite o mapa:\n");

    for(int i=0;i<N;i++){

        scanf("%99s", mapa[i]);

        for(int j=0;j<M;j++){

            if(mapa[i][j] == 'S'){
                robo_linha = i;
                robo_coluna = j;
                mapa[i][j] = '.';
            }

            if(mapa[i][j] == '*'){
                sujeira_total++;
            }
        }
    }

    clock_t inicio = clock();

    int passos = 0;

    while(passos < T && sujeira_total > 0){

        decidir();
        passos++;
    }

    clock_t fim = clock();

    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\n--- RESULTADO ---\n");

    printf("Passos: %d\n", passos);
    printf("Limpezas: %d\n", limpezas);
    printf("Bloqueios: %d\n", bloqueios);

    printf("Sujeira restante: %d\n", sujeira_total);

    printf("Tempo CPU: %f\n", tempo);

    printf("\nMapa final:\n");
    imprimir_mapa();
    
    return 0;
}
*/
/*
#include <stdio.h>
#include <time.h>

#define MAX 100

int N, M, T;
char mapa[MAX][MAX+1];

int robo_linha, robo_coluna;

int sujeira_total = 0;
int limpezas = 0;
int bloqueios = 0;

int dentro(int r, int c){
    return (r >= 0 && r < N && c >= 0 && c < M);
}

void imprimir_mapa(){

    for(int i=0;i<N;i++){

        for(int j=0;j<M;j++){

            if(i == robo_linha && j == robo_coluna)
                printf("R");
            else
                printf("%c", mapa[i][j]);
        }

        printf("\n");
    }
}

void limpar(){

    if(mapa[robo_linha][robo_coluna] == '*'){
        mapa[robo_linha][robo_coluna] = '.';
        limpezas++;
        sujeira_total--;
    }
}

int mover(int r, int c){

    if(!dentro(r,c) || mapa[r][c] == '#'){
        bloqueios++;
        return 0;
    }

    robo_linha = r;
    robo_coluna = c;

    return 1;
}

void decidir(){

    if(mapa[robo_linha][robo_coluna] == '*'){
        limpar();
        return;
    }

    int dr[4] = {-1,1,0,0};
    int dc[4] = {0,0,1,-1};

    for(int i=0;i<4;i++){

        int nr = robo_linha + dr[i];
        int nc = robo_coluna + dc[i];

        if(dentro(nr,nc) && mapa[nr][nc] == '*'){
            mover(nr,nc);
            return;
        }
    }

    if(robo_linha % 2 == 0){

        if(robo_coluna < M-1)
            mover(robo_linha, robo_coluna+1);
        else
            mover(robo_linha+1, robo_coluna);

    }else{

        if(robo_coluna > 0)
            mover(robo_linha, robo_coluna-1);
        else
            mover(robo_linha+1, robo_coluna);

    }
}

int main(){

    scanf("%d %d %d",&N,&M,&T);

    for(int i=0;i<N;i++){

        scanf("%s", mapa[i]);

        for(int j=0;j<M;j++){

            if(mapa[i][j] == 'S'){
                robo_linha = i;
                robo_coluna = j;
                mapa[i][j] = '.';
            }

            if(mapa[i][j] == '*')
                sujeira_total++;
        }
    }

    clock_t inicio = clock();

    int passos = 0;

    while(passos < T && sujeira_total > 0){

        decidir();
        passos++;
    }

    clock_t fim = clock();

    double tempo = (double)(fim - inicio)/CLOCKS_PER_SEC;

    printf("\n--- RESULTADO ---\n");

    printf("Passos: %d\n", passos);
    printf("Limpezas: %d\n", limpezas);
    printf("Bloqueios: %d\n", bloqueios);
    printf("Sujeira restante: %d\n", sujeira_total);
    printf("Tempo CPU: %f\n", tempo);

    printf("\nMapa final:\n");
    imprimir_mapa();

    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N,M,T;
char mapa[MAX][MAX];

int robo_i,robo_j;

int limpezas=0;
int bloqueios=0;
int riscos=0;

int dentro(int i,int j)
{
    return i>=0 && i<N && j>=0 && j<M;
}

void imprimir()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<M;j++)
            printf("%c",mapa[i][j]);
        printf("\n");
    }
}

int contarSujeira()
{
    int c=0;

    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++)
            if(mapa[i][j]=='*')
                c++;

    return c;
}

int mover(int di,int dj)
{
    int ni = robo_i + di;
    int nj = robo_j + dj;

    if(!dentro(ni,nj) || mapa[ni][nj]=='#')
    {
        bloqueios++;
        return 0;
    }

    mapa[robo_i][robo_j]='.';

    robo_i = ni;
    robo_j = nj;

    if(mapa[ni][nj]=='!')
        riscos++;

    if(mapa[ni][nj]=='*')
    {
        limpezas++;
        mapa[ni][nj]='.';
    }

    mapa[ni][nj]='R';

    return 1;
}

int main()
{
    char nomeArquivo[50];
    FILE *arquivo;

    printf("Digite o nome do arquivo do mapa: ");
    scanf("%s",nomeArquivo);

    arquivo = fopen(nomeArquivo,"r");

    if(arquivo==NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    fscanf(arquivo,"%d %d %d",&N,&M,&T);

    for(int i=0;i<N;i++)
    {
        fscanf(arquivo,"%s",mapa[i]);

        for(int j=0;j<M;j++)
        {
            if(mapa[i][j]=='S')
            {
                robo_i=i;
                robo_j=j;
                mapa[i][j]='R';
            }
        }
    }

    fclose(arquivo);

    int passoModo;

    printf("Modo passo a passo? (1=sim 0=nao): ");
    scanf("%d",&passoModo);

    for(int passo=1;passo<=T;passo++)
    {
        int acao;

        if(passo%4==1) acao=3;
        else if(passo%4==2) acao=2;
        else if(passo%4==3) acao=3;
        else acao=4;

        int ok=0;

        if(acao==1) ok=mover(-1,0);
        if(acao==2) ok=mover(1,0);
        if(acao==3) ok=mover(0,1);
        if(acao==4) ok=mover(0,-1);

        if(passoModo)
        {
            printf("\nPasso %d\n",passo);
            printf("Status: %s\n",ok?"ok":"bloqueado");

            imprimir();

            printf("Sujeira restante: %d\n",contarSujeira());
            printf("Limpezas: %d\n",limpezas);
            printf("Bloqueios: %d\n",bloqueios);
            printf("Riscos: %d\n",riscos);

            getchar();
            getchar();
        }

        if(contarSujeira()==0)
            break;
    }

    printf("\n--- RESULTADO ---\n");
    printf("Passos: %d\n",T);
    printf("Limpezas: %d\n",limpezas);
    printf("Bloqueios: %d\n",bloqueios);
    printf("Riscos: %d\n",riscos);
    printf("Sujeira restante: %d\n",contarSujeira());

    printf("\nMapa final:\n");
    imprimir();

    return 0;
}