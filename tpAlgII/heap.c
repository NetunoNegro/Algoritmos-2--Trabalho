#include <stdio.h>
#include <string.h>
#include "heap.h"

/* funcao auxiliar 1 se heap vazio, 0 caso nao*/
int HeapVazio(struct heap *h) {
    if(h->tam < 1)
        return 1;
    return 0;
}

void InicHeap(struct heap *h) {
    h->tam = 0;
}

struct paciente CriaPaciente(char nome[], int prioridade) {
    struct paciente p;
    /* strncpy limita a quantidade de caracteres passados da origem ao destino*/
    strncpy(p.nome, nome, sizeof(p.nome));
    /* se a origem for muito grande eh necessario inserir indicador de fim da string*/
    p.nome[sizeof(p.nome)-1] = '\0';
    p.prioridade = prioridade;

    return p;
}

char * NomePaciente(struct paciente *p) {
    return p->nome;
}

int PrioridadePaciente(struct paciente *p) {
    return p->prioridade;
}

int InsereHeap(struct heap *h, struct paciente p) {
    long i;
    struct paciente aux;

    i = h->tam + 1;
    if(i > MAXCAPACIDADE) 
        return 0; 

    h->pacientes[i] = p;
    h->tam++;

    /* vai testando a condicao do heap com v[i/2] ate encontrar posicao de p */
    while(i > 1 && h->pacientes[i/2].prioridade < h->pacientes[i].prioridade) {
        aux = h->pacientes[i/2];
        h->pacientes[i/2] = h->pacientes[i];
        h->pacientes[i] = aux;
        i = i/2;
    }

    return 1; 
}

void Heapfy(struct heap *h) {
    int i;
    struct heap hNovo;
    hNovo.tam = 0;

    /* insere todos os elementos do heap original em hNovo */
    for(i = 1; i <= h->tam; i++)
        InsereHeap(&hNovo, h->pacientes[i]);

    /* substitui o heap original pelo heap reorganizado */
    *h = hNovo;
}

struct paciente RemoveHeap(struct heap *h) {
    struct paciente p;

    if(HeapVazio(h)) {
        /* como n pode retornar NULL, valores impossiveis*/
        p.prioridade = -1;  
        p.nome[0] = '\0';
        return p;
    }

    p = h->pacientes[1];
    if(h->tam == 1){
        (h->tam)--;
        return p;
    }

    h->pacientes[1] = h->pacientes[h->tam];
    (h->tam)--;
    SacodeHeap(h, h->tam);
    return p;
}

int ChecaHeap(struct heap *h) {
    int i;

    for(i=h->tam; i>1; i--)
        if(h->pacientes[i].prioridade > h->pacientes[i/2].prioridade)
            /* violou a condicao do heap*/
            return 0;
    return 1;
}

void ImprimeHeap(struct heap *h) {
    int i;

    if(HeapVazio(h))
        printf("Fila vazia");
    for(i=1; i<=h->tam; i++)
        printf("[%d] %s (Prioridade: %d)\n", i, h->pacientes[i].nome, h->pacientes[i].prioridade);
}

void SacodeHeap(struct heap *h, int tam) {
    int i;
    struct paciente aux;

    i = 2;
    while(i <= tam) {
        if(i < tam && h->pacientes[i].prioridade < h->pacientes[i+ 1].prioridade)
            i++;
        if(h->pacientes[i/2].prioridade >= h->pacientes[i].prioridade)
            break;
        
        aux = h->pacientes[i/2];
        h->pacientes[i/2] = h->pacientes[i];
        h->pacientes[i] = aux;
        i = i * 2;
    }
}


void HeapSort(struct heap *h){
    int i;
    struct paciente aux;
    Heapfy(h);
    for (i = h->tam; i > 1; i--){
        aux = h->pacientes[1];
        h->pacientes[1] = h->pacientes[i];
        h->pacientes[i] = aux;
        SacodeHeap(h, i - 1);
    }
}