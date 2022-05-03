#include "../philo.h"

void print_state(t_info *info, int state)
{
    pthread_mutex_lock(&info->args->print);
    if (state == FORK)
        printf ("%4ld #%d gab a fork\n", get_timestamp(info->start_time), info->thread_num + 1);
    if (state == EAT)
        printf ("%4ld #%d are eat\n", get_timestamp(info->start_time), info->thread_num + 1);
    if (state == DFORK)
        printf ("%4ld #%d down forks\n", get_timestamp(info->start_time), info->thread_num + 1);
    if (state == SLEEP)
        printf ("%4ld #%d fall asleep\n", get_timestamp(info->start_time), info->thread_num + 1);
    pthread_mutex_unlock(&info->args->print);

}

void grab_forks (t_info *info, int f1, int f2)
{
    if (f2 == info->args->num_of_philos) 
        f2 = 0;
    // printf("forks  %d %d #%5d\n", f1, f2, info->thread_num + 1);
    // usleep(1000);
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
    usleep(info->args->time_to_eat);
}

void down_forks (t_info *info, int f1, int f2) 
{ 
    if (f2 == info->args->num_of_philos) 
        f2 = 0;
    // printf ("%4ld #%d down forks\n", get_timestamp(info->start_time), info->thread_num + 1);
    print_state(info, DFORK);
    pthread_mutex_unlock(&(info->forks[f1])); 
    pthread_mutex_unlock(&(info->forks[f2])); 
}

void fall_asleep(t_info *info)
{
    // printf ("%4ld #%d fall asleep\n", get_timestamp(info->start_time), info->thread_num + 1);
    print_state(info, SLEEP);
    usleep(info->args->time_to_sleep);
}

void *sit_at_the_table(void *arg)
{
    t_info *info;
    
    info = (t_info *)arg;

    /* if (info->thread_num == 1)
        usleep(500); */
    grab_forks(info, info->thread_num, info->thread_num + 1);
        // printf("Philo #%d are eating\n", info->thread_num + 1);
    getting_meal(info);
    down_forks(info, info->thread_num, info->thread_num + 1);
    fall_asleep(info);
    return NULL;
}

void start_threads(t_args *arguments)
{
	int i;
	t_info *tinfo;
    pthread_mutex_t *forks;
    // pthread_t keeper_id;

	i = 0;

    tinfo = (t_info *)malloc(sizeof(t_info) * arguments->num_of_philos);
    forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arguments->num_of_philos);
    while (i < arguments->num_of_philos)
    {
        pthread_mutex_init(&(forks[i]), NULL);
        tinfo[i].status = -1;
        i++;
    }
	arguments->tinfo = tinfo;
    // pthread_create(&keeper_id, NULL, keeper, arguments);
    i = 0;
    while (i < arguments->num_of_philos)
    {
        tinfo[i].start_time = get_miliseconds();
        tinfo[i].thread_num = i;
        tinfo[i].forks = forks;
		tinfo[i].args = arguments;
        pthread_create(&tinfo[i].thread_id, NULL, sit_at_the_table, &tinfo[i]);
        i++;
        usleep(1500);
    }
	// pthread_detach(keeper_id);
    i = 0;
    while (i < arguments->num_of_philos)
    {
		tinfo[i].status = 0;
        pthread_join(tinfo[i].thread_id, NULL);
        i++;
    }

}