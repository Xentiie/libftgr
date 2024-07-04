/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x11_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:26:57 by reclaire          #+#    #+#             */
/*   Updated: 2024/07/04 16:16:46 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr_x11_int.h"
#include "libft/limits.h"

/*
==================================================
*/
static bool _cmp_keys(void *d1, void *d2)
{
	return ((t_key*)d1)->k == *((U32*)(d2));
}

void _ftx11_register_key_down(t_ftgr_ctx *ctx, U32 key)
{
	t_list *fnd = ft_lstfind(ctx->keys, _cmp_keys, &key);
	if (fnd)
	{
		((t_key*)(fnd->content))->down = TRUE;
		return;
	}

	t_key k = (t_key){ .down = TRUE, .up = FALSE, .k = key };
	ft_lstadd_front(&ctx->keys, ft_lstnew(ft_memdup(&k, sizeof(t_key))));
}

void _ftx11_register_key_up(t_ftgr_ctx *ctx, U32 key)
{
	t_list *fnd = ft_lstfind(ctx->keys, _cmp_keys, &key);
	if (fnd)
	{
		((t_key*)(fnd->content))->down = FALSE;
		((t_key*)(fnd->content))->up = TRUE;
		return;
	}

	t_key k = (t_key){ .down = TRUE, .up = FALSE, .k = key };
	ft_lstadd_front(&ctx->keys, ft_lstnew(ft_memdup(&k, sizeof(t_key))));
}


static void _ftx11_keys_cleanup_chk(void *d)
{
	t_key *key = (t_key *)d;
	if (key->down)
		key->down = FALSE;
}

void _ftx11_keys_cleanup(t_ftgr_ctx *ctx)
{
	if (ctx->keys)
		ft_lstiter(ctx->keys, _ftx11_keys_cleanup_chk);

	ctx->left_mouse_released = FALSE;
	ctx->middle_mouse_released = FALSE;
	ctx->right_mouse_released = FALSE;
	//ft_lstremoveif(&ctx->keys, free, _ftx11_keys_cleanup_chk, NULL);
}
/*
==================================================
*/




bool ftgr_is_key_pressed(t_ftgr_ctx *ctx, U32 key)
{
	t_list *fnd = ft_lstfind(ctx->keys, _cmp_keys, &key);
	return fnd != NULL && !((t_key*)(fnd->content))->up;
}

bool ftgr_is_key_down(t_ftgr_ctx *ctx, U32 key)
{
	t_list *fnd = ft_lstfind(ctx->keys, _cmp_keys, &key);
	if (!fnd)
		return FALSE;
	return ((t_key*)(fnd->content))->down;
}

bool ftgr_is_key_up(t_ftgr_ctx *ctx, U32 key)
{
	t_list *fnd = ft_lstfind(ctx->keys, _cmp_keys, &key);
	if (!fnd)
		return FALSE;
	return ((t_key*)(fnd->content))->up;
}

void ftgr_key_autorepeat(t_ftgr_ctx *ctx, bool active)
{
	if (active)
		XAutoRepeatOn(ctx->display);
	else
		XAutoRepeatOff(ctx->display);
	XFlush(ctx->display);
}
