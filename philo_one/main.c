/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 21:58:57 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/10 15:52:06 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

size_t					ft_strlen(const char *str)
{
	size_t				count;

	count = 0;
	while (*str)
	{
		str++;
		count++;
	}
	return (count);
}

int						main(int argc, char *argv[])
{
	int					idx;

	idx = 1;
	while (argv[idx])
	{
		printf("%d\n", ft_atoi(argv[idx]));
		idx++;
	}
}
