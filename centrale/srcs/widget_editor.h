/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widget_editor.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:26:56 by reclaire          #+#    #+#             */
/*   Updated: 2024/08/24 17:28:02 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_EDITOR_H

# include "libftgr.h"

/*
Will reparent `root` to the widget editor
`root` can be NULL
Returns NULL on allocation failure
*/
t_widget *init_widget_editor(t_widget *root);

#endif