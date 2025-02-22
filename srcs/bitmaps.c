/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:44:36 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/14 03:07:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

//#define BITMAP_TEXT_DEBUG 1

void ftgr_init_bitmap(t_bitmap *bitmap, t_image *img, t_iv2 char_size, U32 line_chars_count, t_iv2 sep_size)
{
	bitmap->img = img;
	bitmap->char_width = char_size.x;
	bitmap->char_height = char_size.y;
	bitmap->line_width = line_chars_count;
	bitmap->sep_width = sep_size.x;
	bitmap->sep_height = sep_size.y;
}

t_iv4 ftgr_bitmap_rect_char_lines(t_bitmap *bitmap, t_iv2 pos, U32 line_width, U32 lines_cnt)
{
	return ivec4(
		pos.x, pos.y,
		pos.x + (line_width * (bitmap->sep_width + bitmap->char_width)), pos.y + (lines_cnt * (bitmap->sep_height + bitmap->char_height)));
}


void ftgr_draw_bitmap_text(t_image *out, t_iv4 rect, t_bitmap *bitmap, string str, F32 scale, t_iv2 kerning, t_color col)
{
	S32 char_size;
	S32 line_size;
	S32 chars_per_line;
	S32 available_lines;
	U64 len;
	S32 str_len;

	S32 bitmap_x_step;
	S32 bitmap_y_step;

	len = ft_strlen(str);
	char_size = (bitmap->char_width * scale + kerning.x);
	line_size = (bitmap->char_height * scale + kerning.y);

	chars_per_line = (rect.z - rect.x + kerning.x) / char_size;
	available_lines = (rect.w - rect.y + kerning.y) / line_size;

	str_len = ft_imin(len, chars_per_line * available_lines);

	bitmap_x_step = bitmap->char_width + bitmap->sep_width;
	bitmap_y_step = bitmap->char_height + bitmap->sep_height;

#if BITMAP_TEXT_DEBUG
	t_iv4 bitmap_debug_draw_rect;
	t_iv2 _ofs = ivec2(0, out->size.y / 2 - bitmap->img->size.y / 2);
	F32	  _scl = 3.0f;
	F32	  aspect_ratio = bitmap->img->size.x / bitmap->img->size.y;
	bitmap_debug_draw_rect.x = _ofs.x;
	bitmap_debug_draw_rect.y = _ofs.y;
	bitmap_debug_draw_rect.z = _ofs.x + (bitmap->img->size.x * _scl);
	bitmap_debug_draw_rect.w = _ofs.y + (bitmap->img->size.y * _scl);

	ftgr_stretch_img(out, bitmap_debug_draw_rect, bitmap->img, ivec4(0, 0, bitmap->img->size.x, bitmap->img->size.y),
					 ftgr_color(255, 255, 255, 255));
#endif

	for (S32 i = 0; i < str_len; i++)
	{
		S8 v = str[i];
		if (v < 32)
			v = ' ';
		v -= 32;

		t_iv2 out_pos = ivec2(rect.x + ((i % chars_per_line) * char_size), rect.y + ((i / chars_per_line) * line_size));
		t_iv2 bitmap_pos
			= ivec2((v % bitmap->line_width) * bitmap_x_step + 1, (v / bitmap->line_width) * bitmap_y_step + 1);

		t_iv4 out_rect = ivec4(out_pos.x, out_pos.y, out_pos.x + bitmap->char_width * scale,
							   out_pos.y + bitmap->char_height * scale);
		t_iv4 bitmap_rect
			= ivec4(bitmap_pos.x, bitmap_pos.y, bitmap_pos.x + bitmap->char_width, bitmap_pos.y + bitmap->char_height);

		ftgr_stretch_img2(out, out_rect, bitmap->img, bitmap_rect, col);

#if BITMAP_TEXT_DEBUG
		{
			t_color chars_rect_col = ftgr_color(0, 0, 0, 255);
			t_color chars_arrows_col = ftgr_color(127, 0, 127, 255);
			ftgr_draw_rect(out, rect, chars_rect_col);
			ftgr_draw_rect(out, out_rect, chars_rect_col);
			ftgr_draw_rect(out, bitmap_debug_draw_rect, chars_arrows_col);
			ftgr_draw_line(out, ivec2((out_rect.x + out_rect.z) / 2, (out_rect.y + out_rect.w) / 2),
						   ivec2(bitmap_debug_draw_rect.x + (bitmap_pos.x * _scl) + bitmap->char_width * _scl / 2,
								 bitmap_debug_draw_rect.y + (bitmap_pos.y * _scl) + bitmap->char_height * _scl / 2),
						   chars_arrows_col);
		}
#endif
	}

#if BITMAP_TEXT_DEBUG2
	{
		ftgr_draw_rect(out, rect, COL_BLACK);
	}
#endif
}
