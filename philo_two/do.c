/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:10:51 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/19 21:37:28 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_doing(t_status status, t_philo *philo, unsigned long interval)
{
	if (g_info.meal_full != FALSE && g_info.full_list[philo->index] == true)
		return (END);
	printf("[%lu]\t %d\t", interval, philo->index + 1);
	if (status == EATING)
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
		accurate_pause(5);
		if ((time > philo->when_eat) && ((time - philo->when_eat) > g_info.time_to_die))
		{
			doing(DEAD, philo, time);
			break ;
		}
		if (g_info.anyone_dead == TRUE)
			break ;
		if (is_all_philos_full() == true)
			break ;
	}
	if (is_all_philos_full() == false)
		g_info.anyone_dead = TRUE;
	return (NULL);
}

int		doing(t_status status, t_philo *philo, unsigned long interval)
{
	int	ret;

	sem_wait(g_info.print_sem);
	if (g_info.anyone_dead == TRUE)
	{
		sem_post(g_info.print_sem);
		return (END);
	}
	ret = print_doing(status, philo, interval);
	if (is_all_philos_full() == TRUE)
	{
		sem_post(g_info.print_sem);
		return (END);
	}
	sem_post(g_info.print_sem);
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
	accurate_pause(3);
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
