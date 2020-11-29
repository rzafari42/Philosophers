#include "philosophers.h"

int main(int ac, char **av)
{
        t_infos args;
        struc_initilization(&args);
        print_struct(&args);
        if (!parsing(ac, av, &args))
                return (ft_strerror(NULL_ARG));
        print_struct(&args);
        return (1);
}