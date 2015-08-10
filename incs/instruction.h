#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include "token.h"

typedef enum _e_param
{
    PARAM_FUNC,
    PARAM_NUMBER,
    PARAM_STR,
    PARAM_VAR
}           e_param;

typedef struct              _s_function
{
    vm_function             callback;
    int                     ac;
    s_param                 **av;
    char                    *name;
}                           s_function;

struct                      _s_param
{
    e_param                 type;

    s_function              *function;
    double                  number;
    char                    *str;
    e_var                   var;
    /* todo cond: if, while, ... */
};

typedef struct              _s_instruction
{
    s_token                 **tokens;
    int                     tokens_length;
    s_param                 *param;

    struct _s_instruction   *next;
}                           s_instruction;

int ft_instruction_split_tokens_by_priority(s_token **tokens, int length);
s_param *ft_instruction_parse_tokens(s_token **tokens, int length);
s_instruction *ft_instruction_parse(s_token **tokens, int length);

#endif
