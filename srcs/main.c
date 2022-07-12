/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:35:31 by abonard           #+#    #+#             */
/*   Updated: 2022/07/12 20:18:42 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>

int	ft_init_mutex(t_general *general)
{
	int	i;
	int	res;

	i = 0;
	while (i < general->nb_philo)
	{
		res = pthread_mutex_init(&(general->fork[i]), NULL);
		if (res != 0)
			return(-1);
		i++;
	}
	res = pthread_mutex_init(&(general->write), NULL);
	if (res != 0)
		return (-1);
	res = pthread_mutex_init(&(general->dead), NULL);
	if (res != 0)
		return (-1);
	res = pthread_mutex_init(&(general->spaghetti), NULL);
	if (res != 0)
		return (-1);
	res = pthread_mutex_init(&(general->manger), NULL);
	if (res != 0)
		return (-1);
	return (0);
}

void	ft_init_philos(t_general *general)
{
	int	i;

	i = 0;
	while (i < general->nb_philo)
	{
		general->philo[i].id = i + 1;
		general->philo[i].id_fork_l = i;
		general->philo[i].id_fork_r = i + 1 % general->nb_philo;
		general->philo[i].nb_spaghet = -1;
		general->philo[i].info = general;
		i++;
	}
	general->is_dead = 0;
	general->she_iz = 0;
}

int	ft_initialize(char **argv, t_general *general)
{
	general->nb_meal = -1;
	general->nb_philo = ft_atoi(argv[1]);
	general->t_death = ft_atoi(argv[2]);
	general->t_eat = ft_atoi(argv[3]);
	general->t_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		general->nb_meal = ft_atoi(argv[5]);
		if (general->nb_meal < 0)
			return (-1);
	}
	else
		general->nb_meal = -1;
	if ((general->nb_philo < 1 || general->nb_philo > 200)
		|| general->t_death < 0 || general->t_eat < 0
		|| general->t_sleep < 0)
		return (-1);
	if (ft_init_mutex(general) == -1)
		return (-1);
	ft_init_philos(general);
	return (0);
}

int	main(int argc, char **argv)
{
	t_general	general;

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Number of arguments incorrect", 2);
		return (1);
	}
	if (ft_initialize(argv, &general) == -1)
	{
		ft_putstr_fd("Cannot initialize Mutex\n", 2);
		return (1);
	}
	if (ft_run_thread(&general) == -1)
	{
		ft_putstr_fd("Cannot run the program\n", 2);
		return (1);
	}
	return (0);
}
