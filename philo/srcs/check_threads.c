/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:06:11 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/31 11:25:03 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	check_death(t_philo *philo)
{
	if (mtx_check_is_dead(philo))
		return (1);
	return (0);
}

int	check_ate(t_philo *philo)
{
	if (mtx_check_all_full(philo))
		return (1);
	return (0);
}

int	check_threads(t_philo *philo)
{
	while (1)
	{
		if (check_ate(philo) || check_death(philo))
			break ;
	}
	return (0);
}
