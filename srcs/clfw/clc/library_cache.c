/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_cache.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:07:18 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 03:48:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/strings.h"

bool clc_cache_lib(ProgramBuilder builder, const_string header_name, cl_program lib, const_string lib_name)
{
	cl_program header_prog;

	ASSERT(builder != NULL, FALSE);
	ASSERT(header_name != NULL, FALSE);
	ASSERT(lib != NULL, FALSE);
	ASSERT(lib_name != NULL, FALSE);

	if (builder->libraries_n >= builder->libraries_alloc)
	{
		Library *new = malloc(sizeof(Library) * builder->libraries_alloc * 2);
		if (UNLIKELY(new == NULL))
		{
			clc_error("cache lib: out of memory\n");
			return FALSE;
		}
		ft_memcpy(new, builder->libraries, sizeof(Library) * builder->libraries_n);
		free(builder->libraries);
		builder->libraries = new;
		builder->libraries_alloc *= 2;
	}

	if ((header_prog = clc_header_get(builder, header_name)) == NULL)
		return FALSE;

	ft_bzero(&builder->libraries[builder->libraries_n], sizeof(Library));
	builder->libraries[builder->libraries_n] = (Library){
		.header = header_prog,
		.header_name = ft_strdup(header_name),
		.lib = lib,
		.lib_name = ft_strdup(lib_name)};

	if (UNLIKELY(builder->libraries[builder->libraries_n].header_name == NULL || builder->libraries[builder->libraries_n].lib_name == NULL))
	{
		free(builder->libraries[builder->libraries_n].header_name);
		free(builder->libraries[builder->libraries_n].lib_name);
		return FALSE;
	}

	clfw_retain_program(header_prog);
	clfw_retain_program(lib);

	builder->libraries_n++;

	return TRUE;
}

Library *clc_get_cached_lib(ProgramBuilder builder, string lib_name)
{
	ASSERT(builder != NULL, FALSE)
	ASSERT(lib_name != NULL, FALSE)

	for (U64 i = 0; i < builder->libraries_n; i++)
	{
		if (!ft_strcmp(builder->libraries[i].lib_name, lib_name))
			return &builder->libraries[i];
	}
	return NULL;
}

