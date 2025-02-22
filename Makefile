# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:26:47 by reclaire          #+#    #+#              #
#    Updated: 2025/01/31 17:07:41 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

test:	packages $(NAME)
			$(CC) $(CFLAGS) $(INCLUDES) test/*.c -L./ $(LIBS_PATHS) -lftgr $(LIBS)

