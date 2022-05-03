#include "../philo.h"
#define PHILOS 4

/* void grab_forks (t_info *info, int f1, int f2)
{
    if (f2 == PHILOS) 
        f2 = 0;
    pthread_mutex_lock(&(info->forks[f2]));
    printf ("%4ld\n", get_timestamp(info->start_time));
    pthread_mutex_lock(&(info->forks[f1]));
    printf ("%4ld\n", get_timestamp(info->start_time));
    usleep(500 * 1000);
}

void down_forks (t_info *info, int f1, int f2) 
{ 
    if (f2 == PHILOS) 
        f2 = 0;
    printf ("%4ld\n", get_timestamp(info->start_time));
    pthread_mutex_unlock(&(info->forks[f1])); 
    pthread_mutex_unlock(&(info->forks[f2])); 
}

void *sit_at_the_table(void *arg)
{
    t_info *info;
    
    info = (t_info *)arg;

    if (info->thread_num == 1)
        usleep(500);
    grab_forks(info, info->thread_num, info->thread_num + 1);
        // printf("Philo #%d are eating\n", info->thread_num + 1);
    down_forks(info, info->thread_num, info->thread_num + 1);
    return NULL;
} */


int main(int argc, char *argv[])
{
    t_args arguments;
         
    get_check_args(argc - 1, argv + 1, &arguments);
    start_threads(&arguments);

    return (0);
}

