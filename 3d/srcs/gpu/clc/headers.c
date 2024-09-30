/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:13:41 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/29 00:25:22 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/strings.h"
#include "libft/path.h"
#include "libft/io.h"

S32 _clc_add_header(ProgramBuilder builder, const_string header_name, cl_program header_prog)
{
	for (U64 i = 0; i < builder->headers_n; i++)
	{
		if (!ft_strcmp(builder->headers_names[i], header_name))
			return 0;
	}

	{ /* grow headers array */
		string *new_names = NULL;
		cl_program *new_programs = NULL;
		if (builder->headers_n >= builder->headers_alloc)
		{
			if (UNLIKELY(
					(new_names = malloc(sizeof(string) * builder->headers_alloc * 2)) == NULL ||
					(new_programs = malloc(sizeof(cl_program) * builder->headers_alloc * 2)) == NULL))
			{
				free(new_names);
				free(new_programs);
				clc_error("couldn't grow headers array: out of memory\n");
				return -1;
			}
			ft_memcpy(new_names, builder->headers_names, sizeof(string) * builder->headers_n);
			ft_memcpy(new_programs, builder->headers_programs, sizeof(cl_program) * builder->headers_n);
		}
	}

	builder->headers_programs[builder->headers_n] = header_prog;
	builder->headers_names[builder->headers_n] = (string)header_name;
	builder->headers_n++;

	return 1;
}

bool clc_include_header(ProgramBuilder builder, const_string path)
{
	S32 err; /* error value for opencl functions */
	S64 ret;
	char st_buffer[16384];
	string str;
	U64 rd;

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

	cl_program header_prog = clCreateProgramWithSource(builder->ctx, 1, (const_string *)&str, &rd, &err);

	if (str != st_buffer)
		free(str);
	string header_name = ft_path_filename(path);
	if (err != 0 || header_name == NULL)
	{
		free(header_name);
		clc_error("couldn't include header '%s': clCreateProgramWithSource returned %s(%d)\n", path, cl_error_lookup_table[-err], err);
		return FALSE;
	}

	ret = _clc_add_header(builder, header_name, header_prog);
	if (ret < 1)
	{
		free(header_name);
		clReleaseProgram(header_prog);
		if (ret == -1)
			return FALSE;
	}

	return TRUE;
}
