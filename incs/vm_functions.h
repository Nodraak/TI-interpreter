#ifndef VM_FUNCTIONS_H_INCLUDED
#define VM_FUNCTIONS_H_INCLUDED

#define VM_SLEEP_HACK_69 100
#define float_equals(x, y)  (abs((x)-(y)) < 1.0/1000/1000)

double get_arg_value(s_param *param);

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
void ft_vm_functions_not_equal(int ac, s_param *av[]);
void ft_vm_functions_greater(int ac, s_param *av[]);
void ft_vm_functions_partent(int ac, s_param *av[]);
void ft_vm_functions_div(int ac, s_param *av[]);
void ft_vm_functions_add(int ac, s_param *av[]);
void ft_vm_functions_neg(int ac, s_param *av[]);
void ft_vm_functions_fact(int ac, s_param *av[]);

#endif
