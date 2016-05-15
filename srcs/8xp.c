
#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "instruction.h"
#include "utils.h"
#include "8xp.h"


char *file_type[] = {
    "Real number",
    "List",
    "Matrix",
    "Y-var or equ",
    "String",
    "Program",
    "Assembler",
    "Picture",
    "Gdb"
};

unsigned char *ft_8xp_read_code(char *file, int *code_length)
{
    FILE *f = NULL;
    unsigned char buf[1024], *raw_code = NULL;
    int header_size = 8+3+40+9+6+8;

    f = fopen(file, "r");
    if (f == NULL)
        ft_abort("fopen");

    /* read header */
    ft_fread(buf, 8, f);
    printf("file type: %s\n", buf);

    ft_fread(buf, 3, f); /* unknown */

    ft_fread(buf, 40, f);
    printf("date: %s\n", buf);

    ft_fread(buf, 8, f); /* unknown */

    ft_fread(buf, 1, f);
    printf("File type: %s\n", file_type[buf[0]]);

    ft_fread(buf, 7, f);
    printf("name: %s\n", buf);

    ft_fread(buf, 7, f); /* unknown */

    /* read code */
    fseek(f, 0, SEEK_END);
    *code_length = ftell(f) - header_size - 3; /* 2 bytes control sum + 1 byte null */

    fseek(f, header_size, SEEK_SET);

    raw_code = ft_calloc(sizeof(char)*(*code_length));
    ft_fread(raw_code, *code_length, f);

    ft_fread(buf, 3, f);
    printf("control sum: %2x%2x\n", buf[0], buf[1]);

    return raw_code;
}


s_instruction *ft_8xp_parse_code(unsigned char *raw_code, int code_length)
{
    unsigned char *code_ptr = raw_code;
    s_token *ci_code[128]; /* current_instruction */
    int ci_index = 0;
    s_instruction *ret = NULL;

    /* loop over the code */
    while (code_ptr < raw_code + code_length)
    {
        s_token *token = ft_token_next(&code_ptr);

        if (token->opcode[0] == T_OPCODE_EOI_1 || token->opcode[0] == T_OPCODE_EOI_2)
        {
            if (ci_index != 0) /* if the instruction is not empty */
            {
                ft_8xp_append_instruction(&ret, ft_instruction_parse(ci_code, ci_index));
                ci_index = 0;
            }
        }
        else /* regular token */
        {
            ci_code[ci_index] = token;
            ci_index ++;

            if (ci_index == 128)
                ft_abort("ParserError: incomming overflow, buffer for code is too small"); // todo fixme
        }
    }

    if (ci_index != 0)
        ft_8xp_append_instruction(&ret, ft_instruction_parse(ci_code, ci_index));

    return ret;
}


void ft_8xp_append_instruction(s_instruction **list, s_instruction *elem)
{
    /* empty instructions should not happend */
    if (elem->tokens_length == 0)
        ft_abort("ParserError: unexpected empty instruction");

    /* empty list */
    if (*list == NULL)
    {
        *list = elem;
    }
    /* append instruction */
    else
    {
        s_instruction *ptr = *list;

        while (ptr->next)
            ptr = ptr->next;

        ptr->next = elem;
    }
}


s_instruction *make_instruction(s_instruction *condition, s_instruction *if_true)
{
    e_param param_type;
    s_param *param = NULL;

    switch (condition->tokens[0]->opcode[0])
    {
        case 0xCE:
            param_type = PARAM_CONDITION_IF;
            break;
        case 0xD1:
            param_type = PARAM_CONDITION_WHILE;
            break;
        case 0xD3:
            param_type = PARAM_CONDITION_FOR;
            break;
        default:
            ft_abort("ParserError: unexpected token or unhandled condition type");
            break;
    }

    param = ft_calloc(sizeof(s_param));
    param->type = param_type;

    param->condition = ft_calloc(sizeof(s_condition));
    param->condition->param = condition->param;
    param->condition->if_true = if_true;
    param->condition->if_false = NULL;

    condition->param = param;
    condition->next = NULL;

    return condition;
}

s_instruction *ft_8xp_parse_conditions(s_instruction **code)
{
    s_instruction *ret = NULL;

    while (*code)
    {
        /*
            if | while
                one ins

            if | while
            then
                multiple ins
            end

            for
                one or multiple ins
            end

        */

        #define cmp_opcode(ins, hex) ((ins)->tokens[0]->opcode[0] == (hex))

        if (cmp_opcode(*code, T_OPCODE_IF))
        {
            s_instruction *code_cond = *code, *if_true = NULL;
            *code = (*code)->next;

            if (cmp_opcode(*code, T_OPCODE_THEN))
            {
                *code = (*code)->next; /* skip Then */

                if_true = ft_8xp_parse_conditions(code); /* parse until End */
            }
            else
            {
                s_instruction *next = (*code)->next; /* get first instruction outside the If */

                if_true = *code;
                if_true->next = NULL; /* maybe I should copy this shit instead */

                *code = next;
            }

            ft_8xp_append_instruction(&ret, make_instruction(code_cond, if_true));
        }
        else if (cmp_opcode(*code, T_OPCODE_WHILE) || cmp_opcode(*code, T_OPCODE_FOR))
        {
            s_instruction *code_cond = *code, *if_true = NULL;
            *code = (*code)->next;

            if_true = ft_8xp_parse_conditions(code); // parse until End

            ft_8xp_append_instruction(&ret, make_instruction(code_cond, if_true));
        }
        else if ((*code)->tokens[0]->opcode[0] == T_OPCODE_END)
        {
            *code = (*code)->next;
            return ret;
        }
        else // standard instruction
        {
            s_instruction *next = (*code)->next;
            (*code)->next = NULL;
            ft_8xp_append_instruction(&ret, *code);
            (*code) = next;
        }
    }

    return ret;
}
