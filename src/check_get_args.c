/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_get_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcarlos <wcarlos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:12:46 by wcarlos           #+#    #+#             */
/*   Updated: 2022/02/24 12:13:24 by wcarlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

int	count_numbers(char *s)
{
	size_t	i;
	int		nums;

	i = 0;
	nums = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] >= '0' && s[i] <= '9')
			nums += 1;
		while (s[i] >= '0' && s[i] <= '9')
			i++;
		i++;
	}
	return (nums);
}

int	check_non_numeric(char *s)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (!ft_strchr("0123456789", s[i]))
			return (0);
		if (ft_strchr("0123456789", s[i]))
			num += 1;
		i++;
	}
	if (num == 0)
		return (0);
	return (1);
}

void set_value(t_args *args, int num, int k)
{
	if (k == 0)
	{
		if (num == 0 || num > 200)
			error_mes(1, args);
		args->num_of_philos = num;
		args->meal_counter = 0;	
	}
	else if (k == 1)
		args->time_to_die = num;
	else if (k == 2)
		args->time_to_eat = num;
	else if (k == 3)
		args->time_to_sleep = num;			
	else if (k == 4)
		args->meal_counter = num;
}

void check_values(t_args *args)
{
	if (args->num_of_philos < 0)
		error_mes(1, args);
	else if (args->time_to_die < 0)
		error_mes(1, args);
	else if (args->time_to_eat < 0)
		error_mes(1, args);
	else if (args->time_to_sleep < 0)
		error_mes(1, args);
	else if (args->meal_counter < 0)
		error_mes(1, args);
}

void	get_check_args(int argc, char **argv, t_args *args)
{
	int	k;
	int	num;

	k = 0;
	if (argc > 5 || argc < 4)
		error_mes(1, args);
	while (k < argc)
	{
		if (!check_non_numeric(argv[k]))
			error_mes(1, args);
		if (count_numbers(argv[k]) > 1)
			error_mes(1, args);
		else if (count_numbers(argv[k]) == 1)
		{
			num = ft_atoi(argv[k]);
			set_value(args, num, k);
		}
		k++;
	}
	pthread_mutex_init(&(args->dead_mutex), NULL);
	args->status = 100;
}
