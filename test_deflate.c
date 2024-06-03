/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_deflate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/06/03 18:52:06 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/std.h"
#include "libft/crypt.h"
#include "libft/images.h"
#include "libft/io.h"
#include "libft/btree.h"
#include "libft/compression/deflate.h"
#include "libft/compression/gzip.h"
#include "libft/bitstreams.h"
#include "libft/limits.h"

#ifndef __USE_MISC
#define __USE_MISC
#endif
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

U16 codes[] = {
	// 8 bits (0 - 143)
	12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252, 2, 130, 66, 194, 34,
	162, 98, 226, 18, 146, 82, 210, 50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26,
	154, 90, 218, 58, 186, 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54,
	182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254, 1,
	129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 177, 113, 241, 9, 137, 73, 201, 41,
	169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249, 5, 133, 69, 197, 37, 165, 101, 229, 21,
	149, 85, 213, 53, 181, 117, 245, 13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61,
	189, 125, 253,

	// 9 bits (144 - 255)
	19, 275, 147, 403, 83, 339, 211, 467, 51, 307, 179, 435, 115, 371, 243, 499, 11, 267, 139, 395, 75,
	331, 203, 459, 43, 299, 171, 427, 107, 363, 235, 491, 27, 283, 155, 411, 91, 347, 219, 475, 59,
	315, 187, 443, 123, 379, 251, 507, 7, 263, 135, 391, 71, 327, 199, 455, 39, 295, 167, 423, 103,
	359, 231, 487, 23, 279, 151, 407, 87, 343, 215, 471, 55, 311, 183, 439, 119, 375, 247, 503, 15,
	271, 143, 399, 79, 335, 207, 463, 47, 303, 175, 431, 111, 367, 239, 495, 31, 287, 159, 415, 95,
	351, 223, 479, 63, 319, 191, 447, 127, 383, 255, 511,

	// 7 bits (256 - 279)
	0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 40, 104, 24, 88, 56, 120, 4, 68, 36, 100, 20, 84, 52, 116,

	// 8 bits (280 - 287)
	3, 131, 67, 195, 35, 163, 99, 227

	// + 2 codes fantomes (288, 289)
};

static void write_code(U16 code_index, t_bitstream *stream)
{
	*(U16 *)(stream->buffer + stream->byte_offset) |= codes[code_index] << stream->bit_offset;

	if (code_index <= 143)
		stream->bit_offset += 8;
	else if (code_index <= 255)
		stream->bit_offset += 9;
	else if (code_index <= 279)
		stream->bit_offset += 7;
	else
		stream->bit_offset += 8;

	stream->byte_offset += stream->bit_offset / 8;
	stream->bit_offset %= 8;
}

static bool write_gzip_header(file fd)
{
	t_gzip_header header = {
		.is_text = FALSE,
		.header_crc16 = TRUE,
		.mtime = 0,
		.extra_flags = FT_GZIP_XFLAG_NONE,
		.os = FT_GZIP_OS_UNIX,

		.extra_data_len = 0,
		.extra_data = NULL,
	
		.filename = "test",
		.comment = "commentaire",

		.state = 0,
	};

	U8 buff[256];
	while (header.state != 1)
	{
		U64 to_write = ft_gzip_write_header(buff, sizeof(buff), &header);
		if (ft_errno != FT_OK)
		{
			printf("Error while writing gzip header !\n");
			printf("Error: %s | State: %d\n", ft_strerror(ft_errno), header.state);
			return FALSE;
		}

		for (int i = 0; i < to_write; i++)
		{
			printf("%#x ", buff[i]);
		}
		printf("\n");

		U64 written = 0;
		while (written < to_write)
		{
			written += ft_fwrite(fd, buff + written, to_write - written);
			if (ft_errno != FT_OK)
			{
				printf("Error while writing to file !\n");
				printf("Error: %s\n", ft_strerror(ft_errno));
				if (ft_errno == FT_ESYSCALL)
					printf("  -> %s\n", strerror(errno));
				return FALSE;
			}
		}
	}
	return TRUE;
}

static void write_gzip_footer(file fd, U32 crc, U32 size)
{
	ft_fwrite(fd, (char *)&crc, sizeof(U32));
	ft_fwrite(fd, (char *)&size, sizeof(U32));
}

void fill_pseudo_random(U8 *buf, U64 size)
{
	U64 i = 0;
	while (i < size - 1)
	{
		U64 n = (U64)(ft_frand(i) * size / 3);
		U8 b = (U8)(ft_frand(i) * (126 - 32) + 32);

		n = n+i > size ? (size - i) : n;
		ft_memset(buf + i, b, n);
		i += n;
	}
}

