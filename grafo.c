/*****************************************************************/
/*   Grafo direcionado | ESDA | L.EEC | 2021/22      */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "heap.h"


grafo *grafo_novo()
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    if(g == NULL)
    {
        return NULL;
    }

    g->tamanho = 0;
    g->nos = NULL;

    return g;
}

no_grafo *no_novo(char *estacao, char *distrito)
{
    if(estacao == NULL || distrito == NULL)
    {
        return NULL;
    }
    // aloca memória para estrutura no_grafo
    no_grafo *no = ( no_grafo* ) malloc(sizeof(no_grafo));
    if ( no == NULL )
    {
        return NULL;
    }

    //copia estacao
	no->estacao = (char*)malloc((strlen(estacao) + 1) * sizeof(char));
    if(no->estacao == NULL)
    {
        free(no);
        return NULL;
    }
    strcpy(no->estacao, estacao);

    //copia distrito
    strcpy(no->distrito, distrito);

    no->tamanho = 0;
    no->arestas = NULL;
    no->p_acumulado = 0;
    no->anterior = NULL;

   return no;
}


no_grafo *no_remove(grafo *g, char *estacao)
{
    if(g == NULL || estacao == NULL)
    {
        return NULL;
    }
    no_grafo *no = NULL;
	int i, no_existe = 0;

	for(i=0; i<g->tamanho; i++)
	{	
		if (strcmp(g->nos[i]->estacao, estacao) == 0)
		{
			no_existe++;
			break;
		}
	}

	if(no_existe != 0)
	{
		no = g->nos[i]; // copia o apontador do nó que se pretende remover
		if (i != (g->tamanho - 1))
			memmove(&g->nos[i], &g->nos[i+1], sizeof(no_grafo *) * (g->tamanho - 1 - i));

		g->nos = realloc(g->nos, (g->tamanho - 1) * sizeof(no_grafo *));
		g->tamanho--;

	}
	return no;
}

int aresta_apaga(aresta_grafo *aresta)
{
    if (aresta == NULL)
        return -1;    

    free(aresta->codigo);
    free(aresta->linha);
    free(aresta);
    return 0;
}

int no_apaga(no_grafo *no)
{
 	if(no == NULL)
	{
		return -1;
	}
    int a;
    for(int i=0; i<no->tamanho; i++)
	{
		a = aresta_apaga(no->arestas[i]);
        if( a == -1)
        {
            return -1;
        }
	}
    free(no->estacao);
    free(no->arestas);
	free(no);
	return 0;
}


int grafo_apaga(grafo *g)
{
    if( g == NULL)
    {
        return -1;
    }
	for(int i=0; i<g->tamanho; i++)
	{
		no_apaga(g->nos[i]);
	}
	free(g->nos);	
	free(g);
    return 0;
}


no_grafo *encontra_no(grafo *g, char *estacao);
int no_insere(grafo *g, no_grafo *no)
{
    if (!g || !no)
        return -1;

    // verifica se o nó já existe
    no_grafo *no_g = encontra_no(g, no->estacao);
    if (no_g)
        return 1;  // (?) perguntar se precisa atualizar o nó (?)

    
    g->nos = (no_grafo **)realloc(g->nos, (g->tamanho + 1) * sizeof(no_grafo *));
    // incrementa o tamanho do numero de nós e insere no vetor de apontadores de nós
    g->nos[g->tamanho] = no;
    g->tamanho++;

    return 0;  
}

// função auxiliar para a "cria_aresta" que retorna 1 se existir a aresta para destino ou 0 se a aresta não existir, -1 se der erro.
int existe_aresta(no_grafo *origem, no_grafo *destino, char *codigo)
{
    if (!origem || !destino)
        return -1;

    //pesquisa em todas as arestas se existe a aresta origem-destino:
    for (int i = 0; i < origem->tamanho; i++)
    {
        if ((origem->arestas[i]->destino == destino) && ((strcmp(origem->arestas[i]->codigo, codigo) == 0)))
            return 1;
    }
    return 0;
}

int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *linha, int distancia, int ano)
{
    if(!origem || !destino || !codigo || !linha )
        return -1;

    if( distancia < 0 )
         return -1;

    // verifica se a aresta existe
    if (existe_aresta(origem, destino, codigo) != 0)
        return 1;

    // cria a nova ligação
    aresta_grafo *ag = (aresta_grafo *)malloc(sizeof(aresta_grafo));
    if (!ag)
        return -1;

    // aloca espaço para o código
    ag->codigo = (char *)malloc((strlen(codigo) + 1) * sizeof(char));
    if (!ag->codigo)
    {
        free(ag);
        return -1;
    }
    strcpy(ag->codigo, codigo);

    // aloca espaço para o companhia
    ag->linha = (char *)malloc((strlen(linha) + 1) * sizeof(char));
    if (!ag->linha)
    {
        free(ag->codigo);
        free(ag);
        return -1;
    }
    strcpy(ag->linha, linha);
    
    ag->destino = destino;
    ag->distancia = distancia;
    ag->inspecao = ano;   

    // insere a nova aresta no vetor de arestas (no final)
    origem->arestas = (aresta_grafo **)realloc(origem->arestas, (origem->tamanho + 1) * sizeof(aresta_grafo *));
    origem->tamanho++;
    origem->arestas[origem->tamanho - 1] = ag;

    return 0;    
}

