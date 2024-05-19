/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/19 16:35:18 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/std.h"
#include "libft/crypt.h"
#include "libft/images.h"
#include "libft/io.h"
#include "libft/btree.h"
#include "libft/compression.h"

#include <stdio.h>
#include <stdlib.h>

#undef MIN
#define MIN(x, y) (x < y ? x : y)

#undef MAX
#define MAX(x, y) (x > y ? x : y)

U8 __buffer[4096];
U8 *buffer = __buffer;
U64 buffer_alloc = 0;

U32 crc = 0;
U32 uncompressed_len = 0;

void write_gzip_header(FILE *f)
{
	char header[] = {0x1f, 0x8b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
	fwrite(header, sizeof(header), 1, f);
}

void write_gzip_buffer(FILE *f)
{
	fwrite(__buffer, buffer - __buffer, 1, f);
}

void write_gzip_footer(FILE *f)
{
	fwrite(&crc, sizeof(crc), 1, f);
	fwrite(&uncompressed_len, sizeof(U32), 1, f);
}

void append_byte(U8 b)
{
	*buffer = b;
	buffer++;
}

void append_bytes(U8 *buf, U64 len)
{
	ft_memcpy(buffer, buf, len);
	buffer += len;
}

void append_u16(U16 n)
{
	append_bytes((U8 *)&n, 2);
}

#define BLOCK_UNCOMPRESSED 0
#define BLOCK_TYPE_1 1
#define BLOCK_TYPE_2 2

void create_block(bool is_last, S32 block_type, string data, U64 data_size)
{
	U8 block_header = 0;
	block_header |= (is_last & 1);
	block_header |= ((block_type & 0x3) << 1);
	append_byte(block_header);

	switch (block_type)
	{
	case BLOCK_UNCOMPRESSED:
		U16 size = data_size;
		append_u16(size);
		append_u16(~size);

		for (int i = 0; i < size; i++)
			append_byte(data[i]);
		break;
	default:
		return;
	}

	crc = ft_crc32_u(data, data_size, crc);
	uncompressed_len += data_size;
}

int main2(int argc, char **argv)
{

	FILE *f = fopen("/home/reclaire/Desktop/libftgr/gzip.gz", "wb+");
	if (!f)
	{
		printf("Couldn't open file\n");
		return 1;
	}

	write_gzip_header(f);

	string data = "test";
	create_block(FALSE, BLOCK_UNCOMPRESSED, data, ft_strlen(data));
	create_block(TRUE, BLOCK_UNCOMPRESSED, data, ft_strlen(data));

	write_gzip_buffer(f);
	write_gzip_footer(f);

	fclose(f);
}

int main()
{
	// Huffman coding
	//string data = "It must be easy to commit crimes as a snake because you don't have to worry about leaving fingerprints.";
	string data = "aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff";
	U64 len = ft_strlen(data);

/*
	t_huffman_node **nodes;
	U64 nodes_count;
	t_huffman_node *tree = ft_create_huffman_tree(data, len, &nodes, &nodes_count);

	t_huffman_node *node = ft_get_huffman_node('g', nodes, nodes_count);
	if (node)
		ft_print_huffman_node(node, TRUE);
	else
		ft_printf("nul\n");

	ft_print_huffman_tree(tree);
	ft_free_huffman_tree(tree);
*/

	ft_lzss(NULL, 0, 0, 0);


}
