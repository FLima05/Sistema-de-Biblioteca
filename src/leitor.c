#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/leitor.h"

leitor leitores[MAX_LEITORES];
int num_leitores = 0;
int proximo_leitor_id = 1;

// Função para salvar os leitores em um arquivo de texto
void salvar_leitores() {
    FILE *fp = fopen("../data/leitores.txt", "w");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de leitores!\n");
        return;
    }
    fprintf(fp, "%d\n", num_leitores);
    fprintf(fp, "%d\n", proximo_leitor_id);
    for(int i = 0; i < num_leitores; i++) {
        fprintf(fp, "%s | %s | %s | %s\n",
            leitores[i].nome,
            leitores[i].email,
            leitores[i].telefone,
            leitores[i].cpf);
    }
    fclose(fp);
    printf("Dados de leitores salvos com sucesso.");
}

// Função para carregar os leitores por um arquivo de texto
void carregar_leitores() {
    FILE *fp = fopen("data/leitores.txt", "r");
    if (!fp) {
        printf("Nenhum arquivo de leitores encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fscanf(fp, "%d", &num_leitores);
    fscanf(fp, "%d", &proximo_leitor_id);
    for (int i = 0; i < num_leitores; i++){
        fscanf(fp, "%s | %s | %s | %s", 
            leitores[i].nome,
            leitores[i].email,
            leitores[i].telefone,
            leitores[i].cpf);
    }
    fclose(fp);
    printf("Dados de leitores carregados: %d encontrado(s).\n", num_leitores);
}

// Função para cadastrar leitores
void cadastrarleitor() {
    if (num_leitores >= MAX_LEITORES) {
        printf("Limite de leitores atingido. \n");
        return;
    }
    
    leitor novo_leitor; 
    novo_leitor.id_leitor = proximo_leitor_id;

    printf("Nome: ");
    scanf(" %[^\n]", novo_leitor.nome);
    printf("Email: ");
    scanf(" %[^\n]", novo_leitor.email);
    printf("Telefone: ");
    scanf(" %[^\n]", novo_leitor.telefone);
    printf("CPF: ");
    scanf(" %[^\n]", novo_leitor.cpf);
    
    leitores[num_leitores] = novo_leitor;
    num_leitores++;
    proximo_leitor_id++;
    salvar_leitores();
    
    printf("Leitor cadastrado com sucesso. ID: %d\n", novo_leitor.id_leitor);
}

int main(){

    cadastrarleitor();

    return 0;
}