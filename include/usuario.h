#ifndef USUARIO_H
#define USUARIO_H

#define MAX_USUARIOS 100

typedef struct {
    int id_usuario;
    char nome[50];
    char email[50];
    char senha[50];
} usuario;

extern usuario usuarios[MAX_USUARIOS];
extern int num_usuarios;
extern int proximo_usuario_id;

void cadastrar_usuario(); 

#endif