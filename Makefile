
#=== VARIABLES ===
NAME = a.out
INC_DIR = incs/
SRCS_DIR = srcs/
SRCS =	main.c utils.c token.c 8xp.c 8xp_parse.c instruction.c vm_functions.c vm.c
OBJ = $(SRCS:.c=.o)
OBJ_DIR = obj/
INCLUDE =
LIBS = -lm

CC = gcc
CFLAGS = -g -Wall -Wextra -fdiagnostics-color=auto -I $(INC_DIR) $(INCLUDE) #-pedantic

#=== SPECIAL ===
.PHONY: all, clean, mrproper, re, cls
.SUFFIXES:

#=== REGLES BINAIRES ===
all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJ))
	@echo "building app"
	@$(CC) $(CFLAGS) $(LIBS) $^ -o $@

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC_DIR)%.h
	@echo "building $@"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)main.o: $(SRCS_DIR)main.c
	@echo "building $@"
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

#=== REGLES SPECIALES ===
clean:
	@echo "cleaning directory (*.obj)"
	@rm -f $(addprefix $(OBJ_DIR), $(OBJ))

mrproper: clean
	@echo "cleaning directory (app + *.obj)"
	@rm -f $(NAME)

re: mrproper all
	@echo "re"

