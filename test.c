/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/22 02:41:20 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/std.h"
#include "libft/crypt.h"
#include "libft/images.h"
#include "libft/io.h"
#include "libft/btree.h"
#include "libft/compression.h"
#include "libft/bitstreams.h"
#include "libft/limits.h"
#include "libft/ht.h"

#define __USE_MISC
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

void test_gzip()
{
	U8 buffer[4096 * 4] = {0};
	file fd = ft_fopen("./test.c", "r");
	S64 s = ft_fread(fd, buffer, sizeof(buffer));
	if (s < 0)
		exit(1);
	ft_fclose(fd);

	fd = ft_fopen("./gzstat.py", "r");
	if (s < sizeof(buffer))
		s += ft_fread(fd, buffer + s, sizeof(buffer) - s);
	ft_fclose(fd);

	
	ft_make_gzip(buffer, s, "/home/reclaire/Desktop/libftgr/test_gzip.gz");

}

void test_compression_lzss()
{
	U64 buffer_init_size = 32768 * 8;
	U8 *buffer = malloc(sizeof(U8) * buffer_init_size);

	DIR *d = opendir("./");
	U64 s = 0;
	struct dirent *ent = readdir(d);
	while (s < buffer_init_size)
	{
		if (!ent)
		{
			printf("Loaded whole dir :)\n");
			break;
		}
		if (ent->d_type != DT_REG)
		{
			ent = readdir(d);
			continue;
		}
		printf("Reading file: %s\n", ent->d_name);

		file fd = ft_fopen(ent->d_name, "r");
		U64 bytes_read;
		while ((bytes_read = ft_fread(fd, buffer + s, buffer_init_size - s)) > 0)
			s += bytes_read;
		ft_fclose(fd);
		ent = readdir(d);
		printf("Filled %lu/%lu bytes of data\n", s, buffer_init_size);
	}

	U8 *compressed = malloc(sizeof(U8) * buffer_init_size);
	t_bitstream stream_in = FT_BITSTREAM_INIT(compressed, buffer_init_size);
	ft_lzss_compress(buffer, s, &stream_in, 32768, 1024);

	printf("Compression: %ld/%lu: %d%%\n", stream_in.bits_read, s * 8, 100 - (stream_in.bits_read * 100 / (s * 8)));

	U8 *decompressed = malloc(sizeof(U8) * buffer_init_size);
	U64 n = ft_lzss_decompress(&stream_in, decompressed, buffer_init_size);
	free(compressed);

	if (!n)
		printf("ERROR\n");

	printf(ft_memcmp(buffer, decompressed, s) == 0 ? "YES\n" : "NO\n");
	free(decompressed);
	free(buffer);
}

void test_huffman_coding()
{
	// Huffman coding
	// string data = "It must be easy to commit crimes as a snake because you don't have to worry about leaving fingerprints.";
	string data = "aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff";
	U64 len = ft_strlen(data);

	t_huffman_node **nodes;
	U64 nodes_count;
	t_huffman_node *tree = ft_create_huffman_tree(data, len, &nodes, &nodes_count);

	t_huffman_node *node = ft_get_huffman_node('f', nodes, nodes_count);
	if (node)
		ft_print_huffman_node(node, TRUE);
	else
		ft_printf("nul\n");

	ft_print_huffman_tree(tree);
	ft_free_huffman_tree(tree);
}

U64 hash_int(void *elem)
{
	return (U64)*(int*)elem;
}

void test_ht()
{
	t_ht *ht = ft_new_hash_table(sizeof(int), 10, hash_int);
	if (!ht)
	{
		printf("error: %s\n", ft_strerror(ft_errno));
		return;
	}
	
	ft_hash_insert(ht, &(int){10});
	if (ft_errno != FT_OK)
	{
		printf("error: %s\n", ft_strerror(ft_errno));
		return;
	}

	ft_hash_get()

	ft_hash_free(ht);
}

int main()
{
	//test_huffman_coding();
	//test_compression_lzss();
	test_ht();
}

