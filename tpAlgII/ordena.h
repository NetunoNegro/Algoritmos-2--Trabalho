#ifndef ORDENA
#define ORDENA

void SelectSort(int v[], int tam, int *compara, int *troca);

void Add_Heap(int v[], int tam);

void heapfy_v(int v[], int tam);

void SacodeHeap_v(int v[], int tam, int *compara, int *troca);

void HeapSort_v(int v[], int tam, int *compara, int *troca);

int Acha_mediana(int v[], int esq, int meio, int dir);

void particao(int v[], int esq, int dir, int *pos_pivo, int *compara, int *troca);

void QuickSort(int v[], int esq, int dir, int *compara, int *troca);

void Gera_Vetores(int v_select[], int v_quick[], int v_heap[], int tam);

void compara_ordenacao(int tam);

#endif
