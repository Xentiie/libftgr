# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/15 17:26:47 by reclaire          #+#    #+#              #
#    Updated: 2024/11/12 02:35:33 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include config.mk

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS)

test:	$(NAME)
			$(CC) $(CFLAGS) $(INCLUDES) $(LIBS_PATHS) -L./ -lftgr $(LIBS) test2.c
.PHONY: test

test_deflate:	$(NAME)
			$(CC) $(CFLAGS) $(INCLUDES) $(LIBS_PATHS) -L./ -lftgr $(LIBS) test_deflate.c
.PHONY: test_deflate

test_text:	$(NAME)
			$(CC) $(CFLAGS) $(INCLUDES) $(LIBS_PATHS) -L./ -lftgr $(LIBS) test_text.c
.PHONY: test_text