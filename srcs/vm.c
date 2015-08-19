
#include <stdio.h>
#include <unistd.h>

#include "instruction.h"
#include "utils.h"
#include "vm.h"

s_vm vm;

void ft_vm_execute_code(s_instruction *ptr_code)
{
    while (ptr_code)
    {
        ft_vm_execute_instruction(ptr_code->param);
        ft_vm_refresh_screen();
        sleep(1);

        ptr_code = ptr_code->next;
    }
}

/*
            printf("func: \"%s\" (ac=%d)\n", ptr->function->name, ptr->function->ac);
            for (j = 0; j < ptr->function->ac; ++j)
                ft_print_sparam(ptr->function->av[j], level+1);

*/

void ft_vm_execute_instruction(s_param *ptr)
{
    ft_print_sparam(ptr, 0, 0);

    switch (ptr->type)
    {
        case PARAM_FUNC:
        case TOKEN_FUNC_WITH_PARAM:
            if (ptr->function->callback == NULL)
            {
                char buf[1024];
                sprintf(buf, "no callback to call for func \"%s\"", ptr->function->name);
                ft_abort(buf);
            }
            ptr->function->callback(ptr->function->ac, ptr->function->av);
            break;

        case PARAM_CONDITION_IF:
            ft_vm_execute_instruction(ptr->condition->param);
            if (vm.ret)
                ft_vm_execute_code(ptr->condition->if_true);
            else
                ft_vm_execute_code(ptr->condition->if_false);
            break;

        case PARAM_CONDITION_WHILE:
            ft_vm_execute_instruction(ptr->condition->param);
            while (vm.ret)
            {
                ft_vm_execute_code(ptr->condition->if_true);
                ft_vm_execute_instruction(ptr->condition->param);
            }

            break;

        default:
            printf("type=%d\n", ptr->type);
            ft_abort("Oups, this should be a func, I have nothing to do here");
            break;
    }
}


void ft_vm_refresh_screen(void)
{
    int i, j;

    printf("+");
    for (i = 0; i < 95; ++i)
        printf("-");
    printf("+\n");

    for (j = 0; j < 63-20; ++j)
    {
        printf("|");
        for (i = 0; i < 95; ++i)
        {
            if (vm.screen[j][i])
                printf("X");
            else
                printf(" ");
        }
        printf("|");

        if (j < 26+1+6) // letters + omega + {x|y}{min|max|grad}
            printf(" %s\t%.2f", ft_var_get_str(j), vm.vars[j]);

        printf("\n");
    }

    /*
    printf("+");
    for (i = 0; i < 95; ++i)
        printf("-");
    printf("+\n");
    */

    printf("\n");
}
