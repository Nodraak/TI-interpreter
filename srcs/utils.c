
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "instruction.h"
#include "utils.h"


void _ft_abort(char *msg, char *file, int line)
{
    fprintf(stderr, "In %s:%d\n", file, line);
    fprintf(stderr, "Error: %s\n", msg);
    fprintf(stderr, "(Errno: %d - %s)\n", errno, strerror(errno));
    exit(1);
}


void *ft_calloc(int size)
{
    void *ret = calloc(1, size);
    if (ret == NULL)
        ft_abort("malloc");
    return ret;
}


void *memdup(void *data, int length)
{
    char *ret = ft_calloc(length*sizeof(char*));
    memcpy(ret, data, length*sizeof(char*));
    return ret;
}


void *ft_get_callback(s_token *token)
{
    printf("get callback for %x - %s\n", token->opcode[0], token->string);
    switch (token->opcode[0])
    {
        // todo
    }
    return NULL;
}
