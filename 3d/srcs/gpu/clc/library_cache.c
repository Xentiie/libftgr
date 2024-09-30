/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_cache.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:07:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/29 00:25:31 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/strings.h"

LibraryCache clc_cache_init()
{
	LibraryCache cache = malloc(sizeof(struct s_library_cache));
	if (UNLIKELY(cache == NULL))
		return NULL;
	cache->libraries_n = 0;
	cache->libraries_alloc = 1;
	cache->libraries = malloc(sizeof(t_library) * cache->libraries_alloc);
	if (cache->libraries == NULL)
	{
		free(cache);
		return NULL;
	}
	return cache;
}

bool clc_cache_lib(LibraryCache cache, ProgramBuilder builder, string header_name, cl_program lib)
{
	array_grow(cache->libraries, cache->libraries_n, cache->libraries_alloc, return FALSE, );

	cl_program header_prog = NULL;
	for (U64 i = 0; i < builder->headers_n; i++)
	{
		if (!ft_strcmp(header_name, builder->headers_names[i]))
		{
			header_prog = builder->headers_programs[i];
			break;
		}
	}

	if (header_prog == NULL)
		return FALSE;

	clRetainProgram(header_prog);
	clRetainProgram(lib);

	cache->libraries[cache->libraries_n++] = (t_library){
		.header = header_prog,
		.header_name = ft_strdup(header_name),
		.lib = lib
	};

	return TRUE;
}

void *clc_get_lib(LibraryCache cache, cl_program *header_prog, cl_program *lib, string *header_name)
{
	t_library *result = NULL;
	if (header_prog && *header_prog)
	{
		for (U64 i = 0; i < cache->libraries_n; i++)
		{
			if (cache->libraries[i].header == *header_prog)
			{
				result = &cache->libraries[i];
				if (lib)
					*lib = result->lib;
				if (header_name)
					*header_name = result->header_name;
				return result->header;
			}
		}
	}
	if (lib && *lib)
	{
		for (U64 i = 0; i < cache->libraries_n; i++)
		{
			if (cache->libraries[i].lib == *lib)
			{
				result = &cache->libraries[i];
				if (header_prog)
					*header_prog = result->header;
				if (header_name)
					*header_name = result->header_name;
				return result->lib;
			}
		}
	}
	if (header_name && *header_name)
	{
		for (U64 i = 0; i < cache->libraries_n; i++)
		{
			if (!ft_strcmp(cache->libraries[i].header_name, *header_name))
			{
				result = &cache->libraries[i];
				if (header_prog)
					*header_prog = result->header;
				if (lib)
					*lib = result->lib;
				return result->header_name;
			}
		}
	}
	return NULL;
}
