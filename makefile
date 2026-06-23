.DEFAULT_GOAL := compile_all
.PHONY = start compile_all delete clear compile_individual

BINARY_NAME := Clubresco
SOURCE_FILES := $(wildcard *.c) $(wildcard sources/*.c)
HEADER_INCLUDE_PATH := -I headers/
OBJECTS_DIR := objects
OBJECT_FILES := $(patsubst %.c, $(OBJECTS_DIR)/%.o, $(notdir $(SOURCE_FILES)))

C_COMPILER := gcc 
WARNING_FLAGS := -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=4 -Wwrite-strings -Waggregate-return -Wcast-qual 

vpath %.c sources:.

compile_all: $(BINARY_NAME)

$(BINARY_NAME): $(OBJECT_FILES)
	@echo "Vinculando objetos no executável $(BINARY_NAME)...\n" 
	$(C_COMPILER) $(WARNING_FLAGS) $(HEADER_INCLUDE_PATH) $(OBJECT_FILES) -o $(BINARY_NAME)

$(OBJECTS_DIR)/%.o: %.c | $(OBJECTS_DIR)
	@echo "Compilando $< como arquivo objeto...\n"
	$(C_COMPILER) $(WARNING_FLAGS) $(HEADER_INCLUDE_PATH) -c $< -o $@

compile_individual: $(SOURCE_FILES)
	@echo "Compilando cada arquivo de origem como um executável individual...\n"
	@for file in $(SOURCE_FILES); do \
		exec_name=$$(basename $$file .c); \
		$(C_COMPILER) $(WARNING_FLAGS) $(HEADER_INCLUDE_PATH) $$file -o $$exec_name; \
	done

start:
	@echo "Inicializando projeto $(BINARY_NAME)\n"
	@mkdir -p sources headers $(OBJECTS_DIR)
	@touch main.c
	@echo "Processo finalizado!\n"

delete:
	@read -p "Digite 'finalizar' para confirmar: " confirm; \
	if [ "$$confirm" = "finalizar" ]; then \
		read -p "Digite o nome do diretório atual: " dir; \
		cp makefile .. ; \
		cd .. && rm -rf "$$dir"; \
	elif [ "$$confirm" != "finalizar" ]; then \
		echo "Operação cancelada\n"; \
	fi

clear: 
	@echo "Ambiente de trabalho limpo\n"
	@rm -f $(BINARY_NAME) $(OBJECTS_DIR)/*.o
	@rm -f $(notdir $(SOURCE_FILES:.c=))

$(OBJECTS_DIR):
	@mkdir -p $(OBJECTS_DIR)
