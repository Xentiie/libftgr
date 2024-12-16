/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_truetype_reader.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:11:20 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/05 03:09:05 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _FT_RETURN
#include "ftgr_truetype.h"

static U32 checksum(U32 *table, U32 numberOfBytesInTable)
{
	U32 sum = 0;
	U32 nLongs = (numberOfBytesInTable + 3) / 4;
	while (nLongs-- > 0)
		sum += *table++;
	return sum;
}

#define reverse16(n) __builtin_bswap16(n)
#define reverse32(n) __builtin_bswap32(n)
#define reverse64(n) __builtin_bswap64(n)

void skip_bytes(filedesc fd, S64 n)
{
	U8 data[256] = {0};
	S64 skipped = 0;
	while (skipped < n)
	{
		S64 out = ft_read(fd, data, MAX(0, n - skipped));
		if (out < 1)
			break;
		skipped += out;
	}
}

U64 read_u64_litteendian(filedesc fd)
{
	U64 n;
	ft_read(fd, (char *)&n, sizeof(U64));
	return n;
}

U64 read_u64_bigendian(filedesc fd)
{
	U64 n;
	ft_read(fd, (char *)&n, sizeof(U64));
	return reverse64(n);
}

S64 read_s64_litteendian(filedesc fd)
{
	S64 n;
	ft_read(fd, (char *)&n, sizeof(S64));
	return n;
}

S64 read_s64_bigendian(filedesc fd)
{
	S64 n;
	ft_read(fd, (char *)&n, sizeof(S64));
	return reverse64(n);
}

U32 read_u32_litteendian(filedesc fd)
{
	U32 n;
	ft_read(fd, (char *)&n, sizeof(U32));
	return n;
}

U32 read_u32_bigendian(filedesc fd)
{
	U32 n;
	ft_read(fd, (char *)&n, sizeof(U32));
	return reverse32(n);
}

S32 read_s32_litteendian(filedesc fd)
{
	S32 n;
	ft_read(fd, (char *)&n, sizeof(S32));
	return n;
}

S32 read_s32_bigendian(filedesc fd)
{
	S32 n;
	ft_read(fd, (char *)&n, sizeof(S32));
	return reverse32(n);
}

U16 read_u16_bigendian(filedesc fd)
{
	U16 n;
	ft_read(fd, (char *)&n, sizeof(U16));
	return reverse16(n);
}

U16 read_u16_littleendian(filedesc fd)
{
	U16 n;
	ft_read(fd, (char *)&n, sizeof(U16));
	return n;
}

S16 read_s16_bigendian(filedesc fd)
{
	S16 n;
	ft_read(fd, (char *)&n, sizeof(S16));
	return reverse16(n);
}

S16 read_s16_littleendian(filedesc fd)
{
	S16 n;
	ft_read(fd, (char *)&n, sizeof(S16));
	return n;
}

U8 read_u8(filedesc fd)
{
	U8 n;
	ft_read(fd, (char *)&n, sizeof(U8));
	return n;
}

F32 to_fixed(U32 n)
{
	return (n >> 16) + ((F32)(n & 0xFFFF)) / U16_MAX;
}

void read_table_header(t_ftgr_truetype_loader *loader)
{
	loader->header = malloc(sizeof(t_truetype_header));
	if (!loader->header)
		FT_RET_ERR(, FT_EOMEM);
	lseek(loader->fd, 0, SEEK_SET);
	loader->header->scaler_type = read_u32_bigendian(loader->fd);
	loader->header->num_tables = read_u16_bigendian(loader->fd);
	loader->header->search_range = read_u16_bigendian(loader->fd);
	loader->header->entry_selector = read_u16_bigendian(loader->fd);
	loader->header->range_shift = read_u16_bigendian(loader->fd);
	loader->header_loaded = TRUE;
}

void read_table_sections(t_ftgr_truetype_loader *loader)
{
	t_truetype_header *header = loader->get_header(loader);
	if (!header)
		return;

	loader->sections = malloc(sizeof(t_table_entry) * header->num_tables);
	if (!loader->sections)
		FT_RET_ERR(, FT_EOMEM);
	for (U16 i = 0; i < header->num_tables; i++)
	{
		loader->sections[i].tag = read_u32_litteendian(loader->fd);
		loader->sections[i].checksum = read_u32_litteendian(loader->fd);
		loader->sections[i].offset = read_u32_bigendian(loader->fd);
		loader->sections[i].length = read_u32_bigendian(loader->fd);
	}
	loader->sections_loaded = TRUE;
}

