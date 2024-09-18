/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 01:05:42 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/12 01:05:50 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./3d.h"

void print_mat(string name, t_mat4x4 mat)
{
	printf("%s {\n", name);
	printf("% 7f % 7f % 7f % 7f\n", mat.m00, mat.m01, mat.m02, mat.m03);
	printf("% 7f % 7f % 7f % 7f\n", mat.m10, mat.m11, mat.m12, mat.m13);
	printf("% 7f % 7f % 7f % 7f\n", mat.m20, mat.m21, mat.m22, mat.m23);
	printf("% 7f % 7f % 7f % 7f\n", mat.m30, mat.m31, mat.m32, mat.m33);
	printf("}\n");
}
