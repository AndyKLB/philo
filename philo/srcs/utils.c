/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:28:14 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/31 11:55:56 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	wrap_mutex(pthread_mutex_t *mutex, t_muthread_code code)
{
	if (code == INIT)
		return (pthread_mutex_init(mutex, NULL));
	else if (code == UNLOCK)
		return (pthread_mutex_unlock(mutex));
	else if (code == LOCK)
		return (pthread_mutex_lock(mutex));
	else if (code == DESTROY)
		return (pthread_mutex_destroy(mutex));
	else
		return (ft_error("wrong code for mutex", 21, 1));
}

int	wrap_thread(pthread_t *thread, void *function, void *function_data,
		t_muthread_code code)
{
	if (code == JOIN)
	{
		if (pthread_join(*thread, NULL))
			return (1);
	}
	else if (code == CREATE)
	{
		if (pthread_create(thread, NULL, function, function_data))
			return (1);
	}
	else
		return (ft_error("wrong code for thread", 21, 1));
	return (0);
}

void	who_sleep(t_philo *philo)
{
	if (philo->philo_id % 2 != 0)
		ft_usleep(100);
	if (philo->philo_id == philo->data->number_of_philos
		&& philo->data->number_of_philos % 2 != 0)
		ft_usleep(100);
}
