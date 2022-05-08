#include "../philo.h"

void completion(t_args *arguments)
{
    int i;

    i = -1;
    while (arguments->tinfo->forks && ++i < arguments->num_of_philos)
        pthread_mutex_destroy(&(arguments->tinfo->forks[i]));
    pthread_mutex_destroy(&(arguments->dead_mutex));
    if (arguments->tinfo->forks)
        free(arguments->tinfo->forks);
    if (arguments->tinfo)
        free(arguments->tinfo);
}

int main(int argc, char *argv[])
{
    t_args arguments;
         
    get_check_args(argc - 1, argv + 1, &arguments);
    init_threads(&arguments);
    completion(&arguments);
    return (0);
}

void error_mes(int num, t_args *arguments)
{
    if (num == 1)
    {
        printf("Arguments error\n");
        exit(1);
    }
    else if (num == 2)
        printf("Malloc error\n");
    else if (num == 3)
        printf("Mutex init error\n");
    else if (num == 4)
        printf("Thread create error\n");
    else if (num == 5)
        printf("Thread join error\n");
    completion(arguments);
    exit(1);
}
