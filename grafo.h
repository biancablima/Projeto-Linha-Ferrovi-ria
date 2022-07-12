/*****************************************************************/
/*   Grafo direcionado | ESDA | L.EEC | 2021/22        */
/*****************************************************************/

#ifndef _GRAFO_H_
#define _GRAFO_H_
#include <time.h>

/* Estrutura ligação ponderada.*/
struct no_grafos;



typedef struct
{
  
    char *codigo;              /* código de troço */
    char *linha;              /* nome da linha ferroviária */
    int distancia;            /* distancia deste troço em metros*/
    int inspecao;             /* ano da última inspeção */
    struct no_grafos *destino;/* apontador para o nó de destino*/

} aresta_grafo;

/* no_grafo e' uma estrutura que tem o nome da estação e
   um vetor de apontadores para os destinatários */
typedef struct no_grafos
{
    char *estacao;               /* string com nome da estação */
    int tamanho;                /* número de posições válidas de ‘arestas’ */
    aresta_grafo **arestas;     /* vetor de apontadores para ‘aresta_grafo’  */
    char distrito[30];          /* string com o nome do distrito*/
     double p_acumulado;        /* peso acumulado,a ser usado no Dijkstra */
     struct no_grafos *anterior;/* nó anterior,a ser usado no Dijkstra */
   
} no_grafo;

/* grafo e' implementado atraves de vetor apontadores de nos e as respetivas ligacoes  */

typedef struct
{
    int tamanho;    /* número de posições válidas de ‘nos’ (estações) */
    no_grafo **nos; /* vetor de apontadores para ‘no_grafo’  */
    
} grafo;

/* Cria grafo de tamanho 0
*  Retorna um apontador para o grafo criado
*/
grafo *grafo_novo();

/*
*  cria um novo no com os valores dos parametros
*  parametro: estacao- vetor de carateres contendo o nome da estacao
*  parametro: distrito - vetor de carateres contendo o nome do distrito
*  retorno: retorna o apontador para o nó criado ou NULL se ocorrer algum erro ou se algum dos parametros nao estiver dentro da gama de valores valida
*/
no_grafo *no_novo(char *estacao, char *distrito);

/* Remove e retorna apontador para o nó do grafo ‘g’, referente a estacao. Retorne NULL em caso de insucesso.
*  parametro g - apontador para o grafo em que se pretende remover o nó
*  parametro estacao - apontador para a estacao cujo o nó se pretende remover
*  retorna apontador para o nó do grafo referente a estacao sem apagá-lo ou NULL se ocorrer algum erro ou se algum dos parametros nao estiver dentro da gama de valores valida
*/
no_grafo *no_remove(grafo *g, char *estacao);

/* Apaga o no e liberta toda a memória associada
*  parametro no - apontador para o no a apagar
*  retorna 0 se for apagado com sucesso e retorna -1 em caso de insucesso
*/
int no_apaga(no_grafo *no);

/* Apaga a aresta e liberta toda a memória associada
*  parametro aresta - apontador para a aresta a apagar
*  retorna 0 se for apagado com sucesso e retorna -1 em caso de insucesso
*/
int aresta_apaga(aresta_grafo *aresta);

/* Apaga grafo e liberta memoria
*  parametro g - apontador para o grafo que se pretende apagar
*/
int grafo_apaga(grafo *g);

/* Insere um no´ no grafo
*  parametro g - apontador para o grafo em que se pretende inserir o no´
*  parametro no - apontador para o no que se pretende inserir
*  retorno 0 se for bem sucedido e -1 em caso de erro e 1 se for repetido
*/
int no_insere(grafo *g, no_grafo *no);

