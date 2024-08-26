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

NAME		=	libftgr.a
include config.mk

INCLUDES	+=	-I../libft -I./ -I./srcs -I./3rdparty/OpenCL/include
#CFLAGS		+=	-Wall -Wextra -Werror -O3 -g
#CFLAGS		+=	-g -fsanitize=address
CFLAGS		+=	-g

$(NAME):	objs $(OBJS)
			ar -rcs $(NAME) $(OBJS)
			cp $(NAME) $(TARGET)_$(NAME)

_libft:
			$(MAKE) -C ../libft
#			mingw32-make.exe -C ../libft

test:	$(NAME) _libft
			$(CC) $(CFLAGS) $(INCLUDES) -L./ -L../libft test2.c -lftgr -lft -lm -lgdi32
#			$(CC) $(CFLAGS) $(INCLUDES) -L./ -L../libft test2.c -lftgr -lft -lm -lX11 -lXext
#			$(CC) $(CFLAGS) $(INCLUDES) -L./ -L./3rdparty/OpenCL/lib -L../libft test.c -lftgr -lft -lm -lgdi32 -lopengl32 -lOpenCL

test_deflate:	$(NAME) _libft
			$(CC) $(CFLAGS) -O3 $(INCLUDES) -L./ -L../libft test_deflate.c -lftgr -lft -lm

test_text:	$(NAME) _libft
			$(CC) $(CFLAGS) -O3 $(INCLUDES) -L./ -L../libft test_text.c -lftgr -lft -lm -lX11 -lXext