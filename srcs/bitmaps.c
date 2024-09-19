/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmaps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:44:36 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/18 15:40:00 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

//#define BITMAP_TEXT_DEBUG 1

void ftgr_init_bitmap(t_bitmap *bitmap, t_ftgr_img *img, t_iv2 char_size, U32 line_chars_count, t_iv2 sep_size)
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

U64 ftgr_bitmap_get_width(t_bitmap *bitmap, t_text text)
{
	S64 len = ft_strlen(text.str);
	return len * (bitmap->char_width * text.scale + text.kerning.x);
}

U64 ftgr_bitmap_get_height(t_bitmap *bitmap, t_text text)
{
	return bitmap->char_height * text.scale + text.kerning.y;
}

void ftgr_draw_bitmap_text(t_ftgr_img *out, t_iv4 rect, t_bitmap *bitmap, t_text text, t_color col)
{
	string str = text.str;
	S32 scale = text.scale;
	S32 xkerning = text.kerning.x;
	S32 ykerning = text.kerning.y;

	U64 str_len = ft_strlen(str);

	F32 out_x_step = bitmap->char_width * scale + xkerning;
	F32 out_y_step = bitmap->char_height * scale + ykerning;

	U32 line_width = (F32)(rect.z - rect.x) / out_x_step;
	U32 lines_cnt = (F32)(rect.w - rect.y) / out_y_step;
	str_len = ft_imin(str_len, line_width * lines_cnt);

	S32 bitmap_x_step = bitmap->char_width + bitmap->sep_width;
	S32 bitmap_y_step = bitmap->char_height + bitmap->sep_height;

	for (U64 i = 0; i < str_len; i++)
	{
		S8 v = str[i];
		if (v < 32)
			v = ' ';
		v -= 32;

		t_iv2 out_pos = ivec2(rect.x + ((i % line_width) * out_x_step), rect.y + ((i / line_width) * out_y_step));
		t_iv2 bitmap_pos = ivec2((v % bitmap->line_width) * bitmap_x_step + 1, (v / bitmap->line_width) * bitmap_y_step + 1);

		t_iv4 out_rect = ivec4(out_pos.x, out_pos.y, out_pos.x + bitmap->char_width * scale, out_pos.y + bitmap->char_height * scale);
		t_iv4 bitmap_rect = ivec4(bitmap_pos.x, bitmap_pos.y, bitmap_pos.x + bitmap->char_width, bitmap_pos.y + bitmap->char_height);

		ftgr_stretch_img2(out, out_rect, bitmap->img, bitmap_rect, col);

#ifdef BITMAP_TEXT_DEBUG
		{
			t_color col = ftgr_rand_color(ofs++);
			ftgr_draw_rect(out, out_rect, col);
			ftgr_draw_rect(out, bitmap_rect, col);
			ftgr_draw_line(out, ivec2((out_rect.x + out_rect.z) / 2, (out_rect.y + out_rect.w) / 2),
						   ivec2((bitmap_rect.x + bitmap_rect.z) / 2, (bitmap_rect.y + bitmap_rect.w) / 2),
						   col);
		}
#endif
	}

#ifdef BITMAP_TEXT_DEBUG2
	{
		ftgr_draw_rect(out, rect, COL_BLACK);	
	}
#endif
}
