/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:49:40 by abonard           #+#    #+#             */
/*   Updated: 2022/07/27 21:01:52 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int		i;
	int		n;
	long	res;

	res = 0;
	i = 0;
	n = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\r' || nptr[i] == '\f')
			i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			n = n * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if (res > 2147483647 || res < -21474836478)
		return (-1);
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

int	ft_a_case(t_general *general)
{
	if (general->nb_philo == 1)
	{
		ft_declare(general, 1, "has taken a fork", 0);
		ft_usleep_alpha(general->t_death + 1);
		ft_declare(general, 1, "is \033[0;91mdead\033[0m", 1);
		pthread_mutex_unlock(&general->write);
		return (0);
	}
	return (1);
}

long long	ft_get_millisec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep_alpha(long long time)
{
	long long	i;

	i = ft_get_millisec();
	while (1)
	{
		if (ft_get_millisec() - i >= time)
			break ;
		usleep(50);
	}
}
