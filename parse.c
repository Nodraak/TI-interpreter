
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "instruction.h"
#include "parse.h"

s_param *parse_int(s_token **tokens, int length)
{
    int i;
    s_param *ret = malloc(sizeof(s_param));
    ret->type = PARAM_INT;
    ret->n = 0;

    for (i = length-1; i >= 0; --i)
        ret->n += ((unsigned char)tokens[i]->opcode[0]-0x30) * pow(10, length-1-i);

    return ret;
}


s_param *parse_str(s_token **tokens, int length)
{
    (void)length; // todo: check overflow somewhere
    int i = 0, str_length = 0;
    s_param *ret = malloc(sizeof(s_param));
    ret->type = PARAM_STR;

    i = 1; // skip first "\""
    while (tokens[i]->opcode[0] != 0x2A)
        i ++;
    str_length = i-1;

    ret->str = malloc(sizeof(char)*str_length);
    for (i = 1; i < str_length+1; ++i)
        ret->str[i-1] = tokens[i]->string[0];
    ret->str[i-1] = '\0';

    return ret;
}


s_param *parse_var(s_token **tokens, int length)
{
    (void)length; // todo: check overflow somewhere
    s_param *ret = NULL;
    ret = malloc(sizeof(s_param));
    ret->type = PARAM_VAR;

    if ((tokens[0]->opcode[0] < 0x41) || (tokens[0]->opcode[0] > 0x5B)) // todo define opcode
    {
        printf("[parse_var] Unknown var\n");
        ret->var = VAR_A;
    }
    else
    {
        ret->var = tokens[0]->opcode[0] - 0x41; // todo define opcode
    }

    return ret;
}


s_param *parse_func(s_token **tokens, int length)
{
    if (length != 1)
        ft_abort("assert failed");

    return sparam_make_function(tokens[0], 0, NULL);
}


s_param *parse_func_with_param(s_token *func, s_token **tokens, int length)
{
    s_param **av = NULL;

    /* if the tokens ends with ")", remove it */
    if (tokens[length-1]->opcode[0] == 0x11) // todo define opcode
        length --;

    if (length == 0) /* no args, just the function call */
    {
        return sparam_make_function(func, 0, NULL);
    }
    else /* there is at least one arg */
    {
        int i = 0, j = 0, nb_args = 0, arg_len = 0;

        // count args
        for (i = 0; i < length; ++i)
        {
            if (tokens[i]->opcode[0] == 0x2B) // todo define opcode
                nb_args ++;
        }
        nb_args ++;

        // get args
        av = malloc(sizeof(s_param*)*nb_args);
        j = 0;
        for (i = 0; i < nb_args; ++i)
        {
            arg_len = 0;
            while ((j < length) && (tokens[j]->opcode[0] != 0x2B))
                j ++, arg_len ++;

            av[i] = ft_tokens_parse_tokens(tokens+j-arg_len, arg_len);
            j++;
        }

        return sparam_make_function(func, nb_args, av);
    }
}


s_param *parse_op(s_token **tokens, int length, int index)
{
    s_param **av = NULL;
    int i = 0, j = 0, arg_len = 0;

    // get args
    av = malloc(sizeof(s_param*)*2);
    j = 0;
    for (i = 0; i < 2; ++i)
    {
        arg_len = 0;
        while ((j < length) && (j != index))
            j ++, arg_len ++;

        av[i] = ft_tokens_parse_tokens(tokens+j-arg_len, arg_len);
        j++;
    }

    return sparam_make_function(tokens[index], 2, av);
}