no_grafo **pesquisa_avancada(grafo *g, char *destino, int *n)
{
    if(g == NULL || destino == NULL || n == NULL)
        return NULL;

    no_grafo **trocos_achados = (no_grafo **)malloc(sizeof(no_grafo*));
    if(trocos_achados == NULL)
        return NULL;

    int pos=0;
    for(int i = 0; i<g->tamanho; i++)
    {
        for(int j=0; j<g->nos[i]->tamanho; j++)
        {
            if(strcmp(g->nos[i]->arestas[j]->destino->estacao, destino) == 0)
            {   
                trocos_achados = (no_grafo **)realloc(trocos_achados,sizeof(no_grafo*)*(pos+1));
                trocos_achados[pos] = g->nos[i];
                pos++;
                *n = pos;
            }
        }
    }
    return trocos_achados;
}

no_grafo **estacoes_distrito (grafo *g, char *distrito, int *n)
{
    if(g==NULL||distrito==NULL)
        return NULL;

    no_grafo **ngaux=NULL;
    (*n)=0;
    for(int i = 0; i<g->tamanho; i++){
        if(strcmp(g->nos[i]->distrito, distrito)==0){
            (*n)++;
            ngaux = (no_grafo**)realloc(ngaux, sizeof(no_grafo *)*(*n));
            ngaux[(*n)-1]=g->nos[i];      
        }
    }
    if((*n)==0)
        return NULL;
    return ngaux;
}

no_grafo **estacoes_linha (grafo *g, char *estacao, char *linha, int *n)
{
    if (!g || !estacao || !linha || !n)
        return NULL;
    
    int c=0;
    (*n)=0;
    no_grafo **ngaux=NULL;
    no_grafo *aux=NULL;
    no_grafo *ant=NULL;

    // pesquisa por estacao no vetor de nós
    for (int i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->estacao, estacao) == 0){
            (*n)++;
            ngaux = (no_grafo**)realloc(ngaux, sizeof(no_grafo *)*(*n));
            ngaux[(*n)-1]=g->nos[i];
            aux=g->nos[i];
            c=1;
            for(int j=0; j<aux->tamanho;j++){
                    if(strcmp(g->nos[i]->arestas[j]->linha,linha)==0){
                        (*n)++;
                        ngaux = (no_grafo**)realloc(ngaux, sizeof(no_grafo *)*(*n));
                        ant=aux;
                        aux=aux->arestas[j]->destino;
                        ngaux[(*n)-1]=aux;
                        break;
                    }
                }
            while(c==1){
                    c=0;
                    for(int j=0; j<aux->tamanho;j++){
                        if(strcmp(aux->arestas[j]->linha,linha)==0 && ant!=aux->arestas[j]->destino){
                            (*n)++;
                            ngaux = (no_grafo**)realloc(ngaux, sizeof(no_grafo *)*(*n));
                            ant=aux;
                            aux=aux->arestas[j]->destino;
                            ngaux[(*n)-1]=aux;
                            c=1;
                            break;
                        }
                    }
                }
            break;
        }
    }
    return ngaux;
}

int metros_linha (grafo *g, char *linha, char *origem)
{    
    if( !g || !linha || !origem) 
        return -1;  
    
    int n, d=0;
    no_grafo** ngaux=estacoes_linha(g, origem, linha, &n);
    for(int i=0; i<n-1; i++){
        for(int j=0; j<ngaux[i]->tamanho; j++){
            if(strcmp(ngaux[i]->arestas[j]->linha,linha)==0 && !strcmp(ngaux[i]->arestas[j]->destino->estacao, ngaux[i + 1]->estacao))
            {
                d += ngaux[i]->arestas[j]->distancia;
                //break;
            }
        }
    }
    free(ngaux);
    return d;
}


