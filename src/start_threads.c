#include "../philo.h"
#include <stdio.h>
#include <sys/types.h>

void print_state(t_info *info, int state)
{
    if (state == DEAD)
        printf ("%4ld #%d died!\n", get_timestamp(info->start_time), info->thread_num + 1);
    printf("HeLOLO %d %d\n", info->thread_num + 1, info->args->meal_counter);
    /* if (!info->args->status)
    {
        printf("JOIN %d T%ld\n", info->thread_num + 1, get_timestamp(info->start_time));
        // pthread_join(info->thread_id, NULL);
    } */
    // pthread_mutex_lock(&(info->args->dead_mutex));
    // if (state != DEAD)
        // pthread_mutex_unlock(&(info->args->dead_mutex));
    if (state == FORK)
        printf ("%4ld #%d has taken a fork\n", get_timestamp(info->start_time), info->thread_num + 1);
    if (state == EAT)
        printf ("%4ld #%d is eating\n", get_timestamp(info->start_time), info->thread_num + 1);
    if (state == SLEEP)
        printf ("%4ld #%d is sleeping\n", get_timestamp(info->start_time), info->thread_num + 1);
    if (state == THINK)
        printf ("%4ld #%d is thinking\n", get_timestamp(info->start_time), info->thread_num + 1);
}

void *sit_at_the_table(void *arg)
{
    t_info *info;
    int i;

    info = (t_info *)arg;
    i = -1;
    printf("STATERD %d\n", info->thread_num + 1);
    if (info->args->meal_counter)
        while (++i < info->args->meal_counter)
            routine(info);
    else
        while (1)
            routine(info);
    // completion(info->args);
    return NULL;
}

int start_threads(t_info *tinfo, pthread_mutex_t *forks, t_args *arguments)
{
    int i;
    ssize_t  time;
    // pthread_t keeper_id;

    i = -1;
    time = get_miliseconds();
    while (++i < arguments->num_of_philos)
    {
        tinfo[i].start_time = time;
        tinfo[i].last_meal = time;
        tinfo[i].thread_num = i;
        tinfo[i].forks = forks;
		tinfo[i].args = arguments;
        if(pthread_create(&tinfo[i].thread_id, NULL, sit_at_the_table, &tinfo[i]))
            return (1);
        usleep(500);
    }
    // arguments->keeper_id = keeper_id;
    // pthread_create(&keeper_id, NULL, keeper, arguments);
    // pthread_detach(keeper_id);
    return (0);
}

void init_threads(t_args *arguments)
{
	int i;
	t_info *tinfo;
    pthread_mutex_t *forks;
    
    tinfo = (t_info *)malloc(sizeof(t_info) * arguments->num_of_philos);
    forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arguments->num_of_philos);
    if (!(tinfo) || !(forks))
        exit(0);
    i = -1;
	arguments->tinfo = tinfo;
	arguments->status = 1;
    while (++i < arguments->num_of_philos)
    {
        pthread_mutex_init(&(forks[i]), NULL);
    }
    if (start_threads(tinfo, forks, arguments))
        exit(0);
    // printf("COMP T%ld\n", get_timestamp(arguments->tinfo[1].start_time));
    // completion(arguments);
}