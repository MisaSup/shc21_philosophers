/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcarlos <wcarlos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:14:52 by wcarlos           #+#    #+#             */
/*   Updated: 2022/02/24 12:14:54 by wcarlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO
# define PHILO
# include <pthread.h>
# include <stdlib.h>
# include <stddef.h>
# include <assert.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

#define DEAD 0
#define SLEEP 1
#define THINK 2
#define EAT 3
#define FORK 11
#define DONE 50

typedef struct thread_info {
    pthread_t       thread_id;       
    pthread_mutex_t *forks;
    int             thread_num;
    ssize_t         start_time;
    ssize_t         last_meal;
    int             status;
    struct arguments *args;
} t_info;

typedef struct arguments {
    int             num_of_philos;
    int             time_to_die;
    int             time_to_eat;
    int             time_to_sleep;
    int             meal_counter;
    int             status;
    t_info          *tinfo;
    pthread_mutex_t dead_mutex;
    pthread_t       keeper_id;
} t_args;

size_t	ft_strlen(const char *s);
int	    ft_atoi(const char *str);
char	*ft_strchr(const char *s, int c);

void	get_check_args(int argc, char **argv, t_args *args);
ssize_t get_miliseconds();
ssize_t get_timestamp(ssize_t start_time);
void    init_threads(t_args *arguments);
void    *keeper(void *info);
void    print_state(t_info *info, int state);
void    routine(t_info *info);

#endif