# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:26:47 by reclaire          #+#    #+#              #
#    Updated: 2024/04/23 03:00:42 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libftgr.a
include config.mk

INCLUDES	+=	-I../libft -I./ -I./srcs
#CFLAGS		+=	-Wall -Wextra -Werror -O3 -g
CFLAGS		+=	-O3 -g

$(NAME):	objs $(OBJS)
			ar -rcs $(NAME) $(OBJS)

_libft:
			make -C ../libft

test:	$(NAME) _libft
			$(CC) $(CFLAGS) $(INCLUDES) -L./ -L../libft test.c -lftgr -lft -lX11 -lXext -lm
