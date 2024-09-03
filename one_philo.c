/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:34:47 by dtorrett          #+#    #+#             */
/*   Updated: 2024/09/03 17:44:28 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*mini_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("1 1 has taken a fork\n");
	printf("%d 1 died\n", philo->die);
	return (NULL);
}

int	one_philo(t_philo *philo, t_forks *forks)
{
	pthread_t	one_philo;

	init_philo(philo, forks, 0);
	pthread_create(&one_philo, NULL, mini_philo, (void *)philo);
	pthread_join(one_philo, NULL);
	free(philo);
	free(forks);
	return (0);
}
