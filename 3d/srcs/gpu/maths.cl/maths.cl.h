/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.cl.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 03:05:43 by reclaire          #+#    #+#             */
/*   Updated: 2024/09/28 02:37:03 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTCL_MATHS_CL_H
#define FTCL_MATHS_CL_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#define unroll __attribute__((opencl_unroll_hint))

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

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
#ifdef FT_OS_WIN
typedef unsigned long long U64;
typedef unsigned long long LU64;
#else
typedef unsigned long U64;
typedef unsigned long long LU64;
#endif
typedef signed char S8;
typedef signed short S16;
typedef signed int S32;
#ifdef FT_OS_WIN
typedef signed long long S64;
typedef signed long long LS64;
#else
typedef signed long S64;
typedef signed long long LS64;
#endif
typedef float F32;
typedef double F64;
typedef long double LF64;

typedef char *string;
typedef char const *const_string;
typedef int *wstring;
typedef int const *const_wstring;
typedef int wchar;

#ifndef __OPENCL_VERSION__
typedef F32 float4 __attribute__((vector_size(sizeof(F32) * 4)));
typedef F32 float3 __attribute__((vector_size(sizeof(F32) * 4)));
typedef F32 float2 __attribute__((vector_size(sizeof(F32) * 2)));
typedef S32 int4 __attribute__((vector_size(sizeof(S32) * 4)));
typedef S32 int3 __attribute__((vector_size(sizeof(S32) * 4)));
typedef S32 int2 __attribute__((vector_size(sizeof(S32) * 2)));

#define global
#define local
#define private
#define constant

#define vec2(x, y) (t_v2){x, y}
#define vec3(x, y, z) (t_v3){x, y, z}
#define vec4(x, y, z, w) (t_v4){x, y, z, w}
#define ivec2(x, y) (t_iv2){x, y}
#define ivec3(x, y, z) (t_iv3){x, y, z}
#define ivec4(x, y, z, w) (t_iv4){x, y, z, w}

#else
#define vec2(x, y) (t_v2)(x, y)
#define vec3(x, y, z) (t_v3)(x, y, z)
#define vec4(x, y, z, w) (t_v4)(x, y, z, w)
#define ivec2(x, y) (t_iv2)(x, y)
#define ivec3(x, y, z) (t_iv3)(x, y, z)
#define ivec4(x, y, z, w) (t_iv4)(x, y, z, w)
#endif

typedef float4 t_v4;
typedef float3 t_v3;
typedef float2 t_v2;
typedef int4 t_iv4;
typedef int3 t_iv3;
typedef int2 t_iv2;


typedef struct s_mat4x4
{
	F32 m00, m10, m20, m30;
	F32 m01, m11, m21, m31;
	F32 m02, m12, m22, m32;
	F32 m03, m13, m23, m33;
} t_mat4x4;

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