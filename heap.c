/*****************************************************************/
/*   Fila de prioridade / min-heap | ESDA | L.EEC | 2021/22     */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

int menor_que(elemento * e1, elemento * e2);

heap* heap_nova(int capacidade)
{
    heap * h = (heap *) malloc(sizeof(heap));

    if (!h)
        return NULL;

    h->tamanho = 0;
    h->capacidade = capacidade;
    h->elementos = (elemento **) calloc(capacidade+1, sizeof(elemento *));


    if (!h->elementos) {
        free(h);
        return NULL;
    }
    for (int i=0;i<=capacidade;i++)
h->elementos[i]=NULL;
    return h;
}

void heap_apaga(heap *h)
{
    int i;

    if(!h)
        return;

    /* apaga todos os elementos e respetivas strings */
    for(i=RAIZ; i<=h->tamanho; i++)
    {
    //    free(h->elementos[i]->no);
        free(h->elementos[i]);
        h->elementos[i]=NULL;
    }

    free(h->elementos);
    free(h);
}


elemento * elemento_novo(double prioridade, no_grafo * no, aresta_grafo *aresta)
{
	if(!no && !aresta)
	return NULL;   

	elemento * elem = (elemento *) malloc(sizeof(elemento));

    if (!elem)
        return NULL;


    elem->no=no;
    elem->aresta=aresta;
    elem->prioridade = prioridade;

    return elem;
}


int heap_insere(heap * h,  no_grafo* no,aresta_grafo *aresta, double prioridade)
{
    elemento * aux=NULL, * elem;
    int i=0;

    /* se heap esta' cheia, nao insere elemento */
    if (h->tamanho >= h->capacidade)
        return 0;

    elem = elemento_novo(prioridade,no, aresta);
    if (!elem)
        return 0;

    /* coloca elemento no fim da heap */
    h->tamanho++;
    i = h->tamanho;
    h->elementos[i] = elem;

     /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
    while (i != RAIZ && menor_que(h->elementos[i], h->elementos[PAI(i)]))
    {
        aux = h->elementos[PAI(i)];
        h->elementos[PAI(i)] = h->elementos[i];
        h->elementos[i] = aux;
        i = PAI(i);
    }
    return 1;
}

no_grafo * heap_remove(heap * h)
{
    int i, filho_maior;
    elemento * aux;
    no_grafo * ret;

    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->tamanho <= 0)
        return NULL;

    ret = h->elementos[RAIZ]->no;
    free(h->elementos[RAIZ]);

    /* coloca ultimo elemento da heap na raiz */
    h->elementos[RAIZ] = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = NULL;
    h->tamanho--;

     i = RAIZ;

    /* enquanto nao chegar 'a base da heap */
    while(FILHO_ESQ(i) <= h->tamanho)
    {
        filho_maior = FILHO_ESQ(i);

        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) <= h->tamanho && menor_que(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)]))
            filho_maior = FILHO_DIR(i);

        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (menor_que(h->elementos[filho_maior], h->elementos[i]))
        {
            aux = h->elementos[filho_maior];
            h->elementos[filho_maior] = h->elementos[i];
            h->elementos[i] = aux;
            i = filho_maior;
        }
        else
            break;
    }

    return ret;
}


aresta_grafo * heap_remove_aresta(heap * h)
{
    int i, filho_maior;
    elemento * aux;
   aresta_grafo * ret;

    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->tamanho <= 0)
        return NULL;

    ret = h->elementos[RAIZ]->aresta;
    free(h->elementos[RAIZ]);

    /* coloca ultimo elemento da heap na raiz */
    h->elementos[RAIZ] = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = NULL;
    h->tamanho--;

     i = RAIZ;

    /* enquanto nao chegar 'a base da heap */
    while(FILHO_ESQ(i) <= h->tamanho)
    {
        filho_maior = FILHO_ESQ(i);

        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) <= h->tamanho && menor_que(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)]))
            filho_maior = FILHO_DIR(i);

        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (menor_que(h->elementos[filho_maior], h->elementos[i]))
        {
            aux = h->elementos[filho_maior];
            h->elementos[filho_maior] = h->elementos[i];
            h->elementos[i] = aux;
            i = filho_maior;
        }
        else
            break;
    }

    return ret;
}


int menor_que(elemento * e1, elemento * e2)
{
    if (e1 == NULL || e2 == NULL)
    {
        return 0;
    }

    return e1->prioridade < e2->prioridade;
}

heap *heap_carrega(grafo *g, int capacidade)
{
    if(!g || capacidade <= 0)
        return NULL;

    heap* h=heap_nova(capacidade);
    if(h == NULL)
        return NULL;

    int k=1, pos_h=1;    
    for(int i=0; i<g->tamanho; i++) // i percorre os nós
    {
        for(int j=0; j<g->nos[i]->tamanho; j++)  // j percorre as arestas de cada nó
        {
            for(int a=1; a<(pos_h + 1); a++)  // percorre a heap em busca de repetidos
            {
                if(a == pos_h)   // no primeiro elemento e última iteração inserir nova aresta, se essa não existe
                {
                    k = heap_insere(h,  NULL, g->nos[i]->arestas[j], g->nos[i]->arestas[j]->inspecao);                    
                    if(k != 1)
                    {   
                        heap_apaga(h);
                        return NULL;
                    }                  
                    pos_h++;
                    break;
                }
                if(strcmp(g->nos[i]->arestas[j]->codigo, h->elementos[a]->aresta->codigo) == 0)
                {
                    break;
                }              
            }
        }
    }    
    return h;
}

aresta_grafo **inspecao_trocos (heap *h, int dias, int *n)
{
    if(!h || dias<=0)
        return NULL;

    int c=0, i=1;
    (*n)=0;

    aresta_grafo **ag=NULL;

    while(c<dias){ //enquanto se tiver mais dias para inspecao
        i=1;
        c += h->elementos[i]->aresta->distancia/10000; //dias que demora a inspecao
        if((h->elementos[i]->aresta->distancia%10000)!=0){
            c=c+1;
        }
        if(c>dias){ //se nao houver dias suficientes para a inspecao retornar o apontador com o que se tem
            break;
        }
        else if(c==dias){ //se houver mas ocupar todos atualizar apontador, n, heap e retornar
            ag = (aresta_grafo**)realloc(ag, sizeof(aresta_grafo *)*((*n)+1));
            ag[(*n)]=heap_remove_aresta(h);
            (*n)++;
            break;
        }       

        //se ainda tiver mais dias, atualizar apontador, n e heap
        ag = (aresta_grafo**)realloc(ag, sizeof(aresta_grafo *)*((*n)+1));
        ag[(*n)]=heap_remove_aresta(h);
        (*n)++;
    }
    if(ag==NULL)

        return NULL;

    return ag;
}
