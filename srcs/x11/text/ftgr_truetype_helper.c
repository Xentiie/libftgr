/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_truetype_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:55:22 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/11 03:25:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftgr_truetype.h"

void print_glyph(t_glyph *glyph)
{
	printf("Glyph:\n");
	printf("	Coords min: (%d %d)\n", glyph->points_min.x, glyph->points_min.y);
	printf("	Coords max: (%d %d)\n", glyph->points_max.x, glyph->points_max.y);
	printf("	Contour end indices length: %u\n", glyph->contour_end_indices_len);

	printf("	Contour end indices: ");
	for (U16 i = 0; i < glyph->contour_end_indices_len; i++)
		printf("%u ", glyph->contour_end_indices[i]);
	printf("\n");

	printf("	Coords length: %lu\n", glyph->points_len);
	printf("	Coords:\n	");
	U16 j = 0;
	for (U64 i = 0; i < glyph->points_len; i++)
	{
		printf("(%d %d) ", glyph->points[i].x, glyph->points[i].y);
		if (j < glyph->contour_end_indices_len && i == glyph->contour_end_indices[j])
		{
			printf("\n	");
			j++;
		}
	}
	printf("\n");
}

void print_truetype_header(t_ftgr_truetype_loader *loader)
{
	t_truetype_header *header = loader->get_header(loader);
	if (!header)
		return;

	printf("scaler_type: %#x\n", header->scaler_type);
	printf("num_tables: %u\n", header->num_tables);
	printf("search_range: %u\n", header->search_range);
	printf("entry_selector: %u\n", header->entry_selector);
	printf("range_shift: %u\n", header->range_shift);
}

void print_table_sections(t_ftgr_truetype_loader *loader)
{
	t_truetype_header *header = loader->get_header(loader);
	t_table_entry *sections = loader->get_sections(loader);
	if (!header || !sections)
		return;
	
	printf("TrueType table:\n");
	for (U16 i = 0; i < header->num_tables; i++)
		printf("	'%.4s': (checksum:%#x) (offset:%u) (length:%u)\n", &sections[i].tag, sections[i].checksum, sections[i].offset, sections[i].length);
}

void print_table_kerning(t_ftgr_truetype_loader *loader)
{
	if (!loader->kerning)
		return;
	printf("Kerning:\n");
	printf("	Version: %#x\n", loader->kerning->version);
	printf("	Subtables count: %u\n", loader->kerning->subtables_count);
	for (U32 i = 0; i < loader->kerning->subtables_count; i++)
	{
		printf("		Subtable #%u\n", i);
		printf("		 Length: %u\n", loader->kerning->tables[i].length);
		printf("		 Length: %u\n", loader->kerning->tables[i].tuple_index);
		printf("		 Vertical: %s | Cross stream: %s | Variation: %s | Format mask: %#x\n",
			(loader->kerning->tables[i].vertical) ? "TRUE" : "FALSE",
			(loader->kerning->tables[i].cross_stream) ? "TRUE" : "FALSE",
			(loader->kerning->tables[i].variation) ? "TRUE" : "FALSE",
			loader->kerning->tables[i].format_mask
			);
	}
}

void print_table_maxp(t_ftgr_truetype_loader *loader)
{
	t_max_profile *maxp = loader->get_maxp(loader);
	if (!loader->maxp)
		return;
	printf("Maxp:\n");
	printf("	Version: %#x\n", loader->maxp->version);
	printf("	Glyph count: %u\n", loader->maxp->glyph_count);
	printf("	Points max: %u\n", loader->maxp->points_max);
	printf("	Contours max: %u\n", loader->maxp->contours_max);
	printf("	Component points max: %u\n", loader->maxp->component_points_max);
	printf("	Component contour max: %u\n", loader->maxp->component_contour_max);
	printf("	Zones max: %u\n", loader->maxp->zones_max);
	printf("	Twilight zones max: %u\n", loader->maxp->twilight_zones_max);
	printf("	Storage max: %u\n", loader->maxp->storage_max);
	printf("	Functions def max: %u\n", loader->maxp->functions_def_max);
	printf("	Instructions def max: %u\n", loader->maxp->instructions_def_max);
	printf("	Stack elem max: %u\n", loader->maxp->stack_elem_max);
	printf("	Instruction size max: %u\n", loader->maxp->instruction_size_max);
	printf("	Components elements max: %u\n", loader->maxp->components_elements_max);
	printf("	Components depth max: %u\n", loader->maxp->components_depth_max);
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

	printf("Header:\n");
	printf("	Scaler type: %u\n", header->scaler_type);
	printf("	Num tables: %u\n", header->num_tables);
	printf("	Search range: %u\n", header->search_range);
	printf("	Entry selector: %u\n", header->entry_selector);
	printf("	Range shift: %u\n", header->range_shift);
}

void print_table_head(t_ftgr_truetype_loader *loader)
{
	t_head *head = loader->get_head(loader);
	if (!head)
		return;

	printf("Head:\n");
	printf("	Version: %f\n", head->version);
	printf("	Font revision: %f\n", head->font_revision);
	printf("	Checksum adjustement: %#x\n", head->checksum_adjustement);
	printf("	Magic n: %#x\n", head->magic_n);
	printf("	Flags: %#x\n", head->flags);
	printf("	Units per em: %u\n", head->units_per_em);
	printf("	Created: %ld\n", head->created);
	printf("	Modified: %ld\n", head->modified);
	printf("	Xmin: %d\n", head->xmin);
	printf("	Ymin: %d\n", head->ymin);
	printf("	Xmax: %d\n", head->xmax);
	printf("	Ymax: %d\n", head->ymax);
	printf("	Mac style: %u\n", head->mac_style);
	printf("	Lowest rec ppem: %u\n", head->lowest_rec_ppem);
	printf("	Font direction hint: %d\n", head->font_direction_hint);
	printf("	Index to loc fmt: %d\n", head->index_to_loc_fmt);
	printf("	Glyph data fmt: %d\n", head->glyph_data_fmt);
}
