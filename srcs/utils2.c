/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:37:03 by abonard           #+#    #+#             */
/*   Updated: 2022/07/27 20:51:20 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "../includes/philo.h"

int	ft_create_thread(t_general *general, t_philo *philo, int i)
{
	int	tmp;

	tmp = 0;
	i = -1;
	while (++i < general->nb_philo)
	{
		tmp = pthread_create(&(philo[i].philo_id), NULL, routine, &(philo[i]));
		if (tmp != 0)
			return (-1);
		pthread_mutex_lock(&general->spaghetti);
		philo[i].last_spaghetti = ft_get_millisec();
		pthread_mutex_unlock(&general->spaghetti);
	}
	return (0);
}

void	ft_declare(t_general *general, int id_philo, char *str, int dead)
{
	pthread_mutex_lock(&(general->write));
	pthread_mutex_lock(&general->dead);
	if (general->is_dead == 1 || general->she_iz == 1)
	{
		pthread_mutex_unlock(&general->dead);
		pthread_mutex_unlock(&general->write);
		return ;
	}
	pthread_mutex_unlock(&general->dead);
	printf("%lli %d %s\n",
		ft_get_millisec() - general->timestamp, id_philo, str);
	if (dead == 0)
		pthread_mutex_unlock(&(general->write));
}

int	ft_lock_eat_unlock(t_general *general, t_philo *philo)
{
	pthread_mutex_lock(&general->dead);
	if (general->is_dead == 1 || general->she_iz == 1)
	{
		pthread_mutex_unlock(&general->dead);
		return (-1);
	}
	pthread_mutex_unlock(&general->dead);
	ft_i_eat(philo);
	pthread_mutex_lock(&general->dead);
	if (general->is_dead == 1 || general->she_iz == 1)
	{
		pthread_mutex_unlock(&general->dead);
		return (-1);
	}
	pthread_mutex_unlock(&general->dead);
	return (1);
}

void	ft_join_philo(t_general *general, t_philo *philo)
{
	int	j;

	usleep(1500000);
	j = general->nb_philo;
	while (--j >= 0)
	{
		if (pthread_join(philo[j].philo_id, NULL) != 0)
			break ;
	}
}
