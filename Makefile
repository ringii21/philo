# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abonard <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 18:45:35 by abonard           #+#    #+#              #
#    Updated: 2022/07/05 17:48:51 by abonard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	./srcs/main.c \
				./srcs/utils.c \
				./srcs/routine.c

INCLUDES	=	./includes/philo.h \

HEAD		= ./includes

NAME		= philo

CC			= clang

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror -pthread -g -fsanitize=thread

.c.o:
		@${CC} ${CFLAGS} -I${HEAD} -c $< -o ${<:.c=.o}
		@echo "${GREEN}[ OK ]	${ORANGE}${<:.s=.o}${NC}"


all:		${NAME} ${NAME2}

${NAME}:	${OBJS}
			@${CC} ${CFLAGS} -I${HEAD} -o ${NAME} $(OBJS)
			@echo "${GREEN}\nphilo  program	has been created${NC}"

clean:
			@${RM} ${OBJS}
			@echo "${GREEN}[ OK ]${RED}	*.o files	deleted${NC}"

fclean:		clean
			@${RM} ${NAME}
			@echo "${GREEN}[ OK ]${RED}	philo program	deleted${NC}"

re :		fclean all

.PHONY:		all	clean	fclean re bonus2 bonus
