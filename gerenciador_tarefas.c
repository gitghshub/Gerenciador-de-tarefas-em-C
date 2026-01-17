#include <stdio.h>
#include <string.h>

#define MAX_TAREFAS 100
#define TAM_TEXTO 100

typedef struct {
    char titulo[TAM_TEXTO];
    int concluida; // 0 = não, 1 = sim
} Tarefa;

void mostrarMenu() {
    printf("\n=== GERENCIADOR DE TAREFAS ===\n");
    printf("1 - Adicionar tarefa\n");
    printf("2 - Listar tarefas\n");
    printf("3 - Marcar tarefa como concluída\n");
    printf("4 - Remover tarefa\n");
    printf("0 - Sair\n");
}

void adicionarTarefa(Tarefa tarefas[], int *total) {
    if (*total >= MAX_TAREFAS) {
        printf("Limite de tarefas atingido.\n");
        return;
    }

    printf("Digite a descrição da tarefa: ");
    getchar(); // limpar buffer
    fgets(tarefas[*total].titulo, TAM_TEXTO, stdin);

    // remove quebra de linha
    tarefas[*total].titulo[strcspn(tarefas[*total].titulo, "\n")] = '\0';
    tarefas[*total].concluida = 0;

    (*total)++;
    printf("Tarefa adicionada com sucesso!\n");
}

void listarTarefas(Tarefa tarefas[], int total) {
    if (total == 0) {
        printf("Nenhuma tarefa cadastrada.\n");
        return;
    }

    printf("\n--- Lista de Tarefas ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d. [%c] %s\n",
               i + 1,
               tarefas[i].concluida ? 'X' : ' ',
               tarefas[i].titulo);
    }
}

void concluirTarefa(Tarefa tarefas[], int total) {
    int indice;
    listarTarefas(tarefas, total);

    if (total == 0) return;

    printf("Digite o número da tarefa concluída: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > total) {
        printf("Número inválido.\n");
        return;
    }

    tarefas[indice - 1].concluida = 1;
    printf("Tarefa marcada como concluída!\n");
}

void removerTarefa(Tarefa tarefas[], int *total) {
    int indice;
    listarTarefas(tarefas, *total);

    if (*total == 0) return;

    printf("Digite o número da tarefa para remover: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > *total) {
        printf("Número inválido.\n");
        return;
    }

    for (int i = indice - 1; i < *total - 1; i++) {
        tarefas[i] = tarefas[i + 1];
    }

    (*total)--;
    printf("Tarefa removida com sucesso!\n");
}

int main() {
    Tarefa tarefas[MAX_TAREFAS];
    int total = 0;
    int opcao;

    do {
        mostrarMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarTarefa(tarefas, &total);
                break;
            case 2:
                listarTarefas(tarefas, total);
                break;
            case 3:
                concluirTarefa(tarefas, total);
                break;
            case 4:
                removerTarefa(tarefas, &total);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}