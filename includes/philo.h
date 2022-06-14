/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:36:07 by abonard           #+#    #+#             */
/*   Updated: 2022/06/09 19:56:50 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

struct s_general;

typedef struct	s_philo
{
	int			id;
	int			id_fork_l;
	int			id_fork_r;
	pthread_t	philo_id;
	struct s_general	*info;
	long long	last_spaghetti;
}	t_philo;

typedef struct	s_general
{
	int				t_sleep;
	int				t_eat;
	int				t_death;
	int				nb_philo;
	int				nb_meal;
	int				is_dead;
	long long		timestamp;
	pthread_mutex_t	write;
	pthread_mutex_t	fork[200];
	t_philo			philo[200];
}	t_general;

int			ft_atoi(const char *nptr);
void		ft_putstr_fd(char *str, int fd);
void		ft_usleep_alpha(long long time, t_general *general);
void		ft_declare(t_general *general, int id_philo, char *str);
int			ft_run_thread(t_general *general);
long long	ft_get_millisec(void);

#endif


