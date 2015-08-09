#ifndef INSTRUCTION_H_INCLUDED
#define INSTRUCTION_H_INCLUDED

#include "token.h"

typedef enum _e_param
{
    PARAM_FUNC,
    PARAM_INT,
    PARAM_STR,
    PARAM_VAR
}           e_param;

typedef struct _s_param s_param;

typedef struct              _s_function
{
    void*(*callback)(int ac, s_param *av[]);
    int                     ac;
    s_param                 **av;
    char                    *name;
}                           s_function;

struct                      _s_param
{
    e_param                 type;

    s_function              *function;
    int                     n;
    char                    *str;
    e_var                   var;
};

typedef struct              _s_instruction
{
    s_token                 **tokens;
    int                     tokens_length;
    s_param                 *param;

    struct _s_instruction   *next;
}                           s_instruction;

int ft_instruction_split_tokens(s_token **tokens, int length);
s_param *ft_tokens_parse_tokens(s_token **tokens, int length);
s_instruction *ft_instruction_parse(s_token **tokens, int length);

#endif