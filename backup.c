// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   Philo.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/08/18 20:00:24 by marvin            #+#    #+#             */
// /*   Updated: 2024/08/18 20:00:24 by marvin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// void error_msg()
// {
// 	printf("%s----------------------%s\n", R, E);
// 	printf("%s        Error%s\n", R, E);
// 	printf("%s----------------------%s\n", R, E);
// 	printf("insert valid arguments:\n");
// 	printf("%snumber of 🧠, time to 💀, time to 🍴, time to 😴%s\n", Y, E);
// 	printf("an additional variable is also valid:\n");
// 	printf("%snumber of times each 🧠 must 🍴%s\n\n", Y, E);
// 	printf("example: 5 800 200 200 7\n");
// 	exit(EXIT_FAILURE);
// }

// //solo se aceptan numeros
// //si encuentra error, llama a la funcion error_msg que finaliza la ejecucion del programa
// //AGREGAR QUE NO PUEDEN SER 0 PHILOSOPOH
// void error_check(char **av)
// {
// 	int i;
// 	int j;
	
// 	i = 1;
// 	while(av[i])
// 	{
// 		j = 0;
// 		while(av[i][j])
// 		{
// 			if (av[i][j] >= '0' && av[i][j] <= '9')
// 				j++;
// 			else
// 				error_msg();
// 		}
// 		i++;
// 	}
// }

// int	ft_atoi(const char *nptr)
// {
// 	int	i;
// 	int	sign;
// 	int	result;

// 	i = 0;
// 	result = 0;
// 	sign = 1;
// 	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == ' '))
// 		i++;
// 	if (nptr[i] == '-')
// 	{
// 		sign = -1;
// 		i++;
// 	}
// 	else if (nptr[i] == '+')
// 		i++;
// 	while (nptr[i] >= '0' && nptr[i] <= '9')
// 	{
// 		result = result * 10 + nptr[i] - '0';
// 		i++;
// 	}
// 	return (result * sign);
// }

// size_t	ft_strlen(const char *s)
// {
// 	size_t	count;

// 	count = 0;
// 	while (s[count])
// 		count++;
// 	return (count);
// }

// void	ft_putendl_fd(char *s, int fd)
// {
// 	if (!s)
// 		return ;
// 	else
// 		write(fd, s, ft_strlen(s));
// 	write(fd, "\n", 1);
// }

// //convierte de microsegundos a milisegundos
// // long get_time(void)
// // {
// //     struct timeval time;
// //     gettimeofday(&time, NULL);
// //     return (time.tv_sec * 1000) + (time.tv_usec / 1000);
// // }

// long init_time(void)
// {
//     struct timeval time;
//     gettimeofday(&time, NULL);
//     return (time.tv_sec * 1000) + (time.tv_usec / 1000);
// }

// long get_time(t_time *time)
// {
//     long current;
    
//     current = init_time();
//     return (current - time->start_time);
// }

// void *ft_eat(t_philo *philo)
// {
// 	t_program_state *state = philo->status;
// 	//printf("PHILO %d ⚠️\n", philo->id);
// 	while (!state->terminate)
// 	{
// 		/*********EAT**************/
// 		usleep(100);
// 		if (state->terminate)
// 			break;
// 		pthread_mutex_lock(&philo->right_fork->lock);
// 		if (state->terminate)
// 			break;
// 		printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id );
// 		if (state->terminate)
// 			break;
// 		usleep(100);
// 		pthread_mutex_lock(&philo->left_fork->lock);
// 		if (state->terminate)
// 			break;
// 		printf("%ld %d has taken a fork\n", get_time(philo->time), philo->id);
// 		philo->last_meal_time = get_time(philo->time);
// 		printf("%ld %d is eating\n", get_time(philo->time), philo->id);
// 		if (state->terminate)
// 			break;
// 		usleep(philo->eat * 1000); //espera a que termine de comer
// 		philo->meals++;
// 		printf("MEALS %d ⚠️\n", philo->meals); //BORRAR
// 		pthread_mutex_unlock(&philo->right_fork->lock);
// 		pthread_mutex_unlock(&philo->left_fork->lock);
// 		if (state->terminate)
// 			break;
		
// 		/*********SLEEP**************/
// 		printf("%ld %d is sleeping\n", get_time(philo->time), philo->id);
// 		usleep(philo->sleep * 1000); //espera a que termine de dormir
// 		if (state->terminate)
// 			break;
		
// 		/*********THINK**************/
// 		printf("%ld %d is thinking\n", get_time(philo->time), philo->id);
// 		if (state->terminate)
// 			break;
// 	}
// 	//printf("check BBB\n"); //borrar
// 	printf("FINALIZO EL PHILO %d ⚠️⚠️⚠️⚠️⚠️\n", philo->id);
// 	//exit(EXIT_FAILURE); //borrar
// 	return(NULL);
// }

