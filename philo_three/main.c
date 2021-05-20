/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:11:07 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/20 21:09:24 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	wait_p_end(t_philo *philos)
{
	int			count;
	int			status;

	count = 0;
	status = 0;
	while (count < g_philo_num)
	{
		waitpid(philos[count].pid, &status, WCONTINUED);
		count++;
	}
}

int		start(t_philo *philos)
{
	int			count;

	count = 0;
	while (count < g_philo_num)
	{
		philos[count].pid = fork();
		if (philos[count].pid == 0)
		{
			philos[count].when_eat = get_relative_time();
			philo_do(&philos[count]);
			break ;
		}
		count += 1;
	}
	return (0);
}

int		main(int argc, char *argv[])
{
	t_philo	*philos;

	if (set_info_argv(&g_info, argc, argv) < 0)
	{
		printf("Argument Error\n");
		return (1);
	}
	init_info(&g_info);
	philos = malloc(sizeof(t_philo) * g_philo_num);
	set_philos(philos);
	sema_init(&g_info);
	start(philos);
	wait_p_end(philos);
	return (0);
}
