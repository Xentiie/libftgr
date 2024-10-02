/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 23:42:30 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/02 18:28:57 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLFW_H
#define CLFW_H

#include "libft/types.h"

#define CL_TARGET_OPENCL_VERSION 300
#include "CL/cl.h"

typedef struct s_cl_device {
	cl_device_id device_id;
	cl_device_type type; //CL_DEVICE_TYPE
	U32 compute_units; //CL_DEVICE_MAX_COMPUTE_UNITS
	U64 max_work_item_size[3]; //CL_DEVICE_MAX_WORK_ITEM_SIZES
	U64 max_work_group_size; //CL_DEVICE_MAX_WORK_GROUP_SIZE

	U32 clock_freq; //CL_DEVICE_MAX_CLOCK_FREQUENCY
	U32 address_bits; //CL_DEVICE_ADDRESS_BITS
	U64 max_mem_alloc; //CL_DEVICE_MAX_MEM_ALLOC_SIZE
	string il_version; //CL_DEVICE_IL_VERSION
	U64 max_param_size; //CL_DEVICE_MAX_PARAMETER_SIZE

	cl_device_mem_cache_type mem_cache_type; //CL_DEVICE_GLOBAL_MEM_CACHE_TYPE
	U32 global_mem_cache_line_size; //CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE
	U64 global_mem_cache_size; //CL_DEVICE_GLOBAL_MEM_CACHE_SIZE
	U64 global_mem_size; //CL_DEVICE_GLOBAL_MEM_SIZE

	U64 max_constant_buffer_size; //CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE
	U64 max_constant; //CL_DEVICE_MAX_CONSTANT_ARGS

	U64 max_global_variable_size; //CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE
	U64 global_variable_prefered_total_size; //CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE

	cl_device_local_mem_type local_mem_type; //CL_DEVICE_LOCAL_MEM_TYPE
	U64 local_mem_size; //CL_DEVICE_LOCAL_MEM_SIZE

	bool mem_error_correction; //CL_DEVICE_ERROR_CORRECTION_SUPPORT
	bool unified_memory; //CL_DEVICE_HOST_UNIFIED_MEMORY
	bool endian; //CL_DEVICE_ENDIAN_LITTLE
	bool available; //CL_DEVICE_AVAILABLE

	string builtin_kernels; //CL_DEVICE_BUILT_IN_KERNELS
	string name; //CL_DEVICE_NAME
	string vendor; //CL_DEVICE_VENDOR
	string driver_version; //CL_DRIVER_VERSION
	string version; //CL_DEVICE_VERSION
	string c_version; //CL_DEVICE_OPENCL_C_VERSION //TODO: use CL_DEVICE_OPENCL_C_ALL_VERSIONS instead
	//TODO: CL_DEVICE_OPENCL_C_FEATURES
	string extensions; //CL_DEVICE_EXTENSIONS

	U64 printf_buf_size; //CL_DEVICE_PRINTF_BUFFER_SIZE

	cl_device_svm_capabilities svm_capabilities; //CL_DEVICE_SVM_CAPABILITIES

	U32 prefered_platform_atm_alignement; //CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT
	U32 prefered_global_atm_alignement; //CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT
	U32 prefered_local_atm_alignement; //CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT

	cl_device_atomic_capabilities atm_capabilities; //CL_DEVICE_ATOMIC_MEMORY_CAPABILITIES

	bool supports_generic_addr_space; //CL_DEVICE_GENERIC_ADDRESS_SPACE_SUPPORT	
} ClDevice;

typedef struct s_cl_platform
{
	cl_platform_id platform_id;
	ClDevice *devices;
	U32 devices_cnt;
	string name;
	string vendor;
	string version;
	string extensions;
	bool embedded; /* CL_PLATFORM_PROFILE  */
} ClPlatform;


typedef struct s_cl_kernel
{
	cl_kernel kernel;
	string kernel_name;
} ClKernel;

typedef struct s_cl_program
{
	/* can be NULL */
	string program_source;
	ClKernel *kernels;
	U64 kernels_cnt;
	cl_program prog;
} ClProgram;

typedef struct s_cl_header
{

} ClHeader;

ClKernel *clfw_get_kernel(ClProgram *program, U64 index);
ClKernel *clfw_get_kernel_by_name(ClProgram *program, string name);
string clfw_get_kernel_name(ClKernel *kernel);

ClPlatform *clfw_query_platforms_devices(U64 *platforms_cnt);

void *_clfw_get_cl_kernel(ClKernel *kernel);
void *_clfw_get_cl_program(ClProgram *program);

S32 clfw_get_last_error();
S32 clfw_get_last_call();
const_string clfw_get_error_title(S32 err);
const_string clfw_get_call_title(S32 call);
const_string clfw_get_last_error_title();
const_string clfw_get_last_call_title();

void clfw_dump_platforms_json(file fd, ClPlatform *platforms, U64 platforms_count);
void clfw_dump_platform_json(file fd, ClPlatform *platform);
void clfw_dump_device_json(file fd, ClDevice *device);

#endif