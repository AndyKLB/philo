/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:50:19 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/30 14:27:21 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_error(char *message, size_t size_message, int error)
{
	write(2, message, size_message);
	return(error);
}

int	main(int argc, char **argv)
{
		t_data data;
	if (!check_data(argv, argc))
	{
		if (parsing_data(argv, &data))
			return (1);
		if (data_init(&data))
			return (1);
		// if (launch_threads(&data, data.number_of_philos, data.philos))
		// 	return (1);
		ft_free_philos(&data, data.number_of_philos);
	}
	return (0);
}
