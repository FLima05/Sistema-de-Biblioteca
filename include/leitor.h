#ifndef LEITOR_H
#define LEITOR_H

#define MAX_LEITORES 100

typedef struct {
    int id_leitor;
    char nome[100];
    char email[100];
    char telefone[20];
    char cpf[20];
} leitor;

extern leitor leitores[MAX_LEITORES];
extern int num_leitores;
extern int proximo_leitor_id;

void cadastrarleitor();
void salvar_leitores();
void carregar_leitores();

#endif
