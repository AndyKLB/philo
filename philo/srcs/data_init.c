/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:27:17 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/30 15:31:28 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_free_philos(t_data *data, int index)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		wrap_mutex(&data->lock_meals, DESTROY);
		wrap_mutex(&data->lock_write, DESTROY);
		wrap_mutex(&data->lock_death, DESTROY);
		while (i < index)
		{
			wrap_mutex(&data->philos[i].first_fork, DESTROY);
			i++;
		}
		free(data->philos);
		data->philos = NULL;
	}
}
void	init_mutexes(t_philo *philo)
{
	int	i;

	i = -1;
	if (philo->data->number_of_philos == 1)
	{
		philo->second_fork = NULL;
		return ;
	}
	while (++i < philo->data->number_of_philos)
	{
		if (i == philo->data->number_of_philos - 1)
			philo[i].second_fork = &philo[0].first_fork;
		else
			philo[i].second_fork = &philo[i + 1].first_fork;
	}
}

// void print_philo(t_philo *philo, t_data *data)
// {
// 	int i;
	
// 		i = -1;
// 	while (++i < data->number_of_philos)
// 	{
// 		printf("PHILO N %d has eaten %d, full: %d, time last meal: %d\n",
// 			philo[i].philo_id, philo[i].meals_eaten, philo[i].philo_is_full,
// 			philo[i].time_last_meal);
// 		printf("first_fork : %p, second fork: %p\n", &philo[i].first_fork,
// 			philo[i].second_fork);
// 	}
// }

int	philo_init(t_philo *philo, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		philo[i].data = data;
		philo[i].philo_id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].philo_is_full = false;
		philo[i].thread_id = (pthread_t)0;
		philo[i].time_last_meal = 0;
		if (wrap_mutex(&philo[i].first_fork, INIT))
			return (ft_free_philos(data, i), ft_error("error mutex init", 16,
					1));
	}
	init_mutexes(philo);
	// print_philo(philo, data);
	return (0);
}

int	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_program = false;
	data->start_program = ft_get_time();
	if (data->start_program == 1)
		return (ft_error("error gettime", 13, 1));
	data->all_philo_full = 0;
	data->philo_is_dead = false;
	data->supervisor = (pthread_t)0;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
		return (ft_error("malloc error\n", 14, 1));
	if (wrap_mutex(&data->lock_write, INIT) != 0
		|| wrap_mutex(&data->lock_death, INIT) != 0
		|| wrap_mutex(&data->lock_meals, INIT) != 0)
	{
		ft_free_philos(data, 0);
		return (ft_error("error mutex init", 16, 1));
	}
	if (philo_init(data->philos, data))
		return (ft_free_philos(data, data->number_of_philos),
			ft_error("error mutex init", 16, 1));
	return (0);
}
