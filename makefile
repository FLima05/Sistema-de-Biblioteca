## MAKEFILE DO PROJETO ##

# --------- Compilador e flags ---------
CC = gcc
CFLAGS = -Wall -Wextra -I./include

# --------- Diretórios ---------
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
DATA_DIR = data

# --------- Executável ---------
TARGET = $(BUILD_DIR)/main

# --------- Fontes ---------
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/emprestimo.c \
       $(SRC_DIR)/leitor.c \
       $(SRC_DIR)/livro.c \
       $(SRC_DIR)/menu.c \
       $(SRC_DIR)/usuario.c

# --------- Converte cada .C em um .O correspondente ---------
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# --------- Headers ---------
HEADERS = $(INCLUDE_DIR)/emprestimo.h $(INCLUDE_DIR)/leitor.h $(INCLUDE_DIR)/livro.h $(INCLUDE_DIR)/menu.h $(INCLUDE_DIR)/usuario.h

## REGRAS ##

# ---------- Regra principal (execução com 'make' ou 'mingw32-make') ---------
all: $(BUILD_DIR) $(DATA_DIR) $(TARGET)
	@echo "Compilacao concluida com sucesso!"

# ---------- Regra para criar o diretório build (caso não exista) ---------
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# ---------- Regra para criar o diretório data (caso não exista) ---------
$(DATA_DIR):
	mkdir -p $(DATA_DIR)

# ---------- Regra para conectar os .O e criar o executável ---------
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Executavel criado: $@"

# ---------- Regra para compilar os arquivos .C em .O ---------
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado: $<"

# ---------- Regra para limpar os arquivos compilados ---------
clean:
	rm -rf $(BUILD_DIR) $(DATA_DIR)
	@echo "Build removida!"

# ---------- Regra para rodar o programa (após compilar) ---------
run: all
	$(TARGET)

# ---------- Regra para mostrar informações ---------
info:
	@echo === INFORMACOES DO PROJETO ===
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Diretorio de origem: $(SRC_DIR)"
	@echo "Diretorio de data: $(DATA_DIR)"
	@echo "Diretorio de build: $(BUILD_DIR)"

# --------- Declaração de alvos que não correspondem a arquivos ---------
.PHONY: all clean run info