
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "instruction.h"
#include "vm_functions.h"
#include "utils.h"


void _ft_abort(char *msg, const char *file, const char *func, int line)
{
    fprintf(stderr, "In %s:%d - %s\n", file, line, func);
    fprintf(stderr, "Error: %s\n", msg);
    fprintf(stderr, "(Errno: %d - %s)\n", errno, strerror(errno));
    exit(1);
}


void *ft_calloc(int size)
{
    void *ret = calloc(1, size);
    if (ret == NULL)
        ft_abort("ParserError: malloc failed");
    return ret;
}


void *memdup(void *data, int length)
{
    char *ret = ft_calloc(length*sizeof(char*));
    memcpy(ret, data, length*sizeof(char*));
    return ret;
}


int ft_fread(unsigned char *buf, int size, FILE *f)
{
    int ret = fread((char*)buf, 1, size, f);
    buf[ret] = '\0';
    return ret;
}
