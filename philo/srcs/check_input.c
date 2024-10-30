/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:21:21 by ankammer          #+#    #+#             */
/*   Updated: 2024/10/30 12:41:33 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_is_digit(char c)
{
	return (c >= '0' || c <= '9');
}

char	*is_valid_input(char *str)
{
	int	i;
	int	len;
	int	j;

	len = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (NULL);
	if (!ft_is_digit(str[i]))
		return (NULL);
	j = i;
	while (ft_is_digit(str[i]) && str[i])
	{
		i++;
		len++;
	}
	if (len > 10)
		return (NULL);
	return (str + j);
}

long	ft_atol(char *str)
{
	long	res;
	int		i;

	res = 0;
	i = 0;
	str = is_valid_input(str);
	if (str)
	{
		while (ft_is_digit(str[i]) && str[i])
		{
			res = res * 10 + (str[i] - 48);
			i++;
		}
		if (res > INT_MAX)
			return (0);
		return (res);
	}
	return (0);
}

int	check_data(char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		return (ft_error("wrong inputs number of data is 5 or 6", 38, 1));
	if (ft_atol(argv[1]) <= 0)
		return (ft_error("error : invalid philo numbers\n", 31, 1));
	if (ft_atol(argv[2]) <= 0)
		return (ft_error("error : invalid time to death\n", 31, 1));
	if (ft_atol(argv[3]) <= 0)
		return (ft_error("error : invalid time to eat\n", 29, 1));
	if (ft_atol(argv[4]) <= 0)
		return (ft_error("error : invalid time to sleep\n", 31, 1));
	if (argv[5] && (ft_atol(argv[5]) <= 0))
		return (ft_error("error : invalid max meals by philo\n", 36, 1));
	return (0);
}

int	parsing_data(char **argv, t_data *data)
{
	data->number_of_philos = ft_atol(argv[1]);
	if (data->number_of_philos <= 0)
		return (ft_error("error: wrong number of philo", 28, 1));
	data->time_to_death = ft_atol(argv[2]);
	if (data->time_to_death <= 0)
		return (ft_error("error: wrong time of death", 26, 1));
	data->time_to_eat = ft_atol(argv[3]);
	if (data->time_to_eat <= 0)
		return (ft_error("error: wrong time to eat", 24, 1));
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_sleep <= 0)
		return (ft_error("error: wrong time to sleep", 26, 1));
	if (argv[5])
	{
		data->num_max_meals = ft_atol(argv[5]);
		if (data->num_max_meals <= 0)
			return (ft_error("error: wrong max meals", 22, 1));
	}
	else
		data->num_max_meals = -1;
	return (0);
}
