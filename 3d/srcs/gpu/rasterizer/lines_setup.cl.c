/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines_setup.cl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:34:53 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 09:11:26 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.cl.h"

t_v4 vertex_shader(t_v3 p, t_mat4x4 world_to_clip);

__kernel void vertex_main(
	global t_v3 *pnts, U64 pnts_cnt,
	global t_iv2 *lns, U64 lns_cnt,
	global S32 *atm_sublines,
	global t_v4 *out,
	t_mat4x4 world_to_clip)
{
	S32 id = get_global_id(0);
	if (id >= lns_cnt)
		return;

	t_iv2 l = lns[id];
	t_v3 p1 = pnts[l.x];
	t_v3 p2 = pnts[l.y];

	t_v4 pp1 = vertex_shader(p1, world_to_clip);
	t_v4 pp2 = vertex_shader(p2, world_to_clip);

	out[l.x] = pp1;
	out[l.y] = pp2;
	atomic_inc(atm_sublines);
	atomic_inc(atm_sublines);
}