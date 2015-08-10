
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
    ft_print_sparam(ptr, 0);

    switch (ptr->type)
    {
        case PARAM_FUNC:
            if (ptr->function->callback == NULL)
                ft_abort("no callback to call");
            ptr->function->callback(ptr->function->ac, ptr->function->av);
            break;
        default:
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

    for (j = 0; j < 63-30; ++j)
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

        if (j < 26)
            printf(" %c %.2lf", 'A'+j, vm.var[j]);

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