/* cria uma aresta (troco) entre o no 'origem' e o no 'destino'
* parametro origem - apontador para o nó de origem da aresta
* parametro destino - apontador para o nó de destino da aresta
* parametro codigo - vetor de carateres contendo o nome do codigo
* parametro linha - vetor de carateres contendo o nome do linha
* parametro distancia - inteiro com a distancia do troço
* parametro preco - float com o preço do troço
* parametro codigo - inteiro com o ano da última inspeção
* retorno 0 se for bem sucedido, -1 em caso de erro e 1 se for repetido
*/
int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *linha, int distancia, int ano); 

/* Cria e retorna um grafo direccionado, tipo vetor de adjacência, apartir de um ficheiro.
*  parametro nome_ficheiro - apontador para o ficheiro
*  retorno de um apontador para o novo grafo, em caso de erro retorna NULL
*/
grafo *grafo_importa(const char *nome_ficheiro);

/* encontra no´no grafo que tem um determinado estacao
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro estacao - apontador para uma string que se pretende procurar nas estações
*  retorna um apontador para um nó do grafo, em caso de erro retorna NULL
*/
no_grafo *encontra_no(grafo *g, char *estacao);

/* Pesquisa no grafo ‘g’ o troço com determinado ‘codigo’, retornando por referência através do argumento ‘aresta_pos’ a posição da respetiva aresta nos vetores de arestas do nó retornado. 
* Visto que o troço existe duas vezes, como consequência existem dois nós que têm esse troço. 
* Devem escolher o nó que tiver o nome da estação mais baixo alfabeticamente. 
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro codigo - apontador para o codigo do troço que se pretende procurar no grafo
*  retorna um apontador para um nó do grafo que tem essa viagem, em caso de erro retorna NULL
*  obs: retorna a posicao do troço no vetor de troços por regerência atravês do inteiro aresta_pos
*/
no_grafo *encontra_troco(grafo *g, char *codigo, int *aresta_pos);

/*Retorna um vetor de apontadores para todos os nós do grafo ‘g’ que tenham troços directos a chegar ao nó com o nome ‘destino’.
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro destino - apontador para o destino(estacao) que se pretende procurar no grafo
* Retorna NULL se não forem encontrados voos ou em caso de erro. O tamanho do vetor deve ser retornado por referência através do argumento ‘n’.
*/
no_grafo **pesquisa_avancada(grafo *g, char *destino, int *n);

/* Retorna um vetor de apontadores para todos os nós do grafo ‘g’ que façam parte do distrito  ‘ distrito’. 
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro distrito - string com o nome do distrito
*  Retorna NULL se não forem encontrados estações ou em caso de erro. O tamanho do vetor deve ser retornado por referência através do argumento ‘n’.
*/
no_grafo **estacoes_distrito (grafo *g, char *distrito, int *n);

/* Retorna um vetor de apontadores para todos os nós do grafo ‘g’ que façam parte da mesma ‘linha’.
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro estacao - string com o nome do estacao
*  parametro linha - string com o nome da linha
*  Retorna NULL se não forem encontrados troços ou em caso de erro. O tamanho do vetor deve ser retornado por referência através do argumento ‘n’.
*  Obs: A ‘estacao‘ é a primeira dessa linha.
*/
no_grafo **estacoes_linha (grafo *g, char *estacao, char *linha, int *n);

/* Retorna os metros de uma determinada ‘linha’ que começa no nó ‘origem’ .
*  parametro g - apontador para o grafo em que se pretende procurar
*  parametro origem - string com o nome da estacao de origem
*  parametro linha - string com o nome da linha
*  Retorna -1 em caso de insucesso.
*/
int metros_linha (grafo *g, char *linha, char *origem);

/*Calcula o trajeto mais rápido entre as estacões de ‘origem’ e ‘destino'.
* Retorna um vetor de apontadores para todos os nós do grafo ‘g’ desse trajeto.
* Retorna NULL se não for encontrada nenhuma combinação de voos válida ou em caso de erro.
* O tamanho do vetor deve ser retornado por referência através do argumento ‘n’.
*/
no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino,  int *n);



#endif
