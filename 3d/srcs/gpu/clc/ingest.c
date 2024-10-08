/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ingest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:13:09 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/08 03:31:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/strings.h"
#include "libft/io.h"

bool clc_ingest_program(ProgramBuilder builder, cl_program prog, bool compiled)
{
	clc_debug("ingest program at index %llu\n", (LU64)builder->programs_n);
	array_grow(builder->programs, builder->programs_n, builder->programs_alloc, return FALSE, );
	builder->programs[builder->programs_n++] = (program){.prog = prog, .compiled = compiled};
	return TRUE;
}

bool clc_ingest_file(ProgramBuilder builder, const_string path)
{
	file fd;
	S64 ret;
	char st_buffer[16384];
	string str = st_buffer;
	U64 alloc = sizeof(st_buffer);
	U64 rd = 0;

	clc_debug("ingest file %s\n", path);
	if (UNLIKELY((fd = ft_fopen(path, "r")) == (file)-1))
	{
		clc_error("couldn't ingest source file '%s': %s\n", path, ft_strerror2(ft_errno));
		return FALSE;
	}

	while ((ret = ft_fread(fd, str + rd, (alloc - 1) - rd)) > 0)
	{
		rd += ret;
		if (rd == (alloc - 1))
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

	bool err = clc_ingest_str(builder, str);
	if (str != st_buffer)
		free(str);
	return err;
}

bool clc_ingest_str(ProgramBuilder builder, const_string src)
{
	U64 len = ft_strlen(src);
	cl_program p = clfw_create_program_with_source(builder->device->ctx, 1, &src, &len);
	if (p == NULL)
	{
		clc_error("couldn't build source\n");
		return FALSE;
	}

	return clc_ingest_program(builder, p, FALSE);
}

bool clc_ingest_library(ProgramBuilder builder, LibraryCache lib_cache, string lib_name)
{
	cl_program lib = NULL;
	cl_program hdr = NULL;

	if (clc_get_lib(lib_cache, &hdr, &lib, &lib_name) == NULL)
		return FALSE;

	if (_clc_add_header(builder, lib_name, hdr) == -1)
		return FALSE;

	if (!clc_ingest_program(builder, lib, TRUE))
		return FALSE;
	return TRUE;
}
