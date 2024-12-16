/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:40:24 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/12 13:38:23 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "widgets2.h"
#include "libftgr.h"

#include "libft/time.h"
#include "libft/io.h"

#include <stdlib.h>
#include <stdio.h>

S32 main()
{
	t_ftgr_ctx *ctx;
	t_ftgr_win *win;


	ctx = ftgr_create_ctx();
	win = ftgr_new_window(ctx, ivec2(400, 400), "widget stress test");
	win->w_root->name = "root";


}
