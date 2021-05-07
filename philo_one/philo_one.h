/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhpark <junhpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 21:51:04 by junhpark          #+#    #+#             */
/*   Updated: 2021/05/07 22:02:56 by junhpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <unistd.h>
# include <stdlib.h>

/*
**		main.c
*/

size_t		ft_strlen(const char *str);

/*
**		ft_atoi.c
*/
int					ft_atoi(const char *str);
double				mk_num(const char *str, int num_len);
double				make_ten(int size);
int					find_error(const char *str);
int					pass_ch_len_num(const char *str);

#endif
