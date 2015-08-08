#ifndef EIGHTXP_H_INCLUDED
#define EIGHTXP_H_INCLUDED

#include "instruction.h"

int ft_fread(char *buf, int size, FILE *f);
char *ft_8xp_read_code(char *file, int *code_length);
s_instruction *ft_8xp_parse_code(char *raw_code, int code_length);

#endif
