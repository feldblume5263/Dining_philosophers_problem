/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:10:44 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/19 21:35:40 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	use_fork_without_dup(t_philo *philo, t_info *info)
{
	sem_wait(info->forks);
	sem_wait(info->forks);
	doing(RIGHT_TAKEN, philo, get_relative_time());
	doing(LEFT_TAKEN, philo, get_relative_time());
	doing(EATING, philo, get_relative_time());
	philo->meal_num++;
	if (info->meal_full != FALSE && philo->meal_num == info->meal_full)
	{
		info->full_list[philo->index] = 1;
		printf("[%lu]\t %d\t", get_relative_time(), philo->index + 1);
		printf("is now full and happy   :)\n");
		sem_post(info->forks);
		sem_post(info->forks);
		return (END);
	}
	philo->when_eat = get_relative_time();
	spend_time_of(EATING);
	sem_post(info->forks);
	sem_post(info->forks);
	return (CONTINUE);
}

int	eat(t_philo *philo, t_info *info)
{
	if (g_info.anyone_dead == TRUE)
		return (END);
	if (is_all_philos_full() == FALSE)
	{
		sem_wait(info->eating_philo);
		if (use_fork_without_dup(philo, info) == END)
		{
			sem_post(info->eating_philo);
			return (END);
		}
		sem_post(info->eating_philo);
	}
	else
		return (END);
	return (CONTINUE);
}