void fill_random(U8 *buf, U64 size)
{
	for (U64 i = 0; i < size; i++)
		buf[i] = (U8)(ft_frand(i) * (126 - 32) + 32);
}

U32 mk_offset(int bit_offset, t_bitstream *stream, file cmp_fd, U64 *len)
{
	U32 crc = 0;
	U8 buf[115] = {[0 ... 114] = 'a'};

	ft_bstrm_write_bit(stream, 0);

	ft_bstrm_write_bit(stream, 1);
	ft_bstrm_write_bit(stream, 0);

#define write_char                     \
	{                                  \
		write_code('a', stream);       \
		ft_fwrite(cmp_fd, "a", 1);     \
		crc = ft_crc32_u("a", 1, crc); \
		(*len)++;                      \
	}
#define offset_bit_1                             \
	{                                            \
		write_code(280, stream);                 \
                                                 \
		/* 5 extra bits */                       \
		ft_bstrm_write_bit(stream, 0);           \
		ft_bstrm_write_bit(stream, 0);           \
		ft_bstrm_write_bit(stream, 0);           \
		ft_bstrm_write_bit(stream, 0);           \
                                                 \
		/* distance code */                      \
		ft_bstrm_write_bit(stream, 0);           \
		ft_bstrm_write_bit(stream, 0);           \
		ft_bstrm_write_bit(stream, 0);           \
		ft_bstrm_write_bit(stream, 0);           \
		ft_bstrm_write_bit(stream, 0);           \
                                                 \
		ft_fwrite(cmp_fd, buf, sizeof(buf));     \
		crc = ft_crc32_u(buf, sizeof(buf), crc); \
		(*len) += 115;                           \
	}

	write_char;
	write_char;
	write_char;

	for (int i = 0; i < bit_offset; i++)
		offset_bit_1;

	write_code(256, stream);

	return crc;
}

void test_deflate(int bit_offset)
{
	U8 buffer[10000] = {0};
	U8 data[1024] = {0};
	//fill_random(data, sizeof(data));
	fill_pseudo_random(data, sizeof(data));

	file cmp_fd = ft_fopen("tests_gzip/test_gzip.txt", "w+");
	file out_fd = ft_fopen("tests_gzip/gzip.gz", "w+");

	t_deflate_stream stream = ft_deflate_init_stream(data, sizeof(data), buffer, sizeof(buffer));

	U64 len = 0;
	if (bit_offset != 0)
	{
		t_bitstream test = FT_BITSTREAM_INIT(buffer, sizeof(buffer));
		stream.crc32 = mk_offset(bit_offset, &test, cmp_fd, &len);
		stream.s.bit_offset = test.bit_offset;
		stream.out_used = test.byte_offset;
	}

	U64 total_used = 0;
	if (!write_gzip_header(out_fd))
		return;
	if (!ft_deflate_next_block(&stream, 2048, 0, 0))
	{
		printf("Error: %d:%s\n", ft_errno, ft_strerror(ft_errno));
		exit(1);
	}
	ft_fwrite(cmp_fd, data, stream.in_used);
	ft_fwrite(out_fd, buffer, stream.out_used);
	total_used += stream.in_used;

	ft_bzero(buffer, sizeof(buffer));
	U32 crc_sv = stream.crc32;
	stream = ft_deflate_init_stream(data, sizeof(data), buffer, sizeof(buffer));
	stream.crc32 = crc_sv;
	if (!ft_deflate_next_block(&stream, 2048, 1, 1))
	{
		printf("Error: %d:%s\n", ft_errno, ft_strerror(ft_errno));
		exit(1);
	}
	ft_deflate_end(&stream);
	ft_fwrite(cmp_fd, data, stream.in_used);
	total_used += stream.in_used;

	//ft_inflate(buffer, stream.s.out_i);

	ft_fwrite(out_fd, buffer, stream.out_used);

	U64 tmp;
	ft_gzip_write_footer((U8*)&tmp, stream.crc32, len + total_used);
	ft_fwrite(out_fd, (U8*)&tmp, 4);

	ft_fclose(cmp_fd);
	ft_fclose(out_fd);
}

void speedtest()
{
	U8 buffer[10000] = {0};
	U8 data[4096];
	fill_pseudo_random(data, sizeof(data));

	t_deflate_stream stream = ft_deflate_init_stream(data, sizeof(data), buffer, sizeof(buffer));
	if (!ft_deflate_next_block(&stream, 2048, 1, 1))
	{
		printf("Error: %d:%s\n", ft_errno, ft_strerror(ft_errno));
		exit(1);
	}
}

int main(int argc, char **argv)
{
	test_deflate(argc > 1 ? ft_atoi(argv[1]) : 0);

	//for (int i = 0; i < 1000; i++)
	//	speedtest();

	// ~1.0
}
