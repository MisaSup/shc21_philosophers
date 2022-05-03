/* #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h> */
#include "../philo.h"

ssize_t get_miliseconds()
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * (ssize_t)1000 + current.tv_usec / 1000);
}

ssize_t get_timestamp(ssize_t start_time)
{
	// printf("times %ld %ld\n", get_miliseconds(), start_time);
	return (get_miliseconds() - start_time);
}

/* int main()
{
	struct timeval start;
	struct timeval end;

	gettimeofday(&start, NULL);
	printf("start sec: %ld micro: %d \n", start.tv_sec, start.tv_usec);
	ssize_t st =  get_miliseconds(&start);
	// usleep(10000000);
	// usleep(1500 * 1000);
	sleep(2);
	// write(1, "h\n", 2);

	gettimeofday(&end, NULL);
	ssize_t en = get_timestamp(st);

	//  t = end.tv_usec - start.tv_usec;

	printf("%ld s, %d micros\n", end.tv_sec - start.tv_sec , end.tv_usec - start.tv_usec);
	printf("%ld ms\n", (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec)/1000);
	printf("%ld ms\n", en);

	return (0);
} */