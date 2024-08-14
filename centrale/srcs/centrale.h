/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centrale.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 04:08:13 by reclaire          #+#    #+#             */
/*   Updated: 2024/08/11 04:08:13 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CENTRALE_H

#include "libftgr.h"

#define BITMAP_BLACK_PATH "./font_bitmap_black.png"
#define BITMAP_WHITE_PATH "./font_bitmap_white.png"

extern t_ftgr_ctx *ctx; // ftgr context
extern t_ftgr_win *main_win; // main window

extern t_ftgr_img *main_bitmap_img;
extern t_bitmap main_bitmap;

#endif