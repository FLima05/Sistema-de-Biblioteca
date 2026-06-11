#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/livro.h"

livro livros[MAX_LIVROS];
int num_livros = 0;
int proximo_livro_id = 1;

// Função para salvar os livros em um arquivo de texto
void salvar_livro() {
    FILE *fp = fopen("data/livros.txt", "w");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de livros!\n");
        return;
    }
    fprintf(fp, "%d\n", num_livros);
    fprintf(fp, "%d\n", proximo_livro_id);
    for(int i = 0; i < num_livros; i++) {
        fprintf(fp, "%d | %s | %s | %c\n",
            livros[i].id_livro,
            livros[i].titulo,
            livros[i].autor,
            livros[i].disponivel);
    }
    fclose(fp);
    printf("Dados de livros salvos com sucesso.");
}

// Função para carregar os livros por um arquivo de texto
void carregar_livros() {
    FILE *fp = fopen("data/livros.txt", "r");
    if (!fp) {
        printf("Nenhum arquivo de livros encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fscanf(fp, "%d", &num_livros);
    fscanf(fp, "%d", &proximo_livro_id);
    for (int i = 0; i < num_livros; i++){
        fscanf(fp, "%d | %s | %s | %c", 
            &livros[i].id_livro,
            livros[i].titulo,
            livros[i].autor,
            &livros[i].disponivel);
    }
    fclose(fp);
    printf("Dados de livros carregados: %d encontrado(s).\n", num_livros);
}

// Função para cadastrar livros
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
}

// Função para listar os livros cadastrados
void listar_livros(){
    if (num_livros == 0){
        printf("Não há livros cadastrados no momento.");
    }

    printf("\n=== LIVROS CADASTRADOS ===\n");
    for(int i = 0; i < num_livros; i++){
        printf("%d | %s | %s | %c\n",
            livros[i].id_livro,
            livros[i].titulo,
            livros[i].autor,
            livros[i].disponivel);
    }
}

// int main(){

//     cadastrarlivro();
//     listar_livros();

//     return 0;
// }