#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "instruction.h"

void *ft_calloc(int size);
void _ft_abort(char *msg, char *file, int line);
void *memdup(void *data, int length);
void *ft_get_callback(s_token *token);

#define ft_abort(msg) _ft_abort(msg, __FILE__, __LINE__);

#endif
