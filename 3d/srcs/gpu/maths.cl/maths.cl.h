/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.cl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 03:05:43 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/03 10:56:43 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTCL_MATHS_CL_H
#define FTCL_MATHS_CL_H

#include "clfw.cl.h"

#define FT_F32_U32(flt) ((union {F32 f; U32 b; }){.f = flt}.b)
#define FT_U32_F32(bits) ((union {F32 f; U32 b; }){.b = bits}.f)

#define FT_F32_PZERO FT_U32_F32(0x00000000) // 0 00000000 00000000000000000000000
#define FT_F32_NZERO FT_U32_F32(0x80000000) // 1 00000000 00000000000000000000000

#ifdef INFINITY
#define FT_F32_PINFINITY INFINITY  // 0 11111111 00000000000000000000000
#define FT_F32_NINFINITY -INFINITY // 1 11111111 00000000000000000000000
#define FT_F32_INF FT_F32_PINFINITY
#else
#define FT_F32_PINFINITY FT_U32_F32(0x7F800000) // 0 11111111 00000000000000000000000
#define FT_F32_NINFINITY FT_U32_F32(0xFF800000) // 1 11111111 00000000000000000000000
#define FT_F32_INF FT_F32_PINFINITY
#endif

#ifdef NAN
#define FT_F32_PQNAN NAN  // 0 11111111 1??????????????????????
#define FT_F32_NQNAN -NAN // 1 11111111 1??????????????????????
#define FT_F32_QNAN FT_F32_PQNAN
#else
#define FT_F32_PQNAN FT_U32_F32(0x7FC00001) // 0 11111111 1??????????????????????
#define FT_F32_NQNAN FT_U32_F32(0xFFC00001) // 1 11111111 1??????????????????????
#define FT_F32_QNAN FT_F32_PQNAN
#endif

#if defined(__has_builtin) && __has_builtin(__builtin_nans)
#define FT_F32_PSNAN __builtin_nansf("")  // 0 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_NSNAN -__builtin_nansf("") // 1 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_SNAN FT_F32_PSNAN
#else
#define FT_F32_PSNAN FT_U32_F32(0x7F800001) // 0 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_NSNAN FT_U32_F32(0xFF800001) // 1 11111111 0nnnnnnnnnnnnnnnnnnnnnn
#define FT_F32_SNAN FT_F32_PSNAN
#endif

#define FT_F32_PIND FT_U32_F32(0x7FC00000) // 0 11111111 10000000000000000000000
#define FT_F32_NIND FT_U32_F32(0xFFC00000) // 1 11111111 10000000000000000000000

#define FT_F32_ISZERO(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PZERO))
#define FT_F32_ISPZERO(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PZERO))
#define FT_F32_ISNZERO(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_NZERO))

#define FT_F32_ISINF(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PINFINITY))
#define FT_F32_ISPINF(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_PINFINITY))
#define FT_F32_ISNINF(flt) (FT_F32_U32(flt) == FT_F32_U32(FT_F32_NINFINITY))

#if defined(__has_builtin) && __has_builtin(__builtin_isnan)
#define FT_F32_ISNAN(flt) (__builtin_isnan(flt))
#else
#define FT_F32_ISNAN(flt) (((FT_F32_U32(flt) & 0x7F800000) == 0x7F800000) && ((FT_F32_U32(flt) & 0x007FFFFF) != 0))
#endif

#if defined(__has_builtin) && __has_builtin(__builtin_issignaling)
#define FT_F32_ISSNAN(flt) (FT_F32_ISNAN(flt) && __builtin_issignaling(flt))
#define FT_F32_ISQNAN(flt) (FT_F32_ISNAN(flt) && !__builtin_issignaling(flt))
#else
#define FT_F32_ISSNAN(flt) (FT_F32_ISNAN(flt) && ((FT_F32_U32(flt) & 0x00400000) == 0))
#define FT_F32_ISQNAN(flt) (FT_F32_ISNAN(flt) && ((FT_F32_U32(flt) & 0x00400000) == 0x00400000))
#endif

