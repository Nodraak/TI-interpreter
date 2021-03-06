
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "instruction.h"
#include "debug.h"
#include "8xp_parse.h"


s_param *ft_8xp_parse_number(s_token **tokens, int length)
{
    int i = 0, exponent = 0;
    s_param *ret = ft_calloc(sizeof(s_param));
    ret->type = PARAM_NUMBER;
    ret->number = 0;

    for (i = length-1; i >= 0; --i)
    {
        int n = ft_token_get_number(tokens[i]);

        if (n == -1) /* got a point, ie the number is a float */
        {
            ret->number *= pow(10, -exponent);
            exponent = 0;
        }
        else
            ret->number += n * pow(10, exponent);

        exponent += 1;
    }

    return ret;
}


s_param *ft_8xp_parse_str(s_token **tokens, int length)
{
    int i = 0, str_length = 0;
    s_param *ret = ft_calloc(sizeof(s_param));
    ret->type = PARAM_STR;

    i = 1; /* skip first T_TYPE_DOUBLE_QUOTES */
    while ((i < length) && (tokens[i]->type != T_TYPE_DOUBLE_QUOTES))
        i ++;
    str_length = i-1;

    if (i == length)
        ft_abort("SyntaxError: T_TYPE_DOUBLE_QUOTES not found");

    ret->str = ft_calloc(sizeof(char)*str_length);
    for (i = 1; i < str_length+1; ++i)
        ret->str[i-1] = tokens[i]->string[0];
    ret->str[i-1] = '\0';

    return ret;
}


s_param *ft_8xp_parse_var(s_token **tokens, int length)
{
    s_param *ret = NULL;
    ret = ft_calloc(sizeof(s_param));
    ret->type = PARAM_VAR;

    if (length != 1)
        ft_abort("ParserError: unexpected number of tokens");

    ret->var = ft_token_get_var(tokens[0]);

    return ret;
}


s_param *ft_8xp_parse_func(s_token **tokens, int length)
{
    if (length != 1)
        ft_abort("ParserError: unexpected number of tokens");

    return ft_8xp_parse_make_function(tokens[0], 0, NULL);
}


s_param *ft_8xp_parse_func_with_param(s_token *func, s_token **tokens, int length)
{
    s_param **av = NULL;

    /* if the tokens ends with T_TYPE_PARENTHESIS_CLOSE, remove it */
    if (tokens[length-1]->type == T_TYPE_PARENTHESIS_CLOSE)
        length --;

    if (length == 0) /* no args, just the function call */
    {
        return ft_8xp_parse_make_function(func, 0, NULL);
    }
    else /* there is at least one arg */
    {
        int i = 0, j = 0, nb_args = 0, arg_len = 0;

        /* count args */
        for (i = 0; i < length; ++i)
        {
            if (tokens[i]->type == T_TYPE_COMA)
                nb_args ++;
        }
        nb_args ++;

        /* get args */
        av = ft_calloc(sizeof(s_param*)*nb_args);
        j = 0;
        for (i = 0; i < nb_args; ++i)
        {
            arg_len = 0;
            while ((j < length) && (tokens[j]->type != T_TYPE_COMA))
                j ++, arg_len ++;

            if (arg_len == 0)
                ft_abort("SyntaxError: no argument found for a function requiring (at least) one");
            av[i] = ft_instruction_parse_tokens(tokens+j-arg_len, arg_len);
            j++;
        }

        return ft_8xp_parse_make_function(func, nb_args, av);
    }
}


s_param *ft_8xp_parse_op(s_token **tokens, int length, int index)
{
    s_param **av = NULL;
    int i = 0, j = 0, arg_len = 0;

    /* get args*/
    av = ft_calloc(sizeof(s_param*)*2);
    j = 0;
    for (i = 0; i < 2; ++i)
    {
        arg_len = 0;
        while ((j < length) && (j != index))
            j ++, arg_len ++;

        if (arg_len != 0)
        {
            av[i] = ft_instruction_parse_tokens(tokens+j-arg_len, arg_len);
        }
        else
        {
            if (tokens[index]->opcode[0] == T_OPCODE_FACT)
                return ft_8xp_parse_make_function(tokens[index], 1, av);
            else
                ft_abort("SyntaxError: no argument found for an operator requiring one");
        }

        j++;
    }

    return ft_8xp_parse_make_function(tokens[index], 2, av);
}


s_param *ft_8xp_parse_make_function(s_token *token, int ac, s_param **av)
{
    s_param *ret = NULL;
    s_function *function = NULL;

    /* function */
    function = ft_calloc(sizeof(s_function));
    function->callback = token->callback;
    function->name = strdup(token->string);
    function->ac = ac;
    function->av = av;

    /* ret */
    ret = ft_calloc(sizeof(s_param));
    ret->type = PARAM_FUNC;
    ret->function = function;

    return ret;
}
