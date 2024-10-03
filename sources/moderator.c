/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moderator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:42:12 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/03 13:12:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_death(t_philo *philo)
{
	int		i;
	long	current_time;

	i = -1;
	while (++i < philo->amount_philo) 
	{
		current_time = get_time(philo->time);
		if ((current_time - philo[i].last_meal_time) >= philo->die)
		{
			philo->status->terminate = true;
			printf("%ld %d died\n", get_time(philo->time), philo[i].id);
			return (1);
		}
	}
	return (0);
}

//the modderator hecks if any philosopher have died and if they 
//have eaten enough.
//if i is equal to the amount of philosophers, that means that all 
//of them have eaten enough times
void	*ft_moderator(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (!philo->status->terminate)
	{
		if (check_death(philo) == 1)
			break ;
		if (philo->status->terminate)
			break ;
		i = -1;
		while (philo->q > 0 && ++i < philo->amount_philo)
		{
			if (philo[i].meals < philo->q)
				break ;
		}
		if (philo->q > 0 && i == philo->amount_philo)
		{
			philo->status->terminate = true;
			break ;
		}
		usleep (100000); //revisa cada segundo //che pero no es un monton?
	}
	return (NULL);
}
