#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include "token.h"

typedef enum _e_param
{
    PARAM_FUNC,
    PARAM_NUMBER,
    PARAM_STR,
    PARAM_VAR,
    PARAM_CONDITION_IF,
    PARAM_CONDITION_WHILE,
    PARAM_CONDITION_FOR
}           e_param;

typedef struct _s_instruction s_instruction;

typedef struct              _s_function
{
    vm_function             callback;
    int                     ac;
    s_param                 **av;
    char                    *name;
}                           s_function;

typedef struct              _s_condition
{
    s_param                 *param;
    s_instruction           *if_true;
    s_instruction           *if_false;
}                           s_condition;

struct                      _s_param
{
    e_param                 type;

    s_function              *function;
    double                  number;
    char                    *str;
    e_var                   var;
    s_condition             *condition;
};

struct                      _s_instruction
{
    s_token                 **tokens;
    int                     tokens_length;
    s_param                 *param;
    int                     instruction_id;

    struct _s_instruction   *next;
};

void ft_instruction_advance_while(s_token **tokens, int *i, int length, e_t_type_type type);
int ft_instruction_split_tokens_by_priority(s_token **tokens, int length);
s_param *ft_instruction_parse_tokens(s_token **tokens, int length);
s_instruction *ft_instruction_parse(s_token **tokens, int length);

#endif
