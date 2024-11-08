/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:05:42 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 00:37:13 by reclaire         ###   ########.fr       */
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
