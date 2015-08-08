
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "instruction.h"
#include "token.h"


void *memdup(void *data, int length)
{
    char *ret = malloc(length*sizeof(char*));
    memcpy(ret, data, length*sizeof(char*));
    return ret;
}


s_param *parse_int(s_token **tokens, int length)
{
    int i;
    s_param *ret = malloc(sizeof(s_param));
    ret->type = PARAM_INT;
    ret->n = 0;

    for (i = length-1; i >= 0; --i)
        ret->n += (tokens[i]->opcode[0]-0x30) * pow(10, length-1-i);

    return ret;
}


s_param *parse_str(s_token **tokens, int length)
{
    // todo: check overflow somewhere
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


void *ft_callback(s_param *av[])
{
    printf("in ft_callback\n");
    return NULL;
}


void *ft_get_callback(s_token *token)
{
    printf("get callback %x\n", token->opcode[0]);
    switch (token->opcode[0])
    {
        // todo
    }
    return NULL;
}


s_param *parse_func(s_token *func, s_token **tokens, int length)
{
    s_param *ret = NULL;
    s_function *function = NULL;

    /* function */

    function = malloc(sizeof(s_function));
    function->callback = ft_get_callback(func);
    function->name = strdup(func->string);

    if (length == 0) /* no args, just the function call */
    {
        function->ac = 0;
        function->av = NULL;
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

        function->ac = nb_args;

        // get args
        function->av = malloc(sizeof(s_param*)*nb_args);
        j = 0;
        for (i = 0; i < nb_args; ++i)
        {
            arg_len = 0;
            while (j < length && tokens[j]->opcode[0] != 0x2B)
                j ++, arg_len ++;

            function->av[i] = ft_tokens_parse_tokens(tokens+j-arg_len, arg_len);
            j++;
        }
    }

    /* ret */

    ret = malloc(sizeof(s_param));
    ret->type = PARAM_FUNC;
    ret->function = function;

    return ret;
}

/******************************************************************************/

int ft_tokens_split_get_index(s_token **tokens, int length)
{
    int i = 0;
    int ret_index = -1;
    int ret_priority = -1;

    for (i = 0; i < length; ++i)
    {
        if ((tokens[i]->priority != 0) && (tokens[i]->priority > ret_priority))
        {
            ret_index = i;
            ret_priority = tokens[i]->priority;
        }

        if ((tokens[i]->type == TOKEN_FUNC) || (tokens[i]->opcode[0] == 0x10))  // todo define opcode (0x10 == "(")
        {
            do {
                i ++;
            } while ((i < length) && (tokens[i]->opcode[0] != 0x11));
        }
    }

    /* if nothing to split because only a function (maybe with arguments) */
    if (ret_index == -1 && tokens[0]->type == TOKEN_FUNC)
        return 0;

    return ret_index;
}


s_param *ft_tokens_parse_tokens(s_token **tokens, int length)
{
    int index = ft_tokens_split_get_index(tokens, length);

    if (index == -1)
    {
        if (tokens[0]->type == TOKEN_INT)
            return parse_int(tokens, length);
        else if (tokens[0]->opcode[0] == 0x2A) // todo define op "\""
            return parse_str(tokens, length);
        /*else if tokens[0] == var
            return parse_var(tokens, length);
        else if tokens[0] == func
            return parse_func(tokens[0], tokens[1:], length-1);
            other
        todo todo lots of todo
        */
        else
        {
            printf("NotImplemented (token_type=%d) (todo or error ?)\n", tokens[0]->type);
            s_param *ret = malloc(sizeof(s_param));
            ret->type = PARAM_INT;
            ret->n = 42;
            return ret;
        }
    }
    else
    {
        s_token *op = memdup(tokens[index], sizeof(s_token));
        *(tokens[index]) = (s_token){{0x2B}, 0, TOKEN_OTHER, "[    ] ,"}; // todo define opcode
        return parse_func(op, &tokens[1], length-1);
    }
}


s_instruction *ft_instruction_parse(s_token **tokens, int length)
{
    s_instruction *ret = NULL;

    ret = malloc(sizeof(s_instruction));
    ret->tokens = memdup(tokens, length);
    ret->tokens_length = length;
    ret->param = ft_tokens_parse_tokens(tokens, length);
    ret->next = NULL;

    return ret;
}
