
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "utils.h"
#include "token.h"
#include "8xp_parse.h"
#include "debug.h"
#include "instruction.h"


int instruction_id = 0;

void ft_instruction_advance_while(s_token **tokens, int *i, int length, e_t_type_type type)
{
    (*i) ++; /* skip starting token */

    while ((*i < length) && (tokens[*i]->type != type))
    {
        /* discard instructions inside parenthesis (higher priority) or a function (param) */
        if ((*i < length) && ((tokens[*i]->type == T_TYPE_FUNC_WITH_PARAM) || (tokens[*i]->type == T_TYPE_PARENTHESIS_OPEN)))
        {
            ft_instruction_advance_while(tokens, i, length, T_TYPE_PARENTHESIS_CLOSE);
            (*i) ++;
        }
        /* discard instructions inside double quotes (text) */
        if ((*i < length) && (tokens[*i]->type == T_TYPE_DOUBLE_QUOTES))
        {
            ft_instruction_advance_while(tokens, i, length, T_TYPE_DOUBLE_QUOTES);
            (*i) ++;
        }

        (*i) ++;
    }
}


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

        /* discard instructions inside parenthesis (higher priority) or a function (param) */
        if ((i < length) && ((tokens[i]->type == T_TYPE_FUNC_WITH_PARAM) || (tokens[i]->type == T_TYPE_PARENTHESIS_OPEN)))
            ft_instruction_advance_while(tokens, &i, length, T_TYPE_PARENTHESIS_CLOSE);
        /* discard instructions inside double quotes (text) */
        if (((i < length)) && (tokens[i]->type == T_TYPE_DOUBLE_QUOTES))
            ft_instruction_advance_while(tokens, &i, length, T_TYPE_DOUBLE_QUOTES);
    }

    /* if nothing to split because only a function with param */
    if (ret_index == -1 && tokens[0]->type == T_TYPE_FUNC_WITH_PARAM)
        return 0;

    return ret_index;
}


s_param *ft_instruction_parse_tokens(s_token **tokens, int length)
{
    int index = 0;

    if (length == 0)
        ft_abort("ParserError: length == 0, nothing to parse");

    index = ft_instruction_split_tokens_by_priority(tokens, length);

    if (index == -1)
    {
        if (tokens[0]->type == T_TYPE_NUMBER)
        {
            int i = 0, only_int = 1;
            for (i = 0; i < length; ++i)
            {
                if (tokens[i]->type != T_TYPE_NUMBER)
                    only_int = 0;
            }

            if (only_int)
                return ft_8xp_parse_number(tokens, length);
            else
            {
                s_token *token_times = ft_token_get(0x82);
                s_param **av = ft_calloc(sizeof(s_param*)*2);
                av[0] = ft_8xp_parse_number(tokens, length-1);
                av[1] = ft_8xp_parse_var(&tokens[length-1], 1);

                return ft_8xp_parse_make_function(token_times, 2, av);
            }
        }
        else if (tokens[0]->type == T_TYPE_DOUBLE_QUOTES)
            return ft_8xp_parse_str(tokens, length);
        else if (tokens[0]->type == T_TYPE_VAR)
            return ft_8xp_parse_var(tokens, length);
        else if (tokens[0]->type == T_TYPE_FUNC)
            return ft_8xp_parse_func(tokens, length);
        else
        {
            print_tokens(tokens, length, 0);
            printf("T_TYPE_type=%d opcode=%x instruction_id=%d\n", tokens[0]->type, tokens[0]->opcode[0], instruction_id);
            ft_abort("NotImplementedError (ParserError)");
            return NULL; /* silent warning */
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
    ret->instruction_id = instruction_id;
    ret->next = NULL;

    instruction_id ++;

    return ret;
}
