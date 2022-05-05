#include "../philo.h"
#include <stdio.h>

void completion(t_args *arguments)
{
    int i;

    i = -1;
    printf("HERE\n");
    while (++i < arguments->num_of_philos)
    {
        printf("id %ld\n", arguments->tinfo[i].thread_id);
        // pthread_join(arguments->tinfo[i].thread_id, NULL);
        printf("HERE2\n");
    }
    // pthread_detach(arguments->keeper_id);
        printf("HERE3\n");
    if (arguments->tinfo->forks)
    {
        i = -1;
        while (++i < arguments->num_of_philos)
            pthread_mutex_destroy(&(arguments->tinfo->forks[i]));
        free(arguments->tinfo->forks);
    }
    if (arguments->tinfo)
    {
        free(arguments->tinfo);
        pthread_mutex_unlock(&(arguments->dead_mutex));
        pthread_mutex_destroy(&(arguments->dead_mutex));
    }
        printf("HERE4\n");
    // exit(0);
}