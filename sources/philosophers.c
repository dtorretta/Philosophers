/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:39:04 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/06 18:19:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//Before each movement, it checks if the moderator has set the termination flag.
//If the flag is false, it continues until it has taken both forks and eaten.
//ft_eat will return 1 if a philosopher dies.
static int take_forks(t_philo *philo, t_program_state *state)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork->lock);
		if (check_status(philo, state, 1)) //lefyt
			return(1);
		printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id );
		pthread_mutex_lock(&philo->right_fork->lock);
		if (check_status(philo, state, 3))
			return(1);		
		printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id);	
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->lock);
		if (check_status(philo, state, 2))
			return(1);
		printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id);
		pthread_mutex_lock(&philo->left_fork->lock);
		if (check_status(philo, state, 3))
			return(1);
		printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id);
	}
	printf("%ld %d is eating\n", get_time(philo->time), philo->id);
	return(0);
}

static int	ft_eat(t_philo *philo, t_program_state *state)
{
	usleep(100);
	if(take_forks(philo, state))
		return(1);
	pthread_mutex_lock(&philo->lock);
	philo->last_meal_time = get_time(philo->time);
	philo->meals++;
	pthread_mutex_unlock(&philo->lock);
	usleep(philo->eat * 1000 + 100);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->left_fork->lock);
		usleep(100); //ver
		pthread_mutex_unlock(&philo->right_fork->lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->right_fork->lock);
		usleep(100); //ver
		pthread_mutex_unlock(&philo->left_fork->lock);
	}	
	return (0);
}

static void	*ft_routine(t_philo *philo)
{
	t_program_state	*state;

	state = philo->status;
	while (1)
	{
		usleep(100);
		if (check_status2 (philo))
			break ;
		if (ft_eat(philo, state))
			break ;
		if (check_status2 (philo))
			break ;
		printf("%ld %d is sleeping\n", get_time(philo->time), philo->id);
		usleep(philo->sleep * 1000 + 200);
		if (check_status2 (philo))
			break ;
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
