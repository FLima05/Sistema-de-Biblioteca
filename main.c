#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 100
#define MAX_LEITORES 100
#define MAX_EMPRESTIMOS 100

typedef struct {
    int id;
    char nome[50];
    char email[50];
    char senha[50];
} ADMIN;

typedef struct {
    
    int id_livro;
    char data_publicacao[50];
    char titulo[100];
    char editora[50];
    int disponivel;
    char idioma[50];
    char autor[100];
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

//////////////////////////////////////////////// CADASTRO DE LIVROS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

// Função para salvar os livros em um arquivo de texto
void salvar_livro(livro novo_livro) {
    FILE *Cadastro_livros;

    Cadastro_livros = fopen("Cadastro_livros.txt", "a");

    if(!Cadastro_livros) {
        printf("ERRO: Nao foi possivel salvar o arquivo de livros!\n");
        return;
    }

    fprintf(
        Cadastro_livros,
        "ID: %05d| Livro: %s| Autor: %s| Editora: %s| Data de pub: %s| Disponivel: %d|\n",
        novo_livro.id_livro,
        novo_livro.titulo,
        novo_livro.autor,
        novo_livro.editora,
        novo_livro.data_publicacao,
        novo_livro.disponivel
    );

    fclose(Cadastro_livros);
    printf("Livro cadastrado com sucesso. ID: %05d\n", novo_livro.id_livro);
}

////////////////////////////////// CADASTRO DE LIVROS (MAURICIO) /////////////////

void cadastrarlivro(livro *livros, int *num_livros) {
    if (*num_livros >= MAX_LIVROS) {
        printf("Limite de livros atingido. \n");
        return;
    }
    
    livro novo_livro;
    novo_livro.id_livro = *num_livros + 1;
    printf("Titulo: ");
    scanf(" %99[^\n]", novo_livro.titulo);
    printf("Autor: ");
    scanf(" %99[^\n]", novo_livro.autor);
    printf("Editora: ");
    scanf (" %49[^\n]", novo_livro.editora);
    printf("Data de publicacao: ex(10/10/2008): ");
    scanf (" %49[^\n]", novo_livro.data_publicacao);
    printf("Quantidade de livros: ");
    scanf("%d", &novo_livro.disponivel);
    
    salvar_livro(novo_livro);
    
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
    scanf(" %99[^\n]", novo_leitor.nome);
    printf("Email: ");
    scanf(" %99[^\n]", novo_leitor.email);
    printf("Telefone: ");
    scanf(" %19[^\n]", novo_leitor.telefone);
    printf("CPF: ");
    scanf(" %19[^\n]", novo_leitor.cpf);
    
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

////////////////////////////////// LISTAR LIVROS ////////////////////////////////////////////////////////

void listar_livros(){
    
    livro listar_livros;

    FILE *fp = fopen("Cadastro_livros.txt", "r");
    rewind(fp);
    if (!fp) { 
        printf("Nenhum arquivo de livros encontrado. Iniciando com banco vazio.\n");
        return;
    }

    printf("Deseja Procurar por um livro especifico? (S/N): ");
    char resposta;
    scanf(" %c", &resposta);

    if(resposta == 'S' || resposta == 's') {
        char titulo_procurado[100];
        printf("Digite o titulo do livro: ");
        scanf(" %99[^\n]", titulo_procurado);
        int encontrado = 0;

        while (fscanf(fp, "ID: %d| Livro: %99[^|]| Autor: %99[^|]| Editora: %49[^|]| Data de pub: %49[^|]| Disponivel: %d|\n",
                   &listar_livros.id_livro, listar_livros.titulo, listar_livros.autor, listar_livros.editora, listar_livros.data_publicacao, &listar_livros.disponivel) == 6) {
            if (strcmp(listar_livros.titulo, titulo_procurado) == 0) {
                printf("\n==============================\n");
                printf("ID: %d\n", listar_livros.id_livro);
                printf("Titulo: %s\n", listar_livros.titulo);
                printf("Autor:  %s\n", listar_livros.autor);
                printf("Editora: %s\n", listar_livros.editora);
                printf("Data de publicacao: %s\n", listar_livros.data_publicacao);
                printf("Disponivel: %d\n", listar_livros.disponivel);
                printf("------------------------------\n");
                encontrado = 1;
            }
        }

        if (!encontrado) {
            printf("Livro com o titulo '%s' nao encontrado.\n", titulo_procurado);
        }
    } else {

    while (fscanf(fp, "ID: %d| Livro: %99[^|]| Autor: %99[^|]| Editora: %49[^|]| Data de pub: %49[^|]| Disponivel: %d|\n",
               &listar_livros.id_livro, listar_livros.titulo, listar_livros.autor, listar_livros.editora, listar_livros.data_publicacao, &listar_livros.disponivel) == 6) {
        
        printf("\n==============================\n");
        printf("ID: %d\n", listar_livros.id_livro);
        printf("Titulo: %s\n", listar_livros.titulo);
        printf("Autor:  %s\n", listar_livros.autor);
        printf("Editora: %s\n", listar_livros.editora);
        printf("Data de publicacao: %s\n", listar_livros.data_publicacao);
        printf("Disponivel: %d\n", listar_livros.disponivel);
        printf("------------------------------\n");
    }
    fclose(fp);
    }
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

void salvar_ADMIN(ADMIN adm) {

    FILE *ADMLIST = fopen("admin.txt", "a+");
    if (!ADMLIST) {
        printf("ERRO: Nao foi possivel salvar o arquivo de administradores!\n");
        return;
    }
    
    fprintf(ADMLIST, "%d;%s;%s;%s\n", adm.id, adm.nome, adm.email, adm.senha);
    fclose(ADMLIST);
}

 void cadastrar_ADMIN() {
    
    ADMIN adm;
    printf("Digite o nome do administrador: ");
    scanf(" %49[^\n]", adm.nome);
    printf("Digite o email do administrador: ");
    scanf(" %49[^\n]", adm.email);
    printf("Digite a senha do administrador: ");
    scanf(" %49[^\n]", adm.senha);
    adm.id = 1;
    salvar_ADMIN(adm);

    printf("Administrador cadastrado com sucesso.\n");
}

int validar_ADMIN() {
    char email[50];
    char senha[50];
    
    printf("Email: ");
    scanf(" %49[^\n]", email);
    printf("Senha: ");
    scanf(" %49[^\n]", senha);
    
    FILE *ADMLIST = fopen("admin.txt", "r");
    if (!ADMLIST) {
        printf("ERRO: Nao foi possivel abrir o arquivo de administradores!\n");
        return 0;
    }
    
    ADMIN adm;
    while (fscanf(ADMLIST, "%d;%49[^;];%49[^;];%49[^\n]", &adm.id, adm.nome, adm.email, adm.senha) == 4) {
        if (strcmp(adm.email, email) == 0 && strcmp(adm.senha, senha) == 0) {
            fclose(ADMLIST);
            printf("Autenticacao bem-sucedida. Bem-vindo, %s!\n", adm.nome);
            return 1; // Autenticacao bem-sucedida
        }
    }
    
    fclose(ADMLIST);
    return 0; // Autenticacao falhou
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

////////////////////////////////////////////////// MÓDULO DE RELATÓRIOS //////////////////////////////////////////////////

// 1. Relatório geral de livros
void relatorio_livros(livro *livros, int num_livros) {
    if (num_livros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("\n==============================\n");
    printf("     RELATÓRIO GERAL DE LIVROS\n");
    printf("==============================\n");
    printf("Total de livros: %d\n\n", num_livros);

    for (int i = 0; i < num_livros; i++) {
        printf("ID: %d\n", livros[i].id_livro);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor:  %s\n", livros[i].autor);
        printf("Status: %s\n", livros[i].disponivel == 'S' ? "Disponivel" : "Emprestado");
        printf("------------------------------\n");
    }
}

// 2. Relatório de livros disponíveis
void relatorio_livros_disponiveis(livro *livros, int num_livros) {
    printf("\n==============================\n");
    printf("    LIVROS DISPONÍVEIS\n");
    printf("==============================\n");

    int count = 0;
    for (int i = 0; i < num_livros; i++) {
        if (livros[i].disponivel == 'S') {
            printf("ID: %d | Titulo: %s | Autor: %s\n",
                   livros[i].id_livro, livros[i].titulo, livros[i].autor);
            count++;
        }
    }

    if (count == 0) printf("Nenhum livro disponivel no momento.\n");
    else printf("\nTotal disponivel: %d\n", count);
}

// 3. Relatório de livros emprestados
void relatorio_livros_emprestados(livro *livros, int num_livros,
                                   emprestimo *emprestimos, int num_emprestimos,
                                   leitor *leitores, int num_leitores) {
    printf("\n==============================\n");
    printf("      LIVROS EMPRESTADOS\n");
    printf("==============================\n");

    int count = 0;
    for (int i = 0; i < num_livros; i++) {
        if (livros[i].disponivel == 'N') {
            // Busca o empréstimo ativo desse livro
            for (int j = 0; j < num_emprestimos; j++) {
                if (emprestimos[j].id_livro == livros[i].id_livro) {
                    // Busca o nome do leitor
                    char nome_leitor[100] = "Desconhecido";
                    for (int k = 0; k < num_leitores; k++) {
                        if (leitores[k].id_leitor == emprestimos[j].id_leitor) {
                            strcpy(nome_leitor, leitores[k].nome);
                            break;
                        }
                    }
                    printf("Livro: %s | Leitor: %s\n", livros[i].titulo, nome_leitor);
                    printf("Emprestado em: %s | Devolucao prevista: %s\n",
                           emprestimos[j].data_emprestimo, emprestimos[j].data_devolucao);
                    printf("------------------------------\n");
                    count++;
                    break;
                }
            }
        }
    }

    if (count == 0) printf("Nenhum livro emprestado no momento.\n");
    else printf("Total emprestado: %d\n", count);
}

// 4. Relatório de leitores cadastrados
void relatorio_leitores(leitor *leitores, int num_leitores) {
    if (num_leitores == 0) {
        printf("Nenhum leitor cadastrado.\n");
        return;
    }

    printf("\n==============================\n");
    printf("    RELATÓRIO DE LEITORES\n");
    printf("==============================\n");
    printf("Total de leitores: %d\n\n", num_leitores);

    for (int i = 0; i < num_leitores; i++) {
        printf("ID: %d | Nome: %s\n", leitores[i].id_leitor, leitores[i].nome);
        printf("Email: %s | Tel: %s | CPF: %s\n",
               leitores[i].email, leitores[i].telefone, leitores[i].cpf);
        printf("------------------------------\n");
    }
}

// 5. Relatório de empréstimos por leitor
void relatorio_por_leitor(emprestimo *emprestimos, int num_emprestimos,
                           leitor *leitores, int num_leitores,
                           livro *livros, int num_livros) {
    if (num_leitores == 0) {
        printf("Nenhum leitor cadastrado.\n");
        return;
    }

    printf("\n==============================\n");
    printf("  EMPRÉSTIMOS POR LEITOR\n");
    printf("==============================\n");

    for (int i = 0; i < num_leitores; i++) {
        int total = 0;
        printf("\nLeitor: %s (ID: %d)\n", leitores[i].nome, leitores[i].id_leitor);

        for (int j = 0; j < num_emprestimos; j++) {
            if (emprestimos[j].id_leitor == leitores[i].id_leitor) {
                char titulo[100] = "Desconhecido";
                for (int k = 0; k < num_livros; k++) {
                    if (livros[k].id_livro == emprestimos[j].id_livro) {
                        strcpy(titulo, livros[k].titulo);
                        break;
                    }
                }
                printf("  - Livro: %s | Emprestado: %s | Devolucao: %s\n",
                       titulo, emprestimos[j].data_emprestimo, emprestimos[j].data_devolucao);
                total++;
            }
        }

        if (total == 0) printf("  Nenhum emprestimo registrado.\n");
        else printf("  Total de emprestimos: %d\n", total);
        printf("------------------------------\n");
    }
}

// Menu do módulo de relatórios
void zona_relatorios(livro *livros, int num_livros,
                     leitor *leitores, int num_leitores,
                     emprestimo *emprestimos, int num_emprestimos) {
    int opcao = -1;
    while (opcao != 0) {
        printf("\n--- RELATÓRIOS ---\n");
        printf("1. Relatorio geral de livros\n");
        printf("2. Livros disponiveis\n");
        printf("3. Livros emprestados\n");
        printf("4. Leitores cadastrados\n");
        printf("5. Emprestimos por leitor\n");
        printf("0. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: relatorio_livros(livros, num_livros); break;
            case 2: relatorio_livros_disponiveis(livros, num_livros); break;
            case 3: relatorio_livros_emprestados(livros, num_livros, emprestimos, num_emprestimos, leitores, num_leitores); break;
            case 4: relatorio_leitores(leitores, num_leitores); break;
            case 5: relatorio_por_leitor(emprestimos, num_emprestimos, leitores, num_leitores, livros, num_livros); break;
            case 0: printf("Voltando...\n"); break;
            default: printf("Opcao invalida.\n"); break;
        }
    }
}

/////////////////////////////////// NÃO COLOCAR NENHUM PROCEDIMENTO À BAIXO DAQUI ///////////////////////////////////

void menu_principal(livro *livros, int *num_livros, leitor *leitores, int *num_leitores, emprestimo *emprestimos, int *num_emprestimos){
    int opcao = -1;
    while (opcao != 0) {
        printf("\n--- MENU DE GESTAO ---\n");
        printf("1. Cadastrar Livro \n");
        printf("2. Cadastrar Leitor \n");
        printf("3. Zona do Empréstimo \n");
        printf("0. Voltar \n");
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
                cadastrar_ADMIN();
                break;
            case 3:
                if (validar_ADMIN()) {
                    // Menu Principal -> Cadastro de livros, leitores e zona de empréstimos
                    menu_principal(livros, &num_livros, leitores, &num_leitores, emprestimos, &num_emprestimos);
                } else {
                    printf("Email ou senha incorretos.\n");
                }
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
