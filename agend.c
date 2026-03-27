#include <stdio.h>
#include <string.h>

// Definição da estrutura para armazenar os dados
typedef struct {
    char nome[100];
    char fone[20];
} Registro;

// Função para exibir o menu de opções
void mostrarMenu() {
    printf("\n--- GERENCIADOR DE CONTATOS ---\n");
    printf("1 - Adicionar Contato\n");
    printf("2 - Listar Todos\n");
    printf("3 - Gravar no Arquivo\n");
    printf("4 - Carregar do Arquivo\n");
    printf("5 - Sair\n");
    printf("Escolha: ");
}

// Função para salvar os dados em um arquivo CSV
void gravarDados(Registro lista[], int qtd) {
    FILE *arq = fopen("dados_agenda.csv", "w");

    if (arq == NULL) {
        printf("Erro: Nao foi possivel criar o arquivo.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(arq, "%s,%s\n", lista[i].nome, lista[i].fone);
    }

    fclose(arq);
    printf("Dados gravados com sucesso!\n");
}

// Função para ler os dados do arquivo e retornar a quantidade lida
int carregarDados(Registro lista[]) {
    FILE *arq = fopen("dados_agenda.csv", "r");

    if (arq == NULL) {
        printf("Aviso: Arquivo de dados nao encontrado.\n");
        return 0;
    }

    int contador = 0;
    // Leitura formatada ignorando a virgula como separador
    while (fscanf(arq, " %[^,],%[^\n]\n", lista[contador].nome, lista[contador].fone) == 2) {
        contador++;
    }

    fclose(arq);
    printf("%d contatos carregados do arquivo.\n", contador);
    return contador;
}

int main() {
    Registro agenda[100]; // Limite de 100 contatos
    int opcao;
    int totalContatos = 0;

    while (1) {
        mostrarMenu();
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        if (opcao == 1) {
            if (totalContatos < 100) {
                printf("Nome do contato: ");
                scanf("%[^\n]", agenda[totalContatos].nome);
                getchar();

                printf("Telefone: ");
                scanf("%s", agenda[totalContatos].fone);
                getchar();

                totalContatos++;
                printf("Contato adicionado!\n");
            } else {
                printf("Erro: Memoria cheia.\n");
            }
        } 
        else if (opcao == 2) {
            printf("\n--- LISTA DE CONTATOS ---\n");
            for (int i = 0; i < totalContatos; i++) {
                printf("%d. Nome: %s | Tel: %s\n", i + 1, agenda[i].nome, agenda[i].fone);
            }
        } 
        else if (opcao == 3) {
            gravarDados(agenda, totalContatos);
        } 
        else if (opcao == 4) {
            totalContatos = carregarDados(agenda);
        } 
        else if (opcao == 5) {
            printf("Encerrando programa...\n");
            break;
        } 
        else {
            printf("Opcao invalida!\n");
        }
    }

    return 0;
}