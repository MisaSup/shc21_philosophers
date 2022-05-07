#include "../philo.h"

ssize_t get_miliseconds()
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * (ssize_t)1000 + current.tv_usec / 1000);
}

ssize_t get_timestamp(ssize_t start_time)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * (ssize_t)1000 + current.tv_usec / 1000) - start_time);
}

void timer(ssize_t start, int finish)
{
	while (get_timestamp(start) != finish)
		usleep(500);
}