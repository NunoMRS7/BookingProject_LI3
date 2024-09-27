# Especifica a diretoria onde os arquivos de cabeçalho estão localizados
IDIR = include
# Especifica o compilador a ser utilizado
CC = gcc

# Flags do compilador
CFLAGS = -g -Wall -Wextra -pedantic -O2 -I$(IDIR) $(shell pkg-config --cflags glib-2.0)

# Alvo padrão
all: main testes

# Especifica o diretoria onde os arquivos .o serão armazenados
ODIR = src/obj

# Bibliotecas a serem vinculadas ao programa
LIBS = -lm -lcurses $(shell pkg-config --libs glib-2.0)

# Encontra todos os arquivos de cabeçalho no diretoria 'include'
DEPS = $(wildcard $(IDIR)/*.h)

# Gera uma lista de arquivos de objeto a partir de arquivos de origem no diretoria 'src'
OBJ = $(patsubst src/%.c, $(ODIR)/%.o, $(wildcard src/*.c))

$(info $$OBJ is [${OBJ}])

# Constrói o executável
$(ODIR)/%.o: src/%.c $(DEPS)
	mkdir -p $(ODIR)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compila os ficheiros num executável chamado 'programa-principal'
main: $(OBJ)
	$(CC) -o programa-principal $^ $(CFLAGS) $(LIBS)

# Compila os ficheiros num executável chamado 'programa-testes'
testes: $(OBJ)
	$(CC) -o programa-testes $^ $(CFLAGS) $(LIBS)

# Informa o make que o alvo clean não representa um arquivo real,
# mas sim uma ação de limpeza
.PHONY: clean

# Limpa os arquivos gerados
clean:
	rm -f $(ODIR)/*.o programa-*
	rm -f Resultados/*.txt
	rm -f Resultados/*.csv