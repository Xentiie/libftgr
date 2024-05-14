.DEFAULT_GOAL := all
all: objs $(NAME)

TARGET=linux
RM=rm -rf
CC=gcc
CFLAGS=-DFT_OS_LINUX 
INCLUDES=
LIBS_PATHS=
LIBS=
OBJS_PATH=./objs
SRCS=./srcs/x11/ftgr_ctx.c ./srcs/x11/ftgr_windows.c ./srcs/x11/ftgr_keys.c ./srcs/x11/ftgr_screen_size.c ./srcs/x11/ftgr_utils.c ./srcs/x11/ftgr_images.c ./srcs/x11/ftgr_clear_win.c ./srcs/x11/ftgr_free.c ./srcs/x11/ftgr_time.c ./srcs/x11/ftgr_xkb.c ./srcs/x11/ftgr_poll.c ./srcs/x11/ftgr_mouse.c
OBJS=./objs/ftgr_ctx.o ./objs/ftgr_windows.o ./objs/ftgr_keys.o ./objs/ftgr_screen_size.o ./objs/ftgr_utils.o ./objs/ftgr_images.o ./objs/ftgr_clear_win.o ./objs/ftgr_free.o ./objs/ftgr_time.o ./objs/ftgr_xkb.o ./objs/ftgr_poll.o ./objs/ftgr_mouse.o

objs:
	mkdir -p ./objs
./objs/ftgr_ctx.o: ./srcs/x11/ftgr_ctx.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_ctx.c -o ./objs/ftgr_ctx.o

./objs/ftgr_windows.o: ./srcs/x11/ftgr_windows.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_windows.c -o ./objs/ftgr_windows.o

./objs/ftgr_keys.o: ./srcs/x11/ftgr_keys.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_keys.c -o ./objs/ftgr_keys.o

./objs/ftgr_screen_size.o: ./srcs/x11/ftgr_screen_size.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_screen_size.c -o ./objs/ftgr_screen_size.o

./objs/ftgr_utils.o: ./srcs/x11/ftgr_utils.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_utils.c -o ./objs/ftgr_utils.o

./objs/ftgr_images.o: ./srcs/x11/ftgr_images.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_images.c -o ./objs/ftgr_images.o

./objs/ftgr_clear_win.o: ./srcs/x11/ftgr_clear_win.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_clear_win.c -o ./objs/ftgr_clear_win.o

./objs/ftgr_free.o: ./srcs/x11/ftgr_free.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_free.c -o ./objs/ftgr_free.o

./objs/ftgr_time.o: ./srcs/x11/ftgr_time.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_time.c -o ./objs/ftgr_time.o

./objs/ftgr_xkb.o: ./srcs/x11/ftgr_xkb.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_xkb.c -o ./objs/ftgr_xkb.o

./objs/ftgr_poll.o: ./srcs/x11/ftgr_poll.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_poll.c -o ./objs/ftgr_poll.o

./objs/ftgr_mouse.o: ./srcs/x11/ftgr_mouse.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_mouse.c -o ./objs/ftgr_mouse.o


clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		 all clean fclean re
