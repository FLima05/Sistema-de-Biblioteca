#ifndef EMPRESTIMO_H
#define EMPRESTIMO_H

#define MAX_EMPRESTIMOS 100

typedef struct {
    int id_emprestimo;
    int id_leitor;
    int id_livro;
    char data_emprestimo[20];
    char data_devolucao[20];
} emprestimo;

extern emprestimo emprestimos[MAX_EMPRESTIMOS];
extern int num_emprestimos;
extern int proximo_emprestimo_id;

void cadastraremprestimo();
void emprestimo_ativo();
void emprestimo_devolucao();
void historico_emprestimo();
// void emprestimo_devolucao(livro *livros, int num_livros);
// void historico_emprestimo(emprestimo *emprestimos, int num_emprestimos, leitor *leitores, int num_leitores, livro *livros, int num_livros);
void salvar_emprestimos();
void carregar_emprestimos();


#endif