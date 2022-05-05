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
#define DFORK -11 //DELETE

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

void    init_threads(t_args *arguments);
void	get_check_args(int argc, char **argv, t_args *args);
ssize_t get_miliseconds();
ssize_t get_timestamp(ssize_t start_time);
void    *keeper(void *info);
void print_state(t_info *info, int state);
void routine(t_info *info);
void completion(t_args *arguments);
// // RULES
// void	push(t_st **a, t_st **b, char c);
// void	swap(t_st **a, t_st **b, char c);
// void	rotate(t_st **a, t_st **b, char c);
// void	reverser(t_st **a, t_st **b, char c);
// void	rotate_mv(t_st **head);
// // MAIN
// void	get_check_args(int argc, char **argv, t_st **head);
// void	check_number(char **str, int num, t_st **head, int exit_option);
// void	detect_multi_sign(char **str, t_st **head, int exit_option, int indx);
// void	start_sort(t_st **a);
// void	delete_list(t_st **head);
// void	exit_psw(int n, char **str, t_st **head);
// // LIST
// t_st	*ft_lstnew(int content);
// void	ft_lstadd_back(t_st **head, t_st *new);
// void	ft_lstadd_front(t_st **head, t_st *new);
// int		ft_lstcount(t_st **head);
// void	ft_lstremove_node(t_st **head);
// t_st	*ft_lstsearch(t_st **head, int num);
// int		ft_search_node_indx(t_st **head, int num);
// t_st	*get_node_by_index(t_st **head, int i);
// // SORT
// void	base_case(t_st **head, char c);
// void	redux_sort(t_st **a, t_st **b);
// int		get_min(t_st **head);
// int		get_max(t_st **head);
// int		is_sorted(t_st **head, char c);
// void	set_index(t_st **head);
// t_st	*get_next_min(t_st **head);
// // LIB
// int		ft_atoi(const char *str);
// size_t	ft_strlen(const char *s);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	**ft_split(const char *s, char c);
// char	*ft_strchr(const char *s, int c);

#endif
