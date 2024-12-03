/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 00:31:39 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 00:33:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "libft/limits.h"
#include "libft/maths.h"
#include "libft/ansi.h"

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
