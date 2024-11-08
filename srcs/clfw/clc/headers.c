/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:13:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 05:17:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/strings.h"
#include "libft/path.h"
#include "libft/io.h"

bool _clc_add_header(ProgramBuilder builder, const_string header_name, cl_program header_prog)
{
	ASSERT(builder != NULL, -1);
	ASSERT(builder->headers_names != NULL, -1);
	ASSERT(header_name != NULL, -1);
	ASSERT(header_prog != NULL, -1);

	clc_debug("adding header '%s'\n", header_name);

	{ /* grow headers array */
		string *new_names = NULL;
		cl_program *new_programs = NULL;
		if (builder->headers_n >= builder->headers_alloc)
		{
			clc_debug("array growth: builder->headers_names/builder->headers_programs (%llu -> %llu)\n", (LU64)builder->headers_alloc, (LU64)(builder->headers_alloc * 2));
			if (UNLIKELY(
					(new_names = malloc(sizeof(string) * builder->headers_alloc * 2)) == NULL ||
					(new_programs = malloc(sizeof(cl_program) * builder->headers_alloc * 2)) == NULL))
			{
				free(new_names);
				free(new_programs);
				clc_error("couldn't grow headers array: out of memory\n");
				return FALSE;
			}
			ft_memcpy(new_names, builder->headers_names, sizeof(string) * builder->headers_n);
			ft_memcpy(new_programs, builder->headers_programs, sizeof(cl_program) * builder->headers_n);

			free(builder->headers_names);
			free(builder->headers_programs);
			builder->headers_names = new_names;
			builder->headers_programs = new_programs;
		}
	}

	clfw_retain_program(header_prog);
	builder->headers_programs[builder->headers_n] = header_prog;
	builder->headers_names[builder->headers_n] = (string)header_name;
	builder->headers_n++;

	return TRUE;
}

bool _clc_include_header_src(ProgramBuilder builder, const_string header_name, const_string src, U64 len)
{
	cl_program header_prog;

	if (UNLIKELY((header_prog = clfw_create_program_with_source(builder->device->ctx, 1, &src, &len)) == NULL))
		return FALSE;

	if (!_clc_add_header(builder, header_name, header_prog))
	{
		return FALSE;
		clfw_release_program(header_prog);
	}
	return TRUE;
}

#if 0
bool clc_include_header(ProgramBuilder builder, const_string path)
{
	S64 ret;
	char st_buffer[16384];
	string str;
	U64 rd;

	ASSERT(builder != NULL, FALSE)
	ASSERT(builder->device != NULL, FALSE);
	ASSERT(path != NULL, FALSE)

	clc_debug("read header %s\n", path);
	{ /* read file */
		file fd;
		U64 alloc;

		if (UNLIKELY((fd = ft_fopen(path, "r")) == (file)-1))
		{
			clc_error("couldn't ingest source file '%s': %s\n", path, ft_strerror2(ft_errno));
			return FALSE;
		}

		rd = 0;
		str = st_buffer;
		alloc = sizeof(st_buffer);

		while ((ret = ft_fread(fd, str + rd, (alloc - 1) - rd)) > 0)
		{
			rd += ret;
			if (rd == (alloc - 1)) /* grow buffer */
			{
				string new = malloc(sizeof(char) * alloc * 2);
				if (new == NULL)
				{
					if (str != st_buffer)
						free(str);
					ft_fclose(fd);
					clc_error("couldn't ingest source file '%s': out of memory\n", path);
					return FALSE;
				}
				ft_strlcpy(new, str, rd);
				if (str != st_buffer)
					free(str);
				str = new;
				alloc *= 2;
			}
		}
		str[rd] = '\0';

		ft_fclose(fd);
		if (ret < 0)
		{
			if (str != st_buffer)
				free(str);
			clc_error("couldn't ingest source file '%s': %s\n", path, ft_strerror2(ft_errno));
			return FALSE;
		}
	}

	cl_program header_prog = clfw_create_program_with_source(builder->device->ctx, 1, (const_string *)&str, &rd);

	if (str != st_buffer)
		free(str);

	string header_name = ft_path_filename(path);
	if (header_prog == NULL || header_name == NULL)
	{
		free(header_name);
		clc_error("couldn't include header '%s'\n", path);
		return FALSE;
	}

	ret = _clc_add_header(builder, header_name, header_prog);
	if (ret < 1)
	{
		free(header_name);
		clfw_release_program(header_prog);
		if (ret == -1)
			return FALSE;
	}

	return TRUE;
}
#endif

bool clc_has_header(ProgramBuilder builder, const_string header_name)
{
	for (U64 i = 0; i < builder->headers_n; i++)
	{
		if (!ft_strcmp(builder->headers_names[i], header_name))
			return TRUE;
	}
	return FALSE;
}

cl_program clc_header_get(ProgramBuilder builder, const_string header_name)
{
	for (U64 i = 0; i < builder->headers_n; i++)
	{
		if (!ft_strcmp(header_name, builder->headers_names[i]))
			return builder->headers_programs[i];
	}
	return NULL;
}

bool clc_include_header(ProgramBuilder builder, const_string path)
{
	string str;
	U64 len;

	ASSERT(builder != NULL, FALSE)
	ASSERT(builder->device != NULL, FALSE);
	ASSERT(path != NULL, FALSE)

	string header_name = ft_path_filename(path);
	if (header_name == NULL)
	{
		clc_error("couldn't include header '%s': out of memory\n", path);
		return FALSE;
	}

	if (clc_has_header(builder, header_name))
		return TRUE;

	clc_debug("read header %s\n", path);
	{ /* read file */
		file fd;

		if (UNLIKELY((fd = ft_fopen(path, "r")) == (file)-1))
		{
			clc_error("couldn't ingest source file '%s': %s\n", path, ft_strerror2(ft_errno));
			return FALSE;
		}

		if (UNLIKELY((str = (string)ft_readfile(fd, &len)) == NULL))
		{
			clc_error("couldn't ingest source file '%s': %s\n", path, ft_strerror2(ft_errno));
			return FALSE;
		}

		ft_fclose(fd);
	}

	return _clc_include_header_src(builder, header_name, str, len);
}

bool clc_include_header_src(ProgramBuilder builder, const_string header_name, const_string src)
{
	S32 ret;
	cl_program header_prog;
	const_string ptr;
	U64 len;

	if (UNLIKELY((ptr = ft_strdup_l(header_name, &len)) == NULL))
		return FALSE;
	if (UNLIKELY((header_prog = clfw_create_program_with_source(builder->device->ctx, 1, &src, &len)) == NULL))
	{
		free((void *)ptr);
		return FALSE;
	}

	ret = _clc_add_header(builder, ptr, header_prog);
	if (ret < 1)
	{
		clfw_release_program(header_prog);
		if (ret == -1)
			return FALSE;
	}
	return TRUE;
}
