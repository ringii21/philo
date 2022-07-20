/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:37:03 by abonard           #+#    #+#             */
/*   Updated: 2022/07/20 17:08:35 by abonard          ###   ########.fr       */
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
