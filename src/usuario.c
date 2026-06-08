#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/usuario.h"

usuario usuarios[MAX_USUARIOS];
int num_usuarios = 0;
int proximo_usuario_id = 1;

// Função para cadastrar um usuário (admin)
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