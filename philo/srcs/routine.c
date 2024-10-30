/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:20:25 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/30 16:03:31 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_eat(t_philo *philo)
{

}

void	ft_sleep(t_philo *philo)
{

}

void	ft_thinking(t_philo *philo)
{

}

void	*ft_routine(void *philos_void)
{
	t_philo	*philo;

	philo = (t_philo *)philos_void;
	if (philo->philo_id % 2 == 0)
		ft_usleep(100);
	while (!ft_check_end(philo->data))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_thinking(philo);
	}
	if (ft_check_alive(philo->data))
		print_routine(philo, DEAD_MSG);
	return (philos_void);
}
