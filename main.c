#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 100
#define MAX_LEITORES 100
#define MAX_EMPRESTIMOS 100

typedef struct {
    int id_livro;
    char titulo[100];
    char autor[100];
    char disponivel;
} livro;

typedef struct {
    int id_leitor;
    char nome[100];
    char email[100];
    char telefone[20];
    char cpf[20];
} leitor;

typedef struct {
    int id_emprestimo;
    int id_leitor;
    int id_livro;
    char data_emprestimo[20];
    char data_devolucao[20];
} emprestimo;
///////////////////////////////////////////////////// CADASTRO DOS LIVROS //////////////////////////////////////////////////////////////////
void cadastrarlivro(livro *livros, int *num_livros) {
    if (*num_livros >= MAX_LIVROS) {
        printf("Limite de livros atingido. \n");
        return;
    }
    
    livro novo_livro;
    novo_livro.id_livro = *num_livros + 1;
    printf("Titulo: ");
    scanf(" %[^\n]", novo_livro.titulo);
    printf("Autor: ");
    scanf(" %[^\n]", novo_livro.autor);
    novo_livro.disponivel = 'S'; // Ajustado para maiúsculo
    
    livros[*num_livros] = novo_livro;
    (*num_livros)++;
    
    printf("Livro cadastrado com sucesso. ID: %d\n", novo_livro.id_livro);
}
////////////////////////////////////////////////// CADASTRO DOS LEITORES //////////////////////////////////////////////////////////////////
void cadastrarleitor(leitor *leitores, int *num_leitores) {
    if (*num_leitores >= MAX_LEITORES) {
        printf("Limite de leitores atingido. \n");
        return;
    }
    
    leitor novo_leitor; 
    novo_leitor.id_leitor = *num_leitores + 1;
    printf("Nome: ");
    scanf(" %[^\n]", novo_leitor.nome);
    printf("Email: ");
    scanf(" %[^\n]", novo_leitor.email);
    printf("Telefone: ");
    scanf(" %[^\n]", novo_leitor.telefone);
    printf("CPF: ");
    scanf(" %[^\n]", novo_leitor.cpf);
    
    leitores[*num_leitores] = novo_leitor;
    (*num_leitores)++;
    
    printf("Leitor cadastrado com sucesso. ID: %d\n", novo_leitor.id_leitor);
}
 ////////////////////////////////////////////// CADASTRO DE EMPRESTIMO //////////////////////////////////////////////////////////////////   
void cadastraremprestimo(emprestimo *emprestimos, int *num_emprestimos, leitor *leitores, livro *livros, int num_leitores, int num_livros) {
    if (*num_emprestimos >= MAX_EMPRESTIMOS) {
        printf("Limite de emprestimos atingido. \n");
        return;
    }
    
    emprestimo novo_emprestimo; 
    novo_emprestimo.id_emprestimo = *num_emprestimos + 1;
    printf("ID do leitor: ");
    scanf("%d", &novo_emprestimo.id_leitor);
    printf("ID do livro: "); 
    scanf("%d", &novo_emprestimo.id_livro);
    
    printf("Data de emprestimo (dd/mm/aaaa): ");
    scanf(" %[^\n]", novo_emprestimo.data_emprestimo);
    printf("Data de devolucao (dd/mm/aaaa): ");
    scanf(" %[^\n]", novo_emprestimo.data_devolucao);
    
    // verificar se o leitor existe
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
    
    emprestimos[*num_emprestimos] = novo_emprestimo;
    (*num_emprestimos)++;
    printf("Emprestimo cadastrado com sucesso. \n");
}

typedef struct {
    char nome[50];
    char email[50];
    char senha[50];
} usuario;
/////////////////////////////////////////////////////////// MENU INICIAL /////////////////////////////////////////////////////////////////
void menu_biblioteca() {
    printf("\n=================================\n       SISTEMA BIBLIOTECA\n=================================");
    printf("\n1 - Cadastrar livros\n");
    printf("2 - Listar livros\n");
    printf("3 - Cadastrar usuário\n");
    printf("4 - Menu de Gestão (Empréstimos e Leitores)\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}
///////////////////////////////////////////////////////// CADASTRO DO USUÁRIO ////////////////////////////////////////////////////////////////
void cadastrar_usuario() {
    usuario u;
    printf("Digite o nome do usuário: ");
    scanf(" %49[^\n]", u.nome);
    printf("Digite o email do usuário: ");
    scanf(" %49[^\n]", u.email);
    printf("Digite a senha do usuário: ");
    scanf(" %49[^\n]", u.senha);
    printf("Usuário cadastrado com sucesso.\n");
}
//////////////////////////////////////////////// EM DESENVOLVIMENTO(BRUNO) ///////////////////////////////////////////////////////////////
void emprestimo_ativo(){ printf("Listando emprestimos ativos...\n"); }
void emprestimo_devolucao(){ printf("Realizando devolucao...\n"); }
void historico_emprestimo(){ printf("Exibindo historico...\n"); }
//////////////////////////////////////// ZONA DE EMPRESTIMOS //////////////////////////////////////////////////////////////////////////
void zona_emprestimos(emprestimo *emprestimos, int *num_emprestimos, leitor *leitores, livro *livros, int num_leitores, int num_livros){
    int opcao = -1; // Variável declarada para este escopo
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
                cadastraremprestimo(emprestimos, num_emprestimos, leitores, livros, num_leitores, num_livros);
                break;
            case 2:
                emprestimo_ativo();
                break;
            case 3:
                emprestimo_devolucao();
                break; // Adicionado break faltante
            case 4:
                historico_emprestimo();
                break;
            case 0:
                printf("Voltando ao menu anterior... \n");
                return; // Substitui o exit(0) para não fechar o programa inteiro
            default:
                printf("Opcao invalida. \n");
                break;
        }
    }
}

/////////////////////////////////// NÃO COLOCAR NENHUM PROCEDIMENTO À BAIXO DAQUI /////////////////////////////////////////////////////

void menu_principal(livro *livros, int *num_livros, leitor *leitores, int *num_leitores, emprestimo *emprestimos, int *num_emprestimos){
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
                cadastrarlivro(livros, num_livros);
                break;
            case 2:
                cadastrarleitor(leitores, num_leitores);
                break;
            case 3:
                zona_emprestimos(emprestimos, num_emprestimos, leitores, livros, *num_leitores, *num_livros);
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
/////////////////////////////////////////////////// EXECUÇÃO INICIAL DO CÓDIGO //////////////////////////////////////////////////////////////
void executar() {
    // Arrays declarados na base do programa para garantir que os dados fiquem salvos
    livro livros[MAX_LIVROS];
    leitor leitores[MAX_LEITORES];
    emprestimo emprestimos[MAX_EMPRESTIMOS];
    int num_livros = 0;
    int num_leitores = 0;
    int num_emprestimos = 0;
    
    int opcao = -1;

    while(opcao != 0){
        menu_biblioteca(); //Menu inicial
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarlivro(livros, &num_livros);
                break;
            case 2:
                printf("Listar livros (ainda nao implementado)\n");
                break;
            case 3:
                cadastrar_usuario();
                break;
            case 4:
                // Menu Principal -> Cadastro de livros, leitores e zona de empréstimos
                menu_principal(livros, &num_livros, leitores, &num_leitores, emprestimos, &num_emprestimos);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }
}

int main() {
    executar();
    return 0;
}