/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_truetype.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:01:33 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/11 03:42:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftgr_truetype.h"

SECTION_GETTER_IMPL(t_truetype_header *, header)
SECTION_GETTER_IMPL(t_head *, head)
SECTION_GETTER_IMPL(t_table_entry *, sections)
SECTION_GETTER_IMPL(U32 *, loca)
SECTION_GETTER_IMPL(t_glyph *, glyphs)
SECTION_GETTER_IMPL(t_kerning *, kerning)
SECTION_GETTER_IMPL(t_max_profile *, maxp)

void draw_glyph(t_glyph glyph, t_ftgr_img *img, S32 xoffset)
{
	t_iv2 min = ivec2(S32_MAX, S32_MAX);
	t_iv2 max = ivec2(S32_MIN, S32_MIN);
	for (int i = 0; i < glyph.points_len; i++)
	{
		min.x = MIN(glyph.points[i].x, min.x);
		min.y = MIN(glyph.points[i].y, min.y);

		max.x = MAX(glyph.points[i].x, max.x);
		max.y = MAX(glyph.points[i].y, max.y);
	}

	printf("%d %d\n%d %d\n", min.x, max.x, min.y, max.y);

//#define conv(p) vec2_int(vec2_scl(ft_invlerp2_i(min, max, p), scale))
#define conv(p) ivec2(p.x / 10 + xoffset, p.y / 10)
	int scale = 300;

	int contourStartIndex = 0;

	for (int i = 0; i < glyph.contour_end_indices_len; i++)
	{
		int points_n = glyph.contour_end_indices[i] - contourStartIndex + 1;
		t_color col = (t_color){(i%3) == 0 ? 255 : 0, (i%3) == 1 ? 255 : 0, (i%3) == 2 ? 255 : 0, 255};

		t_iv2 *points = glyph.points + contourStartIndex;
		for (int j = 0; j < points_n; j++)
		{
			t_iv2 st = conv(points[j]);
			t_iv2 nd = conv(points[(j + 1) % points_n]);
			ftgr_draw_line(img, st, nd, col);
		}
		contourStartIndex = glyph.contour_end_indices[i] + 1;
	}
}

void *ftgr_load_font(file fd, t_ftgr_img *img)
{
	t_ftgr_truetype_loader *loader = malloc(sizeof(t_ftgr_truetype_loader));
	if (!loader)
		__FTRETURN_ERR(NULL, FT_EOMEM);
	ft_bzero(loader, sizeof(t_ftgr_truetype_loader));

	loader->fd = fd;
	loader->get_header = get_header;
	loader->get_head = get_head;
	loader->get_sections = get_sections;
	loader->get_loca = get_loca;
	loader->get_glyphs = get_glyphs;
	loader->get_kerning = get_kerning;
	loader->get_maxp = get_maxp;

	print_truetype_loader(loader);
	loader->get_glyphs(loader);	

	draw_glyph(loader->glyphs[0], img, 70);
	draw_glyph(loader->glyphs[5], img, 140);
	draw_glyph(loader->glyphs[6], img, 210);
	//draw_glyph(loader->glyphs[3], img, 280);
	//draw_glyph(loader->glyphs[4], img, 350);

//	read_glyph(fd, &glyph);
//	printf("Glyph:\n");
//	print_glyph(&glyph);
//	draw_glyph(glyph, img, 52);

	return loader;
}
