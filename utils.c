
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "instruction.h"
#include "utils.h"


void ft_abort(char *msg)
{
    fprintf(stderr, "Error: %s\n", msg);
    fprintf(stderr, "(Errno: %d %s)\n", errno, strerror(errno));
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
    char *ret = malloc(length*sizeof(char*));
    memcpy(ret, data, length*sizeof(char*));
    return ret;
}


s_param *sparam_make_function(s_token *token, int ac, s_param **av)
{
    s_param *ret = NULL;
    s_function *function = NULL;

    /* function */
    function = malloc(sizeof(s_function));
    function->callback = ft_get_callback(token);
    function->name = strdup(token->string);
    function->ac = ac;
    function->av = av;

    /* ret */
    ret = malloc(sizeof(s_param));
    ret->type = PARAM_FUNC;
    ret->function = function;

    return ret;
}


void *ft_get_callback(s_token *token)
{
    //printf("get callback %x\n", token->opcode[0]);
    switch (token->opcode[0])
    {
        // todo
    }
    return NULL;
}
