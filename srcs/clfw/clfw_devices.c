/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw_devices.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:40:48 by reclaire          #+#    #+#             */
/*   Updated: 2024/11/12 14:56:34 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clfw_private.h"
#include "libft/strings.h"
#include "libft/io.h"

static const_string device_params_names[] = {
	"CL_DEVICE_TYPE",									 /* 0x1000 */
	"CL_DEVICE_VENDOR_ID",								 /* 0x1001 */
	"CL_DEVICE_MAX_COMPUTE_UNITS",						 /* 0x1002 */
	"CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS",				 /* 0x1003 */
	"CL_DEVICE_MAX_WORK_GROUP_SIZE",					 /* 0x1004 */
	"CL_DEVICE_MAX_WORK_ITEM_SIZES",					 /* 0x1005 */
	"CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR",			 /* 0x1006 */
	"CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT",			 /* 0x1007 */
	"CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT",				 /* 0x1008 */
	"CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG",			 /* 0x1009 */
	"CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT",			 /* 0x100A */
	"CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE",			 /* 0x100B */
	"CL_DEVICE_MAX_CLOCK_FREQUENCY",					 /* 0x100C */
	"CL_DEVICE_ADDRESS_BITS",							 /* 0x100D */
	"CL_DEVICE_MAX_READ_IMAGE_ARGS",					 /* 0x100E */
	"CL_DEVICE_MAX_WRITE_IMAGE_ARGS",					 /* 0x100F */
	"CL_DEVICE_MAX_MEM_ALLOC_SIZE",						 /* 0x1010 */
	"CL_DEVICE_IMAGE2D_MAX_WIDTH",						 /* 0x1011 */
	"CL_DEVICE_IMAGE2D_MAX_HEIGHT",						 /* 0x1012 */
	"CL_DEVICE_IMAGE3D_MAX_WIDTH",						 /* 0x1013 */
	"CL_DEVICE_IMAGE3D_MAX_HEIGHT",						 /* 0x1014 */
	"CL_DEVICE_IMAGE3D_MAX_DEPTH",						 /* 0x1015 */
	"CL_DEVICE_IMAGE_SUPPORT",							 /* 0x1016 */
	"CL_DEVICE_MAX_PARAMETER_SIZE",						 /* 0x1017 */
	"CL_DEVICE_MAX_SAMPLERS",							 /* 0x1018 */
	"CL_DEVICE_MEM_BASE_ADDR_ALIGN",					 /* 0x1019 */
	"CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE",				 /* 0x101A */
	"CL_DEVICE_SINGLE_FP_CONFIG",						 /* 0x101B */
	"CL_DEVICE_GLOBAL_MEM_CACHE_TYPE",					 /* 0x101C */
	"CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE",				 /* 0x101D */
	"CL_DEVICE_GLOBAL_MEM_CACHE_SIZE",					 /* 0x101E */
	"CL_DEVICE_GLOBAL_MEM_SIZE",						 /* 0x101F */
	"CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE",				 /* 0x1020 */
	"CL_DEVICE_MAX_CONSTANT_ARGS",						 /* 0x1021 */
	"CL_DEVICE_LOCAL_MEM_TYPE",							 /* 0x1022 */
	"CL_DEVICE_LOCAL_MEM_SIZE",							 /* 0x1023 */
	"CL_DEVICE_ERROR_CORRECTION_SUPPORT",				 /* 0x1024 */
	"CL_DEVICE_PROFILING_TIMER_RESOLUTION",				 /* 0x1025 */
	"CL_DEVICE_ENDIAN_LITTLE",							 /* 0x1026 */
	"CL_DEVICE_AVAILABLE",								 /* 0x1027 */
	"CL_DEVICE_COMPILER_AVAILABLE",						 /* 0x1028 */
	"CL_DEVICE_EXECUTION_CAPABILITIES",					 /* 0x1029 */
	"CL_DEVICE_QUEUE_PROPERTIES",						 /* 0x102A */
	"CL_DEVICE_QUEUE_ON_HOST_PROPERTIES",				 /* 0x102A */
	"CL_DEVICE_NAME",									 /* 0x102B */
	"CL_DEVICE_VENDOR",									 /* 0x102C */
	"CL_DRIVER_VERSION",								 /* 0x102D */
	"CL_DEVICE_PROFILE",								 /* 0x102E */
	"CL_DEVICE_VERSION",								 /* 0x102F */
	"CL_DEVICE_EXTENSIONS",								 /* 0x1030 */
	"CL_DEVICE_PLATFORM",								 /* 0x1031 */
	"CL_DEVICE_DOUBLE_FP_CONFIG",						 /* 0x1032 */
	"CL_DEVICE_HALF_FP_CONFIG",							 /* 0x1033 */
	"CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF",			 /* 0x1034 */
	"CL_DEVICE_HOST_UNIFIED_MEMORY",					 /* 0x1035 */
	"CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR",				 /* 0x1036 */
	"CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT",				 /* 0x1037 */
	"CL_DEVICE_NATIVE_VECTOR_WIDTH_INT",				 /* 0x1038 */
	"CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG",				 /* 0x1039 */
	"CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT",				 /* 0x103A */
	"CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE",				 /* 0x103B */
	"CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF",				 /* 0x103C */
	"CL_DEVICE_OPENCL_C_VERSION",						 /* 0x103D */
	"CL_DEVICE_LINKER_AVAILABLE",						 /* 0x103E */
	"CL_DEVICE_BUILT_IN_KERNELS",						 /* 0x103F */
	"CL_DEVICE_IMAGE_MAX_BUFFER_SIZE",					 /* 0x1040 */
	"CL_DEVICE_IMAGE_MAX_ARRAY_SIZE",					 /* 0x1041 */
	"CL_DEVICE_PARENT_DEVICE",							 /* 0x1042 */
	"CL_DEVICE_PARTITION_MAX_SUB_DEVICES",				 /* 0x1043 */
	"CL_DEVICE_PARTITION_PROPERTIES",					 /* 0x1044 */
	"CL_DEVICE_PARTITION_AFFINITY_DOMAIN",				 /* 0x1045 */
	"CL_DEVICE_PARTITION_TYPE",							 /* 0x1046 */
	"CL_DEVICE_REFERENCE_COUNT",						 /* 0x1047 */
	"CL_DEVICE_PREFERRED_INTEROP_USER_SYNC",			 /* 0x1048 */
	"CL_DEVICE_PRINTF_BUFFER_SIZE",						 /* 0x1049 */
	"CL_DEVICE_IMAGE_PITCH_ALIGNMENT",					 /* 0x104A */
	"CL_DEVICE_IMAGE_BASE_ADDRESS_ALIGNMENT",			 /* 0x104B */
	"CL_DEVICE_MAX_READ_WRITE_IMAGE_ARGS",				 /* 0x104C */
	"CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE",				 /* 0x104D */
	"CL_DEVICE_QUEUE_ON_DEVICE_PROPERTIES",				 /* 0x104E */
	"CL_DEVICE_QUEUE_ON_DEVICE_PREFERRED_SIZE",			 /* 0x104F */
	"CL_DEVICE_QUEUE_ON_DEVICE_MAX_SIZE",				 /* 0x1050 */
	"CL_DEVICE_MAX_ON_DEVICE_QUEUES",					 /* 0x1051 */
	"CL_DEVICE_MAX_ON_DEVICE_EVENTS",					 /* 0x1052 */
	"CL_DEVICE_SVM_CAPABILITIES",						 /* 0x1053 */
	"CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE",	 /* 0x1054 */
	"CL_DEVICE_MAX_PIPE_ARGS",							 /* 0x1055 */
	"CL_DEVICE_PIPE_MAX_ACTIVE_RESERVATIONS",			 /* 0x1056 */
	"CL_DEVICE_PIPE_MAX_PACKET_SIZE",					 /* 0x1057 */
	"CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT",	 /* 0x1058 */
	"CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT",		 /* 0x1059 */
	"CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT",		 /* 0x105A */
	"CL_DEVICE_IL_VERSION",								 /* 0x105B */
	"CL_DEVICE_MAX_NUM_SUB_GROUPS",						 /* 0x105C */
	"CL_DEVICE_SUB_GROUP_INDEPENDENT_FORWARD_PROGRESS",	 /* 0x105D */
	"CL_DEVICE_NUMERIC_VERSION",						 /* 0x105E */
	"CL_DEVICE_EXTENSIONS_WITH_VERSION",				 /* 0x1060 */
	"CL_DEVICE_ILS_WITH_VERSION",						 /* 0x1061 */
	"CL_DEVICE_BUILT_IN_KERNELS_WITH_VERSION",			 /* 0x1062 */
	"CL_DEVICE_ATOMIC_MEMORY_CAPABILITIES",				 /* 0x1063 */
	"CL_DEVICE_ATOMIC_FENCE_CAPABILITIES",				 /* 0x1064 */
	"CL_DEVICE_NON_UNIFORM_WORK_GROUP_SUPPORT",			 /* 0x1065 */
	"CL_DEVICE_OPENCL_C_ALL_VERSIONS",					 /* 0x1066 */
	"CL_DEVICE_PREFERRED_WORK_GROUP_SIZE_MULTIPLE",		 /* 0x1067 */
	"CL_DEVICE_WORK_GROUP_COLLECTIVE_FUNCTIONS_SUPPORT", /* 0x1068 */
	"CL_DEVICE_GENERIC_ADDRESS_SPACE_SUPPORT",			 /* 0x1069 */
	NULL,												 /* 0x106A */
	NULL,												 /* 0x106B */
	NULL,												 /* 0x106C */
	NULL,												 /* 0x106D */
	NULL,												 /* 0x106E */
	"CL_DEVICE_OPENCL_C_FEATURES",						 /* 0x106F */
	"CL_DEVICE_DEVICE_ENQUEUE_CAPABILITIES",			 /* 0x1070 */
	"CL_DEVICE_PIPE_SUPPORT",							 /* 0x1071 */
	"CL_DEVICE_LATEST_CONFORMANCE_VERSION_PASSED",		 /* 0x1072 */
};

