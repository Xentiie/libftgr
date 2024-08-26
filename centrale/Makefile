# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:26:47 by reclaire          #+#    #+#              #
#    Updated: 2024/07/02 18:33:07 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	centrale
include config.mk

INCLUDES	+=	-I../../libft -I./ -I./srcs -I../
#CFLAGS		+=	-Wall -Wextra -Werror -O3 -g
#CFLAGS		+=	-g -fsanitize=address
CFLAGS		+=	-g

_libftgr:
			$(MAKE) -C ../

_libft:
			$(MAKE) -C ../../libft

$(NAME):	_libft _libftgr objs $(OBJS)
			$(CC) $(CFLAGS) $(INCLUDES) $(LIBS_PATHS) $(OBJS) $(LIBS) -o $(NAME)
