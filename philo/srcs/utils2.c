/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:50:50 by ankammer          #+#    #+#             */
/*   Updated: 2025/01/01 14:48:19 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_routine(t_philo *philo, char *str)
{
	t_data	*data;

	data = philo->data;
	printf("%ld %d %s\n", ft_get_time() - philo->data->start_program,
		philo->philo_id, str);
}

long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(long millisec)
{
	long	start;
	long	current;

	start = ft_get_time();
	if (start == -1)
		return (1);
	while (1)
	{
		current = ft_get_time();
		if (current == -1)
			return (1);
		if (current - start >= millisec)
			break ;
		usleep(500);
	}
	return (0);
}
