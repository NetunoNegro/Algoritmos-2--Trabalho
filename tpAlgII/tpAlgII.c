#include <stdio.h>
#include <string.h>
#include "heap.h"
#include "ordena.h"

void RemoverEspacoDireita(char palavra[]) {
    int tamanho = strlen(palavra);
    
    while (tamanho > 0 && palavra[tamanho-1] == ' ') {
        palavra[tamanho-1] = '\0';
        tamanho--;
    }
}

int main() {
    struct heap h;
    struct paciente p;
    char nome[80];
    int loop, operacao, prioridade;

    InicHeap(&h);
    loop = 1;
    while (loop) {
        printf("\n========= MENU ENFERMEIRA CHEFE =========\n");
        printf("1 - Inserir paciente\n");
        printf("2 - Remover paciente de maior prioridade\n");
        printf("3 - Atualizar prioridade de um paciente\n");
        printf("4 - Imprimir heap\n");
        printf("5 - Ordenar Pacientes\n");
        printf("6 - Checar Heap\n");
        printf("7 - Heapfy\n");
        printf("8 - Compara desempenho de Algoritmos de ordenação\n");
        printf("0 - Encerrar programa\n");
        printf("\nEscolha uma operacao: ");
        scanf("%d", &operacao);
        /* como ha leitura de strings tenho que retirar /n do buffer*/
        while(getchar() != '\n'); 

        switch(operacao) {
            case 1:
                printf("Digite o nome do paciente: ");
                /* fgets para evitar overflow e ler espacos em branco*/
                fgets(nome, sizeof(nome), stdin);
                /* sinaliza o final da string */
                nome[strcspn(nome, "\n")] = '\0';
                RemoverEspacoDireita(nome);

                printf("Digite a prioridade do paciente: ");
                scanf("%d", &prioridade);
                while(getchar() != '\n'); 
    
                p = CriaPaciente(nome, prioridade);
                if(InsereHeap(&h, p))
                    printf("Paciente Inserido!");
                else 
                    printf("Fila cheia");
                break;
            case 2:
                p = RemoveHeap(&h);
                if(PrioridadePaciente(&p) != -1) 
                    printf("Paciente %s (Prioridade %d) removido.", NomePaciente(&p), PrioridadePaciente(&p));
                else   
                    printf("Fila vazia"); 
                
                printf("\nPressione Enter para continuar...");
                /* espera o usuario apertar qualquer tecla para continuar*/
                getchar();
                break;
            case 3:
                printf("Digite o nome do paciente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                RemoverEspacoDireita(nome);

                printf("Digite a prioridade do paciente: ");
                scanf("%d", &prioridade);
                while(getchar() != '\n');
                
                if(AtualizaPrioridadeHeap(&h, nome, prioridade))
                    printf("Prioridade do paciente alterada");
                else   
                    printf("Paciente nao encontrado");

                printf("\nPressione Enter para continuar...");
                /* espera o usuario apertar qualquer tecla para continuar*/
                getchar();
                break;
            case 4: 
                ImprimeHeap(&h);
                printf("\nPressione Enter para continuar...");
                /* espera o usuario apertar qualquer tecla para continuar*/
                getchar();
                break;
            case 5:
                HeapSort(&h); /* ta errado , vou arrumar*/
                break;
            case 6:
                if(ChecaHeap(&h))
                    printf("Cumpre os requisitos de Heap");
                else
                    printf("Viola as condições do Heap");

                printf("\nPressione Enter para continuar...");
                /* espera o usuario apertar qualquer tecla para continuar*/
                getchar();
                break;
            case 7:
                Heapfy(&h);
                printf("Heapfy aplicado");
                
                printf("\nPressione Enter para continuar...");
                /* espera o usuario apertar qualquer tecla para continuar*/
                getchar();
                break;
            case 8:
                compara_ordenacao(1024); /* envia tamanho do vetor, integer, padrão 1024*/
                break;
            case 0:
                loop = 0;
                printf("\nPrograma Encerrado\n");
                break;
            default:
                printf("\nOperacao invalida!");
                break;
        }
    }

    return 0;
}
