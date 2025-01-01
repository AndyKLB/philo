/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:30:07 by ankammer          #+#    #+#             */
/*   Updated: 2025/01/01 15:12:31 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	mtx_check_all_full(t_philo *philo)
{
	wrap_mutex(&philo->data->lock_meals, LOCK);
	if (philo->data->num_max_meals == -1)
		return (wrap_mutex(&philo->data->lock_meals,
				UNLOCK), 0);
	if (philo->data->all_philo_full == philo->data->number_of_philos)
		return (wrap_mutex(&philo->data->lock_meals,
				UNLOCK), 1);
	wrap_mutex(&philo->data->lock_meals, UNLOCK);
	return (0);
}

int	mtx_check_is_dead(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->number_of_philos)
	{
		wrap_mutex(&philo->data->lock_meals, LOCK);
		if (ft_get_time()
			- philo[i].time_last_meal >= philo->data->time_to_death)
		{
			wrap_mutex(&philo->data->lock_meals, UNLOCK);
			wrap_mutex(&philo->data->lock_death, LOCK);
			philo->data->one_philo_died = 1;
			wrap_mutex(&philo->data->lock_death, UNLOCK);
			wrap_mutex(&philo->data->lock_write, LOCK);
			print_routine(philo, DEAD_MSG);
			wrap_mutex(&philo->data->lock_write, UNLOCK);
			return (1);
		}
		wrap_mutex(&philo->data->lock_meals, UNLOCK);
	}
	i = 0;
	return (0);
}

int	mtx_check_end_by_death(t_philo *philo)
{
	wrap_mutex(&philo->data->lock_death, LOCK);
	if (philo->data->one_philo_died || philo->data->number_of_philos == 1)

		return (wrap_mutex(&philo->data->lock_death, UNLOCK), 1);
	wrap_mutex(&philo->data->lock_death, UNLOCK);
	return (0);
}

int	mtx_check_is_full(t_philo *philo)
{
	wrap_mutex(&philo->data->lock_meals, LOCK);
	if (philo->data->num_max_meals == -1)
		return (wrap_mutex(&philo->data->lock_meals, UNLOCK), 0);
	if (philo->philo_is_full)
		return (wrap_mutex(&philo->data->lock_meals, UNLOCK), 1);
	wrap_mutex(&philo->data->lock_meals, UNLOCK);
	return (0);
}
