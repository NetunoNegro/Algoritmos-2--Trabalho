#include <stdio.h>
#include <string.h>
#include "heap.h"

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
        printf("0 - Encerrar programa\n");
        printf("\nEscolha uma operacao: ");
        scanf("%d", &operacao);
        /* como ha leitura de strings tenho que retirar /n do buffer*/
        getchar();

        switch(operacao) {
            case 1:
                printf("Digite o nome do paciente: ");
                fflush(stdout);
                /* fgets para evitar overflow e ler espacos em branco*/
                fgets(nome, sizeof(nome), stdin);
                /* sinaliza o final da string */
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite a prioridade do paciente: ");
                /*fflush garante que a mensagem apareca antes de pedir entrada*/
                fflush(stdout);
                scanf("%d", &prioridade);
    
                p = CriaPaciente(nome, prioridade);
                if(InsereHeap(&h, p))
                    printf("Paciente Inserido!");
                else 
                    printf("Fila cheia");
                break;
            case 2:
                p = RemoveHeap(&h);
                printf("Paciente %s (Prioridade %d) removido.", NomePaciente(&p), PrioridadePaciente(&p));  
                break;
            case 3:
                printf("Atualizar paciente");
                break;
            case 4: 
                ImprimeHeap(&h);
                printf("\nPressione Enter para continuar...");
                /* espera o usuario apertar qualquer tecla para continuar*/
                getchar();
                break;
            case 5:
                HeapSort(&h);
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
