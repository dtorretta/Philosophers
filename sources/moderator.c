/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moderator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:42:12 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/07 12:16:08 by marvin           ###   ########.fr       */
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
		pthread_mutex_lock(&philo[i].lock);
		if ((current_time - philo[i].last_meal_time) >= philo->die)
		{
			pthread_mutex_lock(&philo->status->lock);
			philo->status->terminate = true;
			printf("%ld %d died\n", get_time(philo->time), philo[i].id);
			pthread_mutex_unlock(&philo->status->lock);
			pthread_mutex_unlock(&philo[i].lock);
			return (1);
		}
		pthread_mutex_unlock(&philo[i].lock);
	}
	return (0);
}

static int	check_meals(t_philo *philo)
{
	int		i;
	
	i = -1;
	while (philo->q > 0 && ++i < philo->amount_philo)
	{
		pthread_mutex_lock(&philo[i].lock);
		if (philo[i].meals < philo->q)
		{
			pthread_mutex_unlock(&philo[i].lock);
			break ;
		}
		pthread_mutex_unlock(&philo[i].lock);
	}
	if (philo->q > 0 && i == philo->amount_philo)
	{
		pthread_mutex_lock(&philo->status->lock);
		philo->status->terminate = true;
		pthread_mutex_unlock(&philo->status->lock);
		return (1);
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

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_status2 (philo))
			break ;
		if (check_death(philo))
			break ;
		if (check_meals(philo))
			break ;
	}
	return (NULL);
}
