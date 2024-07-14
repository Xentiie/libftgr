import re

txt = """
	head->version = reverse32(head->version);
	head->font_revision = reverse32(head->font_revision);
	head->checksum_adjustement = reverse32(head->checksum_adjustement);
	head->magic_n = reverse32(head->magic_n);
	head->flags = reverse16(head->flags);
	head->units_per_em = reverse16(head->units_per_em);
	head->created = reverse64(head->created);
	head->modified = reverse64(head->modified);
	head->xmin = reverse16(head->xmin);
	head->ymin = reverse16(head->ymin);
	head->xmax = reverse16(head->xmax);
	head->ymax = reverse16(head->ymax);
	head->mac_style = reverse16(head->mac_style);
	head->lowest_rec_ppem = reverse16(head->lowest_rec_ppem);
	head->font_direction_hint = reverse16(head->font_direction_hint);
	head->index_to_loc_fmt = reverse16(head->index_to_loc_fmt);
	head->glyph_data_fmt = reverse16(head->glyph_data_fmt);
"""

for m in re.findall(r'\thead->([\w]+) = reverse([0-9][0-9]).*', txt):
    print(f'    printf("{m[0].replace("_", " ").capitalize()}: {f"%lu" if m[1] == "64" else f"%u"}", head->{m[0]});')
