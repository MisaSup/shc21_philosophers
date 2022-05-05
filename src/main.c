#include "../philo.h"

int main(int argc, char *argv[])
{
    t_args arguments;
         
    get_check_args(argc - 1, argv + 1, &arguments);
    init_threads(&arguments);
    return (0);
}

