#include "../philo.h"
#include <stdio.h>
#include <sys/types.h>

void print_state(t_info *info, int state)
{
    if (state == DEAD)
    {
        pthread_mutex_lock(&info->args->dead_mutex);
        printf ("%4ld #%d died!\n", get_timestamp(info->start_time), info->thread_num + 1);
    }
    if (info->args->status)
    {
        if (state == FORK)
            printf ("%4ld #%d has taken a fork\n", get_timestamp(info->start_time), info->thread_num + 1);
        else if (state == EAT)
            printf ("%4ld #%d is eating\n", get_timestamp(info->start_time), info->thread_num + 1);
        else if (state == SLEEP)
            printf ("%4ld #%d is sleeping\n", get_timestamp(info->start_time), info->thread_num + 1);
        else if (state == THINK)
            printf ("%4ld #%d is thinking\n", get_timestamp(info->start_time), info->thread_num + 1);
    }
}

void *sit_at_the_table(void *arg)
{
    t_info *info;
    int i;

    info = (t_info *)arg;
    i = -1;
    if (info->args->meal_counter)
    {
        while (info->args->status != DEAD && ++i < info->args->meal_counter)
            routine(info);
        if (info->args->status != DEAD)
            info->args->status = DONE;
    }
    else
        while (info->args->status != DEAD)
            routine(info);
    return NULL;
}

void set_params(t_info *tinfo, pthread_mutex_t *forks, t_args *arguments, int i)
{
    tinfo[i].thread_num = i;
    tinfo[i].forks = forks;
	tinfo[i].args = arguments;
}

int start_threads(t_info *tinfo, pthread_mutex_t *forks, t_args *arguments)
{
    int i;
    ssize_t  time;
    pthread_t keeper_id;

    i = -1;
    time = get_miliseconds();
    while (++i < arguments->num_of_philos)
    {
        tinfo[i].start_time = time;
        tinfo[i].last_meal = time;
        set_params(tinfo, forks, arguments, i);
        if(pthread_create(&tinfo[i].thread_id, NULL, sit_at_the_table, &tinfo[i]))
            return (4);
        usleep(100);
    }
    pthread_create(&keeper_id, NULL, keeper, arguments);
	pthread_detach(keeper_id);
    i = -1;
    while (++i < arguments->num_of_philos)
        if(pthread_join(tinfo[i].thread_id, NULL))
            return (5);
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
        error_mes(2, arguments);
    i = -1;
    while (++i < arguments->num_of_philos)
    {
        if(pthread_mutex_init(&(forks[i]), NULL))
            error_mes(3, arguments);
        tinfo[i].status = -1;
    }
	arguments->tinfo = tinfo; 
    i = start_threads(tinfo, forks, arguments);
    if (i)
        error_mes(i, arguments);
}