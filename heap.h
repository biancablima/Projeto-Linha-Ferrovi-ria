/*****************************************************************/
/*   Fila de prioridade / min-heap | ESDA | L.EEC | 2021/22    */
/*****************************************************************/

#ifndef HEAP_H
#define HEAP_H
#include "grafo.h"

typedef struct {
    double prioridade;
    no_grafo *no;
    aresta_grafo *aresta;
} elemento;

typedef struct {
    /* numero de elementos no vetor */
    int tamanho;
    /* tamanho maximo do vetor */
    int capacidade;

    /* vetor de apontadores para elementos */
    elemento ** elementos;
} heap;

/* cria nova heap */
heap* heap_nova(int tamanho_maximo);

/* apaga heap */
void heap_apaga(heap *h);

/* insere elemento na heap com uma determinada prioridade */
int heap_insere(heap *h,  no_grafo *no, aresta_grafo *aresta, double prioridade);

/* remove elemento na raiz da heap retornando o no_agrafo */
no_grafo * heap_remove(heap * h);

/* remove elemento na raiz da heap retornando a aresta_agrafo */
aresta_grafo * heap_remove_aresta(heap * h);


/* Cria e preenche uma heap, com uma dada ‘capacidade’ e o conteúdo do grafo ‘g’. 
*  Cada elemento da heap deve serr composto pelos troços(aresta), o campo estação deve ficar a NULL e a prioridade é o ano da inspeção.
*  parametro g - apontador para o grafo
*  parametro capacidade - inteiro com o numero maximo da capacidade da geap
*   Retorna o apontador para a heap criada se bem sucedido ou NULL em caso de impossibilidade por falta de capacidade ou outro erro.
*/
heap *heap_carrega(grafo *g, int capacidade);

/*Retorna um vetor de apontadores de troços (arestas_grafo). Esses troços devem estar pela ordem do mais antigo ao mais recente. Esses troços devem ser retirados da heap.
*  parametro h - apontador para a heap se pretende usar
*  parametro dias - inteiro com o numero de dias a inspecionar
* Retorna NULL se não forem encontrados troços ou em caso de erro. O tamanho do vetor deve ser retornado por referência através do argumento ‘n’.
* Obs: por dia consegue-se inspecionar 10Km. Quando um troço tem por exemplo 32 Km, consegue-se inspecionar em teoria 3.2 dias, arredonda-se sempre para cima logo fica 4 dias.
* Obs: se tivermos 4 dias para inspecionar e o troço mais antigo tiver 55 Km não se inspeciona nada. Ou seja, se o próximo troço a ser inspecionado não conseguir ser inspecionado completamente, não se faz mais nada.  
*/
aresta_grafo **inspecao_trocos (heap *h, int dias, int *n);

#endif /* HEAP_H */
