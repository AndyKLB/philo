/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:17:35 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/30 13:59:55 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	launch_threads(t_data *data, int nb_philo, t_philo *philos)
{
	int	i;

	i = -1;
	if (wrap_thread(&data->supervisor, &check_threads, data, CREATE))
		return (ft_free_philos(data, nb_philo), ft_error(ER_THC, 19, 1));
	while (++i < nb_philo)
	{
		if (wrap_thread(&philos[i].thread_id, &ft_routine, &philos[i], CREATE))
		{
			while (--i >= 0)
				wrap_thread(&philos[i].thread_id, NULL, NULL, JOIN);
			wrap_thread(&data->supervisor, NULL, NULL, JOIN);
			return (ft_free_philos(data, nb_philo), ft_error(ER_THC, 19, 1));
		}
	}
	if (wrap_thread(&data->supervisor, NULL, NULL, JOIN))
		ft_error(ER_THJ, 19, 1);
	i = -1;
	while (++i < nb_philo)
	{
		if (wrap_thread(&philos[i].thread_id, NULL, NULL, JOIN))
			ft_error(ER_THJ, 19, 1);
	}
	return (ft_free_philos(data, nb_philo), 0);
}
