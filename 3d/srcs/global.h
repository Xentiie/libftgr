/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 22:55:48 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/27 03:40:45 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
#define GLOBAL_H

#include "libft/types.h"

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
#define array_grow(arr, count, alloc, onerror, onsuccess)                                           \
	do                                                                                              \
	{                                                                                               \
		if ((count) >= (alloc))                                                                     \
		{                                                                                           \
			clc_debug("array growth: " #arr " (%llu -> %llu)\n", (LU64)(alloc), (LU64)(alloc * 2)); \
			typeof((arr)) _grow_array_new = malloc(sizeof((arr)[0]) * (alloc) * 2);                 \
			if (UNLIKELY(_grow_array_new == NULL))                                                  \
			{                                                                                       \
				log_error(NULL, "out of memory: can't grow array " #arr "\n");                      \
				FT_DEPAREN(onerror);                                                                \
			}                                                                                       \
			ft_memcpy(_grow_array_new, (arr), sizeof(arr[0]) * (count));                            \
			free((arr));                                                                            \
			(arr) = _grow_array_new;                                                                \
			(alloc) *= 2;                                                                           \
			FT_DEPAREN(onsuccess);                                                                  \
		}                                                                                           \
                                                                                                    \
	} while (0)

#endif