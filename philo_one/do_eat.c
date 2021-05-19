/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:10:44 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/19 21:34:43 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	use_fork_without_dup(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->forks[philo->right_fork_num]);
	doing(RIGHT_TAKEN, philo, get_relative_time());
	pthread_mutex_lock(&info->forks[philo->left_fork_num]);
	doing(LEFT_TAKEN, philo, get_relative_time());
	doing(EATING, philo, get_relative_time());
	philo->meal_num++;
	if (info->meal_full != FALSE && philo->meal_num == info->meal_full)
	{
		info->full_list[philo->index] = 1;
		printf("[%lu]\t %d\t", get_relative_time(), philo->index + 1);
		printf("is now full and happy   :)\n");
		pthread_mutex_unlock(&info->forks[philo->right_fork_num]);
		pthread_mutex_unlock(&info->forks[philo->left_fork_num]);
		return (END);
	}
	philo->when_eat = get_relative_time();
	spend_time_of(EATING);
	pthread_mutex_unlock(&info->forks[philo->right_fork_num]);
	pthread_mutex_unlock(&info->forks[philo->left_fork_num]);
	return (CONTINUE);
}

int	eat(t_philo *philo, t_info *info)
{
	if (g_info.anyone_dead == TRUE)
		return (END);
	if (is_all_philos_full() == FALSE)
	{
		if (use_fork_without_dup(philo, info) == END)
			return (END);
	}
	else
		return (END);
	return (CONTINUE);
}

