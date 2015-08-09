#ifndef EIGHTXP_H_INCLUDED
#define EIGHTXP_H_INCLUDED

#include "instruction.h"

void ft_append_instruction(s_instruction **list, s_instruction *elem);
int ft_fread(unsigned char *buf, int size, FILE *f);
unsigned char *ft_8xp_read_code(char *file, int *code_length);
s_instruction *ft_8xp_parse_code(unsigned char *raw_code, int code_length);

#endif
