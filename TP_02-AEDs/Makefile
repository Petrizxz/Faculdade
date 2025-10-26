# ================================
# CONFIGURAÇÕES BÁSICAS
# ================================

# Compilador a ser usado
CC = gcc

# Flags de compilação:
CFLAGS = -Wall -Wextra -g \
         -IModel_TAD_Drone \
         -IModel_TAD_Galpao \
         -IModel_TAD_Lista_Pacote \
         -IModel_TAD_Combinacao \
         -IModel_TAD_Pacote

# Lista de todos os arquivos fonte (.c) do projeto
SRCS = main.c \
       Model_TAD_Drone/TAD_Drone.c \
       Model_TAD_Galpao/TAD_Galpao.c \
       Model_TAD_Lista_Pacote/TAD_Lista_Pacotes.c \
       Model_TAD_Combinacao/TAD_Combinacao.c \
       Model_TAD_Pacote/TAD_Pacote.c

# Gera a lista de objetos (.o) automaticamente
OBJS = $(SRCS:.c=.o)

# ================================
# SUPORTE MULTIPLATAFORMA
# ================================

ifeq ($(OS),Windows_NT)
    TARGET = tp02.exe
    RM = del /Q 2>nul
    FIXPATH = $(subst /,\,$1)
    RUN_CMD = .\$(TARGET)
else
    TARGET = tp02
    RM = rm -f
    FIXPATH = $1
    RUN_CMD = ./$(TARGET)
endif

# ================================
# REGRAS DE COMPILAÇÃO
# ================================

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(call FIXPATH,$(OBJS)) $(call FIXPATH,$(TARGET))

run: $(TARGET)
	$(RUN_CMD)

debug: $(TARGET)
ifeq ($(OS),Windows_NT)
	gdb $(TARGET)
else
	gdb ./$(TARGET)
endif

.PHONY: all clean run debug