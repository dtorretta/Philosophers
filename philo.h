/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: dtorrett <dtorrett@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/09/03 17:05:53 by dtorrett          #+#    #+#             */
/*   Updated: 2024/09/03 17:05:53 by dtorrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define R "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define E "\033[0m"

typedef struct s_time
{
	long	start_time;
}	t_time;

typedef struct s_program_state
{
	bool	terminate;
}	t_program_state;

typedef struct s_forks
{
	pthread_mutex_t	lock;
}	t_forks;

//id -> order
//die -> lifetime
//q -> number of times each philosopher must eat
//last_meal_time will be counted since the philosopher STARTS eating
typedef struct s_philo
{
	int				amount_philo;
	int				id;
	int				die;
	int				eat;
	int				sleep;
	int				q;
	int				meals;
	long			last_meal_time;
	pthread_t		thread_id;
	t_forks			*left_fork;
	t_forks			*right_fork;
	bool			terminate;
	t_program_state	*status;
	t_time			*time;
}	t_philo;

/*ERRORS*/
void	error_msg(void);
void	error_check(char **av);
//faltan mas

/*INIT*/
void	init_philo(t_philo *philo, t_forks *forks, int i);
void	init_data(char **av, t_philo *philo, t_forks *forks);
long	init_time(void);
long	get_time(t_time *time);

/*UTILS*/
int		ft_atoi(const char *nptr);
void	ft_putendl_fd(char *s, int fd);
//FREE

/*ONE PHILO*/
int		one_philo(t_philo *philo, t_forks *forks);

/*MODERATOR*/
void	*ft_moderator(void *arg);

/*PHILOSOPHERS*/
void	*ft_philosopher(void *arg);

#endif