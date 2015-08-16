
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "8xp.h"
#include "utils.h"
#include "token.h"
#include "instruction.h"


void print_tokens(s_token **tokens, int length)
{
    int i, j;

    printf("opcode");
    for (i = 0; i < length; ++i)
    {
        printf(" ");
        for (j = 0; j < 4; ++j)
        {
            if (tokens[i]->opcode[j])
                printf("%02x", tokens[i]->opcode[j]);
        }
    }
    printf("\n");

    printf("string");
    for (i = 0; i < length; ++i)
        printf(" %s", tokens[i]->string);
    printf("\n");
}


void ft_print_sparam(s_param *param, int level)
{
    int i = 0, j = 0;

    for (i = 0; i < level*4; ++i)
        printf(" ");

    switch (param->type)
    {
        case PARAM_NUMBER:
            printf("int: \"%.2f\"\n", param->number);
            break;
        case PARAM_STR:
            printf("str: \"%s\"\n", param->str);
            break;
        case PARAM_FUNC:
            printf("func: \"%s\" (ac=%d)\n", param->function->name, param->function->ac);
            for (j = 0; j < param->function->ac; ++j)
                ft_print_sparam(param->function->av[j], level+1);
            break;
        case PARAM_VAR:
            if (param->var == VAR_OMEGA)
                printf("var: \"Omega\"\n");
            else
                printf("var: \"%c\"\n", 'A'+param->var);
            break;
        case PARAM_CONDITION:
            printf("\r");
            ft_print_sparam(param->condition->param, level+1);

            for (i = 0; i < level*4; ++i)
                printf(" ");
            printf("instruction: %p\n", param->condition->instruction);

            break;

        default:
            printf("<unknown type %d (todo)>\n", param->type);
    }
}


void ft_print_code(s_instruction *ptr_code)
{
    while (ptr_code)
    {
        print_tokens(ptr_code->tokens, ptr_code->tokens_length);
        ft_print_sparam(ptr_code->param, 0);
        printf("\n");
        ptr_code = ptr_code->next;
    }
}


char *program[] = {
    "data/AATEST.8Xp",
    "data/ABC.8Xp",
    "data_save/BASE.8Xp",
    "data/WTC.8Xp",
};


int main(void)
{
    unsigned char *raw_code = NULL;
    int code_length;
    s_instruction *code = NULL;

    raw_code = ft_8xp_read_code(program[2], &code_length);
    printf("\n---------------------------------------- Parse code:\n\n");
    code = ft_8xp_parse_code(raw_code, code_length);
    printf("\n---------------------------------------- Printf code:\n\n");
    ft_print_code(code);
    printf("\n---------------------------------------- Execute code:\n\n");
    ft_vm_execute_code(code);

    return 0;
}
