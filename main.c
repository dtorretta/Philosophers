/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:00:24 by marvin            #+#    #+#             */
/*   Updated: 2024/08/18 20:00:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_msg()
{
	printf("%s----------------------%s\n", R, E);
	printf("%s        Error%s\n", R, E);
	printf("%s----------------------%s\n", R, E);
	printf("insert valid arguments:\n");
	printf("%snumber of 🧠, time to 💀, time to 🍴, time to 😴%s\n", Y, E);
	printf("an additional variable is also valid:\n");
	printf("%snumber of times each 🧠 must 🍴%s\n\n", Y, E);
	printf("example: 5 800 200 200 7\n");
	exit(EXIT_FAILURE);
}

//solo se aceptan numeros
//si encuentra error, llama a la funcion error_msg que finaliza la ejecucion del programa
//AGREGAR QUE NO PUEDEN SER 0 PHILOSOPOH
void error_check(char **av)
{
	int i;
	int j;
	
	i = 1;
	while(av[i])
	{
		j = 0;
		while(av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				error_msg();
		}
		i++;
	}
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

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	else
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

long init_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

long get_time(t_time *time)
{
    long current;
    
    current = init_time();
    return (current - time->start_time);
}

int ft_eat(t_philo *philo, t_program_state *state)
{
	pthread_mutex_lock(&philo->right_fork->lock);
	if (state->terminate)
		return (1);
	printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id );
	if (state->terminate)
		return (1);
	usleep(100);
	pthread_mutex_lock(&philo->left_fork->lock);
	if (state->terminate)
		return (1);
	printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id);
	philo->last_meal_time = get_time(philo->time);
	printf("%ld %d is eating\n", get_time(philo->time), philo->id);
	if (state->terminate)
		return (1);
	usleep(philo->eat * 1000); //espera a que termine de comer
	philo->meals++;
	pthread_mutex_unlock(&philo->right_fork->lock);
	pthread_mutex_unlock(&philo->left_fork->lock);
	return(0);
}

void *ft_routine(t_philo *philo)
{
	t_program_state *state = philo->status;
	while (!state->terminate)
	{
		usleep(100);
		if (state->terminate)
			break;
		if (ft_eat(philo, state) == 1)
			break;
		if (state->terminate)
			break;
		printf("%ld %d is sleeping\n", get_time(philo->time), philo->id);
		usleep(philo->sleep * 1000); //espera a que termine de dormir
		if (state->terminate)
			break;
		printf("%ld %d is thinking\n", get_time(philo->time), philo->id);
		if (state->terminate)
			break;
	}
	return(NULL);
}

void *ft_philosopher(void *arg)
{
	t_philo  *philo;
	
	philo = (t_philo *)arg;
	printf("%ld %d is thinking\n", get_time(philo->time), philo->id);
	if(philo->amount_philo % 2 == 0) //si hay cantidad par
	{
		if(philo->id % 2 != 0 || philo->id == 1) //empiezan a comer los filosofos impares
			return(ft_routine(philo));
	}
	else //si hay cantidad impar
	{
		if(philo->id % 2 == 0) //empiezan a comer los filosofos pares
			return(ft_routine(philo));
	}
	usleep(philo->eat * 1000);
	return(ft_routine(philo));
}

// Control del tiempo de vida de los filósofos
int check_death(t_philo *philo)
{
	int i;
	long current_time;
	
	i = -1;
	while(++i < philo->amount_philo) 
	{
		current_time = get_time(philo->time);
		if((current_time - philo[i].last_meal_time) >= philo->die)
		{
			philo->status->terminate = true;
			printf("%ld %d died\n", get_time(philo->time), philo[i].id);
			return(1);
		}
	}
	return(0);
}

void *ft_moderator(void *arg)
{
	t_philo  *philo;
	
	philo = (t_philo *)arg;
	int i;	
	while(!philo->status->terminate) //chequeos que se realizan hasta que alguien muere, o todos comen
	{
		if (check_death(philo) == 1)
			break;
		if (philo->status->terminate) //necesario?
			break;
		i = -1;
		while(philo->q > 0 && ++i < philo->amount_philo)
		{
			if(philo[i].meals < philo->q)
				break;
		}
		if (philo->q > 0 && i == philo->amount_philo) //si termina el while loop con i = n es porque todos comieron
		{   
			philo->status->terminate = true;
			break;
		}
		usleep(100000); //revisa cada segundo //che pero no es un monton?
	}
	return(NULL);
}

void init_data(char **av, t_philo *philo, t_forks *forks, int i)
{
    philo[i].amount_philo = atoi(av[1]);
    philo[i].id = i + 1; // Enumerar desde 1
    philo[i].die = atoi(av[2]);
    philo[i].eat = atoi(av[3]);
    philo[i].sleep = atoi(av[4]);
    if (av[5])
        philo[i].q = atoi(av[5]);
    else
        philo[i].q = -1;
   
    philo[i].meals = 0;
    philo[i].last_meal_time = 0;
    philo[i].right_fork = &forks[i];
    philo[i].left_fork = &forks[(i + 1) % atoi(av[1])];
    philo[i].terminate = false;
}

void threads(char **av, t_philo *philo, t_forks *forks, t_program_state *state, t_time *time)
{
	int i;
	pthread_t moderator_id;
	
	i = -1;	
	while(++i < atoi(av[1])) //tanto los filosofos como los tenedores se inicializan desde el 0
	{
		pthread_mutex_init(&forks[i].lock, NULL); // Inicializar tenedores
		init_data(av, philo, forks, i); // Inicializar filósofos
		philo[i].status = state; // Asocia el estado con cada filósofo //si lo saco sa segfault
		philo[i].time = time; 
		usleep(100);
		pthread_create(&philo[i].thread_id, NULL, ft_philosopher, &philo[i]); //Crear threads para los filósofos. Cada hilo comenzará a ejecutar la función ft_philosopher
		usleep(100);
	}
	pthread_create(&moderator_id, NULL, ft_moderator, (void*)philo); //Crear 1 thread para el monitor
	pthread_join(moderator_id, NULL); //Esperar a que el moderator termine
	i = -1;
	while(++i < atoi(av[1])) //Esperar a que los filósofos terminen
		pthread_join(philo[i].thread_id, NULL);
	i = -1;
	while(++i < atoi(av[1]))
		pthread_mutex_destroy(&forks[i].lock);
	free(philo);
	free(forks);
}

int main(int ac, char **av)
{
	t_philo *philo;
	t_forks  *forks;
	t_program_state state;
	t_time time;

	if (ac < 5 || ac > 6) 
		error_msg();
	error_check(av);
	philo = malloc(sizeof(t_philo) * atoi(av[1])); //philo ahora apunta a la primera estructura en un bloque continuo de memoria que tiene espacio para n estructuras t_philo.
	forks = malloc(sizeof(t_forks) * atoi(av[1]));
	if(!philo || !forks)
		return(EXIT_FAILURE);
	if(atoi(av[1]) == 1)
	{
		printf("1 1 is thinking\n");
		printf("1 1 has taken a fork\n");
		printf("%d 1 died\n", atoi(av[2]));
		return(0);
	}
	time.start_time = init_time();
	state.terminate = false;
	threads(av, philo, forks, &state, &time);
	return(0);
}
