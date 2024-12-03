/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_cl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:12:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/12 02:18:39 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/strings.h"

string clean_cl_file(const_string file, U64 len)
{
	string out;
	string ptr;

	if (UNLIKELY((out = malloc(sizeof(char) * len)) == NULL))
		return NULL;

	ptr = out;
	while (*file)
	{
		printf("%3s\n", file);
		if (*file == '/' && *(file + 1) == '*')
		{
			while (*(file + 1) && !(*file == '*' && *(file + 1) == '/'))
				file++;
			if (*(file + 1))
			{
				file += 2;
				if (!(*file))
					break;
			}
			
		}
		*ptr = *file;
		ptr++;
		file++;
	}
	*ptr = '\0';

	return out;
}

#if defined(TEST)
int main()
{
	string data;
	U64 data_len;
	t_file *f;

	f = ft_fopen("/mnt/c/Users/reclaire/Desktop/libftgr/srcs/clfw.cl/clfw.cl.h", "r");
	if (f== NULL)
	{
		ft_printf("%s\n", ft_strerror2(ft_errno));
		return 1;
	}
	data = ft_freadfile(f, &data_len);
	
	printf("%s\n", data);

	return 0;
	string res = clean_cl_file(data, data_len);
	free(data);
	ft_printf("%s\n", res);
}
#endif