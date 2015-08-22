
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "8xp.h"
#include "utils.h"
#include "token.h"
#include "instruction.h"
#include "vm.h"



void printf_level_instruction(int level)
{
    int i;
    for (i = 0; i < level; ++i)
        printf(" |  ");
}


void print_tokens(s_token **tokens, int length, int level_instruction)
{
    int i, j;

    printf_level_instruction(level_instruction);
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

    printf_level_instruction(level_instruction);
    printf("string");
    for (i = 0; i < length; ++i)
        printf(" %s", tokens[i]->string);
    printf("\n");
}


void ft_print_sparam(s_param *param, int level_instruction, int level)
{
    int i = 0, j = 0;

    printf_level_instruction(level_instruction);
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
                ft_print_sparam(param->function->av[j], level_instruction, level+1);
            break;
        case PARAM_VAR:
            printf("var: \"%s\"\n", ft_var_get_str(param->var));
            break;
        case PARAM_CONDITION_IF:
        case PARAM_CONDITION_WHILE:
        case PARAM_CONDITION_FOR:
            printf("\r");
            ft_print_sparam(param->condition->param, level_instruction, level+1);

            printf_level_instruction(level_instruction);
            for (i = 0; i < level*4; ++i)
                printf(" ");
            printf("if_true: %p\n", param->condition->if_true);
            ft_print_code(param->condition->if_true, level_instruction+1);

            printf_level_instruction(level_instruction);
            for (i = 0; i < level*4; ++i)
                printf(" ");
            printf("if_false: %p\n", param->condition->if_false);

            break;

        default:
            printf("<unknown type %d (todo)>\n", param->type);
    }
}


void ft_print_code(s_instruction *ptr_code, int level_instruction)
{
    while (ptr_code)
    {
        printf_level_instruction(level_instruction);
        print_tokens(ptr_code->tokens, ptr_code->tokens_length, level_instruction);
        ft_print_sparam(ptr_code->param, level_instruction, 0);
        printf_level_instruction(level_instruction);
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

    printf("\n---------------------------------------- Read code:\n\n");
    raw_code = ft_8xp_read_code(program[2], &code_length);

    printf("\n---------------------------------------- Parse code:\n\n");
    code = ft_8xp_parse_code(raw_code, code_length);

    printf("\n---------------------------------------- Printf1 code:\n\n");
    ft_print_code(code, 0);

    printf("\n---------------------------------------- Parse conditions:\n\n");
    code = ft_8xp_parse_conditions(&code);

    printf("\n---------------------------------------- Printf2 code:\n\n");
    ft_print_code(code, 0);

    printf("\n---------------------------------------- Execute code:\n\n");
    ft_vm_execute_code(code);

    return 0;
}
