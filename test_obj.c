/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:57:10 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/07 20:16:35 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/io.h"
#include "libftgr.h"
#include <stdio.h>
#include <stdlib.h>

static const_string valid_tags[] = {
	"vp",
	"deg",
	"bmat",
	"step",
	"cstype",
	"p",
	"l",
	"curv",
	"curv2 ",
	"surf",
	"parm",
	"trim",
	"hole",
	"scrv",
	"sp",
	"end",
	"con",
	"g",
	"s",
	"mg",
	"o",
	"bevel",
	"c_interp",
	"d_interp",
	"lod",
	"shadow_obj",
	"trace_obj",
	"ctech",
	"stech",
};

#define CHK_END()                        \
	do                                   \
	{                                    \
		if (UNLIKELY(buffer[i] == '\0')) \
			goto invalid_wavefront;      \
	} while (0)
#define SKIP_WHITESPACES()                            \
	do                                                \
	{                                                 \
		while (buffer[i] == ' ' || buffer[i] == '\t') \
			i++;                                      \
		CHK_END();                                    \
	} while (0)

/*
Verifie si le nombre est bien formé. La longueur du nombre est stocké dans `k`
*/
#define ASSERT_FLOAT()                                                  \
	do                                                                  \
	{                                                                   \
		k = i;                                                          \
		if (buffer[k] == '-')                                           \
			k++;                                                        \
		if (!ft_isdigit(buffer[k++]))                                   \
			goto invalid_wavefront;                                     \
		while (ft_isdigit(buffer[k]))                                   \
			k++;                                                        \
		if (buffer[k] == '.')                                           \
		{                                                               \
			k++;                                                        \
			if (!ft_isdigit(buffer[k++]))                               \
				goto invalid_wavefront;                                 \
			while (ft_isdigit(buffer[k]))                               \
				k++;                                                    \
		}                                                               \
		if (buffer[k] != ' ' && buffer[k] != '\t' && buffer[k] != '\0') \
			goto invalid_wavefront;                                     \
	} while (0)

typedef struct s_mesh
{
	U8 *vertices;
	U8 *indices;

	U8 vert_bytes;
	U8 ind_bytes;
	U64 vertices_n;
	U64 indices_n;
} t_mesh;

#define WAVEFRONT_VERT_SIZE_INT_1 1
#define WAVEFRONT_VERT_SIZE_INT_2 2
#define WAVEFRONT_VERT_SIZE_INT_4 4
#define WAVEFRONT_VERT_SIZE_INT_8 8
#define WAVEFRONT_VERT_SIZE_INT_AUTO 9
#define WAVEFRONT_VERT_SIZE_FLT_4 0x40
#define WAVEFRONT_VERT_SIZE_FLT_8 0x80
#define WAVEFRONT_VERT_SIZE_FLT_AUTO 0x90

typedef enum
{
	AUTO,
	FLT32,
	FLT64,
	INT8,
	INT16,
	INT32,
	INT64,

} e_mesh_vi_size;

static const 


U8 highest_one_bit(U64 n)
{
	U8 l;
	while (n >>= 1)
		++l;
	return l;
}

static void conv_Un_Un();

static void conv_U8_U16();
static void conv_U8_U32();
static void conv_U8_U64();

static void conv_U16_U8();
static void conv_U16_U32();
static void conv_U16_U64();

static void conv_U32_U8();
static void conv_U32_U16();
static void conv_U32_U64();

static void conv_U32_U8();
static void conv_U32_U16();
static void conv_U64_U32();

static void conv_U8_F32();
static void conv_U8_F64();
static void conv_U16_F32();
static void conv_U16_F64();
static void conv_U32_F32();
static void conv_U32_F64();
static void conv_U64_F32();
static void conv_U64_F64();

