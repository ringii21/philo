/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:11:43 by abonard           #+#    #+#             */
/*   Updated: 2022/07/27 21:01:53 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../includes/philo.h"

void	ft_i_eat(t_philo *philo)
{
	t_general	*general;

	general = philo->info;
	pthread_mutex_lock(&(general->fork[philo->id_fork_l]));
	ft_declare(general, philo->id, "has taken a fork", 0);
	pthread_mutex_lock(&(general->fork[philo->id_fork_r]));
	ft_declare(general, philo->id, "has taken a fork", 0);
	ft_declare(general, philo->id, "is eating", 0);
	pthread_mutex_lock(&general->manger);
	philo->nb_spaghet++;
	pthread_mutex_unlock(&general->manger);
	ft_usleep_alpha(general->t_eat);
	pthread_mutex_lock(&general->spaghetti);
	philo->last_spaghetti = ft_get_millisec();
	pthread_mutex_unlock(&general->spaghetti);
	pthread_mutex_unlock(&(general->fork[philo->id_fork_l]));
	pthread_mutex_unlock(&(general->fork[philo->id_fork_r]));
}

int	ft_meals_check(t_general *info, t_philo *philo)
{
	int	i;
	int	c;

	c = 0;
	while (1)
	{
		i = 0;
		while (info->she_iz == 0 && i < info->nb_philo)
		{
			pthread_mutex_lock(&info->manger);
			if (philo[i].nb_spaghet == info->nb_meal)
				c++;
			pthread_mutex_unlock(&info->manger);
			if (c == info->nb_philo)
			{
				pthread_mutex_lock(&info->dead);
				info->she_iz = 1;
				pthread_mutex_unlock(&info->dead);
				return (-1);
			}
			usleep(200);
			i++;
		}
	}
	return (1);
}

void	*routine(void *philo_void)
{
	t_philo		*philo;
	t_general	*general;

	philo = (t_philo *)philo_void;
	general = philo->info;
	if (philo->id % 2)
		usleep(10000);
	while (1)
	{
		if (ft_lock_eat_unlock(general, philo) == -1)
			break ;
		ft_declare(general, philo->id, "is \033[0;93msleeping\033[0m", 0);
		ft_usleep_alpha(general->t_sleep);
		pthread_mutex_lock(&general->dead);
		if (general->is_dead == 1 || general->she_iz == 1)
		{
			pthread_mutex_unlock(&general->dead);
			break ;
		}
		pthread_mutex_unlock(&general->dead);
		ft_declare(general, philo->id, "is \033[0;94mthinking\033[0m", 0);
	}
	return (0);
}

int	ft_dead_check(t_general *info, t_philo *philo, int check)
{
	int	i;

	while (1)
	{
		i = 0;
		while (info->is_dead == 0 && i < info->nb_philo)
		{
			pthread_mutex_lock(&info->spaghetti);
			if (ft_get_millisec() - philo[i].last_spaghetti > info->t_death)
			{
				check = 1;
				pthread_mutex_unlock(&info->spaghetti);
				ft_declare(info, i + 1, "is \033[0;91mdead\033[0m", 1);
				pthread_mutex_lock(&info->dead);
				info->is_dead = 1;
				pthread_mutex_unlock(&info->dead);
				return (-1);
			}
			if (check == 0)
				pthread_mutex_unlock(&info->spaghetti);
			usleep(200);
			i++;
		}
	}
	return (1);
}

int	ft_run_thread(t_general *general, int i)
{
	t_philo	*philo;

	philo = general->philo;
	general->timestamp = ft_get_millisec();
	if (ft_a_case(general) == 0)
		return (0);
	if (ft_create_thread(general, philo, i) == -1)
		return (-1);
	if (general->nb_meal != -1)
	{
		if (ft_meals_check(general, philo) == -1)
		{
			ft_join_philo(general, philo);
			return (0);
		}
	}
	if (ft_dead_check(general, philo, 0) == -1)
	{
		pthread_mutex_unlock(&general->write);
		ft_join_philo(general, philo);
		return (0);
	}
	pthread_mutex_unlock(&(general->write));
	ft_join_philo(general, philo);
	return (0);
}
