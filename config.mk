.DEFAULT_GOAL := all
all: objs $(NAME)

TARGET=windows
RM=rm -rf
CC=x86_64-w64-mingw32-gcc
CFLAGS=-DFT_OS_WIN 
INCLUDES=
LIBS_PATHS=
LIBS=
OBJS_PATH=./objs
SRCS=./srcs/windows/ftgr_ctx.c ./srcs/windows/ftgr_err.c ./srcs/windows/ftgr_images.c ./srcs/windows/ftgr_keys.c ./srcs/windows/ftgr_mouse.c ./srcs/windows/ftgr_poll.c ./srcs/windows/ftgr_quit.c ./srcs/windows/ftgr_time.c ./srcs/windows/ftgr_ui.c ./srcs/windows/ftgr_utils.c ./srcs/windows/ftgr_windows.c ./srcs/img_draw_utils.c
OBJS=./objs/ftgr_ctx.o ./objs/ftgr_err.o ./objs/ftgr_images.o ./objs/ftgr_keys.o ./objs/ftgr_mouse.o ./objs/ftgr_poll.o ./objs/ftgr_quit.o ./objs/ftgr_time.o ./objs/ftgr_ui.o ./objs/ftgr_utils.o ./objs/ftgr_windows.o ./objs/img_draw_utils.o

objs:
	mkdir -p ./objs
./objs/ftgr_ctx.o: ./srcs/windows/ftgr_ctx.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_ctx.c -o ./objs/ftgr_ctx.o

./objs/ftgr_err.o: ./srcs/windows/ftgr_err.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_err.c -o ./objs/ftgr_err.o

./objs/ftgr_images.o: ./srcs/windows/ftgr_images.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_images.c -o ./objs/ftgr_images.o

./objs/ftgr_keys.o: ./srcs/windows/ftgr_keys.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_keys.c -o ./objs/ftgr_keys.o

./objs/ftgr_mouse.o: ./srcs/windows/ftgr_mouse.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_mouse.c -o ./objs/ftgr_mouse.o

./objs/ftgr_poll.o: ./srcs/windows/ftgr_poll.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_poll.c -o ./objs/ftgr_poll.o

./objs/ftgr_quit.o: ./srcs/windows/ftgr_quit.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_quit.c -o ./objs/ftgr_quit.o

./objs/ftgr_time.o: ./srcs/windows/ftgr_time.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_time.c -o ./objs/ftgr_time.o

./objs/ftgr_ui.o: ./srcs/windows/ftgr_ui.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_ui.c -o ./objs/ftgr_ui.o

./objs/ftgr_utils.o: ./srcs/windows/ftgr_utils.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_utils.c -o ./objs/ftgr_utils.o

./objs/ftgr_windows.o: ./srcs/windows/ftgr_windows.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/windows/ftgr_windows.c -o ./objs/ftgr_windows.o

./objs/img_draw_utils.o: ./srcs/img_draw_utils.c
	$(CC) $(CFLAGS) $(INCLUDES) -c ./srcs/img_draw_utils.c -o ./objs/img_draw_utils.o


clean:
			$(RM) $(OBJS)

fclean:	clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		 all clean fclean re
