#ifndef DEBUG_H_INCLUDED
#define DEBUG_H_INCLUDED

#include "instruction.h"

void printf_level_instruction(int level);
void print_tokens(s_token **tokens, int length, int level_instruction);
void ft_print_sparam(s_param *param, int level_instruction, int level);
void ft_print_code(s_instruction *ptr_code, int level_instruction);

#endif