#if !defined(FT_PI)
#define FT_PI 3.14159265358979323846f
#endif /* FT_PI */

#if !defined(FT_DEG_TO_RAD)
#define FT_DEG_TO_RAD 0.01745329251
#endif /* FT_DEG_TO_RAD */
#if !defined(FT_RAD_TO_DEG)
#define FT_RAD_TO_DEG 57.2957795131
#endif /* FT_RAD_TO_DEG */

F32 ft_radians(F32 degrees);
F32 rcp(F32 v);

t_v4 *ft_mat4x4_col(t_mat4x4 *mat, S32 c);
float *ft_mat4x4_get(t_mat4x4 *mat, S32 r, S32 c);
void ft_mat4x4_set_col(t_mat4x4 *mat, S32 c, t_v4 v);
void ft_mat4x4_set_row(t_mat4x4 *mat, S32 r, t_v4 v);

t_mat4x4 ft_mat4x4_transpose(t_mat4x4 mat);
t_mat4x4 ft_mat4x4_invert(t_mat4x4 mat);
float ft_mat4x4_det(t_mat4x4 v);
t_mat4x4 ft_mat4x4_perspective(F32 fov, F32 near, F32 far);

t_mat4x4 ft_mat4x4_mult_mat(t_mat4x4 a, t_mat4x4 b);
t_mat4x4 ft_mat4x4_mult_float(t_mat4x4 a, F32 b);
t_v4 ft_mat4x4_mult_v4(t_mat4x4 a, t_v4 b);

t_mat4x4 ft_mat4x4_scale_v2(t_v2 v);
t_mat4x4 ft_mat4x4_scale_v3(t_v3 v);
t_mat4x4 ft_mat4x4_scale_v4(t_v4 v);
t_mat4x4 ft_mat4x4_scale_iv2(t_iv2 v);
t_mat4x4 ft_mat4x4_scale_iv3(t_iv3 v);
t_mat4x4 ft_mat4x4_scale_iv4(t_iv4 v);

t_mat4x4 ft_mat4x4_translate_v2(t_v2 v);
t_mat4x4 ft_mat4x4_translate_v3(t_v3 v);
t_mat4x4 ft_mat4x4_translate_iv2(t_iv2 v);
t_mat4x4 ft_mat4x4_translate_iv3(t_iv3 v);

t_mat4x4 ft_mat4x4_rotate_euler(t_v3 rot);

t_mat4x4 ft_mat4x4_fit_to_view(t_v2 pos, t_v2 size, t_v2 view_size);

extern constant t_mat4x4 ft_mat4x4_identity;

F32 ft_noise2(t_v2 p);
F32 ft_noise3(t_v3 p);

F32 ft_invlerp(F32 a, F32 b, F32 t);
t_v2 ft_invlerp2(t_v2 a, t_v2 b, F32 t);
t_v3 ft_invlerp3(t_v3 a, t_v3 b, F32 t);
t_v4 ft_invlerp4(t_v4 a, t_v4 b, F32 t);

#define ft_radians radians
#define ft_degrees degrees
#define ft_lerp mix
#define ft_normalize normalize
#define ft_dot dot
#define ft_smoothstep smoothstep
#define ft_abs abs
#define ft_ceil ceil
#define ft_floor floor
#define ft_frac(x) (x - ft_floor(x))

t_v2 ft_line_intersect(t_v2 l1p1, t_v2 l1p2, t_v2 l2p1, t_v2 l2p2);
F32 ft_dist_line(t_v2 p, t_v2 s1, t_v2 s2);

U64 ft_magnitude(S64 n);
U64 ft_umagnitude(U64 n);

t_v2 ft_rand_circle(U32 seed);
t_v2 ft_rotate2(t_v2 v, F32 angle, t_v2 origin);

#endif