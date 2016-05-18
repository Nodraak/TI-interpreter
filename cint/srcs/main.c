
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "8xp.h"
#include "utils.h"
#include "token.h"
#include "instruction.h"
#include "vm.h"
#include "debug.h"
#include "vm_functions.h"


int main(int ac, char *av[])
{
    unsigned char *raw_code = NULL;
    int code_length;
    s_instruction *code = NULL;

    if (ac != 2)
    {
        printf("Usage: %s FILE\n", av[0]);
        exit(1);
    }

    printf("\n---------------------------------------- Read code (read 8xp file as raw bytes):\n\n");
    raw_code = ft_8xp_read_code(av[1], &code_length);

    printf("\n---------------------------------------- Parse code (raw code to tokens):\n\n");
    code = ft_8xp_parse_code(raw_code, code_length);

    printf("\n---------------------------------------- Printf1 code:\n\n");
    ft_print_code(code, 0);

    printf("\n---------------------------------------- Parse conditions (tokens to final AST):\n\n");
    code = ft_8xp_parse_conditions(&code);

    printf("\n---------------------------------------- Printf2 code:\n\n");
    ft_print_code(code, 0);

    printf("\n---------------------------------------- Execute code:\n\n");
    ft_vm_init();
    ft_vm_execute_code(code);

    return 0;
}
