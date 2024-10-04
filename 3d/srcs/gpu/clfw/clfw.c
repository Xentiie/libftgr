/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:03:47 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/02 16:04:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clfw_private.h"
#include "libft/strings.h"

ClKernel *clfw_get_kernel(ClProgram *program, U64 index)
{
	if (index >= program->kernels_cnt)
		return NULL;
	return &program->kernels[index];
}

ClKernel *clfw_get_kernel_by_name(ClProgram *program, string name)
{
	for (U64 i = 0; i < program->kernels_cnt; i++)
	{
		if (!ft_strcmp(name, program->kernels[i].kernel_name))
			return &program->kernels[i];
	}
	return NULL;
}

string clfw_get_kernel_name(ClKernel *kernel)
{
	return kernel->kernel_name;
}


void *_clfw_get_cl_kernel(ClKernel *kernel) { return kernel->kernel; }
void *_clfw_get_cl_program(ClProgram *program) { return program->prog; }