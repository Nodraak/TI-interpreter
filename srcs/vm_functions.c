
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "instruction.h"
#include "utils.h"
#include "vm.h"
#include "vm_functions.h"

/*

graph
calc
maths

-> todo: scale functions (cf EceCity)

*/

/*******************************************************************************
    Private functions
*******************************************************************************/

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

void clear_screen(void)
{
    int i, j;

    for (j = 0; j < 63; ++j)
    {
        for (i = 0; i < 95; ++i)
            vm.screen[j][i] = ' ';
    }
}

void set_pxl(int x, int y, int value)
{
    if (x >= 0 && x < 95 && y >= 0 && y < 63)
        vm.screen[y][x] = value ? 'X' : ' ';
}

void hline(double x1, double x2, double y, int colored)
{
    double i;
    for (i = x1; i <= x2; ++i)
        set_pxl(i, y, colored);
}

void vline(double x, double y1, double y2, int colored)
{
    double j;
    for (j = y1; j <= y2; ++j)
        set_pxl(x, j, colored);
}

void line(double x1, double y1, double x2, double y2, int colored)
{
    if (float_equals(x1, x2))
        vline(x1, y1, y2, colored);
    else if (float_equals(y1, y2))
        hline(x1, x2, y1, colored);
    else
    {
        // toto: maybe improve this
        double coeff, i;

        if (x1 > x2)
        {
            double tmp = x1;
            x1 = x2;
            x2 = tmp;
        }
        coeff = (y2-y1) / (x2-x1);
        for (i = x1; i <= x2; ++i)
            set_pxl(i, y1 + (i-x1)*coeff, colored);
    }
}

/*******************************************************************************
    Public functions
*******************************************************************************/

void ft_vm_functions_effecr(int ac, s_param *av[])
{
    (void)ac, (void)av;
    clear_screen();
    // todo draw cursor ?
}

void ft_vm_functions_effdessin(int ac, s_param *av[])
{
    (void)ac, (void)av;
    clear_screen();
    // todo draw axis
}

void ft_vm_functions_text(int ac, s_param *av[])
{
    (void)ac, (void)av;
    printf("in text todo\n");
}

void ft_vm_functions_line(int ac, s_param *av[])
{
    double args[4];
    int i, colored = 1;

    if ((ac != 4) && (ac != 5))
        ft_abort("SyntaxError: wrong argument count");

    for (i = 0; i < 4; ++i)
        args[i] = get_arg_value(av[i]);

    if (ac == 5)
        colored = 0;

    line(args[0], args[1], args[2], args[3], colored);
}

void ft_vm_functions_ptaff(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    set_pxl(get_arg_value(av[0]), get_arg_value(av[1]), 1); // todo debug me
}

void ft_vm_functions_ptnaff(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    set_pxl(get_arg_value(av[0]), get_arg_value(av[1]), 0); // todo debug me
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
        ft_abort("SyntaxError: wrong argument count");
    if (av[1]->type != PARAM_VAR)
        ft_abort("SyntaxError: wrong type");

    vm.vars[av[1]->var] = get_arg_value(av[0]);
}

void ft_vm_functions_if(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]);
}

void ft_vm_functions_while(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]);
}

void ft_vm_functions_for(int ac, s_param *av[])
{
    double incr = 1; /* default increment is 1 */

    if ((ac != 3) && (ac != 4))
        ft_abort("SyntaxError: wrong argument count");

    if (ac == 4)
        incr = get_arg_value(av[3]);

    vm.vars[av[0]->var] += incr;
    vm.ret = vm.vars[av[0]->var] <= get_arg_value(av[2]);
}

void ft_vm_functions_equal(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = float_equals(get_arg_value(av[0]), get_arg_value(av[1]));
}


void ft_vm_functions_not_equal(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = !float_equals(get_arg_value(av[0]), get_arg_value(av[1]));
}

void ft_vm_functions_greater(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]) > get_arg_value(av[1]);
}

void ft_vm_functions_lower(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]) < get_arg_value(av[1]);
}

void ft_vm_functions_partent(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = (int)(get_arg_value(av[0]));
}

void ft_vm_functions_partdec(int ac, s_param *av[])
{
    double val = 0;

    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    val = get_arg_value(av[0]);
    vm.ret = val - (int)(val);
}

void ft_vm_functions_div(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]) / get_arg_value(av[1]);
}

void ft_vm_functions_add(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]) + get_arg_value(av[1]);
}

void ft_vm_functions_sub(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]) - get_arg_value(av[1]);
}

void ft_vm_functions_mul(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]) * get_arg_value(av[1]);
}

void ft_vm_functions_neg(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = -get_arg_value(av[0]);
}

void ft_vm_functions_fact(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    if (get_arg_value(av[0]) == 69)
        usleep(1000*VM_SLEEP_HACK_69);
    else
        ft_abort("NotImplemented");
}

void ft_vm_function_pow(int ac, s_param *av[])
{
    if (ac != 2)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = pow(get_arg_value(av[0]), get_arg_value(av[1]));
}

void ft_vm_function_square(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = get_arg_value(av[0]) * get_arg_value(av[0]);
}

void ft_vm_function_sqrt(int ac, s_param *av[])
{
    if (ac != 1)
        ft_abort("SyntaxError: wrong argument count");

    vm.ret = sqrt(get_arg_value(av[0]));
}
