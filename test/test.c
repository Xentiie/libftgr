/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:46:09 by reclaire          #+#    #+#             */
/*   Updated: 2025/05/27 14:32:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftGFX.h"

#include "libft/io.h"

S32 main()
{
	struct s_ftGFX_ctx *ctx;
	struct s_ftGFX_window *win;

	struct s_ftGFX_event event;

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

	while (!ctx->should_close)
	{
		ftGFX_new_frame(ctx);
		ftGFX_poll_all(ctx);

		if (ctx->mouse[0] == 1 || ctx->mouse[2] == 1)
		ft_printf(			"%d %d\n", ctx->mouse[0], ctx->mouse[2]);
		if (ftGFX_is_mouse_pressed(ctx, FTGFX_MOUSE_LEFT))
			ft_printf("left\n");
		if (ftGFX_is_mouse_pressed(ctx, FTGFX_MOUSE_RIGHT))
			ft_printf("right\n");
		if (ftGFX_is_mouse_released(ctx, FTGFX_MOUSE_LEFT))
			ft_printf("left\n");
		if (ftGFX_is_mouse_released(ctx, FTGFX_MOUSE_RIGHT))
			ft_printf("right\n");
	}

	ftGFX_destroy_ctx(ctx);
}
