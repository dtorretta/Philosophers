/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:32:23 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/06 17:58:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int check_status2(t_philo *philo)
{
	pthread_mutex_lock(&philo->status->lock);
		if (philo->status->terminate)
		{
			pthread_mutex_unlock(&philo->status->lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->status->lock);
	return (0);
}

int check_status(t_philo *philo, t_program_state *state, int i)
{
	pthread_mutex_lock(&state->lock);
		if (state->terminate)
		{
			if(i == 1 || i == 3)
				pthread_mutex_unlock(&philo->left_fork->lock);
			if(i == 2 || i == 3)
				pthread_mutex_unlock(&philo->right_fork->lock);
			pthread_mutex_unlock(&state->lock);
			return (1);
		}
	pthread_mutex_unlock(&state->lock);
	return (0);
}


int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' '))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}

void ft_putendl_fd(char *s, int fd)
{
    size_t count;
    
    count = 0;
    if (!s)
        return;
    while (s[count])
        count++;
    write(fd, s, count);
    write(fd, "\n", 1);
}

void ft_free(t_philo *philo, t_forks *forks)
{
	int i;
	
	i= -1;
	while (++i < philo->amount_philo)
	{
		pthread_mutex_destroy(&philo[i].lock);
		if (&philo[i].left_fork)
			pthread_mutex_destroy(&philo[i].left_fork->lock);
	}
	free(philo);
	free(forks);
}
