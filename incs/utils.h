#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "instruction.h"

void ft_abort(char *msg);
void *ft_calloc(int size);
void *memdup(void *data, int length);
s_param *sparam_make_function(s_token *token, int ac, s_param **av);
void *ft_get_callback(s_token *token);

#endif
