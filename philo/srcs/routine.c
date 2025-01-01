/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:20:25 by ankammer          #+#    #+#             */
/*   Updated: 2025/01/01 15:56:47 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_take_fork(t_philo *philo)
{
	if (mtx_check_is_full(philo) || mtx_check_end_by_death(philo))
		return (1);
	if (philo->philo_id % 2 == 0)
	{
		wrap_mutex(&philo->first_fork, LOCK);
		wrap_mutex(philo->second_fork, LOCK);
	}
	else
	{
		wrap_mutex(philo->second_fork, LOCK);
		wrap_mutex(&philo->first_fork, LOCK);
	}
	if (mtx_check_end_by_death(philo))
		return (wrap_mutex(&philo->first_fork, UNLOCK),
			wrap_mutex(philo->second_fork, UNLOCK), 1);
	wrap_mutex(&philo->data->lock_write, LOCK);
	print_routine(philo, FORK_MSG);
	print_routine(philo, FORK_MSG);
	print_routine(philo, EAT_MSG);
	wrap_mutex(&philo->data->lock_write, UNLOCK);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (mtx_check_end_by_death(philo) || mtx_check_is_full(philo))
		return (wrap_mutex(&philo->first_fork, UNLOCK),
			wrap_mutex(philo->second_fork, UNLOCK), 1);
	wrap_mutex(&philo->data->lock_meals, LOCK);
	philo->meals_eaten++;
	if (philo->meals_eaten >= philo->data->num_max_meals
		&& !philo->philo_is_full)
	{
		philo->philo_is_full = 1;
		philo->data->all_philo_full++;
	}
	philo->time_last_meal = ft_get_time();
	wrap_mutex(&philo->data->lock_meals, UNLOCK);
	if (mtx_check_end_by_death(philo) || mtx_check_is_full(philo))
		return (wrap_mutex(&philo->first_fork, UNLOCK),
			wrap_mutex(philo->second_fork, UNLOCK), 1);
	ft_usleep(philo->data->time_to_eat);
	wrap_mutex(&philo->first_fork, UNLOCK);
	wrap_mutex(philo->second_fork, UNLOCK);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (mtx_check_end_by_death(philo) || mtx_check_is_full(philo))
		return (1);
	wrap_mutex(&philo->data->lock_write, LOCK);
	print_routine(philo, SLEEP_MSG);
	wrap_mutex(&philo->data->lock_write, UNLOCK);
	ft_usleep(philo->data->time_to_sleep);
	return (0);
}

int	ft_thinking(t_philo *philo)
{
	if (mtx_check_end_by_death(philo) || mtx_check_is_full(philo))
		return (1);
	if (philo->philo_id != philo->data->number_of_philos)
		ft_usleep(360 / 1000);
	wrap_mutex(&philo->data->lock_write, LOCK);
	print_routine(philo, THINK_MSG);
	wrap_mutex(&philo->data->lock_write, UNLOCK);
	return (0);
}

void	*ft_routine(void *philos_void)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = (t_philo *)philos_void;
	who_sleep(philo);
	while (1)
	{
		if (mtx_check_end_by_death(philo) || mtx_check_is_full(philo))
			break ;
		if (ft_take_fork(philo))
			break ;
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (ft_thinking(philo))
			break ;
	}
	return (philos_void);
}
