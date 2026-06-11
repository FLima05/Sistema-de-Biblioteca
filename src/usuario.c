#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuario.h"

usuario usuarios[MAX_USUARIOS];
int num_usuarios = 0;
int proximo_usuario_id = 1;

void salvar_usuarios() {
    FILE *fp = fopen("data/usuarios.txt", "w");
    if (!fp) {
        printf("ERRO: Nao foi possivel salvar o arquivo de usuarios!\n");
        return;
    }
    fprintf(fp, "%d\n", num_usuarios);
    fprintf(fp, "%d\n", proximo_usuario_id);
    for(int i = 0; i < num_usuarios; i++) {
        fprintf(fp, "%d | %s | %s | %s\n",
            usuarios[i].id_usuario,
            usuarios[i].nome,
            usuarios[i].email,
            usuarios[i].senha);
    }
    fclose(fp);
    printf("Dados de usuarios salvos com sucesso.");
}

// Função para carregar os usuarios por um arquivo de texto
void carregar_usuarios() {
    FILE *fp = fopen("data/usuarios.txt", "r");
    if (!fp) {
        printf("Nenhum arquivo de usuarios encontrado. Iniciando com banco vazio.\n");
        return;
    }
    fscanf(fp, "%d", &num_usuarios);
    fscanf(fp, "%d", &proximo_usuario_id);
    for (int i = 0; i < num_usuarios; i++){
        fscanf(fp, "%d | %s | %s | %s", 
            &usuarios[i].id_usuario,
            usuarios[i].nome,
            usuarios[i].email,
            usuarios[i].senha);
    }
    fclose(fp);
    printf("Dados de usuarios carregados: %d encontrado(s).\n", num_usuarios);
}

// Função para cadastrar um usuário (admin)
void cadastrar_usuario() {

    if (num_usuarios >= MAX_USUARIOS) {
        printf("Limite de usuarios atingido. \n");
        return;
    }

    usuario u;

    u.id_usuario = proximo_usuario_id;

    printf("Digite o nome do usuário: ");
    scanf(" %49[^\n]", u.nome);
    printf("Digite o email do usuário: ");
    scanf(" %49[^\n]", u.email);
    printf("Digite a senha do usuário: ");
    scanf(" %49[^\n]", u.senha);
    printf("Usuário cadastrado com sucesso.\n");

    usuarios[num_usuarios] = u;
    num_usuarios++;
    proximo_usuario_id++;
    salvar_usuarios();
}