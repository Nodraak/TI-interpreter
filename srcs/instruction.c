
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "token.h"
#include "8xp_parse.h"
#include "instruction.h"


int ft_instruction_split_tokens_by_priority(s_token **tokens, int length)
{
    int i = 0;
    int ret_index = -1;
    int ret_priority = 100;

    for (i = 0; i < length; ++i)
    {
        if ((tokens[i]->priority != 0) && (tokens[i]->priority < ret_priority))
        {
            ret_index = i;
            ret_priority = tokens[i]->priority;
        }

        /* discard instructions inside parenthesis or a function */
        if ((tokens[i]->type == TOKEN_FUNC_WITH_PARAM) || (tokens[i]->type == TOKEN_PARENTHESIS_OPEN))
        {
            do {
                i ++;
            } while ((i < length) && (tokens[i]->type != TOKEN_PARENTHESIS_CLOSE));
        }
    }

    /* if nothing to split because only a function with param */
    if (ret_index == -1 && tokens[0]->type == TOKEN_FUNC_WITH_PARAM)
        return 0;

    return ret_index;
}


s_param *ft_instruction_parse_tokens(s_token **tokens, int length)
{
    int index = ft_instruction_split_tokens_by_priority(tokens, length);

    if (index == -1)
    {
        if (tokens[0]->type == TOKEN_INT)
            return ft_8xp_parse_int(tokens, length);
        else if (tokens[0]->type == TOKEN_DOUBLE_QUOTES)
            return ft_8xp_parse_str(tokens, length);
        else if (tokens[0]->type == TOKEN_VAR)
            return ft_8xp_parse_var(tokens, length);
        else if (tokens[0]->type == TOKEN_FUNC)
            return ft_8xp_parse_func(tokens, length);
        else
        {
            printf("NotImplemented (token_type=%d) (todo or error ?) -> opcode=%x\n", tokens[0]->type, tokens[0]->opcode[0]);
            s_param *ret = ft_calloc(sizeof(s_param));
            ret->type = PARAM_INT;
            ret->n = 42;
            return ret;
        }
    }
    else if (index == 0)
    {
        return ft_8xp_parse_func_with_param(tokens[0], &tokens[1], length-1);
    }
    else
    {
        return ft_8xp_parse_op(tokens, length, index);
    }
}


s_instruction *ft_instruction_parse(s_token **tokens, int length)
{
    s_instruction *ret = NULL;

    ret = ft_calloc(sizeof(s_instruction));
    ret->tokens = memdup(tokens, length);
    ret->tokens_length = length;
    ret->param = ft_instruction_parse_tokens(tokens, length);
    ret->next = NULL;

    return ret;
}
