/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw_private.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 22:03:32 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/11 00:33:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLFW_PRIVATE_H
#define CLFW_PRIVATE_H

#include "clfw/clfw.h"
#include "libft/macros.h"
#include "log.h"

extern S32 clfw_last_call;
extern S32 clfw_last_error;
extern const_string clfw_func_calls[];

#define clfw_tag "clfw"
#define clfw_error(...) log_error(clfw_tag, __VA_ARGS__)
#define clfw_warn(...) log_warn(clfw_tag, __VA_ARGS__)
#define clfw_info(...) log_info(clfw_tag, __VA_ARGS__)
#define clfw_debug(...) log_debug(clfw_tag, __VA_ARGS__)

#define array_len(x) (sizeof(x) / sizeof(x[0]))

/*
initializes an array, where 'arr' is the buffer, 'count' is the number of elements in the array
and 'alloc' is the current allocation space for the array.
Executes 'onerror' on malloc failure
*/
#define array_init(arr, count, alloc, onerror)                             \
	do                                                                     \
	{                                                                      \
		(count) = 0;                                                       \
		(alloc) = 1;                                                       \
		(arr) = malloc(sizeof(arr[0]) * (alloc));                          \
		if (UNLIKELY((arr) == NULL))                                       \
		{                                                                  \
			log_error(NULL, "out of memory: can't init array " #arr "\n"); \
			FT_DEPAREN(onerror);                                           \
		}                                                                  \
	} while (0)

/*
Grow the array if needed, where 'arr' is the buffer, 'count' is the number of elements in the array
and 'alloc' is the current allocation space for the array.
Executes 'onerror' on malloc failure
*/
#define array_grow(arr, count, alloc, onerror, onsuccess)                                                  \
	do                                                                                                     \
	{                                                                                                      \
		if ((count) >= (alloc))                                                                            \
		{                                                                                                  \
			U64 _new_array_alloc = (alloc) == 0 ? 1 : (alloc) * 2;                                         \
			clc_debug("array growth: " #arr " (%llu -> %llu)\n", (LU64)(alloc), (LU64)(_new_array_alloc)); \
			typeof((arr)) _grow_array_new = malloc(sizeof((arr)[0]) * (_new_array_alloc) * 2);             \
			if (UNLIKELY(_grow_array_new == NULL))                                                         \
			{                                                                                              \
				log_error(NULL, "out of memory: can't grow array " #arr "\n");                             \
				FT_DEPAREN(onerror);                                                                       \
			}                                                                                              \
			ft_memcpy(_grow_array_new, (arr), sizeof((arr)[0]) * (count));                                 \
			free((arr));                                                                                   \
			(arr) = _grow_array_new;                                                                       \
			(alloc) = _new_array_alloc;                                                                    \
			FT_DEPAREN(onsuccess);                                                                         \
		}                                                                                                  \
                                                                                                           \
	} while (0)

#endif