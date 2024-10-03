/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:39:57 by dtorrett          #+#    #+#             */
/*   Updated: 2024/10/03 16:13:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	error_msg(void)
{
	printf("%s-------------------------------------------%s\n", R, E);
	printf("%s                  Error%s\n", R, E);
	printf("%s-------------------------------------------%s\n", R, E);
	printf("\nInsert valid arguments:\n");
	printf("\n%s🧠 [Number of philosophers]\n", Y);
	printf("%s💀 [Time to die]\n", Y);
	printf("%s🍴 [Time to eat]\n", Y);
	printf("%s😴 [Time to sleep] %s\n", Y, E);
	printf("\nAn additional variable is also valid:\n");
	printf("\n%s✅ [Number of meals]%s\n", Y, E);
	printf("\nexample: 5 800 200 200 7\n\n");
	exit(EXIT_FAILURE);
}

//Only numeric arguments are accepted.
//If an error is found, it calls the error_msg function,
// which terminates the program execution.
void	error_check(char **av)
{
	int	i;
	int	j;

	i = 1;
	if (atoi(av[1]) == 0)
		error_msg();
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
