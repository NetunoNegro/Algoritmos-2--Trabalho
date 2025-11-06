#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "ordena.h"

/*selection sort, tamanho por padrão vai ser 1024*/
void SelectSort(int v[], int tam, int *compara, int *troca){
    int i, j, menor, aux;
    for (i = 0; i < tam; i++){
        menor = i;
        for (j = i + 1; j < tam; j++){
            if (v[menor] > v[j])
                menor = j;
            *compara = *compara + 1;
        }
        if (menor != i){ /*adicionado para não trocar caso o menor seja o primeiro do loop de j, assim *troca pode ser != tam*/
            aux = v[menor];
            v[menor] = v[i];
            v[i] = aux;
            *troca = *troca + 1;
        }
    }
}

void Add_Heap(int v[], int tam){
    int aux;
    int i = tam + 1;
    while (i > 1 && v[i/2] < v[i]){
        aux = v[i];
        v[i] = v[i/2];
        v[i/2] = aux;
        i = i/2;
    }
}

/* não contar desempenho de heapfy no heapsort pois foi feito assim em aula*/
void heapfy_v(int v[], int tam){
    int i;
    for (i = 1; i < tam; i++)
        Add_Heap(v, i);
}

void SacodeHeap_v(int v[], int tam, int *compara, int *troca){
    int aux;
    int i = 2;
    while (i <= tam){
        if (i < tam && v[i] < v[i+1]){
            i++;
            *compara = *compara + 1; /*comparação de v[i] com v[i+1]*/
        }
        else if (i < tam) {
            *compara = *compara + 1;/*se v[i+1] existir mas não for > que v[i], ainda houve comparação*/
        }
        *compara = *compara + 1; /*comparação para break*/
        if (v[i/2] >= v[i])
            break;
        aux = v[i/2];
        v[i/2] = v[i];
        v[i] = aux;
        i = i * 2;
        *troca = *troca + 1;
    }
}

/*vetor do heap é de 1 até 1024, os outros 2 0 até 1023*/
void HeapSort_v(int v[], int tam, int *compara, int *troca){
    int i, aux;
    heapfy_v(v, tam);
    for (i = tam; i > 1; i--){
        aux = v[1];
        v[1] = v[i];
        v[i] = aux;
        *troca = *troca + 1;
        SacodeHeap_v(v, i - 1, compara, troca);
    }
}

/*nao conto desempenho de Acha_mediana pois não acho necessário*/
int Acha_mediana(int v[], int esq, int meio, int dir){
    if ((v[esq] >= v[meio] && v[esq] <= v[dir]) || (v[esq] >= v[dir] && v[esq] <= v[meio]))
        return esq;
    if ((v[meio] >= v[esq] && v[meio] <= v[dir]) || (v[meio] >= v[dir] && v[meio] <= v[esq]))
        return meio;
    return dir;
}

void particao(int v[], int esq, int dir, int *pos_pivo, int *compara, int *troca){
    int i, j , pivo, aux;
    int p_pivo = Acha_mediana(v, esq, (esq + dir) / 2, dir);
    aux = v[esq];
    v[esq] = v[p_pivo];
    v[p_pivo] = aux;
    pivo = v[esq];
    i = esq;
    j = dir;
    while (i < j){
        while(v[i] <= pivo && i < dir){
            i++;
            *compara = *compara + 1;
        }
        *compara = *compara + 1; /*se sair do while, ainda teve 1 comparação*/
        while (v[j] > pivo){
            j--;
            *compara = *compara + 1;
        }
        *compara = *compara + 1; /*se sair do while, ainda teve 1 comparação*/
        if (i < j){
            aux = v[j];
            v[j] = v[i];
            v[i] = aux;
            *troca = *troca + 1;
        }
    }
    v[esq] = v[j];
    v[j] = pivo;
    *pos_pivo = j;
    *troca = *troca + 1;
}

void QuickSort(int v[], int esq, int dir, int *compara, int *troca){
    int pos_pivo;
    if (esq < dir){
        particao(v, esq, dir, &pos_pivo, compara, troca);
        QuickSort(v, esq, pos_pivo -1, compara, troca);
        QuickSort(v, pos_pivo + 1, dir, compara, troca);
    }
}


/*gera 3 vetores "iguais" para fazer a comparação
o vetor heap vai de 1 até tam, o resto de 0 até tam-1.*/
void Gera_Vetores(int v_select[], int v_quick[], int v_heap[], int tam){
    int i;
    srand(time(NULL));
    for (i = 0; i < tam; i++){
        v_select[i] = rand();
        v_quick[i] = v_select[i];
        v_heap[i + 1] = v_select[i];
    }
}

/*faz todo o proesso de gerar vetores aleatórios iguais, imprimir ele
realizar a ordenação e impressão do vetor depois de ordenado
também faz a impressão das comparações e trocas que cada algoritmo faz*/
void compara_ordenacao(int tam){
    int v_select[tam], v_quick[tam], v_heap[tam + 1];
    int compara_select, troca_select;
    int compara_quick, troca_quick;
    int compara_heap, troca_heap;
    int i;

    compara_select = 0;
    troca_select = 0;
    compara_quick = 0;
    troca_quick = 0;
    compara_heap = 0;
    troca_heap = 0;

    Gera_Vetores(v_select, v_quick, v_heap, tam);

    printf("\n\n");
    printf("Vetor = \n");
    for (i = 0; i < tam; i++){
        printf("%d ", v_select[i]);
    }

    SelectSort(v_select, tam, &compara_select, &troca_select);
    QuickSort(v_quick, 0 , tam - 1, &compara_quick, &troca_quick);
    HeapSort_v(v_heap, tam, &compara_heap, &troca_heap);

    printf("\n\n");
    for (i = 0; i < tam; i++){
        printf("%d ", v_select[i]);
    }
    printf("\n\n");
    printf("comparações select : %d\n", compara_select);
    printf("trocas select: %d", troca_select);
    printf("\n\n");
    
    for (i = 0; i < tam; i++){
        printf("%d ", v_quick[i]);
    }
    printf("\n\n");
    printf("comparações quick : %d\n", compara_quick);
    printf("trocas quick: %d", troca_quick);
    printf("\n\n");

    for (i = 1; i <= tam; i++){
        printf("%d ", v_heap[i]);
    }
    printf("\n\n");
    printf("comparações heap : %d\n", compara_heap);
    printf("trocas heap: %d", troca_heap);
    printf("\n\n");
}