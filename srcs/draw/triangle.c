/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 19:39:00 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/06 19:46:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

void ftgr_draw_triangle(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col)
{
	ftgr_draw_line(img, p1, p2, col);
	ftgr_draw_line(img, p2, p3, col);
	ftgr_draw_line(img, p3, p1, col);
}

void ftgr_draw_triangle_bound(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound)
{
	ftgr_draw_line_bound(img, p1, p2, col, bound);
	ftgr_draw_line_bound(img, p2, p3, col, bound);
	ftgr_draw_line_bound(img, p3, p1, col, bound);
}

void ftgr_draw_triangle2(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col)
{
	ftgr_draw_line2(img, p1, p2, col);
	ftgr_draw_line2(img, p2, p3, col);
	ftgr_draw_line2(img, p3, p1, col);
}

void ftgr_draw_triangle_bound2(t_ftgr_img *img, t_iv2 p1, t_iv2 p2, t_iv2 p3, t_color col, t_iv4 bound)
{
	ftgr_draw_line_bound2(img, p1, p2, col, bound);
	ftgr_draw_line_bound2(img, p2, p3, col, bound);
	ftgr_draw_line_bound2(img, p3, p1, col, bound);
}