t_mesh *parse_wavefront(const_string *path, e_mesh_vi_size *v_size, e_mesh_vi_size *i_size)
{
	static const e_mesh_vi_size _default_auto = AUTO;

	char buffer[2048];
	file fd;
	U64 indices_alloc, vertices_alloc;
	U8 *indices, *vertices;
	U8 indices_size, vertices_size;
	bool indices_auto, vertices_auto;
	bool indices_flt, vertices_flt;

	S64 ret, rd, i, j, k, vert, ind;

	indices_alloc = 32;
	vertices_alloc = 32;
	vert = 0;
	ind = 0;
	indices = NULL;
	vertices = NULL;

	if (i_size == NULL)
		i_size = (e_mesh_vi_size *)&_default_auto;
	if (v_size == NULL)
		v_size = (e_mesh_vi_size *)&_default_auto;

	indices_auto = *i_size == AUTO;
	indices_flt = *i_size == FLT32 || *i_size == FLT64;
	indices_size = (indices_auto ? INT8 : (indices_flt ? ft_pow(1, *i_size - 1) : ft_pow(1, *i_size - 3)));

	vertices_auto = *v_size == AUTO;
	vertices_flt = *v_size == FLT32 || *v_size == FLT64;
	vertices_size = (vertices_auto ? INT8 : (vertices_flt ? ft_pow(1, *v_size - 1) : ft_pow(1, *v_size - 3)));

	if (UNLIKELY((indices = malloc(indices_size * indices_alloc)) == NULL) ||
		UNLIKELY((vertices = malloc(vertices_size * vertices_alloc)) == NULL) ||
		UNLIKELY((fd = ft_fopen(path, "r")) == -1))
	{
		free(indices);
		free(vertices);
		return NULL;
	}

	rd = 0;
	do
	{
		while (rd < sizeof(buffer))
		{
			ret = ft_fread(fd, buffer, sizeof(buffer) - rd);
			if (UNLIKELY(ret < 0))
				goto invalid_wavefront;
			if (ret == 0)
				break;
			rd += ret;
		}

		i = 0;
		while ((i < rd) && buffer[i] != '\0' && buffer[i] != '\n')
			i++;
		buffer[i] = '\0';

		i = 0;
		SKIP_WHITESPACES();

		/*
		Le plus commun c'est 'v', 'vt', 'vn', et 'f'.
		Le switch est sur les 2 premiers char, donc pour 'v' et 'f' on inclut
		l'espace (ou le \t)
		*/
		switch (*(U16 *)(buffer + i))
		{
			/* On switch sur ( (U8)char1 | ((U8)char2) << 8 ) */
		case ('v' | (' ' << 8)):
		case ('v' | ('\t' << 8)):
			i += 2; // v


			for (j = 0; j < 3; j++)
			{

				SKIP_WHITESPACES();
				ASSERT_FLOAT();

				F32 f = ft_atof(buffer + i);
				if (vertices_auto && !vertices_flt && ft_frac(f) != 0)
				{
					vertices_flt = TRUE;
					
					U8 new_vertices_size = (sizeof(F32) > vertices_size) ? sizeof(F32) - vertices_size : vertices_size;
					U64 growth_factor = UNLIKELY(vert + 3 >= vertices_alloc) ? 3 : 1;

					const static void (*conv_funcs[])(U8 *, U8*, U64 n) = {
						NULL
					};

					void (*conv)(U8 *old, U8 *new);

					U8 *new = malloc(new_vertices_size * vertices_alloc * growth_factor);
					if (new == NULL)
						goto invalid_wavefront;
					for (S64 l = 0; l < vert; l++)
					{
						for (U8 m = 0; m < vertices_size)
						vertices[m]
					}
				}

				i += k;
			}

			if (UNLIKELY(vert + 3 >= vertices_alloc))
			{
				U8 *new = malloc(vertices_size * vertices_alloc * 3);
				if (new == NULL)
					goto invalid_wavefront;
				ft_memcpy(new, vertices, vertices_size * vertices_alloc);
				free(vertices);
				vertices = new;
				vertices_alloc *= 3;
			}

			break;

		case ('f' | (' ' << 8)):
		case ('f' | ('\t' << 8)):
			break;

		case ('v' | ('t' << 8)):
			i += 2; // vt

			if (UNLIKELY(i >= rd) || (UNLIKELY(buffer[i] != ' ' || buffer[i] != '\t')))
				goto invalid_wavefront;

			while ((i < rd) && (buffer[i] == ' ' || buffer[i] == '\t'))
				i++;
			if (UNLIKELY(i >= rd))
				goto invalid_wavefront;

			break;

		case ('v' | ('n' << 8)):
			break;

		default:
			/* Tout le reste (qu'on ne gere pas mais on verifie quand meme la validité) */
			for (j = 0; j < sizeof(valid_tags) / sizeof(valid_tags[0]); j++)
			{
				U64 tag_len = ft_strlen(valid_tags[j]);
				// TODO: fix
				if (!ft_strncmp(valid_tags[j], (buffer + i), UNLIKELY(rd < tag_len) ? rd : tag_len))
				{
					if (buffer[i + tag_len] == ' ' || buffer[i + tag_len] == '\t')
						goto valid_tag;
				}
			}
			/* INVALID */
			break;
		valid_tag:
			break;
		}

		rd -= i;
		ft_memcpy(buffer, buffer + i, rd);
	} while (rd != 0);

	return NULL;

invalid_wavefront:
	free(indices);
	free(vertices);
	ft_fclose(fd);
	return NULL;
}

int main(S32 argc, const_string *argv)
{
	if (argc < 2)
	{
		printf("No objects specified\n");
		return 1;
	}

	t_ftgr_ctx *ctx = ftgr_create_ctx();
	t_ftgr_win *win = ftgr_new_window(ctx, ivec2(400, 400), "3D");

	t_ftgr_img *display = ftgr_new_img(ctx, ivec2(400, 400));

	t_mesh *mesh = parse_wavefront(argv[1]);

	while (ftgr_poll(ctx))
	{
	}
}
