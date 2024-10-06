/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:33:53 by dtorrett          #+#    #+#             */
/*   Updated: 2024/09/03 17:33:53 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	threads(t_philo *philo, t_forks *forks, t_program_state *state, t_time *time)
{
	int			i;
	pthread_t	moderator_id;

	i = -1;
	while (++i < philo->amount_philo)
	{
		init_philo(philo, forks, i);
		philo[i].status = state;
		philo[i].time = time; 
		usleep(100);
		pthread_create(&philo[i].thread_id, NULL, ft_philosopher, &philo[i]);
		usleep(100);
	}
	pthread_create(&moderator_id, NULL, ft_moderator, (void *)philo);
	pthread_join(moderator_id, NULL);
	i = -1;
	while (++i < philo->amount_philo)
		pthread_join(philo[i].thread_id, NULL);
	ft_free(philo, forks);
}

int	main(int ac, char **av)
{
	t_philo			*philo;
	t_forks			*forks;
	t_program_state	state;
	t_time			time;

	if (ac < 5 || ac > 6) 
		error_msg();
	error_check(av);
	philo = malloc(sizeof(t_philo) * atoi(av[1]));
	forks = malloc(sizeof(t_forks) * atoi(av[1]));
	if (!philo || !forks)
		return (EXIT_FAILURE);
	init_data(av, philo, forks);
	if (atoi(av[1]) == 1)
		return (one_philo(philo, forks));
	time.start_time = init_time();
	state.terminate = false;
	threads(philo, forks, &state, &time);
	return (0);
}
