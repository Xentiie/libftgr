/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw.cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:52:53 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/11 22:12:07 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLFW_CL_H
#define CLFW_CL_H

#ifndef __OPENCL_VERSION__
#define global
#define local
#define private
#define constant
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define unroll __attribute__((opencl_unroll_hint))

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

U64 clfw_get_clock();

#endif