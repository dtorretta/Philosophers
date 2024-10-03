/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:39:57 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/03 13:40:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_msg(void)
{
	printf("%s-------------------------------------------------%s\n", R, E);
	printf("%s                      Error%s\n", R, E);
	printf("%s-------------------------------------------------%s\n", R, E);
	printf("\nInsert valid arguments:\n");
	printf("%snumber of 🧠, time to 💀, time to 🍴, time to 😴%s\n", Y, E);
	printf("\nAn additional variable is also valid:\n");
	printf("%snumber of times each 🧠 must 🍴%s\n\n", Y, E);
	printf("example: 5 800 200 200 7\n\n");
	exit(EXIT_FAILURE);
}

//Only numeric arguments are accepted.
//If an error is found, it calls the error_msg function,
// which terminates the program execution.
//AGREGAR QUE NO PUEDEN SER 0 PHILOSOPOH ???????????
void	error_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
			else
				error_msg();
		}
		i++;
	}
}
