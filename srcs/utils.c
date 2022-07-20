/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:49:40 by abonard           #+#    #+#             */
/*   Updated: 2022/07/20 15:44:45 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int i;
	int n;
	long res;
	
	res = 0;
	i = 0;
	n = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n' || nptr[i] == '\v'
		|| nptr[i] == '\r' || nptr[i] == '\f')
			i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		{
			if (nptr[i] == '-')
				n = n * -1;
			i++;
		}
	while(nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * n);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

long long	ft_get_millisec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return((time.tv_sec *1000) + (time.tv_usec / 1000));
}

void	ft_declare(t_general *general, int id_philo, char *str)
{
	//pthread_mutex_lock(&general->dead);
	if (general->is_dead == 0)
	{
		pthread_mutex_lock(&(general->write));
		printf("time:%lli id_philo:%d action:%s\n",
			ft_get_millisec() - general->timestamp, id_philo, str);
		pthread_mutex_unlock(&(general->write));
	}
	//pthread_mutex_unlock(&general->dead);
}

void	ft_usleep_alpha(long long time, t_general *general)
{
	long long	i;

	i = ft_get_millisec();
	while (1)
	{
		pthread_mutex_lock(&general->dead);
		if (general->is_dead == 1)
			break;
		pthread_mutex_unlock(&general->dead);
		if (ft_get_millisec() - i >= time)
			break;

		usleep(50);
	}
}
