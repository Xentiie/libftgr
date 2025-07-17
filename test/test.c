/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/07/11 17:42:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX.h"

#include "libft/io.h"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

S32 main()
{
	struct s_ftGFX_ctx *ctx;
	struct s_ftGFX_window *win;

	struct s_ftGFX_event event;

	filedesc serv_sock;

	if ((ctx = ftGFX_create_ctx()) == NULL)
	{
		ft_perror("ftGFX_create_ctx");
		return 1;
	}

	if ((win = ftGFX_create_window(ctx, ivec2(200, 200), "test test")) == NULL)
	{
		ft_perror("ftGFX_create_window");
		return 1;
	}

	if ((serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
	{
		ft_perror("socket");
		return 1;
	}

	struct sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(55555);

	if (bind(serv_sock, &addr, sizeof(addr)) < 0)
	{
		ft_perror("bind");
		return 1;
	}

	if (listen(serv_sock, 3) < 0)
	{
		ft_perror("listen");
		return 1;
	}

	filedesc client_sock;
	U64 socklen = sizeof(addr);
	if ((client_sock = accept(serv_sock, (struct sockaddr *)&addr, (socklen_t *)&socklen)) < 0)
	{
		ft_perror("accept");
		return 1;
	}

	while (!win->should_close)
	{
		ftGFX_new_frame(ctx);
		ftGFX_poll_all(ctx);

		fd_set rd_set, wr_set;
		FD_ZERO(&rd_set);
		FD_ZERO(&wr_set);

		FD_SET(client_sock, &rd_set);
		struct timeval timeout = {.tv_sec = 0, .tv_usec = 1000};
		S32 nready = 0;
		if (select(client_sock + 1, &rd_set, &wr_set, NULL, &timeout))
		

		ftGFX_blt_screen(win);
		ftGFX_display_fps(win);
	}

	ftGFX_destroy_ctx(ctx);
}
