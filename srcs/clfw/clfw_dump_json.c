/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw_dump_json.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 21:15:48 by reclaire          #+#    #+#             */
/*   Updated: 2024/12/03 20:38:33 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clfw_private.h"

#ifdef FT_OS_WIN
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#define _U64_fmt "%llu"
#define _S64_fmt "%lls"
#else
#define _U64_fmt "%lu"
#define _S64_fmt "%ls"
#endif
#define json_begin_obj(...) ft_fprintf(f, __VA_OPT__(__VA_ARGS__ ":") "{")
#define json_end_obj() ft_fprintf(f, "}")
#define json_sep() ft_fprintf(f, ",")
#define json_begin_array(...) ft_fprintf(f, __VA_OPT__("\"" __VA_ARGS__ "\":")"[")
#define json_end_array() ft_fprintf(f, "]")
#define dump_json_val(p, v)                                                                                                                                                                                         \
	{                                                                                                                                                                                                               \
		ft_fprintf(f, "\"" #v "\":");                                                                                                                                                                              \
		ft_fprintf(f, _Generic((p->v), U64: _U64_fmt, U32: "%u", U16: "%u", U8: "%s", S64: _S64_fmt, S32: "%d", S16: "%d", S8: "%d", string: "\"%s\""), _Generic((p->v), U8: (p->v ? "true" : "false"), default: p->v)); \
	}

void clfw_dump_device_json(t_file *f, ClDevice device)
{
	json_begin_obj();
	dump_json_val(device, type);
	json_sep();
	dump_json_val(device, compute_units);
	json_sep();
	json_begin_array("max_work_item_size");
	ft_fprintf(f, _U64_fmt","_U64_fmt","_U64_fmt, device->max_work_item_size[0], device->max_work_item_size[1], device->max_work_item_size[2]);
	json_end_array();
	json_sep();
	dump_json_val(device, max_work_group_size);
	json_sep();
	dump_json_val(device, clock_freq);
	json_sep();
	dump_json_val(device, address_bits);
	json_sep();
	dump_json_val(device, max_mem_alloc);
	json_sep();
	dump_json_val(device, il_version);
	json_sep();
	dump_json_val(device, max_param_size);
	json_sep();
	dump_json_val(device, mem_cache_type);
	json_sep();
	dump_json_val(device, global_mem_cache_line_size);
	json_sep();
	dump_json_val(device, global_mem_cache_size);
	json_sep();
	dump_json_val(device, global_mem_size);
	json_sep();
	dump_json_val(device, max_constant_buffer_size);
	json_sep();
	dump_json_val(device, max_constant);
	json_sep();
	dump_json_val(device, max_global_variable_size);
	json_sep();
	dump_json_val(device, global_variable_prefered_total_size);
	json_sep();
	dump_json_val(device, local_mem_type);
	json_sep();
	dump_json_val(device, local_mem_size);
	json_sep();
	dump_json_val(device, mem_error_correction);
	json_sep();
	dump_json_val(device, unified_memory);
	json_sep();
	dump_json_val(device, endian);
	json_sep();
	dump_json_val(device, available);
	json_sep();
	//dump_json_val(device, builtin_kernels);
	//json_sep();
	dump_json_val(device, name);
	json_sep();
	dump_json_val(device, vendor);
	json_sep();
	dump_json_val(device, driver_version);
	json_sep();
	dump_json_val(device, version);
	json_sep();
	dump_json_val(device, c_version);
	json_sep();
	dump_json_val(device, extensions);
	json_sep();
	dump_json_val(device, printf_buf_size);
	json_sep();
	dump_json_val(device, svm_capabilities);
	json_sep();
	dump_json_val(device, prefered_platform_atm_alignement);
	json_sep();
	dump_json_val(device, prefered_global_atm_alignement);
	json_sep();
	dump_json_val(device, prefered_local_atm_alignement);
	json_sep();
	dump_json_val(device, atm_capabilities);
	json_sep();
	dump_json_val(device, supports_generic_addr_space);

	json_end_obj();
}

void clfw_dump_platform_json(t_file *f, ClPlatform platform)
{
	json_begin_obj();

	dump_json_val(platform, name);
	json_sep();
	dump_json_val(platform, vendor);
	json_sep();
	dump_json_val(platform, version);
	json_sep();
	dump_json_val(platform, extensions);
	json_sep();
	dump_json_val(platform, embedded);
	json_sep();
	dump_json_val(platform, devices_cnt);
	json_sep();

	json_begin_array("devices");
	for (U64 i = 0; i < platform->devices_cnt; i++)
	{
		clfw_dump_device_json(f, platform->devices[i]);
		if (i != platform->devices_cnt - 1)
			json_sep();
	}
	json_end_array();

	json_end_obj();
}

void clfw_dump_platforms_json(t_file *f, ClPlatform *platforms, U64 platforms_count)
{
	json_begin_array();
	for (U64 i = 0; i < platforms_count; i++)
	{
		clfw_dump_platform_json(f, platforms[i]);
		if (i != platforms_count - 1)
			json_sep();
	}
	json_end_array();
}

#ifdef FT_OS_WIN
#pragma GCC diagnostic pop
#endif