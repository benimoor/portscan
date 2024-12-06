#include "portscanner.h"

int main(int ac, char **av)
{
    int exit_code;

    exit_code = check_arguments(ac, av);
    
    if (exit_code == 0)
        exit_code = scan_ports(ac, av);

    return (exit_code);
}