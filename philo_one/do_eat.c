/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:10:44 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/14 23:27:59 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NOTE 철학자가 죽지 않도록하는 나의 알고리즘임
int	use_fork_without_dup(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&info->forks[philo->right_fork_num]);
	doing(RIGHT_TAKEN, philo, get_relative_time());
	pthread_mutex_lock(&info->forks[philo->left_fork_num]);
	doing(LEFT_TAKEN, philo, get_relative_time());
	doing(EATING, philo, get_relative_time());
	philo->meal_num++;
	if (info->meal_full != FALSE && philo->meal_num >= info->meal_full)
	{
		info->full_list[philo->index] = 1;
		doing(NOTICE, philo, get_relative_time());
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

// NOTE 먹는 행위.
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
	// 1. 누군가 죽었는지 판단해서 죽었다면, 바로 return
	// 2. 먹는 알고리즘 info->forks에 대해서 mutex가 쓰임. 매우매우 중요한 부분

	// 나는 철학자가 죽지 않게 하는 알고리즘으로써 아래 함수를 썼음. 본인 방법을 생각해보면 좋을 듯
	// eat_one_direction(t_philo *philo, t_info *info)
}

