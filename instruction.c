
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

void *ft_callback(s_param *av[])
{
    printf("in ft_callback\n");
    return NULL;
}


void *ft_get_callback(s_token *token)
{
    switch (token->opcode[0])
    {
        case 0x42:
            return ft_callback;
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

    // count args
    int i = 0, j = 0, nb_args = 0, arg_len = 0;
    for (i = 0; i < length; ++i)
    {
        if (tokens[i]->opcode[0] == 0x2B) // todo define opcode
            nb_args ++;
    }
    nb_args ++;

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
        /*else if tokens[0] == "\""
            return parse_str(tokens, length);
        else if tokens[0] == var
            return parse_var(tokens, length);
        else if tokens[0] == func
            return parse_func(tokens[0], tokens[1:], length-1);
        todo todo lots of todo
        */
        else
        {
            ft_abort("NotImplemented (token_type=%d) (todo or error ?)", tokens[0]->type);
            return NULL; /* silent warning */
        }
    }
    else
    {
        s_token *op = tokens[index];
        *(tokens[index]) = (s_token){{0x2B}, 0, TOKEN_OTHER, "[    ] ,"}; // todo define opcode
        return parse_func(op, tokens, length);
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
