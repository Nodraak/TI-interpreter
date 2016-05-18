#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include "instruction.h"

void *ft_calloc(int size);
void _ft_abort(char *msg, const char *file, const char *func, int line);
void *memdup(void *data, int length);
int ft_fread(unsigned char *buf, int size, FILE *f);

#define ft_abort(msg) _ft_abort(msg, __FILE__, __FUNCTION__, __LINE__);

#endif
