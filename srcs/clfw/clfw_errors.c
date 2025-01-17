/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clfw_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:32:37 by reclaire          #+#    #+#             */
/*   Updated: 2024/10/02 03:41:28 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clfw_private.h"
#include "libft/io.h"

S32 clfw_last_error = 0;
S32 clfw_last_call = 0;

const_string clfw_error_titles[] = {
	"SUCCESS",
	"CL_DEVICE_NOT_FOUND",
	"CL_DEVICE_NOT_AVAILABLE",
	"CL_COMPILER_NOT_AVAILABLE",
	"CL_MEM_OBJECT_ALLOCATION_FAILURE",
	"CL_OUT_OF_RESOURCES",
	"CL_OUT_OF_HOST_MEMORY",
	"CL_PROFILING_INFO_NOT_AVAILABLE",
	"CL_MEM_COPY_OVERLAP",
	"CL_IMAGE_FORMAT_MISMATCH",
	"CL_IMAGE_FORMAT_NOT_SUPPORTED",
	"CL_BUILD_PROGRAM_FAILURE",
	"CL_MAP_FAILURE",
	"CL_MISALIGNED_SUB_BUFFER_OFFSET",
	"CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST",
	"CL_COMPILE_PROGRAM_FAILURE",
	"CL_LINKER_NOT_AVAILABLE",
	"CL_LINK_PROGRAM_FAILURE",
	"CL_DEVICE_PARTITION_FAILED",
	"CL_KERNEL_ARG_INFO_NOT_AVAILABLE",
	"CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR", "CL_UNKNOWN_ERROR",
	"CL_INVALID_VALUE",
	"CL_INVALID_DEVICE_TYPE",
	"CL_INVALID_PLATFORM",
	"CL_INVALID_DEVICE",
	"CL_INVALID_CONTEXT",
	"CL_INVALID_QUEUE_PROPERTIES",
	"CL_INVALID_COMMAND_QUEUE",
	"CL_INVALID_HOST_PTR",
	"CL_INVALID_MEM_OBJECT",
	"CL_INVALID_IMAGE_FORMAT_DESCRIPTOR",
	"CL_INVALID_IMAGE_SIZE",
	"CL_INVALID_SAMPLER",
	"CL_INVALID_BINARY",
	"CL_INVALID_BUILD_OPTIONS",
	"CL_INVALID_PROGRAM",
	"CL_INVALID_PROGRAM_EXECUTABLE",
	"CL_INVALID_KERNEL_NAME",
	"CL_INVALID_KERNEL_DEFINITION",
	"CL_INVALID_KERNEL",
	"CL_INVALID_ARG_INDEX",
	"CL_INVALID_ARG_VALUE",
	"CL_INVALID_ARG_SIZE",
	"CL_INVALID_KERNEL_ARGS",
	"CL_INVALID_WORK_DIMENSION",
	"CL_INVALID_WORK_GROUP_SIZE",
	"CL_INVALID_WORK_ITEM_SIZE",
	"CL_INVALID_GLOBAL_OFFSET",
	"CL_INVALID_EVENT_WAIT_LIST",
	"CL_INVALID_EVENT",
	"CL_INVALID_OPERATION",
	"CL_INVALID_GL_OBJECT",
	"CL_INVALID_BUFFER_SIZE",
	"CL_INVALID_MIP_LEVEL",
	"CL_INVALID_GLOBAL_WORK_SIZE",
	"CL_INVALID_PROPERTY",
	"CL_INVALID_IMAGE_DESCRIPTOR",
	"CL_INVALID_COMPILER_OPTIONS",
	"CL_INVALID_LINKER_OPTIONS",
	"CL_INVALID_DEVICE_PARTITION_COUNT",
	"CL_INVALID_PIPE_SIZE",
	"CL_INVALID_DEVICE_QUEUE",
	"CL_INVALID_SPEC_ID",
	"CL_MAX_SIZE_RESTRICTION_EXCEEDED",
	// 73
};

S32 clfw_get_last_error()
{
	return clfw_last_error;
}

S32 clfw_get_last_call()
{
	return clfw_last_call;
}

const_string clfw_get_error_title(S32 err)
{
	err = -err;
	if (err < 0 || (U32)err >= (sizeof(clfw_error_titles) / sizeof(clfw_error_titles[0])))
		return "CL_UNKNOWN_ERROR";
	return clfw_error_titles[err];
}

const_string clfw_get_call_title(S32 call)
{
	return clfw_func_calls[call];
}

const_string clfw_get_last_error_title()
{
	return clfw_get_error_title(clfw_get_last_error());
}

const_string clfw_get_last_call_title()
{
	return clfw_get_call_title(clfw_get_last_call());
}
