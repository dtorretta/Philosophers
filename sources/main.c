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

static void	threads(t_philo *philo, t_forks *forks, t_program_state *state,
			t_time *time)
{
	int			i;
	pthread_t	moderator_id;

	i = -1;
	//printf("general check 03! philo->eat: %d\n", philo->eat); //borrar
	while (++i < philo->amount_philo)
	{
		pthread_mutex_init(&forks[i].lock, NULL);
		init_philo(philo, forks, i);
		//printf("check 04! philo number %d eat: %d\n", i + 1, philo[i].eat); //borrar
		philo[i].status = state;
		philo[i].time = time; 
		usleep(100);
		//printf("check 05! philo number %d eat: %d\n", i + 1 , philo[i].eat); //borrar
		pthread_create(&philo[i].thread_id, NULL, ft_philosopher, &philo[i]);
		//printf("check 06! philo number %d eat: %d\n", i + 1 , philo[i].eat); //borrar
		usleep(100);
	}
	pthread_create(&moderator_id, NULL, ft_moderator, (void *)philo);
	pthread_join(moderator_id, NULL);
	i = -1;
	while (++i < philo->amount_philo)
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while (++i < philo->amount_philo)
		pthread_mutex_destroy(&forks[i].lock);
	free(philo);
	free(forks);
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
	init_data(av, philo);
	//printf("general check 00! philo->eat: %d\n", philo->eat); //borrar
	if (atoi(av[1]) == 1)
		return (one_philo(philo, forks));
	time.start_time = init_time();
	state.terminate = false;
	//usleep(100); //veer
	//printf("general check 02! philo->eat: %d\n", philo->eat); //borrar
	threads(philo, forks, &state, &time);
	return (0);
}
