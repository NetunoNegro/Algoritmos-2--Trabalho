#ifndef HEAP
#define HEAP

#define MAXCAPACIDADE 100

struct paciente {
    char nome[80];
    int prioridade;
};

struct heap {
    struct paciente pacientes[MAXCAPACIDADE+1]; /* +1 porque começamos a indexar do 1 */
    int tam;
};

/* Todas as funções recebem ponteiro ao heap para evitar copiar toda estrutura
em cada operação */

/* inicia o Heap com tamanho 0 */
void InicHeap(struct heap *h);

/* cria struct paciente usando os parametros nome e prioridade*/
struct paciente CriaPaciente(char nome[], int prioridade);

/* retorna ao usuario o campo nome do paciente*/
char * NomePaciente(struct paciente *p); 

/* retorna ao usuario o campo prioridade do paciente*/
int PrioridadePaciente(struct paciente *p);

/* coloca p em tam+1 e depois insere em uma posição 
em h que respeite o Heap */
int InsereHeap(struct heap *h, struct paciente p);

/* transforma um vetor em Heap usando InsereHeap */
void Heapfy(struct heap *h);

/* remove o elemento com mais prioridade do Heap e insere o ultimo elemento do Heap na primeira posicao*/
struct paciente RemoveHeap(struct heap *h);

/* testa um vetor, retorna 0 se violou condição do Heap e 1 caso contrário */
int ChecaHeap(struct heap *h);

/* imprime o nome e prioridade de todos os elementos no Heap */
void ImprimeHeap(struct heap *h);

/* outras funções do Heap */
void SacodeHeap(struct heap *h, int tam);

void HeapSort(struct heap *h);

#endif
