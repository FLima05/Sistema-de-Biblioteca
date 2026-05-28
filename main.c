#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char nome[50];
	char email[50];
	char senha[50];
} usuario;

void menu_biblioteca() {
	
	printf("\n=================================\n       SISTEMA BIBLIOTECA\n=================================");
	printf("\n1 - Cadastrar livros\n");
	printf("2 - Listar livros\n");
	printf("3 - Cadastrar usuário\n");
	printf("4 - Listar usuários com empréstimos\n");
	printf("5 - realizar empréstimo\n");
	printf("6 - realizar devolução\n");
	printf("0 - Sair\n");

}

void cadastrar_usuario() {
	
	usuario u; // chamando a struct usuario para criar uma variável do tipo usuario

	printf("Digite o nome do usuário: ");
	scanf(" %49[^\n]", u.nome);
	printf("Digite o email do usuário: ");
	scanf(" %49[^\n]", u.email);
	printf("Digite a senha do usuário: ");
	scanf(" %49[^\n]", u.senha);

}

void executar() {

	int opcao = -1;

	while(opcao != 0) {

		menu_biblioteca();
		scanf("%d", &opcao);

		switch(opcao) {
			case 1:
				printf("Cadastrar livros\n");
				break;
			case 2:
				printf("Listar livros\n");
				break;
			case 3:
				cadastrar_usuario();
				break;
			case 4:
				printf("Listar usuários com empréstimos\n");
				break;
			case 5:
				printf("realizar empréstimo\n");
				break;
			case 6:
				printf("realizar devolução\n");
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