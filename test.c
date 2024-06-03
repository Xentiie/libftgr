/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 02:10:39 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/02 18:54:55 by reclaire         ###   ########.fr       */
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

#ifndef __USE_MISC
#define __USE_MISC
#endif
#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	U64 size = 0;
	U8 *data;

	{
		string path = argc > 1 ? argv[1] : "./tests_gzip/gzip.gz";

		struct stat st;
		stat(path, &st);
		data = malloc(sizeof(U8) * st.st_size);

		file fd = ft_fopen(path, "r");
		U64 rd;
		while ((rd = ft_fread(fd, data + size, 4096)) > 0)
		{
			if (rd == -1)
			{
				printf("%s\n", strerror(errno));
				return 1;
			}
			size += rd;
		}
		ft_fclose(fd);
	}
	data += 10;
	size -= 10;

	U8 buffer[10000];
	t_deflate_stream stream = ft_deflate_init_stream(data, size, buffer, sizeof(buffer));
	S32 err = 0;
	while (ft_inflate_next_block(&stream, &err))
	{	
	}
	if (err)
		printf("Error: %d:%s\n", err, ft_inflate_strerror(err));

	printf("Total size: %lu\n", stream.out_used);
	printf("CRC32: %#x\n", stream.crc32);

	free(data - 10);
}
