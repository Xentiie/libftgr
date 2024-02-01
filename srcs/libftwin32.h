/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftwin32.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 23:25:11 by reclaire          #+#    #+#             */
/*   Updated: 2024/01/16 23:25:11 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(LIBFTWIN32_H)
# define LIBFTWIN32_H

# include "libft.h"

typedef void *t_ftwin32_ctx;
typedef void *t_ftwin32_win;

t_ftwin32_ctx	*ftwin32_create_ctx();
void			ftwin32_loop(t_ftwin32_ctx *ctx);

t_ftwin32_win	*ftwin32_new_window(t_ftwin32_ctx *ctx, t_iv2 size, const_string title);
void			ftwin32_free_window(t_ftwin32_win *win);

void			ftwin32_quit(t_ftwin32_ctx *ctx);
void			ftwin32_set_quit_handler(t_ftwin32_ctx *ctx, void (*handler)());

#endif