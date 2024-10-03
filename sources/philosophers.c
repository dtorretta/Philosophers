/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:39:04 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/03 16:24:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Before each movement, it checks if the moderator has set the termination flag.
//If the flag is false, it continues until it has taken both forks and eaten.
//ft_eat will return 1 if a philosopher dies.
static int	ft_eat(t_philo *philo, t_program_state *state)
{
	usleep(100);
	pthread_mutex_lock(&philo->right_fork->lock);
	if (state->terminate)
		return (1);
	printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id );
	pthread_mutex_lock(&philo->left_fork->lock);
	if (state->terminate)
		return (1);
	printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id);
	philo->last_meal_time = get_time(philo->time);
	printf("%ld %d is eating\n", get_time(philo->time), philo->id);
	usleep(philo->eat * 1000);
	philo->meals++;
	pthread_mutex_unlock(&philo->right_fork->lock);
	pthread_mutex_unlock(&philo->left_fork->lock);
	return (0);
}

//ft_eat will return 1 if a philosopher dies.
//After eating, they automatically start sleeping for a fixed period of time,
//and finally, they start thinking for an undefined period.
static void	*ft_routine(t_philo *philo)
{
	t_program_state	*state;

	state = philo->status;
	while (!state->terminate)
	{
		if (ft_eat(philo, state) == 1)
			break ;
		if (state->terminate)
			break ;
		printf("%ld %d is sleeping\n", get_time(philo->time), philo->id);
		usleep(philo->sleep * 1000); //que pasa si muere mientras duerme??
		printf("%ld %d is thinking\n", get_time(philo->time), philo->id);
	}
	return (NULL);
}

//If the number of philosophers is even (q % 2 == 0), 
// those in odd positions start eating.
//Otherwise (if the number of philosophers is odd), 
// those in even positions begin.
void	*ft_philosopher(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%ld %d is thinking\n", get_time(philo->time), philo->id);
	if (philo->amount_philo % 2 == 0)
	{
		if (philo->id % 2 != 0 || philo->id == 1)
			return (ft_routine(philo));
	}
	else 
	{
		if (philo->id % 2 == 0)
			return (ft_routine(philo));
	}
	usleep(philo->eat * 1000);
	return (ft_routine(philo));
}
