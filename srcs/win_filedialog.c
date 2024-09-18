/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_filedialog.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:01:31 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/11 17:09:32 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_win_int.h"

#ifdef FT_OS_WIN

void ftgr_open_filedialog(t_ftgr_win* win)
{
	
	OPENFILENAME fn = {
		.lStructSize = sizeof(OPENFILENAME),
		.hwndOwner = FTGR_WINDOW_INT(win)->window_handle,
		.hInstance = NULL,

	};
	//GetOpenFileName();

}

#endif