/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:11:07 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/15 04:22:14 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philo *philos)
{
	sem_unlink("/forks");
	sem_unlink("/print_sema");
	sem_unlink("/eating_philo");
	free(philos);
	// free(g_info.forks);
	free(g_info.full_list);
}

int		start(t_philo *philos)
{
	int			count;

	count = 0;
	while (count < g_philo_num)
	{
		philos[count].when_eat = get_relative_time();
		pthread_create(&philos[count].thread, NULL, philo_do, (void *)&philos[count]);
		count += 1;
	}
	// accurate_pause(20);
	// count = 1;
	// while (count < g_philo_num)
	// {
	// 	philos[count].when_eat = get_relative_time();
	// 	pthread_create(&philos[count].thread, NULL, philo_do, (void *)&philos[count]);
	// 	count += 2;
	// }
	count = 0;
	while (count < g_philo_num)
	{
		pthread_join(philos[count].thread, NULL);
		count++;
	}
	return (CONTINUE);
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
	free_all(philos);
	return (0);
}