no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, int *n)
{
    if(g==NULL || origem==NULL || destino==NULL || n==NULL || encontra_no(g,destino) == NULL)
        return NULL;

    for(int i = 0;i<g->tamanho;i++){
       g->nos[i]->p_acumulado = __DBL_MAX__;
       g->nos[i]->anterior=NULL;
    }
    no_grafo *temp =encontra_no(g,origem);
    temp->p_acumulado=0;

    heap *h = heap_nova(g->tamanho);
    //insere origem na heap
    heap_insere(h,temp, NULL,0);

    no_grafo *min;

    while (h->tamanho>0){
        min = heap_remove(h);    // remove elemento com menor prioridade
        //percorre arestas:
        for(int i = 0;i<min->tamanho;i++){            
            aresta_grafo *troco = min->arestas[i];
            // comparar numero de trajetos
            if(troco->destino->p_acumulado >  min->p_acumulado + min->arestas[i]->distancia){
                troco->destino->p_acumulado = min->p_acumulado + min->arestas[i]->distancia;
                troco->destino->anterior = min;
                heap_insere(h,troco->destino,NULL,troco->destino->p_acumulado);
            }                
        }
        if(strcmp(min->estacao,destino)==0)
        {
            break;
        }       
    }
    int tam=0,k=0;
    no_grafo **aux = (no_grafo**)malloc((g->tamanho)*sizeof(no_grafo*));
    no_grafo **trajeto = (no_grafo**)malloc((g->tamanho)*sizeof(no_grafo*));
    temp=encontra_no(g,destino);
    while(temp!=NULL){
        aux[tam]=temp;
        tam++;
        temp=temp->anterior;
    }
    //inverter o array porque senão ele fica ao contrário
    for(int i = tam-1; i>=0; i--){
        trajeto[i]=aux[k];
        k++;
    }
    heap_apaga(h);
    free(aux);
    *n=tam;
    return trajeto;
}

no_grafo *encontra_no(grafo *g, char *estacao)
{
    if (!g || !estacao)
        return NULL;

    // pesquisa por estacao no vetor de nós
    for (int i = 0; i < g->tamanho; i++)
    {
        if (strcmp(g->nos[i]->estacao, estacao) == 0)
            return g->nos[i];
    }
    return NULL;
}


no_grafo *encontra_troco(grafo *g, char *codigo, int *aresta_pos)
{
    if(!g || !codigo  || !aresta_pos)
        return NULL;

    no_grafo *no = NULL;
    for(int i = 0; i<g->tamanho; i++)
    {
        for(int j=0; j<g->nos[i]->tamanho; j++)
        {
            if(strcmp(g->nos[i]->arestas[j]->codigo, codigo) == 0)
            {
                no = g->nos[i];
                *aresta_pos = j;
                return no;
            }
        }
    } 
    return NULL;    
}

grafo *grafo_importa(const char *nome_ficheiro)
{
    if (nome_ficheiro == NULL)
        return NULL;

    FILE *f = fopen(nome_ficheiro, "r");
    if (f == NULL)
        return NULL;

    grafo *g = grafo_novo();
    if (g == NULL)
    {
        fclose(f);
        return NULL;
    }
    char str[500] = {0}, codigo[15] = {0}, origem[50] = {0}, destino[50] = {0}, linha[40] = {0}, distritoorigem[40], distritodestino[40];
    int distancia = 0;
    int ano=0;
    int existearesta=0;
    

    char *token;
    no_grafo *no_origem, *no_destino;
    int ret;
    while (fgets(str, 500 * sizeof(char), f) != NULL)
    {
        str[strlen(str) - 1] = '\0';

        token = strtok(str, ";");
        if (!token)
            break;
        strcpy(codigo, token);
   
        token = strtok(NULL, ";");
        strcpy(linha, token);

        token = strtok(NULL, ";");
        strcpy(origem, token);

        token = strtok(NULL, ";");
        strcpy(distritoorigem, token);

        token = strtok(NULL, ";");
        strcpy(destino, token);

        token = strtok(NULL, ";");
        strcpy(distritodestino, token);
   
        token = strtok(NULL, ";");
        distancia = atoi(token);


        token = strtok(NULL, ";");
        ano = atoi(token);
      
      //  printf("%s - %s - %s -%s - %s -%s -%d -%d",codigo,linha,origem,distritoorigem,destino,distritodestino,distancia,ano);
        // procura no grafo um nó com o nome da origem
        no_origem = encontra_no(g, origem);
        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_origem)
        {
           no_origem = no_novo(origem,distritoorigem);
       

            if (no_insere(g, no_origem)==-1)
            {
                fclose(f);

                return NULL;
            }
        }
        // procura no grafo um nó com o nome do destino
        no_destino = encontra_no(g, destino);

        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_destino)
        {
           
           no_destino = no_novo(destino,distritodestino);
        

            if (no_insere(g, no_destino)==-1)
            {
                fclose(f);

                return NULL;
            }
        }


    
    existearesta=0;
    //pesquisa em todas as arestas se existe
    for (int i = 0; i < no_origem->tamanho; i++)
    {

        if ((no_origem->arestas[i]->destino == no_destino) && ((strcmp(no_origem->arestas[i]->codigo, codigo) == 0)))
            existearesta=1;
    }
        if (existearesta == 0)
        {
            
            ret = cria_aresta(no_origem, no_destino, codigo, linha,distancia,ano);

            if (ret == -1)
            {
                fclose(f);

                return NULL;
            }
             ret = cria_aresta(no_destino,no_origem, codigo, linha,distancia,ano);

            if (ret == -1)
            {
                fclose(f);

                return NULL;
            }
        }
    }

    fclose(f);
    return g;
}
