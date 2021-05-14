/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:10:51 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/14 18:21:39 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_doing(t_status status, t_philo *philo, unsigned long interval)
{
	// NOTE 이 함수에서 printf는 이런 것들이 호출 됬음. 적절한 조건문을 활용하길 바람.
	printf("[%lu]\t %d\t", interval, philo->index + 1);
	if (g_info.meal_full != FALSE && g_info.full_list[philo->index] == true)
	{
		printf("is now full and happy   :)\n");
		return (END);
	}
	else if (status == EATING)
		printf("is eating\n");
	else if (status == SLEEPING)
		printf("is sleeping\n");
	else if (status == THINKING)
		printf("is thinking\n");
	else if (status == LEFT_TAKEN || status == RIGHT_TAKEN)
		printf("has taken a fork\n");
	else if (status == DEAD)
	{
		g_info.anyone_dead = true;
		printf("is died\n");
		return (END);
	}
	return (CONTINUE);
}

bool	is_all_philos_full()
{
	int				idx;

	idx = 0;
	if (g_info.meal_full == FALSE)
		return (FALSE);
	while (idx < g_philo_num)
	{
		if (g_info.full_list[idx] == FALSE)
			return (FALSE);
		idx++;
	}
	return (TRUE);
}

void	*monitoring(void *param)
{
	t_philo			*philo;
	unsigned long	time;

	philo = (t_philo *)param;

	while (1)
	{
		time = get_relative_time();
		if ((time - philo->when_eat) > g_info.time_to_die)
		{
			doing(DEAD, philo, time);
			break ;
		}
		if (g_info.anyone_dead == TRUE)
			break ;
		if (is_all_philos_full() == true)
			break ;
	}
	accurate_pause(5);
	return (NULL);
}

int		doing(t_status status, t_philo *philo, unsigned long interval)
{
	int	ret;

	pthread_mutex_lock(&g_info.print_mutex);
	if (g_info.anyone_dead == TRUE)
	{
		pthread_mutex_unlock(&g_info.print_mutex);
		return (END);
	}
	if (is_all_philos_full() == TRUE)
	{
		pthread_mutex_unlock(&g_info.print_mutex);
		return (END);
	}
	ret = print_doing(status, philo, interval);
	pthread_mutex_unlock(&g_info.print_mutex);
	// NOTE 상태에 따라서 philo_do의 while(1)을 나갈 수 있게 함.(exit()을 쓰는 것이 편할지 모르지만, 안 써도 충분히 가능함.)
	if (ret == CONTINUE)
		return (CONTINUE);
	else if (ret == END)
		return (END);
	return (END);
}

void	*philo_do(void *param)
{
	t_philo		*philo;
	pthread_t	thread;

	philo = (t_philo *)param;
	pthread_create(&thread, NULL, monitoring, philo);
	// NOTE 먹고 자고 생각하고
	while (1)
	{
		if (eat(philo, &g_info) == END)
			break ;
		if (doing(SLEEPING, philo, get_relative_time()) == END)
			break ;
		spend_time_of(SLEEPING);
		if (doing(THINKING, philo, get_relative_time()) == END)
			break ;
	}
	pthread_join(thread, NULL);
	return (NULL);
}
