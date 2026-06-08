#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/livro.h"
#include "../include/leitor.h"
#include "../include/emprestimo.h"

emprestimo emprestimos[MAX_EMPRESTIMOS];
int num_emprestimos = 0;
int proximo_emprestimo_id = 1;

// Função para salvar os emprestimos em um arquivo de texto
void salvar_emprestimos() {
    FILE *fp = fopen("data/emprestimos.txt", "w");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de emprestimos!\n");
        return;
    }
    fprintf(fp, "%d\n", num_emprestimos);
    fprintf(fp, "%d\n", proximo_emprestimo_id);
    for(int i = 0; i < num_emprestimos; i++) {
        fprintf(fp, "%d | %d | %d | %s | %s\n",
            emprestimos[i].id_emprestimo,
            emprestimos[i].id_leitor,
            emprestimos[i].id_livro,
            emprestimos[i].data_emprestimo,
            emprestimos[i].data_devolucao);
    }
    fclose(fp);
    printf("Dados de emprestimos salvos com sucesso.");
}

// Função para carregar os emprestimos por um arquivo de texto
void carregar_emprestimos() {
    FILE *fp = fopen("data/emprestimos.txt", "r");
    if (!fp) {
        printf("Nenhum arquivo de emprestimos encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fscanf(fp, "%d", &num_emprestimos);
    fscanf(fp, "%d", &proximo_emprestimo_id);
    for (int i = 0; i < num_emprestimos; i++){
        fscanf(fp, "%d | %d | %d | %s | %s", 
            &emprestimos[i].id_emprestimo,
            &emprestimos[i].id_leitor,
            &emprestimos[i].id_livro,
            emprestimos[i].data_emprestimo,
            emprestimos[i].data_devolucao);
    }
    fclose(fp);
    printf("Dados de emprestimos carregados: %d encontrado(s).\n", num_emprestimos);
}

// Função para cadastrar emprestimos de livros
void cadastraremprestimo() {
    if (num_emprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido. \n");
        return;
    }
    
    emprestimo novo_emprestimo; 
    novo_emprestimo.id_emprestimo = proximo_emprestimo_id;

    printf("ID do leitor: ");
    scanf("%d", &novo_emprestimo.id_leitor);
    printf("ID do livro: "); 
    scanf("%d", &novo_emprestimo.id_livro);
    
    // VERIFICA SE O LEITOR EXISTE
    int i;
    for (i = 0; i < num_leitores; i++) {
        if (leitores[i].id_leitor == novo_emprestimo.id_leitor) {
            break;
        }
    }
    if(i == num_leitores) {
        printf("Leitor nao encontrado. \n");
        return;
    }

    // VERIFICA SE O LIVRO EXISTE E ESTÁ DISPONÍVEL
    int j, livro_encontrado = 0;
    for (j = 0; j < num_livros; j++) {
        if (livros[j].id_livro == novo_emprestimo.id_livro) {
            livro_encontrado = 1;
            if (livros[j].disponivel == 'N') {
                printf("Erro: Este livro ja esta emprestado no momento.\n");
                return;
            }
            break;
        }
    }
    if (!livro_encontrado) {
        printf("Livro nao encontrado.\n");
        return;
    }
    
    printf("Data de emprestimo (dd/mm/aaaa): ");
    scanf(" %[^\n]", novo_emprestimo.data_emprestimo);
    printf("Data de devolucao (dd/mm/aaaa): ");
    scanf(" %[^\n]", novo_emprestimo.data_devolucao);
    
    // Muda o status do livro para Indisponível
    livros[j].disponivel = 'N';

    emprestimos[num_emprestimos] = novo_emprestimo;
    num_emprestimos++;
    proximo_emprestimo_id++;
    salvar_emprestimos();

    printf("Emprestimo cadastrado com sucesso. \n");
}

// Função para mostrar empréstimos ativos
void emprestimo_ativo(){ 
    printf("Listando emprestimos ativos...\n"); 
}

// Função para devolução de livros emprestados
void emprestimo_devolucao() {
    int id_procurado;
    printf("Digite o ID do livro que esta sendo devolvido: ");
    scanf("%d", &id_procurado);

    int i, encontrado = 0;
    for (i = 0; i < num_livros; i++) {
        if (livros[i].id_livro == id_procurado) {
            encontrado = 1;
            if (livros[i].disponivel == 'N') {
                livros[i].disponivel = 'S'; // Livro volta a ficar disponível
                printf("Devolucao do livro '%s' realizada com sucesso!\n", livros[i].titulo);
            } else {
                printf("Aviso: Esse livro ja consta como disponivel no sistema.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Erro: Livro com ID %d nao foi encontrado no sistema.\n", id_procurado);
    }
}

// Função para mostrar todos os emprestimos já feitos
void historico_emprestimo() {
    if (num_emprestimos == 0) {
        printf("Nenhum emprestimo registrado no historico ate o momento.\n");
        return;
    }

    printf("\n==== HISTORICO DE EMPRESTIMOS ====\n");
    for (int i = 0; i < num_emprestimos; i++) {
        char nome_leitor[100] = "Desconhecido";
        char titulo_livro[100] = "Desconhecido";

        // Busca o nome do leitor
        for (int j = 0; j < num_leitores; j++) {
            if (leitores[j].id_leitor == emprestimos[i].id_leitor) {
                strcpy(nome_leitor, leitores[j].nome);
                break;
            }
        }

        // Busca o título do livro
        for (int k = 0; k < num_livros; k++) {
            if (livros[k].id_livro == emprestimos[i].id_livro) {
                strcpy(titulo_livro, livros[k].titulo);
                break;
            }
        }

        printf("ID Emprestimo: %d | Leitor: %s | Livro: %s\n", emprestimos[i].id_emprestimo, nome_leitor, titulo_livro);
        printf("Data Emprestimo: %s | Data Devolucao: %s\n", emprestimos[i].data_emprestimo, emprestimos[i].data_devolucao);
        printf("---------------------------------\n");
    }
}