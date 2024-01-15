# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/12 18:06:37 by reclaire          #+#    #+#              #
#    Updated: 2024/01/12 18:06:37 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := detect

NAME	=	libftgr.a
SRCS    =   libftgr.c
OBJS	=	${SRCS:.c=.o}

RM			=	rm -f

WSLENV ?= notwsl
ifndef WSLENV
	CFLAGS += -D FT_WIN32
	CC := x86_64-w64-mingw32-gcc
	DEP := libftwin32/libftwin32.a

	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
	    CFLAGS += -D AMD64
	else
	    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	        CFLAGS += -D AMD64
	    endif
	    ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	        CFLAGS += -D IA32
	    endif
	endif
else
	ifeq ($(OS),Windows_NT)
	    CFLAGS += -D FT_WIN32
		CC := x86_64-w64-mingw32-gcc
		DEP := libftwin32/libftwin32.a

	    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
	        CFLAGS += -D AMD64
	    else
	        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	            CFLAGS += -D AMD64
	        endif
	        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
	            CFLAGS += -D IA32
	        endif
	    endif
	else
	    UNAME_S := $(shell uname -s)
		CC := gcc
		DEP := libftx11/libftx11.a

	    ifeq ($(UNAME_S),Linux)
	        CFLAGS += -D FT_LINUX
	    endif
	    ifeq ($(UNAME_S),Darwin)
	        CFLAGS += -D FT_OSX
	    endif
	    UNAME_P := $(shell uname -p)
	    ifeq ($(UNAME_P),x86_64)
	        CFLAGS += -D AMD64
	    endif
	    ifneq ($(filter %86,$(UNAME_P)),)
	        CFLAGS += -D IA32
	    endif
	    ifneq ($(filter arm%,$(UNAME_P)),)
	        CFLAGS += -D ARM
	    endif
	endif
endif

INCLUDES  	=	-I../libft
CFLAGS		:=	-Wall -Wextra -Werror -O3
ifdef MOREFLAGS
CFLAGS		:=	$(CFLAGS) $(MOREFLAGS)
endif
ifeq ($(filter tests, $(MAKECMDGOALS)), tests) || ($(filter tests_re, $(MAKECMDGOALS)), tests_re)
CFLAGS		:=	$(CFLAGS) -D FT_MEMCHECK
endif


%.o: %.c
			$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS) $(DEP)

libftwin32/libftwin32.a:
			make -C ./libftwin32 no-lib

libftx11/libftx11.a:
			make -C ./libftx11 no-lib

detect:		$(DEP) $(NAME)



clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean detect clean

.PHONY:		detect clean fclean re