static string get_platform_param(cl_platform_id platform, cl_platform_info param)
{
	string ptr;
	U64 size;

	if (!clfw_get_platform_info(platform, param, 0, NULL, &size))
		return NULL;

	if (UNLIKELY((ptr = malloc(sizeof(char) * (size + 1))) == NULL))
	{
		ft_errno = FT_EOMEM;
		clfw_last_error = 0;
		return NULL;
	}

	if (!clfw_get_platform_info(platform, param, size, ptr, NULL))
	{
		free(ptr);
		return NULL;
	}

	ptr[size] = '\0';
	return ptr;
}

static void *get_device_param(cl_device_info *last_info, cl_device_id device, cl_device_info param, void *ptr, U64 size)
{
	*last_info = param;

	bool is_bool_val = size == 1;
	bool ptr_allocated = ptr == NULL;
	if (ptr == NULL)
	{
		if (!clfw_get_device_info(device, param, 0, NULL, &size))
			return NULL;

		if (UNLIKELY((ptr = malloc(sizeof(char) * (size + 1))) == NULL))
		{
			ft_errno = FT_EOMEM;
			clfw_last_error = 0;
			return NULL;
		}
	}

	/* fix bc sizeof(cl_bool) == 4 (cl_bool is typedefed to int), while sizeof(bool) == 1 (typedefed to bool) */
	if (is_bool_val)
	{
		S32 b;
		if (!clfw_get_device_info(device, param, sizeof(b), &b, NULL))
			return NULL;
		*((bool *)ptr) = b;
	}
	else
	{
		if (!clfw_get_device_info(device, param, size, ptr, NULL))
		{
			if (ptr_allocated)
				free(ptr);
			return NULL;
		}
	}

	if (ptr == NULL)
		((string)ptr)[size] = '\0';
	return ptr;
}