t_table_entry *goto_table_entry(string tag, t_ftgr_truetype_loader *loader)
{
	t_truetype_header *header = loader->get_header(loader);
	if (!header)
		return NULL;

	U32 _tag = *(U32 *)tag;
	for (U16 i = 0; i < header->num_tables; i++)
	{
		if (_tag == loader->sections[i].tag)
		{
			lseek(loader->fd, loader->sections[i].offset, SEEK_SET);
			return &loader->sections[i];
		}
	}
	return NULL;
}

void read_table_head(t_ftgr_truetype_loader *loader)
{

	t_table_entry *ent = goto_table_entry("head", loader);
	if (!ent)
		return;

	lseek(loader->fd, ent->offset, SEEK_SET);
	t_head *head = malloc(sizeof(t_head));
	ft_bzero(head, sizeof(t_head));

	head->version = to_fixed(read_u32_bigendian(loader->fd));
	head->font_revision = to_fixed(read_u32_bigendian(loader->fd));
	head->checksum_adjustement = read_u32_bigendian(loader->fd);
	head->magic_n = read_u32_bigendian(loader->fd);
	head->flags = read_u16_bigendian(loader->fd);
	head->units_per_em = read_u16_bigendian(loader->fd);
	head->created = read_u64_bigendian(loader->fd);
	head->modified = read_u64_bigendian(loader->fd);
	head->xmin = read_u16_bigendian(loader->fd);
	head->ymin = read_u16_bigendian(loader->fd);
	head->xmax = read_u16_bigendian(loader->fd);
	head->ymax = read_u16_bigendian(loader->fd);
	head->mac_style = read_u16_bigendian(loader->fd);
	head->lowest_rec_ppem = read_u16_bigendian(loader->fd);
	head->font_direction_hint = read_s16_bigendian(loader->fd);
	head->index_to_loc_fmt = read_s16_bigendian(loader->fd);
	head->glyph_data_fmt = read_s16_bigendian(loader->fd);

	loader->head = head;
	loader->head_loaded = TRUE;
}

void read_table_kerning(t_ftgr_truetype_loader *loader)
{
	t_kerning *kern;

	t_table_entry *kern_table = goto_table_entry("kern", loader);
	if (kern_table == NULL)
		return;

	{
		U32 n_tables;
		U32 version = read_u16_bigendian(loader->fd);
		if (version == 0)
		{
			version |= read_u16_bigendian(loader->fd) << 16;
			if (version != 0x00010000)
				ft_printf("Warning: unknown version");
			n_tables = read_u32_bigendian(loader->fd);
		}
		else
			n_tables = read_u16_bigendian(loader->fd);

		kern = malloc(sizeof(t_kerning) + sizeof(t_kerning_subtable) * n_tables);
		kern->version = version;
		kern->subtables_count = n_tables;
	}

	for (U32 i = 0; i < kern->subtables_count; i++)
	{

		kern->tables[i].length = read_u32_bigendian(loader->fd);
		U16 coverage = read_u16_bigendian(loader->fd);
		kern->tables[i].tuple_index = read_u16_bigendian(loader->fd);

		if (coverage & 0x8000)
			kern->tables[i].vertical = TRUE;
		if (coverage & 0x4000)
			kern->tables[i].cross_stream = TRUE;
		if (coverage & 0x2000)
			kern->tables[i].variation = TRUE;
		if (coverage & 0x00FF)
			kern->tables[i].format_mask = coverage & 0x00FF;
	}
	// TODO: read data
	loader->kerning = kern;
	loader->kerning_loaded = TRUE;
}

void read_table_maxp(t_ftgr_truetype_loader *loader)
{
	t_table_entry *ent = goto_table_entry("maxp", loader);
	if (!ent)
		return;

	lseek(loader->fd, ent->offset, SEEK_SET);
	t_max_profile *maxp = malloc(sizeof(t_max_profile));
	ft_read(loader->fd, (char *)maxp, ent->length);

	maxp->version = reverse32(maxp->version);

	U32 _checksum = checksum((U32 *)maxp, sizeof(t_max_profile));
	ft_printf("%#x %#x %u\n", ent->checksum, _checksum, ent->checksum - _checksum);
	if (_checksum != ent->checksum)
		ft_printf("Warning: maxp invalid checksum\n");

	for (U8 i = 0; i < 14; i++)
		*(((U16 *)maxp) + 2 + i) = reverse16(*(((U16 *)maxp) + 2 + i));
	loader->maxp = maxp;
	loader->maxp_loaded = TRUE;
}