// void *ft_philosopher(void *arg)
// {
// 	t_philo *philo = (t_philo *)arg; //esto es lo que me permite acceder a la funcion

// 	printf("%ld %d is thinking\n", get_time(philo->time), philo->id);
// 	//printf("numero de philo : %d\n", philo->id); //borrar
// 	if(philo->amount_philo % 2 == 0) //si hay cantidad par
// 	{
// 		if(philo->id % 2 != 0 || philo->id == 1) //empiezan a comer los filosofos impares
// 			return(ft_eat(philo));
// 	}
// 	else //si hay cantidad impar
// 	{
// 		if(philo->id % 2 == 0) //empiezan a comer los filosofos pares
// 			return(ft_eat(philo));
// 	}
// 	/*********THINK**************/
// 	//en el caso de que no sea de los seleccionados
// 	//printf("%ld %d is thinking AAA\n", get_time(philo->time), philo->id);
// 	//printf("check BB\n"); //borrar
// 	usleep(philo->eat * 1000);
// 	return(ft_eat(philo));
// }

// void *ft_moderator(void *arg)
// {
// 	t_philo  *philo = (t_philo *)arg;
// 	//t_shared_data  *shared_data = (t_shared_data *)arg;
// 	//t_philo *philo = shared_data->philos;
// 	//t_program_state *state = shared_data->state; //porque status aca si tiene pointer?
// 	long current_time;
// 	int i;
// 	//usleep(100000); //de foy un leve retraso para que si o si vaya primero el philosohp
// 	//printf("CHECK 00\n"); //borrar
// 	//printf("CHECK STATUS 03 %d\n", philo[0].status->terminate); //borrar
	
// 	// pthread_mutex_lock(&philo[i].right_fork->lock);
// 	// pthread_mutex_lock(&philo[i].left_fork->lock);
	
	
// 	while(!philo->status->terminate) //chequeos que se realizan hasta que alguien muere, o todos comen
// 	//while(!state->terminate) //chequeos que se realizan hasta que alguien muere, o todos comen
// 	{
// 		i = -1;
// 		// pthread_mutex_lock(&philo[i].right_fork->lock);
// 		// pthread_mutex_lock(&philo[i].left_fork->lock);
		
// 		while(++i < philo->amount_philo) // Control del tiempo de vida de los filósofos
// 		{
// 			//pthread_mutex_lock(&philo[i].right_fork->lock);
// 			//pthread_mutex_lock(&philo[i].left_fork->lock);
// 			//printf("CHECK 01\n"); //borrar
// 			current_time = get_time(philo->time);
// 			//current_time = init_time();
// 			if((current_time - philo[i].last_meal_time) >= philo->die) //poruqe aveces con . y otras con ->?
// 			{
// 				//printf("tiempo de vida del philo %d : %ld\n", philo[i].id, (current_time - philo[i].last_meal_time));
// 				//pthread_mutex_lock(&philo[i].right_fork->lock);
// 				//pthread_mutex_lock(&philo[i].left_fork->lock);
// 				philo->status->terminate = true;
// 				printf("%ld %d died\n", get_time(philo->time), philo[i].id);
// 				//tengo que usar philo[i].id en vez de filo porque los filosofos estan numerados desde 1
// 				//exit(EXIT_FAILURE);
// 				//printf("CHECK 02\n"); //borrar
				
// 				//state->terminate = true;
// 				break;
// 			}
// 			//pthread_mutex_unlock(&philo[i].right_fork->lock);
// 			//pthread_mutex_unlock(&philo[i].left_fork->lock);
// 		}
// 		if (philo->status->terminate)
// 			break;
// 		i = -1;
// 		while(philo->q > 0 && ++i < philo->amount_philo)
// 		{
// 			if(philo[i].meals < philo->q)
// 				break;
// 		}
		
// 		if (philo->q > 0 && i == philo->amount_philo) //si termina el while loop con i = n es porque todos comieron
// 		{   
// 			printf("CHEEEEEE ⚠️⚠️⚠️⚠️⚠️\n");
// 			philo->status->terminate = true;
// 			break;
// 			//return(EXIT_SUCCESS);
// 		}
// 		//usleep(philo->eat * 1000); //pasa de milisegundo a microsegundo // Revisar el estado cada vez que alguien termina de comer
// 		//pthread_mutex_unlock(&philo[i].right_fork->lock);
// 		//pthread_mutex_unlock(&philo[i].left_fork->lock);
// 		usleep(100000); //revisa cada segundo
// 	}
// 	printf("FINALIZO EL MODERADOR ⚠️⚠️⚠️⚠️⚠️\n");
// 	//exit(EXIT_FAILURE);
// 	return(NULL);
// }



