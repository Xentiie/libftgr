/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:01:42 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/29 00:11:04 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/maths.h"
#include <stdio.h>

static string get_unique_col(void *ptr)
{
	static char buf[100] = {0};
	F32 f1 = ft_frand((S32)(ptr));
	F32 f2 = ft_frand((S32)(ptr + 1));
	F32 f3 = ft_frand((S32)(ptr + 2));

	snprintf(buf, sizeof(buf) - 1, FT_FOREGROUND_COLOR(%d, %d, %d), (S32)(f1*255), (S32)(f2*255), (S32)(f3*255));
	return buf;
}

void print_cl_prog(string txt, cl_program prog)
{
	printf("%s: %s%p\n" FT_CRESET, txt, get_unique_col(prog), prog);
}