ClPlatform *clfw_query_platforms_devices(U64 *platforms_cnt)
{
	ClPlatform *platforms;
	cl_platform_id *platforms_cl;
	U32 num_platforms;
	U64 i;

	platforms = NULL;
	platforms_cl = NULL;
	num_platforms = 0;
	*platforms_cnt = 0;

	if (!clfw_get_platform_ids(0, NULL, &num_platforms))
		return NULL;
	if (num_platforms == 0)
	{
		clfw_last_error = 0;
		return NULL;
	}

	if (UNLIKELY((platforms = malloc(sizeof(struct s_cl_platform) * num_platforms)) == NULL) ||
		UNLIKELY((platforms_cl = malloc(sizeof(cl_platform_id) * num_platforms)) == NULL))
	{
		clfw_last_error = 0;
		ft_errno = FT_EOMEM;
		goto exit_err;
	}

	if (!clfw_get_platform_ids(num_platforms, platforms_cl, NULL))
		goto exit_err;

	ft_bzero(platforms, sizeof(struct s_cl_platform) * num_platforms);
	for (i = 0; i < num_platforms; i++)
	{
		if (UNLIKELY((platforms[i] = malloc(sizeof(struct s_cl_platform))) == NULL))
			goto exit_err;
		platforms[i]->ref = 1;
		platforms[i]->platform_id = platforms_cl[i];

		/* get version */
		if (UNLIKELY((platforms[i]->version = get_platform_param(platforms[i]->platform_id, CL_PLATFORM_VERSION)) == NULL))
			goto exit_err;

		/* get name */
		if (UNLIKELY((platforms[i]->name = get_platform_param(platforms[i]->platform_id, CL_PLATFORM_NAME)) == NULL))
			goto exit_err;

		/* get vendor */
		if (UNLIKELY((platforms[i]->vendor = get_platform_param(platforms[i]->platform_id, CL_PLATFORM_VENDOR)) == NULL))
			goto exit_err;

		/* get extensions */
		if (UNLIKELY((platforms[i]->extensions = get_platform_param(platforms[i]->platform_id, CL_PLATFORM_EXTENSIONS)) == NULL))
			goto exit_err;

		// TODO: ici les crashs n'ont pas a etre fatals. pour le moment je fais ca comme ca prcque ca va vite, mais faudra changer
		cl_device_id *devices_cl;
		U32 num_devices;
		if (!clfw_get_device_ids(platforms[i]->platform_id, CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices))
			goto exit_err;
		if (num_devices == 0)
			continue;
		if (UNLIKELY((platforms[i]->devices = malloc(sizeof(struct s_cl_device) * num_devices)) == NULL) ||
			UNLIKELY((devices_cl = malloc(sizeof(cl_device_id) * num_devices)) == NULL))
			goto exit_err;

		if (!clfw_get_device_ids(platforms[i]->platform_id, CL_DEVICE_TYPE_ALL, num_devices, devices_cl, NULL))
		{
			free(devices_cl);
			goto exit_err;
		}

		cl_device_info last_param;
		for (U64 j = 0; j < num_devices; j++)
		{
			ClDevice dev;
			
			dev = malloc(sizeof(struct s_cl_device));
			platforms[i]->devices[j] = dev;
			ft_bzero(dev, sizeof(struct s_cl_device));
			dev->ref = 1;
			dev->device_id = devices_cl[j];
			if (
				get_device_param(&last_param, dev->device_id, CL_DEVICE_TYPE, &dev->type, sizeof(dev->type)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_COMPUTE_UNITS, &dev->compute_units, sizeof(dev->compute_units)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, dev->max_work_item_size, sizeof(dev->max_work_item_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, &dev->max_work_group_size, sizeof(dev->max_work_group_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_CLOCK_FREQUENCY, &dev->clock_freq, sizeof(dev->clock_freq)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_ADDRESS_BITS, &dev->address_bits, sizeof(dev->address_bits)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_MEM_ALLOC_SIZE, &dev->max_mem_alloc, sizeof(dev->max_mem_alloc)) == NULL ||
				(dev->il_version = get_device_param(&last_param, dev->device_id, CL_DEVICE_IL_VERSION, NULL, 0)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_PARAMETER_SIZE, &dev->max_param_size, sizeof(dev->max_param_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_GLOBAL_MEM_CACHE_TYPE, &dev->mem_cache_type, sizeof(dev->mem_cache_type)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, &dev->global_mem_cache_line_size, sizeof(dev->global_mem_cache_line_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, &dev->global_mem_cache_size, sizeof(dev->global_mem_cache_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_GLOBAL_MEM_SIZE, &dev->global_mem_size, sizeof(dev->global_mem_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, &dev->max_constant_buffer_size, sizeof(dev->max_constant_buffer_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_CONSTANT_ARGS, &dev->max_constant, sizeof(dev->max_constant)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_MAX_GLOBAL_VARIABLE_SIZE, &dev->max_global_variable_size, sizeof(dev->max_global_variable_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_GLOBAL_VARIABLE_PREFERRED_TOTAL_SIZE, &dev->global_variable_prefered_total_size, sizeof(dev->global_variable_prefered_total_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_LOCAL_MEM_TYPE, &dev->local_mem_type, sizeof(dev->local_mem_type)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_LOCAL_MEM_SIZE, &dev->local_mem_size, sizeof(dev->local_mem_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_ERROR_CORRECTION_SUPPORT, &dev->mem_error_correction, sizeof(dev->mem_error_correction)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_HOST_UNIFIED_MEMORY, &dev->unified_memory, sizeof(dev->unified_memory)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_ENDIAN_LITTLE, &dev->endian, sizeof(dev->endian)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_AVAILABLE, &dev->available, sizeof(dev->available)) == NULL ||
				(dev->builtin_kernels = get_device_param(&last_param, dev->device_id, CL_DEVICE_BUILT_IN_KERNELS, NULL, 0)) == NULL ||
				(dev->name = get_device_param(&last_param, dev->device_id, CL_DEVICE_NAME, NULL, 0)) == NULL ||
				(dev->vendor = get_device_param(&last_param, dev->device_id, CL_DEVICE_VENDOR, NULL, 0)) == NULL ||
				(dev->driver_version = get_device_param(&last_param, dev->device_id, CL_DRIVER_VERSION, NULL, 0)) == NULL ||
				(dev->version = get_device_param(&last_param, dev->device_id, CL_DEVICE_VERSION, NULL, 0)) == NULL ||
				(dev->c_version = get_device_param(&last_param, dev->device_id, CL_DEVICE_OPENCL_C_VERSION, NULL, 0)) == NULL ||
				(dev->extensions = get_device_param(&last_param, dev->device_id, CL_DEVICE_EXTENSIONS, NULL, 0)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_PRINTF_BUFFER_SIZE, &dev->printf_buf_size, sizeof(dev->printf_buf_size)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_SVM_CAPABILITIES, &dev->svm_capabilities, sizeof(dev->svm_capabilities)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_PREFERRED_PLATFORM_ATOMIC_ALIGNMENT, &dev->prefered_platform_atm_alignement, sizeof(dev->prefered_platform_atm_alignement)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_PREFERRED_GLOBAL_ATOMIC_ALIGNMENT, &dev->prefered_global_atm_alignement, sizeof(dev->prefered_global_atm_alignement)) == NULL ||
				get_device_param(&last_param, dev->device_id, CL_DEVICE_PREFERRED_LOCAL_ATOMIC_ALIGNMENT, &dev->prefered_local_atm_alignement, sizeof(dev->prefered_local_atm_alignement)) == NULL)
			// get_device_param(&last_param, dev->device_id, CL_DEVICE_ATOMIC_MEMORY_CAPABILITIES, &dev->atm_capabilities, sizeof(dev->atm_capabilities)) == NULL ||
			// get_device_param(&last_param, dev->device_id, CL_DEVICE_GENERIC_ADDRESS_SPACE_SUPPORT, &dev->supports_generic_addr_space, sizeof(dev->supports_generic_addr_space)) == NULL)
			{
				// TODO: ca devrait pas etre grave de crash ici, et un crash ne devrait pas empecher de recup le reste des données
				ft_printf("get_device_param failed at %#x:%s\n", last_param, device_params_names[last_param - 0x1000]);
				exit(1);
			}
		}
		free(devices_cl);
		platforms[i]->devices_cnt = num_devices;
	}

	free(platforms_cl);

	*platforms_cnt = num_platforms;
	return platforms;

exit_err:
	for (U64 i = 0; i < num_platforms; i++)
	{
		free(platforms[i]->devices);
		free(platforms[i]->extensions);
		free(platforms[i]->name);
		free(platforms[i]->vendor);
		free(platforms[i]->version);
	}
	free(platforms);
	free(platforms_cl);
	return NULL;
}

bool clfw_init_device_ctx(ClDevice device)
{
	if (UNLIKELY(device->ctx != NULL))
		return TRUE;
	return (device->ctx = clfw_create_context(NULL, 1, &device->device_id, NULL, NULL)) == NULL;
}

bool clfw_init_device_queue(ClDevice device)
{
	if (UNLIKELY(device->queue != NULL))
		return TRUE;
	return (device->queue = clfw_create_command_queue(device->ctx, device->device_id, 0)) == NULL;
}

void clfw_ref_platform(ClPlatform platform)
{
	platform->ref++;
}

void clfw_deref_platform(ClPlatform platform)
{
	if (platform->ref == 0)
		return;
	platform->ref--;
	if (platform->ref == 0)
		clfw_free_platform(platform);
}

void clfw_free_platform(ClPlatform platform)
{
	free(platform->extensions);
	free(platform->name);
	free(platform->vendor);
	free(platform->version);

	for (U64 i = 0; i < platform->devices_cnt; i++)
		clfw_deref_device(platform->devices[i]);
	free(platform->devices);
}

void clfw_ref_device(ClDevice device)
{
	device->ref++;
}

void clfw_deref_device(ClDevice device)
{
	if (device->ref == 0)
		return;
	device->ref--;
	if (device->ref == 0)
		clfw_free_device(device);
}

void clfw_free_device(ClDevice device)
{
	if (device->ctx)
		clfw_release_context(device->ctx);
	if (device->device_id)
		clfw_release_device(device->device_id);

	free(device->builtin_kernels);
	free(device->name);
	free(device->vendor);
	free(device->driver_version);
	free(device->version);
	free(device->c_version);
	free(device->extensions);
}
