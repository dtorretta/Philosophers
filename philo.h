#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdbool.h>

#define R "\033[31m"
#define G "\033[32m"
#define Y "\033[33m"
#define E "\033[0m"

typedef struct s_time 
{
    long start_time;
} t_time;

typedef struct s_program_state 
{
    bool terminate;
} t_program_state;

typedef struct s_forks //Representa los tenedores, con un mutex para proteger el acceso.
{
    //int i; //orden
    bool available;
    pthread_mutex_t lock;
} t_forks;

typedef struct s_philo
{
    int amount_philo; //number_of_philosophers
    int id; //orden
    int die; //time_to_die 
    int eat; //time_to_eat
    int sleep; //time_to_sleep
    int q; //number_of_times_each_philosopher_must_eat
    int meals;
    long last_meal_time; // Tiempo de la última comida
    pthread_t thread_id; //Cuando creas un hilo con pthread_create, se te proporciona un valor de tipo pthread_t que puedes utilizar para realizar operaciones sobre ese hilo, como esperar a que termine con pthread_join.
    t_forks *left_fork;  // Puntero al tenedor izquierdo
    t_forks *right_fork; // Puntero al tenedor derecho
    bool terminate;
    t_program_state *status;
    t_time *time;
} t_philo;

// typedef struct s_shared_data
// {
//     t_philo *philos;
//     t_program_state *state;
// } t_shared_data;

#endif


// //adds a new node at the end of the list
// void	ft_lstadd_back(t_philo **lst, t_philo *new) //porque t_philo **lst
// {
// 	t_philo	*temp;
// 	t_philo	*head;

// 	if (!new)
// 		return ;
// 	if (!*lst) // Si la lista está vacía, el primer nodo se convierte en la cabeza de la lista
// 	{
// 		*lst = new;
// 		//oara el caso de 1 filosofo, no enlazo el prev y next a si mismo porque quiero haacer uso en el futuro de estos null cuando cheque que exista los fork y que esten disponibles para poder comer.
// 		return ;
// 	}
// 	//printf("check 3\n"); //borrar		
// 	temp = *lst;
// 	head = *lst;
// 	//printf("check 4\n"); //borrar	
// 	//si quiero a;adir el nodo 3
	
// 	//printf("i: %d\n", i); //borrar
// 	//printf("head->philo: %d\n", head->philo); //borrar
// 	while (temp->next != head && temp->next) // ya no puedo usar solo while (temp->next) porque mi linked list es circular. no tiene fin
// 	{
// 		//printf("check 5\n"); //borrar
// 		temp = temp->next; //temp = nodo 2
// 	}
// 	//printf("check 6\n"); //borrar		
	
// 	//enlazo el 2 y el 3
// 	temp->next = new; //nodo 2->next = 3
// 	new->prev = temp; //nodo 3->prev = 2

// 	//enlazo los extremos
// 	new->next = head; //nodo 3->next = 1
// 	head->prev = new; //nodo 1->prev = 3
// }