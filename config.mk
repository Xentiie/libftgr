.DEFAULT_GOAL := all
all: objs $(NAME)

<<<<<<< HEAD
TARGET=linux
RM=rm -rf
CC=gcc
CFLAGS=-DFT_OS_LINUX 
=======
TARGET=windows
RM=rm -rf
CC=x86_64-w64-mingw32-gcc
CFLAGS=-DFT_OS_WIN 
>>>>>>> 3081bf208e6a84c2a8a688c3e159957a4e81b68e
INCLUDES=
LIBS_PATHS=
LIBS=
OBJS_PATH=./objs
<<<<<<< HEAD
SRCS=./srcs/x11/ftgr_ctx.c ./srcs/x11/ftgr_windows.c ./srcs/x11/ftgr_keys.c ./srcs/x11/ftgr_screen_size.c ./srcs/x11/ftgr_utils.c ./srcs/x11/ftgr_images.c ./srcs/x11/ftgr_clear_win.c ./srcs/x11/ftgr_free.c ./srcs/x11/ftgr_time.c ./srcs/x11/ftgr_xkb.c ./srcs/x11/ftgr_poll.c ./srcs/x11/ftgr_mouse.c
OBJS=./objs/ftgr_ctx.o ./objs/ftgr_windows.o ./objs/ftgr_keys.o ./objs/ftgr_screen_size.o ./objs/ftgr_utils.o ./objs/ftgr_images.o ./objs/ftgr_clear_win.o ./objs/ftgr_free.o ./objs/ftgr_time.o ./objs/ftgr_xkb.o ./objs/ftgr_poll.o ./objs/ftgr_mouse.o
=======
SRCS=./srcs/windows/ftgr_ctx.c ./srcs/windows/ftgr_err.c ./srcs/windows/ftgr_images.c ./srcs/windows/ftgr_keys.c ./srcs/windows/ftgr_mouse.c ./srcs/windows/ftgr_poll.c ./srcs/windows/ftgr_quit.c ./srcs/windows/ftgr_time.c ./srcs/windows/ftgr_ui.c ./srcs/windows/ftgr_utils.c ./srcs/windows/ftgr_windows.c ./srcs/img_draw_utils.c
OBJS=./objs/ftgr_ctx.o ./objs/ftgr_err.o ./objs/ftgr_images.o ./objs/ftgr_keys.o ./objs/ftgr_mouse.o ./objs/ftgr_poll.o ./objs/ftgr_quit.o ./objs/ftgr_time.o ./objs/ftgr_ui.o ./objs/ftgr_utils.o ./objs/ftgr_windows.o ./objs/img_draw_utils.o
>>>>>>> 3081bf208e6a84c2a8a688c3e159957a4e81b68e

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

<<<<<<< HEAD
./objs/ftgr_time.o: ./srcs/x11/ftgr_time.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_time.c -o ./objs/ftgr_time.o
=======
./objs/ftgr_ui.o: ./srcs/windows/ftgr_ui.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_ui.c -o ./objs/ftgr_ui.o

./objs/ftgr_utils.o: ./srcs/windows/ftgr_utils.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_utils.c -o ./objs/ftgr_utils.o
>>>>>>> 3081bf208e6a84c2a8a688c3e159957a4e81b68e

./objs/ftgr_xkb.o: ./srcs/x11/ftgr_xkb.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_xkb.c -o ./objs/ftgr_xkb.o

./objs/ftgr_poll.o: ./srcs/x11/ftgr_poll.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_poll.c -o ./objs/ftgr_poll.o

./objs/ftgr_mouse.o: ./srcs/x11/ftgr_mouse.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/x11/ftgr_mouse.c -o ./objs/ftgr_mouse.o

./objs/img_draw_utils.o: ./srcs/img_draw_utils.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/img_draw_utils.c -o ./objs/img_draw_utils.o


clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		 all clean fclean re
