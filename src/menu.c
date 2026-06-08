#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/livro.h"
#include "../include/leitor.h"
#include "../include/emprestimo.h"
#include "../include/menu.h"
#include "../include/usuario.h"

// Menu inicial do sistema
void menu_biblioteca() {
    printf("\n=================================\n        SISTEMA BIBLIOTECA\n=================================");
    printf("\n1 - Listar livros\n");
    printf("2 - Cadastrar usuário\n");
    printf("3 - Menu de Gestão (Empréstimos e Leitores)\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

// Segundo menu do sistema
void menu_principal(){
    int opcao = -1;
    while (opcao != 4) {
        printf("\n--- MENU DE GESTAO ---\n");
        printf("1. Cadastrar Livro \n");
        printf("2. Cadastrar Leitor \n");
        printf("3. Zona do Empréstimo \n");
        printf("4. Voltar \n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                cadastrarlivro();
                break;
            case 2:
                cadastrarleitor();
                break;
            case 3:
                zona_emprestimos();
                break;
            case 4:
                printf("Voltando... \n");
                return;
            default:
                printf("Opcao invalida. \n");
                break;
        }
    }
}

// Menu de emprestimos
void zona_emprestimos(){
    int opcao = -1; 
    while (opcao != 0) {
        printf("\n--- ZONA DE EMPRESTIMOS ---\n");
        printf("1. Cadastrar Emprestimo \n");
        printf("2. Acessar Emprestimos Ativos \n");
        printf("3. Fazer devolução \n");
        printf("4. Acessar Histórico de Emprestimos \n");
        printf("0. Voltar \n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                cadastraremprestimo();
                break;
            case 2:
                emprestimo_ativo();
                break;
            case 3:
                // Atualizado para enviar os livros
                emprestimo_devolucao();
                break; 
            case 4:
                // Atualizado para enviar as três listas e cruzar os dados
                historico_emprestimo();
                break;
            case 0:
                printf("Voltando ao menu anterior... \n");
                return; 
            default:
                printf("Opcao invalida. \n");
                break;
        }
    }
}

// Função para executar tudo em ordem
void executar() {
    carregar_livros();
    carregar_leitores();
    carregar_emprestimos();

    int opcao = -1;

    while(opcao != 0){
        menu_biblioteca(); //Menu inicial
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                listar_livros();
                break;
            case 2:
                cadastrar_usuario();
                break;
            case 3:
                // Menu Principal -> Cadastro de livros, leitores e zona de empréstimos
                menu_principal();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}