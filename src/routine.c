#include "../philo.h"
#include <stdio.h>

void grab_forks (t_info *info, int f1, int f2)
{
    if (f2 == info->args->num_of_philos) 
        f2 = 0;
    pthread_mutex_lock(&(info->forks[f1]));
    print_state(info, FORK);
    while (info->args->num_of_philos == 1 && info->args->status);
    if (info->args->status == DEAD)
        pthread_mutex_unlock(&(info->forks[f1]));
    pthread_mutex_lock(&(info->forks[f2]));
    print_state(info, FORK);
}

void getting_meal(t_info *info)
{
    print_state(info, EAT);
    info->last_meal = get_miliseconds();
    timer(info->last_meal, info->args->time_to_eat);
}

void down_forks (t_info *info, int f1, int f2) 
{ 
    if (f2 == info->args->num_of_philos) 
        f2 = 0;
    pthread_mutex_unlock(&(info->forks[f1]));
    pthread_mutex_unlock(&(info->forks[f2]));
}

void fall_asleep_n_think(t_info *info)
{
    ssize_t start_sleep;

    print_state(info, SLEEP);
    start_sleep = get_miliseconds();
    timer(start_sleep, info->args->time_to_sleep);
    print_state(info, THINK);
}

void routine(t_info *info)
{
    grab_forks(info, info->thread_num, info->thread_num + 1);
    getting_meal(info);
    down_forks(info, info->thread_num, info->thread_num + 1);
    fall_asleep_n_think(info);
}