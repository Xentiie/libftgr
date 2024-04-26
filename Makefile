# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:26:47 by reclaire          #+#    #+#              #
#    Updated: 2024/04/24 15:16:51 by reclaire         ###   ########.fr        #
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
			$(MAKE) -C ../libft
#			mingw32-make.exe -C ../libft

test:	$(NAME) _libft
#			$(CC) $(CFLAGS) $(INCLUDES) -L./ -L../libft test.c -lftgr -lft -lX11 -lXext -lm
			$(CC) $(CFLAGS) $(INCLUDES) -L./ -L../libft test.c -lftgr -lft -lm -lgdi32
