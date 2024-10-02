/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:05:42 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 14:52:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/maths.h"
#include "libft/limits.h"
#include "libft/ansi.h"

#include <stdio.h>

void print_mat(string name, t_mat4x4 mat)
{
	printf("%s {\n", name);
    for (int i = 0; i < 4; i++)
    {
		printf("\t");
        for (int j = 0; j < 4; j++)
            printf("% 7f, ", *ft_mat4x4_get(&mat, i, j));
        printf("\n");
    }
	printf("}\n");
}

string get_unique_col(U64 v)
{
	static char buf[100] = {0};
	v %= S32_MAX;
	F32 f1 = ft_frand((S32)(v));
	F32 f2 = ft_frand((S32)(v + 1));
	F32 f3 = ft_frand((S32)(v + 2));

	snprintf(buf, sizeof(buf) - 1, FT_FOREGROUND_COLOR(%d, %d, %d), (S32)(f1*255), (S32)(f2*255), (S32)(f3*255));
	return buf;
}
