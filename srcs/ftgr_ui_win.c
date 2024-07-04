/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftgr_ui_win.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 23:53:06 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/04 16:09:54 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_int_win.h"

t_ui_element *ftgr_new_ui()
{
	t_ui_element *elem = malloc(sizeof(t_ui_element));

	ft_memset(elem->callbacks, 0, sizeof(elem->callbacks));
	elem->primitives = NULL;
	return elem;
}

t_ui_callback *ftgr_ui_bind(t_ui_element *ui, S32 event, t_ui_callback callback)
{
	t_ui_callback prev = ui->callbacks[event];
	ui->callbacks[event] = callback;
	return prev;
}
