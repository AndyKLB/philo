/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankammer <ankammer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:05:23 by ankammer          #+#    #+#             */
/*   Updated: 2024/12/31 16:12:28 by ankammer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ER_THC "error thread create"
# define ER_THJ "error thread join"
# define DEAD_MSG "died"
# define EAT_MSG "is eating"
# define THINK_MSG "is thinking"
# define SLEEP_MSG "is sleeping"
# define FORK_MSG "has taken a fork"
# define ATEMEALS "All philos ate their "

typedef struct s_data	t_data;

typedef enum e_muthread_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	JOIN,
	DETACH,
	CREATE,
}						t_muthread_code;

typedef struct s_philo
{
	int					philo_id;
	int					meals_eaten;
	bool				philo_is_full;
	pthread_t			thread_id;
	pthread_mutex_t		first_fork;
	pthread_mutex_t		*second_fork;
	t_data				*data;
	long				time_last_meal;

}						t_philo;

typedef struct s_data
{
	long				number_of_philos;
	long				time_to_death;
	long				time_to_eat;
	long				time_to_sleep;
	int					all_philo_full;
	long				num_max_meals;
	pthread_t			supervisor;
	long				start_program;
	bool				one_philo_died;
	pthread_mutex_t		lock_write;
	pthread_mutex_t		lock_meals;
	pthread_mutex_t		lock_death;
	t_philo				*philos;
}						t_data;

int						ft_error(char *str, size_t size_message, int error);
int						parsing_data(char **argv, t_data *arguments);
int						check_data(char **argv, int argc);
int						wrap_mutex(pthread_mutex_t *mutex, t_muthread_code);
int						wrap_thread(pthread_t *thread, void *function,
							void *function_data, t_muthread_code code);
int						data_init(t_data *data);
int						launch_threads(t_data *data, int nb_philo,
							t_philo *philo);
long					ft_get_time(void);
size_t					ft_strlen(char *str);
int						check_threads(t_philo *philo);
void					*ft_routine(void *philos_void);
void					print_routine(t_philo *philo, char *str);
int						ft_usleep(size_t millisec);
void					ft_free_philos(t_data *data, int index);
int						mtx_check_all_full(t_philo *philo);
int						mtx_check_is_dead(t_philo *philo);
int						ft_take_fork(t_philo *philo);
int						mtx_check_is_full(t_philo *philo);
int						mtx_check_end_by_death(t_philo *philo);
void					who_sleep(t_philo *philo);
#endif