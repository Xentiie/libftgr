/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw.cl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:52:53 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/03 10:57:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clfw.cl.h"

U64 clfw_get_clock()
{
	U64 clock_time;
	asm volatile("mov.u64 %0, %%clock64;" : "=l"(clock_time));
	return clock_time;
}
