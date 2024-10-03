/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:40:53 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/03 14:24:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo(t_philo *philo, t_forks *forks, int i)
{
	philo[i].id = i + 1;
	philo[i].meals = 0;
	philo[i].last_meal_time = 0;
	philo[i].right_fork = &forks[i];
	//philo[i].left_fork = &forks[(i + 1) % philo[i].amount_philo];
	philo[i].left_fork = &forks[(i + 1) % philo->amount_philo];
	philo[i].terminate = false;
}

void	init_data(char **av, t_philo *philo)
{
	int i;
	int amount;
	
	i = -1;
	amount = atoi(av[1]);
	while (++i < amount)
	{
		philo[i].amount_philo = amount;
		philo[i].die = atoi(av[2]);
		philo[i].eat = atoi(av[3]);
		philo[i].sleep = atoi(av[4]);
		if (av[5])
			philo[i].q = atoi(av[5]);
		else
			philo[i].q = -1;
	}
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