void read_glyph(filedesc fd, t_glyph *gl)
{
	gl->contour_end_indices_len = read_s16_bigendian(fd);

	gl->points_min.x = read_u16_bigendian(fd);
	gl->points_min.y = read_u16_bigendian(fd);
	gl->points_max.x = read_u16_bigendian(fd);
	gl->points_max.y = read_u16_bigendian(fd);

	gl->contour_end_indices = malloc(sizeof(U16) * gl->contour_end_indices_len);
	for (S16 i = 0; i < gl->contour_end_indices_len; i++)
		gl->contour_end_indices[i] = read_u16_bigendian(fd);

	U16 npoints = gl->contour_end_indices[gl->contour_end_indices_len - 1] + 1;
	U8 *all_flags = malloc(sizeof(U8) * npoints);
	skip_bytes(fd, read_u16_bigendian(fd));

	for (U16 i = 0; i < npoints; i++)
	{
		U8 flag = read_u8(fd);
		all_flags[i] = flag;

		if (flag & GLYPH_FLAG_REPEAT)
		{
			U8 r_cnt = read_u8(fd);
			for (U8 r = 0; r < r_cnt; r++)
				all_flags[++i] = flag;
		}
	}

	gl->points = malloc(sizeof(t_iv2) * npoints);
	ft_bzero(gl->points, sizeof(t_iv2) * npoints);

	for (int i = 0; i < npoints; i++)
	{
		gl->points[i].x = gl->points[MAX(0, i - 1)].x;
		U8 flag = all_flags[i];
		bool on_curve = !!(flag & GLYPH_FLAG_ON_CURVE);
		(void)on_curve;

		if (flag & GLYPH_FLAG_X_SHORT)
		{
			U8 offset = read_u8(fd);
			int sign = !!(flag & GLYPH_FLAG_X_SAME) ? 1 : -1;
			gl->points[i].x += offset * sign;
		}
		else if (!(flag & GLYPH_FLAG_X_SAME))
			gl->points[i].x += read_s16_bigendian(fd);
	}

	for (int i = 0; i < npoints; i++)
	{
		gl->points[i].y = gl->points[MAX(0, i - 1)].y;
		U8 flag = all_flags[i];
		bool on_curve = !!(flag & GLYPH_FLAG_ON_CURVE);
		(void)on_curve;

		if (flag & GLYPH_FLAG_Y_SHORT)
		{
			U8 offset = read_u8(fd);
			int sign = (flag & GLYPH_FLAG_Y_SAME) ? 1 : -1;
			gl->points[i].y += offset * sign;
		}
		else if (!(flag & GLYPH_FLAG_Y_SAME))
			gl->points[i].y += read_s16_bigendian(fd);
	}

	for (int i = 0; i < npoints; i++)
		gl->points[i].y = (gl->points_max.y - (gl->points[i].y - gl->points_min.y));

	gl->points_len = npoints;
}

void read_table_loca(t_ftgr_truetype_loader *loader)
{
	t_table_entry *ent = goto_table_entry("loca", loader);
	t_max_profile *maxp = loader->get_maxp(loader);
	t_head *head = loader->get_head(loader);
	if (!ent || !maxp || !head)
		return;

	bool two_bytes = head->index_to_loc_fmt == 0;
	U32 *loca = malloc(sizeof(U32) * maxp->glyph_count);
	lseek(loader->fd, ent->offset, SEEK_SET);
	if (two_bytes)
	{
		for (U16 i = 0; i < maxp->glyph_count; i++)
			loca[i] = ((U32)read_u16_bigendian(loader->fd)) * 2;
	}
	else
	{
		for (U16 i = 0; i < maxp->glyph_count; i++)
			loca[i] = read_u32_bigendian(loader->fd);
	}

	loader->loca = loca;
	loader->loca_loaded = TRUE;
}

void read_table_glyphs(t_ftgr_truetype_loader *loader)
{
	t_table_entry *ent = goto_table_entry("glyf", loader);
	t_max_profile *maxp = loader->get_maxp(loader);
	U32 *loca = loader->get_loca(loader);
	if (!ent || !maxp || !loca)
		return;

	loader->glyphs = malloc(sizeof(t_glyph) * maxp->glyph_count);

	for (U32 i = 0; i < 8; i++)
	{
		ft_printf("loca: %u\n", loca[i]);
		lseek(loader->fd, ent->offset + loca[i], SEEK_SET);
		read_glyph(loader->fd, &loader->glyphs[i]);
	}

	print_glyph(&loader->glyphs[0]);
	print_glyph(&loader->glyphs[5]);
	print_glyph(&loader->glyphs[6]);

}
