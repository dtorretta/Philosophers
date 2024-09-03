/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:40:53 by dtorrett          #+#    #+#             */
/*   Updated: 2024/09/03 18:21:39 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	init_philo(t_philo *philo, t_forks *forks, int i)
{
	philo[i].id = i + 1;
	philo[i].meals = 0;
	philo[i].last_meal_time = 0;
	philo[i].right_fork = &forks[i];
	philo[i].left_fork = &forks[(i + 1) % philo[i].amount_philo];
	philo[i].terminate = false;
}

void	init_data(char **av, t_philo *philo, t_forks *forks)
{
	philo->amount_philo = atoi(av[1]);
	philo->die = atoi(av[2]);
	philo->eat = atoi(av[3]);
	philo->sleep = atoi(av[4]);
	if (av[5])
		philo->q = atoi(av[5]);
	else
		philo->q = -1;
}

long	init_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long	get_time(t_time *time)
{
	long	current;

	current = init_time();
	return (current - time->start_time);
}
