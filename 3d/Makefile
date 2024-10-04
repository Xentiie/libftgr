# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:26:47 by reclaire          #+#    #+#              #
#    Updated: 2024/09/23 17:16:41 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	3d
include config.mk

INCLUDES	+=	-I../../libft -I./ -I./srcs -I../
#CFLAGS		+=	-Wall -Wextra -Werror -O3 -g
#CFLAGS		+=	-g -fsanitize=address
CFLAGS		+=	-g -O3 -Wno-unknown-pragmas

_libftgr:
			$(MAKE) -C ../

_libft:
			$(MAKE) -C ../../libft

$(NAME):	_libft _libftgr objs $(OBJS)
#$(CC) $(CFLAGS) $(INCLUDES) $(LIBS_PATHS) $(OBJS) $(LIBS) -o $(NAME)
			$(CC) $(INCLUDES) $(LIBS_PATHS) $(OBJS) $(LIBS) -o $(NAME)
