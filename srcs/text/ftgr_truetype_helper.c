/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_truetype_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:55:22 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 03:18:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftgr_truetype.h"

void print_glyph(t_glyph *glyph)
{
	ft_printf("Glyph:\n");
	ft_printf("	Coords min: (%d %d)\n", glyph->points_min.x, glyph->points_min.y);
	ft_printf("	Coords max: (%d %d)\n", glyph->points_max.x, glyph->points_max.y);
	ft_printf("	Contour end indices length: %u\n", glyph->contour_end_indices_len);

	ft_printf("	Contour end indices: ");
	for (U16 i = 0; i < glyph->contour_end_indices_len; i++)
		ft_printf("%u ", glyph->contour_end_indices[i]);
	ft_printf("\n");

	ft_printf("	Coords length: %lu\n", glyph->points_len);
	ft_printf("	Coords:\n	");
	U16 j = 0;
	for (U64 i = 0; i < glyph->points_len; i++)
	{
		ft_printf("(%d %d) ", glyph->points[i].x, glyph->points[i].y);
		if (j < glyph->contour_end_indices_len && i == glyph->contour_end_indices[j])
		{
			ft_printf("\n	");
			j++;
		}
	}
	ft_printf("\n");
}

void print_truetype_header(t_ftgr_truetype_loader *loader)
{
	t_truetype_header *header = loader->get_header(loader);
	if (!header)
		return;

	ft_printf("scaler_type: %#x\n", header->scaler_type);
	ft_printf("num_tables: %u\n", header->num_tables);
	ft_printf("search_range: %u\n", header->search_range);
	ft_printf("entry_selector: %u\n", header->entry_selector);
	ft_printf("range_shift: %u\n", header->range_shift);
}

void print_table_sections(t_ftgr_truetype_loader *loader)
{
	t_truetype_header *header = loader->get_header(loader);
	t_table_entry *sections = loader->get_sections(loader);
	if (!header || !sections)
		return;
	
	ft_printf("TrueType table:\n");
	for (U16 i = 0; i < header->num_tables; i++)
		ft_printf("	'%.4s': (checksum:%#x) (offset:%u) (length:%u)\n", (string)&sections[i].tag, sections[i].checksum, sections[i].offset, sections[i].length);
}

void print_table_kerning(t_ftgr_truetype_loader *loader)
{
	if (!loader->kerning)
		return;
	ft_printf("Kerning:\n");
	ft_printf("	Version: %#x\n", loader->kerning->version);
	ft_printf("	Subtables count: %u\n", loader->kerning->subtables_count);
	for (U32 i = 0; i < loader->kerning->subtables_count; i++)
	{
		ft_printf("		Subtable #%u\n", i);
		ft_printf("		 Length: %u\n", loader->kerning->tables[i].length);
		ft_printf("		 Length: %u\n", loader->kerning->tables[i].tuple_index);
		ft_printf("		 Vertical: %s | Cross stream: %s | Variation: %s | Format mask: %#x\n",
			(loader->kerning->tables[i].vertical) ? "TRUE" : "FALSE",
			(loader->kerning->tables[i].cross_stream) ? "TRUE" : "FALSE",
			(loader->kerning->tables[i].variation) ? "TRUE" : "FALSE",
			loader->kerning->tables[i].format_mask
			);
	}
}

void print_table_maxp(t_ftgr_truetype_loader *loader)
{
	if (!loader->get_maxp(loader))
		return;
	ft_printf("Maxp:\n");
	ft_printf("	Version: %#x\n", loader->maxp->version);
	ft_printf("	Glyph count: %u\n", loader->maxp->glyph_count);
	ft_printf("	Points max: %u\n", loader->maxp->points_max);
	ft_printf("	Contours max: %u\n", loader->maxp->contours_max);
	ft_printf("	Component points max: %u\n", loader->maxp->component_points_max);
	ft_printf("	Component contour max: %u\n", loader->maxp->component_contour_max);
	ft_printf("	Zones max: %u\n", loader->maxp->zones_max);
	ft_printf("	Twilight zones max: %u\n", loader->maxp->twilight_zones_max);
	ft_printf("	Storage max: %u\n", loader->maxp->storage_max);
	ft_printf("	Functions def max: %u\n", loader->maxp->functions_def_max);
	ft_printf("	Instructions def max: %u\n", loader->maxp->instructions_def_max);
	ft_printf("	Stack elem max: %u\n", loader->maxp->stack_elem_max);
	ft_printf("	Instruction size max: %u\n", loader->maxp->instruction_size_max);
	ft_printf("	Components elements max: %u\n", loader->maxp->components_elements_max);
	ft_printf("	Components depth max: %u\n", loader->maxp->components_depth_max);
}

void print_truetype_loader(t_ftgr_truetype_loader *loader)
{
	loader->get_sections(loader);
	print_table_header(loader);
	print_table_head(loader);
	print_table_sections(loader);
	//print_glyph(loader->get_glyphs(loader));
	loader->get_kerning(loader);
	print_table_kerning(loader);
	loader->get_maxp(loader);
	print_table_maxp(loader);
}

void print_table_header(t_ftgr_truetype_loader *loader)
{
	t_truetype_header *header = loader->get_header(loader);
	if (!header)
		return;

	ft_printf("Header:\n");
	ft_printf("	Scaler type: %u\n", header->scaler_type);
	ft_printf("	Num tables: %u\n", header->num_tables);
	ft_printf("	Search range: %u\n", header->search_range);
	ft_printf("	Entry selector: %u\n", header->entry_selector);
	ft_printf("	Range shift: %u\n", header->range_shift);
}

void print_table_head(t_ftgr_truetype_loader *loader)
{
	t_head *head = loader->get_head(loader);
	if (!head)
		return;

	ft_printf("Head:\n");
	ft_printf("	Version: (rounded flt)%d\n", (S32)head->version);
	ft_printf("	Font revision: %f\n", head->font_revision);
	ft_printf("	Checksum adjustement: %#x\n", head->checksum_adjustement);
	ft_printf("	Magic n: %#x\n", head->magic_n);
	ft_printf("	Flags: %#x\n", head->flags);
	ft_printf("	Units per em: %u\n", head->units_per_em);
	ft_printf("	Created: %ld\n", head->created);
	ft_printf("	Modified: %ld\n", head->modified);
	ft_printf("	Xmin: %d\n", head->xmin);
	ft_printf("	Ymin: %d\n", head->ymin);
	ft_printf("	Xmax: %d\n", head->xmax);
	ft_printf("	Ymax: %d\n", head->ymax);
	ft_printf("	Mac style: %u\n", head->mac_style);
	ft_printf("	Lowest rec ppem: %u\n", head->lowest_rec_ppem);
	ft_printf("	Font direction hint: %d\n", head->font_direction_hint);
	ft_printf("	Index to loc fmt: %d\n", head->index_to_loc_fmt);
	ft_printf("	Glyph data fmt: %d\n", head->glyph_data_fmt);
}
