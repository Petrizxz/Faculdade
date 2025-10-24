# ================================
# CONFIGURAÇÕES BÁSICAS
# ================================

# Compilador a ser usado
CC = gcc

# Flags de compilação:
# -Wall   → ativa todos os avisos básicos
# -Wextra → ativa avisos adicionais
# -g      → gera informações de debug (para usar no gdb)
# -I<dir> → adiciona diretórios onde o compilador vai procurar os .h
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
# Exemplo: main.c → main.o, Model_TAD_Drone/TAD_Drone.c → Model_TAD_Drone/TAD_Drone.o
OBJS = $(SRCS:.c=.o)

# ================================
# SUPORTE MULTIPLATAFORMA
# ================================

# Detecta o sistema operacional:
# No Windows (cmd/PowerShell/MinGW/MSYS2) a variável de ambiente $(OS) é "Windows_NT"
# No Linux/Mac/WSL, $(OS) não é definida, então entra no "else"
ifeq ($(OS),Windows_NT)
    # Nome do executável no Windows precisa de ".exe"
    TARGET = tp01.exe
    
    # Comando para remover arquivos no Windows
    # "del /Q" = delete quiet (sem pedir confirmação)
    RM = del /Q
    
    # Converte caminhos para o formato do Windows ( \ em vez de / )
    # Necessário porque "del" não entende "/"
    FIXPATH = $(subst /,\,$1)
else
    # No Linux/Mac/WSL o executável não precisa de extensão
    TARGET = tp01
    
    # Comando para remover arquivos no Linux/Mac/WSL
    RM = rm -f
    
    # No Linux não precisa mexer nos caminhos
    FIXPATH = $1
endif

# ================================
# REGRAS DE COMPILAÇÃO
# ================================

# Regra padrão: quando rodar "make", ele chama o alvo $(TARGET)
all: $(TARGET)

# Como gerar o executável final:
# - depende de todos os objetos (.o)
# - usa o compilador para juntar (linkar) tudo em $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

# Regra genérica para compilar .c em .o:
# - "%": coringa (qualquer nome de arquivo)
# - $< = arquivo de entrada (o .c)
# - $@ = arquivo de saída (o .o)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ================================
# REGRAS ÚTEIS
# ================================

# "make clean" → remove todos os objetos e o executável
# - Usa $(RM), que muda dependendo do sistema
# - Usa $(call FIXPATH,...) para corrigir caminhos no Windows
clean:
	$(RM) $(call FIXPATH,$(OBJS)) $(call FIXPATH,$(TARGET))

# "make run" → compila e executa o programa
# - Garante que o executável exista chamando $(TARGET) antes
# - No Linux: "./tp01"
# - No Windows: "tp01.exe"
run: $(TARGET)
	./$(TARGET)

# ================================
# DEBUG
# ================================

# "make debug" → compila e abre o GDB para depuração
# - No Linux/Mac/WSL: gdb ./tp01
# - No Windows (MinGW/MSYS2): gdb tp01.exe
debug: $(TARGET)

ifeq ($(OS),Windows_NT)
	gdb $(TARGET)
else
	gdb ./$(TARGET)
endif

# Indica que "all", "clean", "run" e "debug" não são arquivos reais
.PHONY: all clean run debug
