//#include <stdio.h>
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

livro livros[MAX_LIVROS];
int num_livros = 0;
int proximo_livro_id = 1;

typedef struct {
    int id_leitor;
    char nome[100];
    char email[100];
    char telefone[20];
    char cpf[20];
} leitor;

leitor leitores[MAX_LEITORES];
int num_leitores = 0;
int proximo_leitor_id = 1;

typedef struct {
    int id_emprestimo;
    int id_leitor;
    int id_livro;
    char data_emprestimo[20];
    char data_devolucao[20];
} emprestimo;

emprestimo emprestimos[MAX_EMPRESTIMOS];
int num_emprestimos = 0;
int proximo_emprestimo_id = 1;

//////////////////////////////////////////////// CADASTRO DE LIVROS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Função para salvar os livros em um arquivo de texto
void salvar_livro() {
    FILE *fp = fopen("data/livro.txt", "w");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de livros!\n");
        return;
    }
    fprintf(fp, "%d\n", num_livros);
    fprintf(fp, "%d\n", proximo_livro_id);
    fprintf(fp, "%d %s %s %c\n", 
            livros[num_livros].id_livro,
            livros[num_livros].titulo,
            livros[num_livros].autor,
            livros[num_livros].disponivel);
    fclose(fp);
}

// Função para carregar os livros por um arquivo de texto
void carregar_livros() {
    FILE *fp = fopen("data/livro.txt", "r");
    if (!fp) {
        printf("Nenhum arquivo de livros encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fread(&num_livros, sizeof(int), 1, fp);
    fread(&proximo_livro_id, sizeof(int), 1, fp);
    fread(livros, sizeof(livro), num_livros, fp);
    fclose(fp);
    printf("Dados de livros carregados: %d encontrado(s).\n", num_livros);
}

void cadastrarlivro() {
    if (num_livros >= MAX_LIVROS) {
        printf("Limite de livros atingido. \n");
        return;
    }
    
    livro novo_livro;
    novo_livro.id_livro = proximo_livro_id;

    printf("Titulo: ");
    scanf(" %[^\n]", novo_livro.titulo);
    printf("Autor: ");
    scanf(" %[^\n]", novo_livro.autor);
    novo_livro.disponivel = 'S'; // Ajustado para maiúsculo
    
    livros[num_livros] = novo_livro;
    num_livros++;
    proximo_livro_id++;
    salvar_livro();

    printf("Livro cadastrado com sucesso. ID: %d\n", novo_livro.id_livro);
    
    FILE *Cadastro_livros;

    Cadastro_livros = fopen("Cadastro_livros.txt", "a");

    if(Cadastro_livros != NULL){

    fprintf(
        Cadastro_livros,
        "ID: %d | Livro: %s | Autor: %s | Disponivel: %c |\n",
        novo_livro.id_livro,
        novo_livro.titulo,
        novo_livro.autor,
        novo_livro.disponivel
    );

    fclose(Cadastro_livros);

}
    
}

////////////////////////////////// LISTAR LIVROS ////////////////////////////////////////////////////////

void listar_livros(){
    
    FILE *Cadastro_livros;
    
    char linha[300];
    
    Cadastro_livros = fopen("Cadastro_livros.txt", "r");
    
    if(Cadastro_livros == NULL){
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    
    printf("\n=== LIVROS CADASTRADOS ===\n\n");
    
    while(fgets(linha, sizeof(linha), Cadastro_livros) != NULL){
        printf("%s", linha);
    }
    
    fclose(Cadastro_livros);
}

///////////////////////////////////////////////// CADASTRO DE LEITORES \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

// Função para salvar os leitores em um arquivo de texto
void salvar_leitores() {
    FILE *fp = fopen("data/leitor.txt", "w");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de leitores!\n");
        return;
    }
    fwrite(&num_leitores, sizeof(int), 1, fp);
    fwrite(&proximo_leitor_id, sizeof(int), 1, fp);
    fwrite(leitores, sizeof(leitor), num_leitores, fp);
    fclose(fp);
}

// Função para carregar os leitores por um arquivo de texto
void carregar_leitores() {
    FILE *fp = fopen("data/leitor.txt", "r");
    if (!fp) {
        printf("Nenhum arquivo de leitores encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fread(&num_leitores, sizeof(int), 1, fp);
    fread(&proximo_leitor_id, sizeof(int), 1, fp);
    fread(leitores, sizeof(leitor), num_leitores, fp);
    fclose(fp);
    printf("Dados de livros carregados: %d encontrado(s).\n", num_livros);
}

//////////////////////////////////////////// CADASTRO DE EMPRESTIMO //////////////////////////////////////

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

    emprestimos[*num_emprestimos] = novo_emprestimo;
    (*num_emprestimos)++;
    printf("Emprestimo cadastrado com sucesso. \n");
}

typedef struct {
    char nome[50];
    char email[50];
    char senha[50];
} usuario;

//////////////////////////////////////////////////// MENU INICIAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void menu_biblioteca() {
    printf("\n=================================\n        SISTEMA BIBLIOTECA\n=================================");
    printf("\n1 - Listar livros\n");
    printf("2 - Cadastrar usuário\n");
    printf("3 - Menu de Gestão (Empréstimos e Leitores)\n");
    printf("0 - Sair\n");
    printf("Opcao: ");
}

//////////////////////////////////////////////////// CADASTRAR USUÁRIO \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

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

/////////////////////////////////////// EM DESENVOLVIMENTO (Cristovão) \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void emprestimo_ativo(){ printf("Listando emprestimos ativos...\n"); }

/////////////////////////////////////// DEVOLUÇÃO \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void emprestimo_devolucao(livro *livros, int num_livros) {
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
////////////////////////////////////////////////////////// HISTÓRICO DE EMPRÉSTIMOS /////////////////////////////////////////////////
void historico_emprestimo(emprestimo *emprestimos, int num_emprestimos, leitor *leitores, int num_leitores, livro *livros, int num_livros) {
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

/////////////////////////////////////////////////// ZONA DE EMPRESTIMOS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

void zona_emprestimos(emprestimo *emprestimos, int *num_emprestimos, leitor *leitores, livro *livros, int num_leitores, int num_livros){
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
                cadastraremprestimo(emprestimos, num_emprestimos, leitores, livros, num_leitores, num_livros);
                break;
            case 2:
                emprestimo_ativo();
                break;
            case 3:
                // Atualizado para enviar os livros
                emprestimo_devolucao(livros, num_livros);
                break; 
            case 4:
                // Atualizado para enviar as três listas e cruzar os dados
                historico_emprestimo(emprestimos, *num_emprestimos, leitores, num_leitores, livros, num_livros);
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

///////////////////////////////////////////////// PERSISTÊNCIA DE DADOS /////////////////////////////////////////////



/////////////////////////////////// NÃO COLOCAR NENHUM PROCEDIMENTO À BAIXO DAQUI ///////////////////////////////////

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
                cadastrarlivro();
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

void executar() {
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
                listar_livros();
                break;
            case 2:
                cadastrar_usuario();
                break;
            case 3:
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
