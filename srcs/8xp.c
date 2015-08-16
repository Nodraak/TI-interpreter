
#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "instruction.h"
#include "utils.h"
#include "8xp.h"


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

    ft_fread(buf, 9, f); /* unknown */

    ft_fread(buf, 6, f);
    printf("name: %s\n", buf);

    ft_fread(buf, 8, f); /* unknown */

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

        if (token->opcode[0] == 0X3E || token->opcode[0] == 0X3F) // todo; this sucks too
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
                ft_abort("incomming overflow");
        }
    }

    if (ci_index != 0)
        ft_8xp_append_instruction(&ret, ft_instruction_parse(ci_code, ci_index));

    return ret;
}


void ft_8xp_append_instruction(s_instruction **list, s_instruction *elem)
{
    /* if empty instruction, skip it */
    if (elem->tokens_length == 0)
    {
        // todo: free elem
        return;
    }

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


s_instruction *ft_8xp_parse_conditions(s_instruction **code)
{
    /*
        todo:
        handle the Then and Else following a If
    */

    s_instruction *ret = NULL;

    while (*code)
    {
        if (((*code)->tokens[0]->opcode[0] == 0xCE) || ((*code)->tokens[0]->opcode[0] == 0xD1)) // todo this sucks : if || while
        {
            s_instruction *tmp = *code;

            (*code) = (*code)->next;
            (*code) = (*code)->next; // todo: remove me when Then is handled properly. Note: in case of While or For, this skip a token
            s_instruction *if_true = ft_8xp_parse_conditions(code);

            s_condition *cond = ft_calloc(sizeof(s_condition));
            cond->param = tmp->param;
            cond->if_true = if_true;
            cond->if_false = NULL;

            s_param *param = ft_calloc(sizeof(s_param));
            param->type = ((*code)->tokens[0]->opcode[0] == 0xCE) ? PARAM_CONDITION_IF : PARAM_CONDITION_WHILE;
            param->condition = cond;

            tmp->param = param;

            tmp->next = NULL;
            ft_8xp_append_instruction(&ret, tmp);
            (*code) = (*code)->next;
        }
        else if ((*code)->tokens[0]->opcode[0] == 0xD4) // todo this sucks : end
        {
            return ret;
        }
        else
        {
            s_instruction *next = (*code)->next;
            (*code)->next = NULL;
            ft_8xp_append_instruction(&ret, *code);
            (*code) = next;
        }
        printf("\n");
    }

    return ret;
}
