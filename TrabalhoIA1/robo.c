
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