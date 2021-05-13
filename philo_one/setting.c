/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:11:19 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/12 17:04:55 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

// NOTE (info->forks)포크에 대해서 하나씩 mutex_init 해주고, (info->print_mutex)print에 대해서도 mutex_init 해준다.
void	mutex_init(t_info *info)
{
	int				idx;

	idx = 0;
	while (idx < g_philo_num)
	{
		pthread_mutex_init(&(info->forks[idx]), NULL);
		// rock과 unlock을 위해
		idx++;
	}
	pthread_mutex_init(&(info->print_mutex), NULL); // 마찬가지
}

// NOTE 철학자에 대한 정보 초기화 t_philo에 있는 값들 설정하기
int		set_philos(t_philo *philos)
{
	unsigned long	init_time;
	int				idx;

	idx = -1;
	while (++idx < g_philo_num)
	{
		philos[idx].meal_num = 0;
		init_time = get_relative_time();
		philos[idx].index = idx;
		philos[idx].when_eat = init_time; // 시작할 때, 먹인다.
		philos[idx].left_fork_num = philos[idx].index;
		philos[idx].right_fork_num = philos[idx].index + 1;
		if (philos[idx].right_fork_num == g_philo_num)
			philos[idx].right_fork_num = 0;
	}
	return (0);
}

// NOTE forks, basetime, anyone_dead, full_list을 초기화 해줌.
int		init_info(t_info *info)
{
	info->anyone_dead = FALSE; // 모니터링에서 시간마다 검사할 예정
	info->basetime = get_present_time();
	info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philosophers);
	if (info->meal_full != FALSE) // 마지막 옵션. 철학자들이 얼마 이상 먹으면 시뮬레이션 종료
	{
		info->full_list = malloc(sizeof(char) * g_philo_num);
		memset(info->full_list, 0, g_philo_num);
	}
	return (0);
}

// NOTE argv 에러처리, argv 값을 t_info에 넣어줌
int		set_info_argv(t_info *info, int argc, char *argv[])
{
	info->meal_full = FALSE;
	if (!(argc == 5 || argc == 6))
		return (-1);
	if ((info->number_of_philosophers = ft_atoi(argv[1])) < 1)
		return (-1);
	g_philo_num = info->number_of_philosophers;
	if ((info->time_to_die = ft_atoi(argv[2])) < 1)
		return (-1);
	if ((info->time_to_eat = ft_atoi(argv[3])) < 1)
		return (-1);
	if ((info->time_to_sleep = ft_atoi(argv[4])) < 1)
		return (-1);
	if (argc == 6)
	{
		if ((info->meal_full = ft_atoi(argv[5])) < 1)
			return (-1);
	}
	return (0);
}
