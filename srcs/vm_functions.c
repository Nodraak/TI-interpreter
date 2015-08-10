
#include <stdlib.h>
#include <stdio.h>

#include "instruction.h"
#include "utils.h"
#include "vm.h"
#include "vm_functions.h"


void ft_vm_functions_effecr(int ac, s_param *av[])
{
    printf("in effecr\n");
}

void ft_vm_functions_disp(int ac, s_param *av[])
{
    printf("in disp\n");
}

void ft_vm_functions_input(int ac, s_param *av[])
{
    if ((ac == 2) && (av[0]->type == PARAM_STR) && (av[1]->type == PARAM_VAR))
    {
        /* todo: better printf */
        printf("%s\n", av[0]->str);
        scanf("%lf", &vm.var[av[1]->var]);
    }
    else
        ft_abort("NotImplemented input");
}

void ft_vm_functions_assign(int ac, s_param *av[])
{
    if ((ac == 2) && (av[0]->type == PARAM_INT) && (av[1]->type == PARAM_VAR))
    {
        vm.var[av[1]->var] = av[0]->n;
    }
    else
        ft_abort("NotImplemented assign");
}
