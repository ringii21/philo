/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:11:43 by abonard           #+#    #+#             */
/*   Updated: 2022/07/12 17:52:27 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../includes/philo.h"

void	ft_i_eat(t_philo *philo)
{
	t_general	*general;

	general = philo->info;
	pthread_mutex_lock(&(general->fork[philo->id_fork_l]));
	ft_declare(general, philo->id, "has taken a fork");
	pthread_mutex_lock(&(general->fork[philo->id_fork_r]));
	ft_declare(general, philo->id, "has taken a fork");
	ft_declare(general, philo->id, "is eating");
	pthread_mutex_lock(&general->manger);
	philo->nb_spaghet++;
	pthread_mutex_unlock(&general->manger);
	ft_usleep_alpha(general->t_eat, general);
	pthread_mutex_lock(&general->spaghetti);
	philo->last_spaghetti = ft_get_millisec();
	pthread_mutex_unlock(&general->spaghetti);
	pthread_mutex_unlock(&(general->fork[philo->id_fork_l]));
	pthread_mutex_unlock(&(general->fork[philo->id_fork_r]));
}

int		ft_meals_check(t_general *info, t_philo *philo)
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
				pthread_mutex_lock(&info->manger);
				info->she_iz = 1;
				pthread_mutex_unlock(&info->manger);
				printf("EVERYBODAY AAAATE\n");
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
		pthread_mutex_lock(&general->dead);
		pthread_mutex_lock(&general->manger);
		if (general->is_dead == 1)
			break;
		pthread_mutex_unlock(&general->dead);
		pthread_mutex_unlock(&general->manger);
		ft_i_eat(philo);
		ft_declare(general, philo->id, "is sleeping");
		ft_usleep_alpha(general->t_sleep, general);
		ft_declare(general, philo->id, "is thinking");
	}
	return(0);
}

int	ft_dead_check(t_general *info, t_philo *philo)
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
				ft_declare(info, i, "is dead");
				pthread_mutex_lock(&info->dead);
				info->is_dead = 1;
				pthread_mutex_unlock(&info->dead);
				return (-1);
			}
			pthread_mutex_unlock(&info->spaghetti);
			usleep(200);
			i++;
		}
	}
	return (1);
}

int	ft_run_thread(t_general *general)
{
	int		i;
	int		tmp;
	t_philo	*philo;

	i = -1;
	tmp = 0;
	philo = general->philo;
	general->timestamp = ft_get_millisec();
	while (++i < general->nb_philo)
	{
		tmp = pthread_create(&(philo[i].philo_id), NULL, routine, &(philo[i]));
		if (tmp != 0)
			return (-1);
		pthread_mutex_lock(&general->spaghetti);
		philo[i].last_spaghetti = ft_get_millisec();
		pthread_mutex_unlock(&general->spaghetti);
	}
	if (general->nb_meal != -1)
		if (ft_meals_check(general, philo) == -1)
			return (0);
	ft_dead_check(general, philo);
	usleep(10000);
	int j = general->nb_philo;
	while (j != 0)
	{
		if (pthread_join(philo[j].philo_id, NULL) != 0)
			break ;
		j--;
	}
	return (0);
}
