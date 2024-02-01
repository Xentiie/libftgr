/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:05:21 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/31 21:05:21 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libftgr.h"


int main()
{
	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(512, 512), "test");

	ftgr_loop(ctx);
}
