
#include <stdlib.h>
#include <stdio.h>

#include "instruction.h"
#include "utils.h"
#include "vm.h"
#include "vm_functions.h"


double get_arg_value(s_param *param)
{
    switch (param->type)
    {
        case PARAM_NUMBER:
            return param->number;
            break;

        case PARAM_VAR:
            return vm.vars[param->var];
            break;

        case PARAM_FUNC:
            ft_vm_execute_instruction(param);
            return vm.ret;
            break;

        default:
            ft_abort("NotImplemented get_arg_value in vm_functions");
            return 0; /* silent warning */
            break;
    }
}

void ft_vm_functions_effecr(int ac, s_param *av[])
{
    (void)ac, (void)av;
    printf("in effecr todo\n");
}

void ft_vm_functions_effdessin(int ac, s_param *av[])
{
    (void)ac, (void)av;
    printf("in effdessin todo\n");
}

void ft_vm_functions_disp(int ac, s_param *av[])
{
    printf("in disp todo\n");
}

void ft_vm_functions_input(int ac, s_param *av[])
{
    if ((ac == 2) && (av[0]->type == PARAM_STR) && (av[1]->type == PARAM_VAR))
    {
        /* todo: better printf */
        printf("%s\n", av[0]->str);
        scanf("%lf", &vm.vars[av[1]->var]);
    }
    else
        ft_abort("NotImplemented input");
}

void ft_vm_functions_assign(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong param count");
    if (av[1]->type != PARAM_VAR)
        ft_abort("SyntaxError: wrong type");

    vm.vars[av[1]->var] = get_arg_value(av[0]);
}

void ft_vm_functions_if(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong param count");

    vm.ret = get_arg_value(av[0]);
}

void ft_vm_functions_while(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong param count");

    vm.ret = get_arg_value(av[0]);
}

void ft_vm_functions_not_equal(int ac, s_param *av[])
{
    double args[2];

    if (ac != 2)
        ft_abort("SyntaxError: wrong param count");

    args[0] = get_arg_value(av[0]);
    args[1] = get_arg_value(av[1]);

    vm.ret = args[0] != args[1];
}


void ft_vm_functions_greater(int ac, s_param *av[])
{
    double args[2];

    if (ac != 2)
        ft_abort("SyntaxError: wrong param count");

    args[0] = get_arg_value(av[0]);
    args[1] = get_arg_value(av[1]);

    vm.ret = args[0] > args[1];
}

void ft_vm_functions_partent(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong param count");

    vm.ret = (int)(get_arg_value(av[0]));
}

void ft_vm_functions_div(int ac, s_param *av[])
{
    double args[2];

    if (ac != 2)
        ft_abort("SyntaxError: wrong param count");

    args[0] = get_arg_value(av[0]);
    args[1] = get_arg_value(av[1]);

    vm.ret = args[0] / args[1];
}

void ft_vm_functions_add(int ac, s_param *av[])
{
    double args[2];

    if (ac != 2)
        ft_abort("SyntaxError: wrong param count");

    args[0] = get_arg_value(av[0]);
    args[1] = get_arg_value(av[1]);

    vm.ret = args[0] + args[1];
}

void ft_vm_functions_neg(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong param count");

    vm.ret = -get_arg_value(av[0]);
}
