/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 00:01:42 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/02 16:04:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clc_private.h"
#include "utils.h"
#include "libft/maths.h"
#include "libft/limits.h"
#include <stdio.h>

void print_cl_prog(string txt, cl_program prog)
{
	printf("%s: %s%p\n" FT_CRESET, txt, get_unique_col((U64)prog), prog);
}
