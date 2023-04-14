/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonard <abonard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:36:07 by abonard           #+#    #+#             */
/*   Updated: 2022/07/27 20:49:42 by abonard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define GREEN "\033[0;92m"
# define PURPLE "\033[0;95m"
# define RED "\033[0;91m"
# define NC "\033[0m"

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

struct	s_general;

typedef struct s_philo
{
	int					id;
	int					id_fork_l;
	int					id_fork_r;
	int					nb_spaghet;
	pthread_t			philo_id;
	struct s_general	*info;
	long long			last_spaghetti;
}	t_philo;

typedef struct s_general
{
	int				t_sleep;
	int				t_eat;
	int				t_death;
	int				nb_philo;
	int				nb_meal;
	int				is_dead;
	int				she_iz;
	long long		timestamp;
	pthread_mutex_t	write;
	pthread_mutex_t	fork[210];
	pthread_mutex_t	dead;
	pthread_mutex_t	manger;
	pthread_mutex_t	spaghetti;
	t_philo			philo[210];
}	t_general;

int			ft_atoi(const char *nptr);
int			ft_run_thread(t_general *general, int i);
int			ft_lock_eat_unlock(t_general *general, t_philo *philo);
int			ft_create_thread(t_general *general, t_philo *philo, int i);
int			ft_a_case(t_general *general);
void		ft_i_eat(t_philo *philo);
void		ft_putstr_fd(char *str, int fd);
void		ft_usleep_alpha(long long time);
void		ft_declare(t_general *general, int id_philo, char *str, int dead);
void		*routine(void *philo_void);
void		ft_join_philo(t_general *general, t_philo *philo);
long long	ft_get_millisec(void);

#endif
