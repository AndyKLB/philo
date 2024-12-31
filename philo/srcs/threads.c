/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:17:35 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/26 14:23:34 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	one_philo(t_philo *philo)
{
	printf("%ld philo N%d %s\n", ft_get_time() - philo->data->start_program,
		philo->philo_id, FORK_MSG);
	ft_usleep(philo->data->time_to_death);
	printf("%ld philo N%d %s\n", ft_get_time() - philo->data->start_program,
		philo->philo_id, DEAD_MSG);
}

int	launch_threads(t_data *data, int nb_philo, t_philo *philos)
{
	int	i;

	i = -1;
	if (nb_philo == 1)
		return(one_philo(philos), 0);
	while (++i < nb_philo)
	{
		if (wrap_thread(&philos[i].thread_id, &ft_routine, &philos[i], CREATE))
		{
			while (--i >= 0)
				wrap_thread(&philos[i].thread_id, NULL, NULL, JOIN);
			return (ft_free_philos(data, nb_philo), ft_error(ER_THC, 19, 1));
		}
	}
	check_threads(philos);
	i = -1;
	while (++i < nb_philo)
	{
		if (wrap_thread(&philos[i].thread_id, NULL, NULL, JOIN))
			ft_error(ER_THJ, 19, 1);
	}
	return (ft_free_philos(data, nb_philo), 0);
}
