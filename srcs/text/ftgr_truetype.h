/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_truetype.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 04:09:57 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/11 03:37:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTGR_TRUETYPE_H
#define FTGR_TRUETYPE_H

#include "../libftgr_int.h"
#include "libft/io.h"
#include "libft/limits.h"
#include "libft/maths.h"

//#define printf(...) do { (printf)("(%s:%d)", __FILE__, __LINE__); (printf)(__VA_ARGS__); } while (0)

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b)

#define GLYPH_FLAG_ON_CURVE (0x1)
#define GLYPH_FLAG_X_SHORT (0x2)
#define GLYPH_FLAG_Y_SHORT (0x4)
#define GLYPH_FLAG_REPEAT (0x8)
#define GLYPH_FLAG_X_SAME (0x10)
#define GLYPH_FLAG_Y_SAME (0x20)

typedef struct s_truetype_header
{
	// A tag to indicate the OFA scaler to be used to rasterize this font; see the note on the scaler type below for more information.
	U32 scaler_type;
	// Number of tables
	U16 num_tables;
	//(maximum power of 2 <= numTables)*16
	U16 search_range;
	// log2(maximum power of 2 <= numTables)
	U16 entry_selector;
	// numTables*16-searchRange
	U16 range_shift;
} t_truetype_header;

typedef struct s_head
{
	F32 version;
	F32 font_revision;
	U32 checksum_adjustement;
	U32 magic_n;
	U16 flags;
	U16 units_per_em;
	S64 created;
	S64 modified;
	S16 xmin;
	S16 ymin;
	S16 xmax;
	S16 ymax;
	U16 mac_style;
	U16 lowest_rec_ppem;
	S16 font_direction_hint;
	S16 index_to_loc_fmt;
	S16 glyph_data_fmt;
} t_head;

typedef struct s_glyph
{
	U16 contour_end_indices_len;
	U16 *contour_end_indices;
	U64 points_len;
	t_iv2 *points;
	t_iv2 points_max;
	t_iv2 points_min;
} t_glyph;

typedef struct s_table_entry
{
	U32 tag;
	U32 checksum;
	U32 offset;
	U32 length;
} t_table_entry;

typedef struct s_kerning_subtable
{
	U32 length;
	bool vertical;
	bool cross_stream;
	bool variation;
	U8 format_mask;
	U16 tuple_index;
} t_kerning_subtable;

typedef struct s_kerning
{
	U32 version;
	U32 subtables_count;

	t_kerning_subtable tables[];
} t_kerning;

typedef struct s_max_profile
{
	U32 version;
	U16 glyph_count;
	U16 points_max;
	U16 contours_max;
	U16 component_points_max;
	U16 component_contour_max;
	U16 zones_max;
	U16 twilight_zones_max;
	U16 storage_max;
	U16 functions_def_max;
	U16 instructions_def_max;
	U16 stack_elem_max;
	U16 instruction_size_max;
	U16 components_elements_max;
	U16 components_depth_max;
} t_max_profile;

#define SECTION_GETTER(type, name) void read_table_##name(struct s_ftgr_truetype_loader *loader)
#define SECTION_INIT(type, name)                                \
	type (*get_##name)(struct s_ftgr_truetype_loader * loader); \
	type name;                                                  \
	bool name##_loaded;
#define SECTION_GETTER_IMPL(type, name)                    \
	type get_##name(struct s_ftgr_truetype_loader *loader) \
	{                                                      \
		if (!(loader->name##_loaded))                      \
			read_table_##name(loader);                     \
		return loader->name;                               \
	}

typedef struct s_ftgr_truetype_loader
{
	file fd;

	SECTION_INIT(t_truetype_header *, header);
	SECTION_INIT(t_head *, head);
	SECTION_INIT(t_table_entry *, sections);
	SECTION_INIT(U32 *, loca);
	SECTION_INIT(t_glyph *, glyphs);
	SECTION_INIT(t_kerning *, kerning);
	SECTION_INIT(t_max_profile *, maxp);

} t_ftgr_truetype_loader;

SECTION_GETTER(t_truetype_header *, header);
SECTION_GETTER(t_head *, head);
SECTION_GETTER(t_table_entry *, sections);
SECTION_GETTER(U32 *, loca);
SECTION_GETTER(t_glyph *, glyphs);
SECTION_GETTER(t_kerning *, kerning);
SECTION_GETTER(t_max_profile *, maxp);

void skip_bytes(file fd, S64 n);

U64 read_u64_litteendian(file fd);
U64 read_u64_bigendian(file fd);
S64 read_s64_litteendian(file fd);
S64 read_s64_bigendian(file fd);

U32 read_u32_litteendian(file fd);
U32 read_u32_bigendian(file fd);
S32 read_s32_litteendian(file fd);
S32 read_s32_bigendian(file fd);

U16 read_u16_littleendian(file fd);
U16 read_u16_bigendian(file fd);
S16 read_s16_littleendian(file fd);
S16 read_s16_bigendian(file fd);

U8 read_u8(file fd);

void print_truetype_loader(t_ftgr_truetype_loader *state);
void print_table_header(t_ftgr_truetype_loader *state);
void print_table_head(t_ftgr_truetype_loader *loader);
void print_table_sections(t_ftgr_truetype_loader *state);
void print_table_kerning(t_ftgr_truetype_loader *state);
void print_table_maxp(t_ftgr_truetype_loader *state);
void print_table_glyphs(t_ftgr_truetype_loader *state);

t_table_entry *goto_table_entry(string tag, t_ftgr_truetype_loader *state);

void read_glyph(file fd, t_glyph *gl);
void print_glyph(t_glyph *glyph);

#endif
