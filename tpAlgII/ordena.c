#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//vai ordenar vetor de 1024 completo então acho que da pra colocar 1024 no lugar do 5 no loop.
//ordenar vetor de integer.
void SelectSort(int v[], int tam){
    int i, j, menor, aux;
    for (i = 0; i < tam; i++){
        menor = i;
        for (j = i + 1; j < tam; j++){
            if (v[menor] > v[j])
                menor = j;
        }
        aux = v[menor];
        v[menor] = v[i];
        v[i] = aux;
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

void heapfy(int v[], int tam){
    int i;
    for (i = 1; i < tam; i++)
        Add_Heap(v, i);
}

void SacodeHeap(int v[], int tam){
    int aux;
    int i = 2;
    while (i <= tam){
        if (i < tam && v[i] < v[i+1])
            i++;
        if (v[i/2] >= v[i])
            break;
        aux = v[i/2];
        v[i/2] = v[i];
        v[i] = aux;
        i = i * 2;
    }
}

//faz de 1 até tam
//ele tem +1 de tamanho e nao usa v[0]
void HeapSort(int v[], int tam){
    int i, aux;
    heapfy(v, tam);
    for (i = tam; i > 1; i--){
        aux = v[1];
        v[1] = v[i];
        v[i] = aux;
        SacodeHeap(v, i - 1);
    }
}

//acha mediana em vetor de integer.
int Acha_mediana(int v[], int esq, int meio, int dir){
    if ((v[esq] >= v[meio] && v[esq] <= v[dir]) || (v[esq] >= v[dir] && v[esq] <= v[meio]))
        return esq;
    if ((v[meio] >= v[esq] && v[meio] <= v[dir]) || (v[meio] >= v[dir] && v[meio] <= v[esq]))
        return meio;
    return dir;
}

void particao(int v[], int esq, int dir, int *pos_pivo){
    int i, j , pivo, aux;
    int p_pivo = Acha_mediana(v, esq, (esq + dir) / 2, dir);
    aux = v[esq];
    v[esq] = v[p_pivo];
    v[p_pivo] = aux;
    pivo = v[esq];
    i = esq;
    j = dir;
    while (i < j){
        while(v[i] <= pivo && i < dir)
            i++;
        while (v[j] > pivo)
            j--;
        if (i < j){
            aux = v[j];
            v[j] = v[i];
            v[i] = aux;
        }
    }
    v[esq] = v[j];
    v[j] = pivo;
    *pos_pivo = j;
}

void QuickSort(int v[], int esq, int dir){
    int pos_pivo;
    if (esq < dir){
        particao(v, esq, dir, &pos_pivo);
        QuickSort(v, esq, pos_pivo -1);
        QuickSort(v, pos_pivo + 1, dir);
    }
}


//gera 3 vetores "iguais" para fazer a comparação
//o vetor heap vai de 1 até tam, o resto de 0 até tam-1.
void Gera_Vetores(int v_select[], int v_quick[], int v_heap[], int tam){
    int i;
    srand(time(NULL));
    for (i = 0; i < tam; i++){
        v_select[i] = rand();
        v_quick[i] = v_select[i];
        v_heap[i + 1] = v_select[i];
    }
}

int main(){
    int n, i;
    scanf("%d", &n);
    int v_select[n], v_quick[n], v_heap[n + 1];
    Gera_Vetores(v_select, v_quick, v_heap, n);
    printf("\n\n");
    for (i = 0; i < n; i++){
        printf("%d ", v_select[i]);
    }
    printf("\n\n");
    for (i = 0; i < n; i++){
        printf("%d ", v_quick[i]);
    }
    printf("\n\n");
    //heap == de 1 até n
    for (i = 1; i <= n; i++){
        printf("%d ", v_heap[i]);
    }
    printf("\n\n");
    SelectSort(v_select, n);
    QuickSort(v_quick, 0 , n - 1);
    HeapSort(v_heap, n);
    printf("\n\n");
    for (i = 0; i < n; i++){
        printf("%d ", v_select[i]);
    }
    printf("\n\n");
    
    for (i = 0; i < n; i++){
        printf("%d ", v_quick[i]);
    }
    printf("\n\n");

    //heap == de 1 até n
    for (i = 1; i <= n; i++){
        printf("%d ", v_heap[i]);
    }
}