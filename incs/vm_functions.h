#ifndef VM_FUNCTIONS_H_INCLUDED
#define VM_FUNCTIONS_H_INCLUDED

#define VM_SLEEP_HACK_69 100
#define float_equals(x, y)  (abs((x)-(y)) < 1.0/1000/1000)

/*
    Private functions
*/

double get_arg_value(s_param *param); /* needed by vm.c */
/*
void clear_screen(void);
void set_pxl(int x, int y, int value);
void hline(double x1, double x2, double y, int colored);
void vline(double x, double y1, double y2, int colored);
void line(double x1, double y1, double x2, double y2, int colored);
*/

/*
    Public functions
*/

void ft_vm_functions_effecr(int ac, s_param *av[]);
void ft_vm_functions_effdessin(int ac, s_param *av[]);
void ft_vm_functions_text(int ac, s_param *av[]);

void ft_vm_functions_line(int ac, s_param *av[]);
void ft_vm_functions_ptaff(int ac, s_param *av[]);
void ft_vm_functions_ptnaff(int ac, s_param *av[]);

void ft_vm_functions_disp(int ac, s_param *av[]);
void ft_vm_functions_input(int ac, s_param *av[]);

void ft_vm_functions_assign(int ac, s_param *av[]);

void ft_vm_functions_if(int ac, s_param *av[]);
void ft_vm_functions_while(int ac, s_param *av[]);
void ft_vm_functions_for(int ac, s_param *av[]);
void ft_vm_functions_equal(int ac, s_param *av[]);
void ft_vm_functions_not_equal(int ac, s_param *av[]);
void ft_vm_functions_greater(int ac, s_param *av[]);
void ft_vm_functions_lower(int ac, s_param *av[]);

void ft_vm_functions_partent(int ac, s_param *av[]);
void ft_vm_functions_partdec(int ac, s_param *av[]);

void ft_vm_functions_div(int ac, s_param *av[]);
void ft_vm_functions_add(int ac, s_param *av[]);
void ft_vm_functions_sub(int ac, s_param *av[]);
void ft_vm_functions_mul(int ac, s_param *av[]);
void ft_vm_functions_neg(int ac, s_param *av[]);
void ft_vm_functions_fact(int ac, s_param *av[]);
void ft_vm_function_pow(int ac, s_param *av[]);
void ft_vm_function_square(int ac, s_param *av[]);
void ft_vm_function_sqrt(int ac, s_param *av[]);

#endif
