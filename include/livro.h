#ifndef LIVRO_H
#define LIVRO_H

#define MAX_LIVROS 100

typedef struct {
    int id_livro;
    char titulo[100];
    char autor[100];
    char disponivel;
} livro;

extern livro livros[MAX_LIVROS];
extern int num_livros;
extern int proximo_livro_id;

void cadastrarlivro();
void listar_livros();
void salvar_livro();
void carregar_livros();

#endif