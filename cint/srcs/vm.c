
#include <stdio.h>
#include <unistd.h>

#include "instruction.h"
#include "utils.h"
#include "vm_functions.h"
#include "debug.h"
#include "vm.h"

s_vm vm;


void ft_vm_init(void)
{
    clear_screen();
}


void ft_vm_execute_code(s_instruction *ptr_code)
{
    while (ptr_code)
    {
        printf("=================================> Next instruction %d\n", ptr_code->instruction_id);
        ft_vm_execute_instruction(ptr_code->param);
        system("clear");
        ft_vm_refresh_screen();
        usleep(1000*1000/25);

        ptr_code = ptr_code->next;
    }
}


void ft_vm_execute_instruction(s_param *ptr)
{
    ft_print_sparam(ptr, 0, 0);

    switch (ptr->type)
    {
        int ac = 0;
        s_param **av = NULL;

        case PARAM_FUNC:
        case T_TYPE_FUNC_WITH_PARAM:
            if (ptr->function->callback == NULL)
            {
                char buf[1024];
                sprintf(buf, "no callback to call for func \"%s\"", ptr->function->name);
                ft_abort(buf);
            }
            // todo assert param count here ?
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

        case PARAM_CONDITION_FOR:
            ac = ptr->condition->param->function->ac;
            av = ptr->condition->param->function->av;

            if ((ac != 3) && (ac != 4))
                ft_abort("SyntaxError: unexpected argument count");

            vm.vars[av[0]->var] = get_arg_value(av[1]);

            do {
                ft_vm_execute_code(ptr->condition->if_true);
                ft_vm_execute_instruction(ptr->condition->param);
            } while (vm.ret);

            break;

        default:
            printf("type=%d\n", ptr->type);
            ft_abort("ParserError: expecting a function");
            break;
    }
}


void ft_vm_refresh_screen(void)
{
    int i, j;

    printf("    ");
    for (i = 1; i <= 9; ++i)
        printf("        %2d", i*10);
    printf("\n");

    printf("  +");
    for (i = 1; i <= 95; ++i)
        printf("%c", i%10==0 ? '+' : '-');
    printf("+\n");

    for (j = 63-1; j >= 0; --j)
    {
        printf("%02d|", j);
        for (i = 0; i < 95; ++i)
            printf("%c", vm.screen[j][i]);
        printf("|");

        if (j < 26+1+6) // letters + omega + {x|y}{min|max|grad}
            printf(" %s\t%.2f", ft_var_get_str(j), vm.vars[j]);

        printf("\n");
    }

    printf("  +");
    for (i = 0; i < 95; ++i)
        printf("-");
    printf("+\n");

    printf("\n");
}
