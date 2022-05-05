#include "../philo.h"
#include <stdio.h>
#include <sys/types.h>

void print_state(t_info *info, int state)
{
    // if (state == DEAD)
    if (state == DEAD)
        printf ("%4ld #%d died!\n", get_timestamp(info->start_time), info->thread_num + 1);
    // pthread_mutex_lock(&(info->args->dead_mutex));
    // if (state != DEAD)
        // pthread_mutex_unlock(&(info->args->dead_mutex));
    if (state == FORK)
        printf ("%4ld #%d has taken a fork\n", get_timestamp(info->start_time), info->thread_num + 1);
    else if (state == EAT)
        printf ("%4ld #%d is eating\n", get_timestamp(info->start_time), info->thread_num + 1);
    else if (state == DFORK) //DELETE
        printf ("%4ld #%d down forks\n", get_timestamp(info->start_time), info->thread_num + 1);
    else if (state == SLEEP)
        printf ("%4ld #%d is sleeping\n", get_timestamp(info->start_time), info->thread_num + 1);
    else if (state == THINK)
        printf ("%4ld #%d is thinking\n", get_timestamp(info->start_time), info->thread_num + 1);
}

void grab_forks (t_info *info, int f1, int f2)
{
    if (f2 == info->args->num_of_philos) 
        f2 = 0;
    pthread_mutex_lock(&(info->forks[f1]));
    print_state(info, FORK);
    pthread_mutex_lock(&(info->forks[f2]));
    print_state(info, FORK);
    // printf ("%4ld #%d gab a fork\n", get_timestamp(info->start_time), info->thread_num + 1);
}

void getting_meal(t_info *info)
{
    // printf ("%4ld #%d are eat\n", get_timestamp(info->start_time), info->thread_num + 1);

    print_state(info, EAT);
    info->last_meal = get_miliseconds();
    usleep(info->args->time_to_eat);
}

void down_forks (t_info *info, int f1, int f2) 
{ 
    if (f2 == info->args->num_of_philos) 
        f2 = 0;
    // printf ("%4ld #%d down forks\n", get_timestamp(info->start_time), info->thread_num + 1);
    print_state(info, DFORK); //DELETE
    pthread_mutex_unlock(&(info->forks[f1]));
    pthread_mutex_unlock(&(info->forks[f2])); 
}

void fall_asleep_n_think(t_info *info)
{
    // printf ("%4ld #%d fall asleep\n", get_timestamp(info->start_time), info->thread_num + 1);
    print_state(info, SLEEP);
    usleep(info->args->time_to_sleep);
    print_state(info, THINK);
}

void routine(t_info *info)
{
    grab_forks(info, info->thread_num, info->thread_num + 1);
    getting_meal(info);
    down_forks(info, info->thread_num, info->thread_num + 1);
    fall_asleep_n_think(info);
}

void *sit_at_the_table(void *arg)
{
    t_info *info;
    int i;

    info = (t_info *)arg;
    i = -1;
    if (info->args->meal_counter)
        while (info->status != DEAD && ++i < info->args->meal_counter)
            routine(info);
    else
        while (info->status != DEAD)
            routine(info);

    return NULL;
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
        tinfo[i].thread_num = i;
        tinfo[i].forks = forks;
		tinfo[i].args = arguments;
        if(pthread_create(&tinfo[i].thread_id, NULL, sit_at_the_table, &tinfo[i]))
            return (1);
        usleep(500);
    }
    pthread_create(&keeper_id, NULL, keeper, arguments);
	pthread_detach(keeper_id);
    i = -1;
    while (++i < arguments->num_of_philos)
        pthread_join(tinfo[i].thread_id, NULL);
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
    while (++i < arguments->num_of_philos)
    {
        pthread_mutex_init(&(forks[i]), NULL);
        tinfo[i].status = -1;
    }
	arguments->tinfo = tinfo;
    if (start_threads(tinfo, forks, arguments))
        exit(0);
}