#include <stdio.h>
#include <stdlib.h>
#define MAX 10


typedef struct aluno
{
    int ra;
    int prox;
} TipoAluno;

typedef struct reservas
{
    TipoAluno listaReservas[MAX];
    int primeiro;
    int ultimo;
    int tam;
    int posLivre[MAX];
    int contAno[8];
} TipoListaEE;




void inicializaLista(TipoListaEE *listaAux)
{
    int i;

    for (i = 0; i < MAX; i++)
    {
        listaAux->listaReservas[i].ra = 140001;
        listaAux->listaReservas[i].prox = -1;
        listaAux->posLivre[i] = 1;
    }

    for (i = 0; i < 8; i++)
        listaAux->contAno[i] = 0;

    listaAux->primeiro = -1;
    listaAux->ultimo = -1;
    listaAux->tam = 0;
}

int procuraPosLivre(TipoListaEE *listaAux)
{
    int i;

    for (i = 0; i < MAX; i++)
        if (listaAux->posLivre[i] == 1)
            return i;

    return -1;

}

int buscaAntecessor(TipoListaEE * listaAux, int ra)
{
    int ant, prox;
    ant = -1; 
    prox = listaAux->primeiro;
    while (prox != -1 && ra > listaAux->listaReservas[prox].ra)
    {

            ant = prox;
            prox = listaAux->listaReservas[ant].prox;

    }

    return ant;
}

void insereElemento(TipoListaEE *listaAux, int ra, int index, int antecessor)
{
    int proximo;

    listaAux->listaReservas[index].ra = ra;

        if (antecessor == -1)
        {
            listaAux->listaReservas[index].prox = listaAux->primeiro;
            listaAux->primeiro = index;            
        }
        else if (antecessor == listaAux->ultimo)
        {   
            listaAux->listaReservas[listaAux->ultimo].prox = index;
            listaAux->ultimo = index;
        }
        else
        {
        proximo = listaAux->listaReservas[antecessor].prox;
        listaAux->listaReservas[antecessor].prox = index;
        listaAux->listaReservas[index].prox = proximo;
        }


    listaAux->tam++;
    listaAux->posLivre[index] = 0;
}

void contaAnoRA(TipoListaEE *listaAux, int ra)
{ 

    switch (ra / 1000)
    {
        case 66: listaAux->contAno[0]++;
        break;

        case 76: listaAux->contAno[1]++;
        break;

        case 86: listaAux->contAno[2]++;
        break;

        case 96: listaAux->contAno[3]++;
        break;

        case 106: listaAux->contAno[4]++;
        break;

        case 116: listaAux->contAno[5]++;
        break;

        case 126: listaAux->contAno[6]++;
        break;

        case 136: listaAux->contAno[7]++;
        break;
    }

}

void imprimeLista(TipoListaEE *listaAux)
{
    int ant, prox;

    ant = listaAux->primeiro; 
    prox = listaAux->primeiro;
    while (prox != -1)
    {
            printf("%d ", listaAux->listaReservas[prox].ra);        
            ant = prox;
            prox = listaAux->listaReservas[ant].prox;      
    }
    printf("\n");
}


int procuraRA(TipoListaEE *listaAux, int ra)
{
    int posAtual;

    posAtual = listaAux->primeiro;
    while (posAtual != -1)
    {
        if (ra == listaAux->listaReservas[posAtual].ra)        
            return posAtual;
        else
        {
            posAtual = listaAux->listaReservas[posAtual].prox;
        }
    }
    return -1;
}

void removeElemento(TipoListaEE *listaAux, int posExcluir)
{
    int posAtual, novoAtual;
    
    novoAtual = listaAux->primeiro;    
    posAtual = listaAux->primeiro;
    
    while (posAtual != posExcluir)
    {
        novoAtual = posAtual;
        posAtual = listaAux->listaReservas[novoAtual].prox;
    }
    
    if(listaAux->primeiro == posExcluir)
        listaAux->primeiro = listaAux->listaReservas[posExcluir].prox;
    else if(listaAux->ultimo == posExcluir)
        listaAux->ultimo = novoAtual;
    else
        listaAux->listaReservas[novoAtual].prox = listaAux->listaReservas[posExcluir].prox;
        
    listaAux->listaReservas[posExcluir].prox = -1;
    listaAux->listaReservas[posExcluir].ra = 140001;
    listaAux->posLivre[posExcluir] = 1;
    listaAux->tam--;

}





int main(void)
{
    TipoListaEE lista;
    int numOperacoes, operacao, numRA, i, posVetor, ant, posRemove, ano = 2011;

    inicializaLista(&lista); 
    scanf("%d", &numOperacoes);

    if (numOperacoes >= 1 && numOperacoes <= 100)
    {

        for (i = 0; i < numOperacoes; i++)
        {
            scanf("%d %d", &operacao, &numRA);
            if (numRA >= 66000 && numRA <= 140000)
            {
                switch (operacao)
                {
                    case 1: if((posVetor = procuraPosLivre(&lista)) != -1)
                            {
                                ant = buscaAntecessor(&lista, numRA);
                                insereElemento(&lista, numRA, posVetor, ant);
                                contaAnoRA(&lista, numRA);                                
                            }else printf("lista cheia\n");
                            imprimeLista(&lista);
                    break;
        
                    case 2: if((posRemove = procuraRA(&lista, numRA)) != -1)
                            {
                                removeElemento(&lista, posRemove);
                            }else printf("nao existe\n");
                            imprimeLista(&lista);
                    break;
                    
                    default: exit(1);
                }
            } else exit(1);
        }

    }else exit(1);

    for(i = 0; i < 8; i++)
    {
        printf("%d: %d\n", ano, lista.contAno[i]);
        ano++;
    }

    return 0;
}
