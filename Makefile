# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:26:47 by reclaire          #+#    #+#              #
#    Updated: 2024/12/03 18:57:39 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

dyn: $(OBJS)
	$(CC) -shared -fPIC $(CFLAGS) -o my_library.so my_library.c

test:	packages $(NAME)
			$(CC) $(CFLAGS) $(INCLUDES) test2.c $(LIBS_PATHS) $(LIBS)

test_deflate:	packages $(NAME)
			$(CC) $(CFLAGS) $(INCLUDES) test_deflate.c $(LIBS_PATHS) $(LIBS)

test_text:	packages $(NAME)
			$(CC) $(CFLAGS) $(INCLUDES) test_text.c $(LIBS_PATHS) $(LIBS)
