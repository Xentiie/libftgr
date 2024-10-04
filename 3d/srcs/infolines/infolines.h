/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infolines.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:19:58 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/30 12:20:44 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFOLINES_H
#define INFOLINES_H

#include "libftgr.h"
#include "libft/lists.h"

t_widget *new_info_line(t_list **lines, t_bitmap *bitmap, string label, string (*get_value_str)(void *), string (*dump_value_str)(void *), void *ptr);

#endif