// //data[0].id = 1
// // void init_data(char **av, t_philo *data, t_forks  *forks, int i)
// // {
// // 	//data->terminate->terminate = false;
// // 	data[i]->amount_philo = atoi(av[1]);
// // 	data->id = (i + 1); //para que esten numerados desde el 1
// // 	printf("numero de philo DDENTRO: %d\n", data->id); //borrar
// // 	data->die = atoi(av[2]);
// // 	data->eat = atoi(av[3]);
// // 	data->sleep = atoi(av[4]);
// // 	if(av[5])
// // 		data->q = atoi(av[5]); // Si no se pasa el argumento, continuar indefinidamente
// // 	else
// //         data->q = -1; 
// // 	data->meals = 0;
// // 	data->last_meal_time = 0; // Inicializa el tiempo de la última comida
// // 	data->right_fork = &forks[i]; //el primer tenedor es el 0
// // 	data->left_fork = &forks[(i + 1) % atoi(av[1])];  //con esto me aseguro que el ultimo filosofo agarre el tenedor 0
// // 	data->terminate = false;
// // 	//data->status = NULL;
// // 	//printf("fork: %d\n", data->fork); //borrar
// // }
// void init_data(char **av, t_philo *philo, t_forks *forks, int i) {
//     philo[i].amount_philo = atoi(av[1]);
//     philo[i].id = i + 1; // Enumerar desde 1
//     //printf("numero de philo DENTRO: %d\n", philo[i].id); // Imprimir el ID dentro de init_data

//     philo[i].die = atoi(av[2]);
//     philo[i].eat = atoi(av[3]);
//     philo[i].sleep = atoi(av[4]);
//     if (av[5])
//         philo[i].q = atoi(av[5]);
//     else
//         philo[i].q = -1;
    
//     philo[i].meals = 0;
//     philo[i].last_meal_time = 0;
//     philo[i].right_fork = &forks[i];
//     philo[i].left_fork = &forks[(i + 1) % atoi(av[1])];
//     philo[i].terminate = false;
// }

// int main(int argc, char **argv)
// {
// 	//(void)argv;
// 	//printf("check 00\n"); //borrar
// 	t_philo *philo;
// 	t_forks  *forks;
// 	pthread_t moderator_id;
// 	t_program_state state; // Estructura de estado compartida
// 	t_time time;
// 	//t_shared_data shared_data; //no deberia ser puntero?  //creo un sahred data para poder apsarle al moderador el puntero de ambas cosas
// 	int i;
// 	int q_philos;
// 	if (argc < 5 || argc > 6) 
// 		error_msg();
// 	i = -1;	
// 	q_philos = atoi(argv[1]);
// 	error_check(argv);
// 	philo = malloc(sizeof(t_philo) * q_philos); //philo ahora apunta a la primera estructura en un bloque continuo de memoria que tiene espacio para n estructuras t_philo.
// 	forks = malloc(sizeof(t_forks) * q_philos);
// 	if(!philo || !forks)
// 		return(EXIT_FAILURE);
// 	time.start_time = init_time();
// 	// shared_data.philos = philo; //es necesario?
// 	// shared_data.state = &state; //es necesario?
// 	state.terminate = false;
// 	//printf("CHECK STATUS 01 %d\n", state.terminate); //borrar
// 	while(++i < q_philos) //tanto los filosofos como los tenedores se inicializan desde el 0
// 	{
// 		pthread_mutex_init(&forks[i].lock, NULL); // Inicializar tenedores
// 		//printf("valor I %d\n", i + 1); //borrar
// 		init_data(argv, philo, forks, i); // Inicializar filósofos
// 		//philo[i].status = false;
// 		philo[i].status = &state; // Asocia el estado con cada filósofo //si lo saco sa segfault
// 		philo[i].time = &time; 
// 		//printf("CHECK STATUS 02 %d\n", philo[i].status->terminate); //borrar
// 		//printf("CHECK 01\n"); //borrar
		
// 		//printf("numero de philo FUERA : %d\n", philo[i].id); //borrar
// 		usleep(100);
// 		pthread_create(&philo[i].thread_id, NULL, ft_philosopher, &philo[i]); //Crear threads para los filósofos. Cada hilo comenzará a ejecutar la función ft_philosopher
// 		usleep(100);
// 	}
// 	pthread_create(&moderator_id, NULL, ft_moderator, (void*)philo); //Crear 1 thread para el monitor
// 	//pthread_create(&moderator_id, NULL, ft_moderator, (void*)&shared_data); //Crear 1 thread para el monitor
// 	pthread_join(moderator_id, NULL); //Esperar a que el moderator termine
// 	i = -1;
// 	while(++i < q_philos) //Esperar a que los filósofos terminen
// 	{	
// 		pthread_join(philo[i].thread_id, NULL);
// 	}
// 	//pthread_join(moderator_id, NULL); //Esperar a que el moderator termine
// 	i = -1;
// 	while(++i < q_philos)
// 		pthread_mutex_destroy(&forks[i].lock);
// 	// printf("check 08\n"); //borrar
// 	free(philo);
// 	free(forks);
// 	return(0);
// }
