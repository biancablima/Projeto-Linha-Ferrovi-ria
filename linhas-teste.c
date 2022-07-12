/*****************************************************************/
/*         Trabalho pratico 2 | ESDA | L.EEC | 2021/22          */
/*****************************************************************/
/*                  NAO ALTERAR ESTE FICHEIRO                    */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "heap.h"


/* VERIFICACOES IMPLEMENTADAS */
int verifica_grafo_novo(grafo **g)
{
    int er = 0;

    *g = grafo_novo();
    if (!(*g))
    {
        printf("...verifica_grafo_novo: grafo novo e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_grafo_novo: grafo novo nao e' NULL (ok)\n");

    if ((*g)->tamanho != 0)
    {
        printf("...verifica_grafo_novo: Tamanho do grafo novo (= %d) 'e diferente do esperado (= 0) (ERRO)\n", (*g)->tamanho);
        er++;
    }
    else
        printf("...verifica_grafo_novo: Tamanho do grafo novo coincide com o esperado (= 0) (ok)\n");

    if ((*g)->nos != NULL)
    {
        printf("...verifica_grafo_novo: O apontador para o vetor de apontadores de nos (= %p) 'e diferente do esperado (= NULL) (ERRO)\n", (*g)->nos);
        er++;
    }
    else
        printf("...verifica_grafo_novo: O apontador para o vetor de apontadores de nos e´ o esperado (= NULL) (ok)\n");    

    return er;
}

int verifica_no_novo(no_grafo **no, char *estacao,  char *distrito)
{
    int er = 0;

    *no = no_novo(estacao,distrito);
    if (!(*no))
    {
        printf("...verifica_no_novo: no novo e' NULL (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_no_novo: no novo nao e' NULL (ok)\n");

    if (strcmp((*no)->estacao, estacao) != 0)
    {
        printf("...verifica_no_novo: Campo estacao do novo no (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*no)->estacao, estacao);
        er++;
    }
    else
        printf("...verifica_no_novo: Campo estacao coincide com o esperado (= %s) (ok)\n", estacao);

    if (strcmp((*no)->distrito, distrito) != 0)
    {
        printf("...verifica_no_novo: Campo distrito do novo no (= %s) e' diferente do esperado (= %s) (ERRO)\n", (*no)->distrito, distrito);
        er++;
    }
    else
        printf("...verifica_no_novo: Campo distrito do novo no coincide com o esperado (= %s) (ok)\n", distrito);

    if ((*no)->tamanho != 0)
    {
        printf("...verifica_no_novo: Campo tamanho do novo no (= %d) e' diferente do esperado (= =) (ERRO)\n", (*no)->tamanho);
        er++;
    }
    else
        printf("...verifica_no_novo: Campo tamanho do novo no coincide com o esperado (= %d) (ok)\n", (*no)->tamanho);

   
    if ((*no)->arestas != NULL)
    {
        printf("...verifica_no_novo: O apontador para o vetor de apontadores de arestas (= %p) 'e diferente do esperado (= NULL) (ERRO)\n", (*no)->arestas);
        er++;
    }
    else
        printf("...verifica_no_novo: O apontador para o vetor de apontadores de arestas e´ o esperado (= NULL) (ok)\n");    

    no_apaga(*no);
    return er;
}

int verifica_no_insere(grafo **g)
{
    int er = 0, erro;
 
  
    no_grafo *no1 = no_novo("vermoin", "Maia");
    no_grafo *no2 = no_novo("campanhã", "Porto");
   
    erro = no_insere(*g, no1);

    if (erro == -1)
    {
        printf("...verifica_no_insere: nao conseguiu inserir (ERRO)\n");
        no_apaga(no1);
        return 1;
    }
    else if (erro == 1)
       no_apaga(no1);

    erro = no_insere(*g, no2);
    if (erro != 0)
       no_apaga(no2);

  

    if (strcmp((*g)->nos[0]->estacao, "vermoin") != 0 || strcmp((*g)->nos[1]->estacao, "campanhã") != 0)
    {
        printf("...verifica_no_insere: nao inseriu correctamente o 1º e 2º nos, nao estao na posicao correta (ERRO)\n");
        er++;
        return er;
    }
    else
        printf("...verifica_no_insere: inseriu o 1º e 2º nos nas posicoes corretas (ok)\n");

    if ((*g)->tamanho != 2)
    {
        printf("...verifica_no_insere: campo tamanho do grafo (= %d) 'e diferente do esperado (= 2) (ERRO)\n", (*g)->tamanho);
        er++;
    }
    else
        printf("...verifica_no_insere:  campo tamanho do grafo coincide com o esperado (= 2) (ok)\n");



    return er;
}

int verifica_cria_aresta(grafo **g)
{
    int er = 0, erro;
   
   if(!(*g))
     {
        printf("...verifica_cria_aresta: nao conseguiu criar a aresta (ERRO)\n");
        return 1;
    }
   
    erro = cria_aresta((*g)->nos[0], (*g)->nos[1],"T01","Linha do Norte",100,2000);
    
    if (erro == -1)
    {
        printf("...verifica_cria_aresta: nao conseguiu criar a aresta (ERRO)\n");
        return 1;
    }
    else if (erro == 1)
    {
        printf("...verifica_cria_aresta: deu aresta já existente  (ERRO)\n");
        er++;
        return er;

    }

    if (strcmp((*g)->nos[0]->arestas[0]->codigo, "T01") != 0)
    {
        printf("...verifica_cria_aresta: codigo da aresta no no' 0 na posicao 0 (=%s) e´ diferente do esperado (='T01') (ERRO)\n",(*g)->nos[0]->arestas[0]->codigo);
        er++;
        return er;
    }
    else
        printf("...verifica_cria_aresta: codigo da aresta no no' 0 na posicao 0 coincide com o esperado (=%s) (ok)\n",(*g)->nos[0]->arestas[0]->codigo);
     
    erro = cria_aresta((*g)->nos[0], (*g)->nos[1],"T02","Linha do Norte",200,1999);

    if ((*g)->nos[0]->tamanho != 2)
    {
        printf("...verifica_cria_aresta: numero de aresta no no´ 0 (= %d) 'e diferente do esperado (= 2) (ERRO)\n", (*g)->nos[0]->tamanho);
        er++;
    }
    else
        printf("...verifica_cria_aresta:  numero de aresta no no´ 0 coincide com o esperado (= 2) (ok)\n");

    erro = cria_aresta((*g)->nos[0], (*g)->nos[1],"T02","Linha do Norte",200,1980);

    if (erro != 1)
    {
        printf("...verifica_cria_aresta: aresta devia ter dado ja´ existente (ERRO)\n");
        er++;
    }
    else 
        printf("...verifica_cria_aresta: aresta já existente  (ok)\n");
    return er;
}


int verifica_no_remove(grafo *g)
{
    int er = 0;

    no_grafo *no;
    no = no_remove(g, "inexistente");
    if (no)
    {
        printf("...verifica_no_remove (teste de estacao inexistente): removeu um nó inexistente (ERRO)\n");
        er++;
        no_apaga(no);
    }
    else
        printf("...verifica_no_remove (teste de estacao inexistente): não removeu nenhum nó (ok)\n");
    

    no = no_remove(g, "vermoin");
  
    if (!no)
    {
        printf("...verifica_no_remove (teste de estacao válida): não removeu (ERRO)\n");
        er++;
        return er;
    }
    else if (strcmp(g->nos[0]->estacao, "campanhã") != 0)
    {
        printf("...verifica_no_remove (teste de estacao válida): primeiro no´ (=%s) 'e diferente do esperado (= 'campanhã') (ERRO)\n",g->nos[0]->estacao);
        er++;
    } else
        printf("...verifica_no_remove (teste de estacao válida): primeiro no´ coincide com o esperado (=%s) (ok)\n",g->nos[0]->estacao);
     

  
    if (g->tamanho !=1)
    {
        printf("...verifica_no_insere: campo tamanho do grafo (= %d) 'e diferente do esperado (= 1) (ERRO)\n", g->tamanho);
        er++;
    }
    else
        printf("...verifica_no_insere:  campo tamanho do grafo coincide com o esperado (= 1) (ok)\n");

    if (no)
        no_apaga(no);
    return er;
}

int verifica_no_apaga()
{
    int erro;
    no_grafo *no1 = no_novo("Candal", "Vila Nova de Gaia");
    erro =  no_apaga(no1);
    if (erro == -1)
    {
        printf("...verifica_no_apaga: deu erro ao apagar o no (ERRO)\n");
        return 1;
    }
    else
        printf("...verifica_no_apaga: apagou com sucesso (ok)\n");
    return 0;
}


int verifica_encontra_troco(grafo *g)
{
    int er = 0;

    no_grafo *no;
    int pos = 0;
    no = encontra_troco(g, "L008", &pos);
    if (!no)
    {
        printf("...verifica_encontra_troco: deu erro ao encontrar o troço (ERRO)\n");
        er++;
    }
    else if (strcmp(no->estacao, "Aveleda") != 0 )
    {
        printf("...verifica_encontra_troco: encontrou o nó de origem errado (= %s) e´ esperado ('Aveleda')(ERRO)\n",no->estacao);
        er++;
    }
    else if ((pos == 1) && (strcmp(no->estacao, "Aveleda") == 0))
    {
        printf("...verifica_encontra_troco: encontrou com sucesso (='Aveleda') (OK)\n");
    }
    else
    {
        printf("...verifica_encontra_troco: encontrou a aresta errada (ERRO)\n");
        er++;
    }

    return er;
}

int verifica_pesquisa_avancada(grafo *g)
{
    int er = 0;

    no_grafo **vno;
   
    int n = 0;
    vno = pesquisa_avancada(g, "Aveiro",  &n);

    if (!vno)
    {
        printf("...verifica_pesquisa_avancada: deu erro ao encontrar os nos (ERRO)\n");
        er++;
    }
    else if (n != 3)
    {
        printf("...verifica_pesquisa_avancada: encontrou número de nós errado (=%d) e´esperado (=3) (ERRO)\n", n);
        free(vno);
        er++;
    }
    else
    {
        free(vno);
        printf("...verifica_pesquisa_avancada: encontrou com sucesso (OK)\n");
    }

    return er;
}


int verifica_estacoes_distrito(grafo *g)
{
    int er = 0;

    no_grafo **vno;
   
    int n = 0;
    vno = estacoes_distrito(g, "AVEIRO",  &n);

    if (!vno)
    {
        printf("...verifica_estacoes_distrito: deu erro ao encontrar os nos do distrito (ERRO)\n");
        er++;
    }
    else if (n != 71)
    {
        printf("...verifica_estacoes_distrito: encontrou número de nós errado (=%d) e´esperado (=71) (ERRO)\n", n);
        free(vno);
        er++;
    }
    else
    {
        free(vno);
        printf("...verifica_estacoes_distrito: encontrou com sucesso (=71) (OK)\n");
    }

    return er;
}

int verifica_estacoes_linha(grafo *g)
{
    int er = 0;

    no_grafo **vno;
   
    int n = 0;
    vno = estacoes_linha(g, "Alcantâra-Mar",  "Linha de Cintura",&n);

    if (!vno)
    {
        printf("...verifica_estacoes_linha: deu erro ao encontrar os nos da linha (ERRO)\n");
        er++;
    }
    else if (n != 9)
    {
        printf("...verifica_estacoes_linha: encontrou número de nós errado (=%d) e´esperado (=9) (ERRO)\n", n);
        free(vno);
        er++;
    }
    else
    {
        free(vno);
        printf("...verifica_estacoes_linha: encontrou com sucesso (=9) (OK)\n");
    }

    return er;
}

int verifica_metros_linha(grafo *g)
{
    int er = 0;

    int vno;
   

    vno = metros_linha(g,  "Linha do Minho", "Porto (São Bento)");

    if (vno==-1)
    {
        printf("...verifica_metros_linha: deu erro ao encontrar os metros da linha (ERRO)\n");
        er++;
    }
    else if (vno != 135903)
    {
        printf("...verifica_metros_linha: encontrou metros errado (=%d) e´esperado (=135903) (ERRO)\n", vno);
        
        er++;
    }
    else
    {
        
        printf("...verifica_metros_linha: encontrou com sucesso (=135903) (OK)\n");
    }

    return er;
}

int verifica_trajeto_mais_rapido(grafo *g)
{
    int er = 0;
    char or[] = "Tavira";
    char de[] = "Caminha";
    int n = 0;

    no_grafo **teste = trajeto_mais_rapido(g, or, de, &n);

    if (!teste)
    {
        printf("...verifica_trajeto_mais_rapido: deu erro ao encontrar o trajeto mais rápido (ERRO)\n");
        er++;
        return er;
    }
    else if (n != 153)
    {

        printf("...verifica_trajeto_mais_rapido: encontrou o número de nós errado (= %d) e´esperado (=153)(ERRO)\n",n);
        er++;
    }
    else if ((strcmp(teste[0]->estacao, "Tavira") != 0) || (strcmp(teste[45]->estacao, "Morgado") != 0) || (strcmp(teste[133]->estacao, "Louro") != 0))
    {
       
        printf("...verifica_trajeto_mais_rapido: encontrou os nós errados (ERRO)\n");
        er++;
    }
    else
    {
        printf("...verifica_trajeto_mais_rapido: encontrou com sucesso (OK)\n");
    }
    free(teste);
    return er;
}

int verifica_heap_carrega(heap **h, grafo *g)
{
    int er = 0;
    int tamanho =600;

    *h = heap_carrega(g, tamanho);

    if (*h)
    {

        if ((*h)->tamanho != 540)
        {
            printf("...verifica_heap_carrega (número de elementos): heap_carrega criou (=%d) elementos e´esperado (=540)(ERRO)\n",(*h)->tamanho);
            er++;
        }
        else
            printf("...verifica_heap_carrega (número de elementos): heap_carrega criou(=540) elementos (OK)\n");

        if (strcmp((*h)->elementos[1]->aresta->codigo,"L003")!=0)
        {
            printf("...verifica_heap_carrega (1º elemnto): 1º elemnto (=%s)e´esperado (='L003')(ERRO)\n",(*h)->elementos[1]->aresta->codigo);
            er++;
        }
        else
            printf("...verifica_heap_carrega (1º elemnto): 1º elemnto (='L003') (OK)\n");    
    }
    else

    {
        printf("...verifica_heap_carrega (número de espaços ocupado): tabela_carrega deu NULL (ERRO)\n");
        er++;
    }

    return er;
}

int verifica_inspecao_trocos(heap *h)
{
    int er = 0;
    int dias =5;
    int n=0;
    aresta_grafo **ret;
    ret = inspecao_trocos(h, dias,&n);
    
    if (ret)
    {

        if (n!= 5)
        {
            printf("...verifica_inspecao_trocos (número de arestas): verifica_inspecao_trocos criou (=%d) arestas e´esperado (=5)(ERRO)\n",n);
            er++;
        }
        else
            printf("...verifica_inspecao_trocos (número de arestas): verifica_inspecao_trocos criou(=5) arestas (OK)\n");

        if (strcmp((h)->elementos[1]->aresta->codigo,"L005")!=0)
        {
            printf("...verifica_inspecao_trocos (1º elemnto que ficou na heap): 1º aresta (=%s)e´esperado (='L005')(ERRO)\n",(h)->elementos[1]->aresta->codigo);
            er++;
        }
        else
            printf("...verifica_inspecao_trocos (1º elemnto que ficou na heap): 1º aresta (='L005') (OK)\n");    
    }
    else

    {
        printf("...verifica_inspecao_trocos: verifica_inspecao_trocos deu NULL (ERRO)\n");
        er++;
    }
free(ret);

    return er;
}


int main()
{
    int errorCount = 0, error;

  

    printf("INICIO DOS TESTES\n");

    printf("\nTESTES DO GRAFO\n\n");

    no_grafo *no=NULL;  
    grafo *g=NULL, *g1=NULL;
    char estacao[] = "melgaço";
    char distrito[] = "Viana do Castelo";

    error = verifica_grafo_novo(&g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_grafo_novo\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_grafo_novo passou\n\n");
    }

    error = verifica_no_novo(&no, estacao, distrito);

    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_no_novo\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_no_novo passou\n\n");
    } 

    error = verifica_no_insere(&g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_no_insere\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_no_insere passou\n\n");
    }


       error = verifica_cria_aresta(&g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_cria_aresta\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_cria_aresta passou\n\n");
    }
    
    error = verifica_no_remove(g);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_no_remove\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_no_remove passou\n\n");
    }

    error = verifica_no_apaga();
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_no_apaga\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_no_apaga passou\n\n");
    }

    char ficheiro[] = "db_linhas.txt";
    g1 = grafo_importa(ficheiro);
  

    error = verifica_encontra_troco(g1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_encontra_troco\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_encontra_troco passou\n\n");
    }

    error = verifica_pesquisa_avancada(g1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_pesquisa_avancada\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_pesquisa_avancada passou\n\n");
    }

     error = verifica_estacoes_distrito(g1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_estacoes_distrito\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_estacoes_distrito passou\n\n");
    }

     error = verifica_estacoes_linha(g1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_estacoes_linha\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_estacoes_linha passou\n\n");
    }

     error = verifica_metros_linha(g1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_metros_linha\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_metros_linha passou\n\n");
    }

   
    error = verifica_trajeto_mais_rapido(g1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_trajeto_mais_rapido\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_trajeto_mais_rapido passou\n\n");
    }

    heap *h;
    error = verifica_heap_carrega(&h,g1);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_heap_carrega\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_heap_carrega passou\n\n");
    }
      error = verifica_inspecao_trocos(h);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_inspecao_trocos\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_inspecao_trocos passou\n\n");
    }

    heap_apaga(h);
    grafo_apaga(g);
    grafo_apaga(g1);
 

    if (errorCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errorCount);

    return 0;
}
