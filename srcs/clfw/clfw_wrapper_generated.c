/*
Auto generated OpenCL wrapper from 'auto_gen_wrapper.py'
*/

#include "clfw_private.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#undef clfw_error
#undef clfw_warn
#undef clfw_info
#undef clfw_debug

#define clfw_error(...) (log_error)(FT_IFDEBUG(_file, _line,) clfw_tag, __VA_ARGS__)
#define clfw_warn(...) (log_warn)(FT_IFDEBUG(_file, _line,) clfw_tag, __VA_ARGS__)
#define clfw_info(...) (log_info)(FT_IFDEBUG(_file, _line,) clfw_tag, __VA_ARGS__)
#define clfw_debug(...) (log_debug)(FT_IFDEBUG(_file, _line,) clfw_tag, __VA_ARGS__)

bool (clfw_get_platform_ids)(CLFW_DEBUG_ARGS(U32 num_entries, cl_platform_id *platforms, U32 *num_platforms))
{
	S32 _err;

	_err = clGetPlatformIDs(num_entries, platforms, num_platforms);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETPLATFORMIDS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETPLATFORMIDS], _CLFW_CALL_CLGETPLATFORMIDS, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_platform_info)(CLFW_DEBUG_ARGS(cl_platform_id platform, cl_platform_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetPlatformInfo(platform, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETPLATFORMINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETPLATFORMINFO], _CLFW_CALL_CLGETPLATFORMINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_device_ids)(CLFW_DEBUG_ARGS(cl_platform_id platform, cl_device_type device_type, U32 num_entries, cl_device_id *devices, U32 *num_devices))
{
	S32 _err;

	_err = clGetDeviceIDs(platform, device_type, num_entries, devices, num_devices);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETDEVICEIDS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETDEVICEIDS], _CLFW_CALL_CLGETDEVICEIDS, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_device_info)(CLFW_DEBUG_ARGS(cl_device_id device, cl_device_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetDeviceInfo(device, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETDEVICEINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETDEVICEINFO], _CLFW_CALL_CLGETDEVICEINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_create_sub_devices)(CLFW_DEBUG_ARGS(cl_device_id in_device, const cl_device_partition_property *properties, U32 num_devices, cl_device_id *out_devices, U32 *num_devices_ret))
{
	S32 _err;

	_err = clCreateSubDevices(in_device, properties, num_devices, out_devices, num_devices_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATESUBDEVICES;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATESUBDEVICES], _CLFW_CALL_CLCREATESUBDEVICES, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_retain_device)(CLFW_DEBUG_ARGS(cl_device_id device))
{
	S32 _err;

	_err = clRetainDevice(device);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINDEVICE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINDEVICE], _CLFW_CALL_CLRETAINDEVICE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_device)(CLFW_DEBUG_ARGS(cl_device_id device))
{
	S32 _err;

	_err = clReleaseDevice(device);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASEDEVICE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASEDEVICE], _CLFW_CALL_CLRELEASEDEVICE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_default_device_command_queue)(CLFW_DEBUG_ARGS(cl_context context, cl_device_id device, cl_command_queue command_queue))
{
	S32 _err;

	_err = clSetDefaultDeviceCommandQueue(context, device, command_queue);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETDEFAULTDEVICECOMMANDQUEUE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETDEFAULTDEVICECOMMANDQUEUE], _CLFW_CALL_CLSETDEFAULTDEVICECOMMANDQUEUE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_device_and_host_timer)(CLFW_DEBUG_ARGS(cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp))
{
	S32 _err;

	_err = clGetDeviceAndHostTimer(device, device_timestamp, host_timestamp);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETDEVICEANDHOSTTIMER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETDEVICEANDHOSTTIMER], _CLFW_CALL_CLGETDEVICEANDHOSTTIMER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_host_timer)(CLFW_DEBUG_ARGS(cl_device_id device, U64 *host_timestamp))
{
	S32 _err;

	_err = clGetHostTimer(device, host_timestamp);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETHOSTTIMER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETHOSTTIMER], _CLFW_CALL_CLGETHOSTTIMER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_context (clfw_create_context)(CLFW_DEBUG_ARGS(const cl_context_properties *properties, U32 num_devices, const cl_device_id *devices, void (*pfn_notify)(const char * errinfo, const void * private_info, U64 cb, void * user_data), void *user_data))
{
	S32 _err;
	cl_context _ret;

	_ret = clCreateContext(properties, num_devices, devices, pfn_notify, user_data, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATECONTEXT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATECONTEXT], _CLFW_CALL_CLCREATECONTEXT, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_context (clfw_create_context_from_type)(CLFW_DEBUG_ARGS(const cl_context_properties *properties, cl_device_type device_type, void (*pfn_notify)(const char * errinfo, const void * private_info, U64 cb, void * user_data), void *user_data))
{
	S32 _err;
	cl_context _ret;

	_ret = clCreateContextFromType(properties, device_type, pfn_notify, user_data, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATECONTEXTFROMTYPE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATECONTEXTFROMTYPE], _CLFW_CALL_CLCREATECONTEXTFROMTYPE, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_retain_context)(CLFW_DEBUG_ARGS(cl_context context))
{
	S32 _err;

	_err = clRetainContext(context);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINCONTEXT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINCONTEXT], _CLFW_CALL_CLRETAINCONTEXT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_context)(CLFW_DEBUG_ARGS(cl_context context))
{
	S32 _err;

	_err = clReleaseContext(context);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASECONTEXT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASECONTEXT], _CLFW_CALL_CLRELEASECONTEXT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_context_info)(CLFW_DEBUG_ARGS(cl_context context, cl_context_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetContextInfo(context, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETCONTEXTINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETCONTEXTINFO], _CLFW_CALL_CLGETCONTEXTINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_context_destructor_callback)(CLFW_DEBUG_ARGS(cl_context context, void (*pfn_notify)(cl_context context, void * user_data), void* user_data))
{
	S32 _err;

	_err = clSetContextDestructorCallback(context, pfn_notify, user_data);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETCONTEXTDESTRUCTORCALLBACK;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETCONTEXTDESTRUCTORCALLBACK], _CLFW_CALL_CLSETCONTEXTDESTRUCTORCALLBACK, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_command_queue (clfw_create_command_queue_with_properties)(CLFW_DEBUG_ARGS(cl_context context, cl_device_id device, const cl_queue_properties *properties))
{
	S32 _err;
	cl_command_queue _ret;

	_ret = clCreateCommandQueueWithProperties(context, device, properties, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATECOMMANDQUEUEWITHPROPERTIES;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATECOMMANDQUEUEWITHPROPERTIES], _CLFW_CALL_CLCREATECOMMANDQUEUEWITHPROPERTIES, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_retain_command_queue)(CLFW_DEBUG_ARGS(cl_command_queue command_queue))
{
	S32 _err;

	_err = clRetainCommandQueue(command_queue);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINCOMMANDQUEUE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINCOMMANDQUEUE], _CLFW_CALL_CLRETAINCOMMANDQUEUE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_command_queue)(CLFW_DEBUG_ARGS(cl_command_queue command_queue))
{
	S32 _err;

	_err = clReleaseCommandQueue(command_queue);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASECOMMANDQUEUE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASECOMMANDQUEUE], _CLFW_CALL_CLRELEASECOMMANDQUEUE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_command_queue_info)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_command_queue_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetCommandQueueInfo(command_queue, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETCOMMANDQUEUEINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETCOMMANDQUEUEINFO], _CLFW_CALL_CLGETCOMMANDQUEUEINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_mem (clfw_create_buffer)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, U64 size, void *host_ptr))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreateBuffer(context, flags, size, host_ptr, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEBUFFER], _CLFW_CALL_CLCREATEBUFFER, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_mem (clfw_create_sub_buffer)(CLFW_DEBUG_ARGS(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void *buffer_create_info))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreateSubBuffer(buffer, flags, buffer_create_type, buffer_create_info, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATESUBBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATESUBBUFFER], _CLFW_CALL_CLCREATESUBBUFFER, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_mem (clfw_create_image)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, const cl_image_desc *image_desc, void *host_ptr))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreateImage(context, flags, image_format, image_desc, host_ptr, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEIMAGE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEIMAGE], _CLFW_CALL_CLCREATEIMAGE, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_mem (clfw_create_pipe)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, U32 pipe_packet_size, U32 pipe_max_packets, const cl_pipe_properties *properties))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreatePipe(context, flags, pipe_packet_size, pipe_max_packets, properties, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEPIPE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEPIPE], _CLFW_CALL_CLCREATEPIPE, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_mem (clfw_create_buffer_with_properties)(CLFW_DEBUG_ARGS(cl_context context, const cl_mem_properties *properties, cl_mem_flags flags, U64 size, void *host_ptr))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreateBufferWithProperties(context, properties, flags, size, host_ptr, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEBUFFERWITHPROPERTIES;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEBUFFERWITHPROPERTIES], _CLFW_CALL_CLCREATEBUFFERWITHPROPERTIES, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_mem (clfw_create_image_with_properties)(CLFW_DEBUG_ARGS(cl_context context, const cl_mem_properties *properties, cl_mem_flags flags, const cl_image_format *image_format, const cl_image_desc *image_desc, void *host_ptr))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreateImageWithProperties(context, properties, flags, image_format, image_desc, host_ptr, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEIMAGEWITHPROPERTIES;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEIMAGEWITHPROPERTIES], _CLFW_CALL_CLCREATEIMAGEWITHPROPERTIES, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_retain_mem_object)(CLFW_DEBUG_ARGS(cl_mem memobj))
{
	S32 _err;

	_err = clRetainMemObject(memobj);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINMEMOBJECT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINMEMOBJECT], _CLFW_CALL_CLRETAINMEMOBJECT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_mem_object)(CLFW_DEBUG_ARGS(cl_mem memobj))
{
	S32 _err;

	_err = clReleaseMemObject(memobj);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASEMEMOBJECT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASEMEMOBJECT], _CLFW_CALL_CLRELEASEMEMOBJECT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_supported_image_formats)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, U32 num_entries, cl_image_format *image_formats, U32 *num_image_formats))
{
	S32 _err;

	_err = clGetSupportedImageFormats(context, flags, image_type, num_entries, image_formats, num_image_formats);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETSUPPORTEDIMAGEFORMATS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETSUPPORTEDIMAGEFORMATS], _CLFW_CALL_CLGETSUPPORTEDIMAGEFORMATS, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_mem_object_info)(CLFW_DEBUG_ARGS(cl_mem memobj, cl_mem_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetMemObjectInfo(memobj, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETMEMOBJECTINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETMEMOBJECTINFO], _CLFW_CALL_CLGETMEMOBJECTINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_image_info)(CLFW_DEBUG_ARGS(cl_mem image, cl_image_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetImageInfo(image, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETIMAGEINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETIMAGEINFO], _CLFW_CALL_CLGETIMAGEINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_pipe_info)(CLFW_DEBUG_ARGS(cl_mem pipe, cl_pipe_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetPipeInfo(pipe, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETPIPEINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETPIPEINFO], _CLFW_CALL_CLGETPIPEINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_mem_object_destructor_callback)(CLFW_DEBUG_ARGS(cl_mem memobj, void (*pfn_notify)(cl_mem memobj, void * user_data), void *user_data))
{
	S32 _err;

	_err = clSetMemObjectDestructorCallback(memobj, pfn_notify, user_data);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETMEMOBJECTDESTRUCTORCALLBACK;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETMEMOBJECTDESTRUCTORCALLBACK], _CLFW_CALL_CLSETMEMOBJECTDESTRUCTORCALLBACK, clfw_get_error_title(_err), _err);
	return _err == 0;
}

void * (clfw_svm_alloc)(CLFW_DEBUG_ARGS(cl_context context, cl_svm_mem_flags flags, U64 size, U32 alignment))
{
	S32 _err;
	void *_ret;

	_ret = clSVMAlloc(context, flags, size, alignment);
	if (UNLIKELY(_ret == NULL))
		_err = CL_OUT_OF_HOST_MEMORY;
	else
		_err = 0;
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSVMALLOC;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSVMALLOC], _CLFW_CALL_CLSVMALLOC, clfw_get_error_title(_err), _err);
	return _ret;

}

bool (clfw_svm_free)(CLFW_DEBUG_ARGS(cl_context context, void *svm_pointer))
{
	FT_IFDEBUG((void)_file; (void)_line);
	clSVMFree(context, svm_pointer);	clfw_last_error = 0;
	clfw_last_call = _CLFW_CALL_CLSVMFREE;
	return TRUE;
}

cl_sampler (clfw_create_sampler_with_properties)(CLFW_DEBUG_ARGS(cl_context context, const cl_sampler_properties *sampler_properties))
{
	S32 _err;
	cl_sampler _ret;

	_ret = clCreateSamplerWithProperties(context, sampler_properties, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATESAMPLERWITHPROPERTIES;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATESAMPLERWITHPROPERTIES], _CLFW_CALL_CLCREATESAMPLERWITHPROPERTIES, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_retain_sampler)(CLFW_DEBUG_ARGS(cl_sampler sampler))
{
	S32 _err;

	_err = clRetainSampler(sampler);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINSAMPLER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINSAMPLER], _CLFW_CALL_CLRETAINSAMPLER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_sampler)(CLFW_DEBUG_ARGS(cl_sampler sampler))
{
	S32 _err;

	_err = clReleaseSampler(sampler);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASESAMPLER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASESAMPLER], _CLFW_CALL_CLRELEASESAMPLER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_sampler_info)(CLFW_DEBUG_ARGS(cl_sampler sampler, cl_sampler_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetSamplerInfo(sampler, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETSAMPLERINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETSAMPLERINFO], _CLFW_CALL_CLGETSAMPLERINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_program (clfw_create_program_with_source)(CLFW_DEBUG_ARGS(cl_context context, U32 count, const char ** strings, const U64 *lengths))
{
	S32 _err;
	cl_program _ret;

	_ret = clCreateProgramWithSource(context, count, strings, lengths, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEPROGRAMWITHSOURCE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEPROGRAMWITHSOURCE], _CLFW_CALL_CLCREATEPROGRAMWITHSOURCE, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_program (clfw_create_program_with_binary)(CLFW_DEBUG_ARGS(cl_context context, U32 num_devices, const cl_device_id *device_list, const U64 *lengths, const unsigned char ** binaries, S32 *binary_status))
{
	S32 _err;
	cl_program _ret;

	_ret = clCreateProgramWithBinary(context, num_devices, device_list, lengths, binaries, binary_status, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEPROGRAMWITHBINARY;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEPROGRAMWITHBINARY], _CLFW_CALL_CLCREATEPROGRAMWITHBINARY, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_program (clfw_create_program_with_built_in_kernels)(CLFW_DEBUG_ARGS(cl_context context, U32 num_devices, const cl_device_id *device_list, const char *kernel_names))
{
	S32 _err;
	cl_program _ret;

	_ret = clCreateProgramWithBuiltInKernels(context, num_devices, device_list, kernel_names, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEPROGRAMWITHBUILTINKERNELS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEPROGRAMWITHBUILTINKERNELS], _CLFW_CALL_CLCREATEPROGRAMWITHBUILTINKERNELS, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_program (clfw_create_program_with_il)(CLFW_DEBUG_ARGS(cl_context context, const void* il, U64 length))
{
	S32 _err;
	cl_program _ret;

	_ret = clCreateProgramWithIL(context, il, length, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEPROGRAMWITHIL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEPROGRAMWITHIL], _CLFW_CALL_CLCREATEPROGRAMWITHIL, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_retain_program)(CLFW_DEBUG_ARGS(cl_program program))
{
	S32 _err;

	_err = clRetainProgram(program);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINPROGRAM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINPROGRAM], _CLFW_CALL_CLRETAINPROGRAM, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_program)(CLFW_DEBUG_ARGS(cl_program program))
{
	S32 _err;

	_err = clReleaseProgram(program);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASEPROGRAM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASEPROGRAM], _CLFW_CALL_CLRELEASEPROGRAM, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_build_program)(CLFW_DEBUG_ARGS(cl_program program, U32 num_devices, const cl_device_id *device_list, const char *options, void (*pfn_notify)(cl_program program, void * user_data), void *user_data))
{
	S32 _err;

	_err = clBuildProgram(program, num_devices, device_list, options, pfn_notify, user_data);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLBUILDPROGRAM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLBUILDPROGRAM], _CLFW_CALL_CLBUILDPROGRAM, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_compile_program)(CLFW_DEBUG_ARGS(cl_program program, U32 num_devices, const cl_device_id *device_list, const char *options, U32 num_input_headers, const cl_program *input_headers, const char ** header_include_names, void (*pfn_notify)(cl_program program, void * user_data), void *user_data))
{
	S32 _err;

	_err = clCompileProgram(program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCOMPILEPROGRAM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCOMPILEPROGRAM], _CLFW_CALL_CLCOMPILEPROGRAM, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_program (clfw_link_program)(CLFW_DEBUG_ARGS(cl_context context, U32 num_devices, const cl_device_id *device_list, const char *options, U32 num_input_programs, const cl_program *input_programs, void (*pfn_notify)(cl_program program, void * user_data), void *user_data))
{
	S32 _err;
	cl_program _ret;

	_ret = clLinkProgram(context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLLINKPROGRAM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLLINKPROGRAM], _CLFW_CALL_CLLINKPROGRAM, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_set_program_release_callback)(CLFW_DEBUG_ARGS(cl_program program, void (*pfn_notify)(cl_program program, void * user_data), void *user_data))
{
	S32 _err;

	_err = clSetProgramReleaseCallback(program, pfn_notify, user_data);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETPROGRAMRELEASECALLBACK;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETPROGRAMRELEASECALLBACK], _CLFW_CALL_CLSETPROGRAMRELEASECALLBACK, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_program_specialization_constant)(CLFW_DEBUG_ARGS(cl_program program, U32 spec_id, U64 spec_size, const void* spec_value))
{
	S32 _err;

	_err = clSetProgramSpecializationConstant(program, spec_id, spec_size, spec_value);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETPROGRAMSPECIALIZATIONCONSTANT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETPROGRAMSPECIALIZATIONCONSTANT], _CLFW_CALL_CLSETPROGRAMSPECIALIZATIONCONSTANT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_unload_platform_compiler)(CLFW_DEBUG_ARGS(cl_platform_id platform))
{
	S32 _err;

	_err = clUnloadPlatformCompiler(platform);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLUNLOADPLATFORMCOMPILER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLUNLOADPLATFORMCOMPILER], _CLFW_CALL_CLUNLOADPLATFORMCOMPILER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_program_info)(CLFW_DEBUG_ARGS(cl_program program, cl_program_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetProgramInfo(program, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETPROGRAMINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETPROGRAMINFO], _CLFW_CALL_CLGETPROGRAMINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_program_build_info)(CLFW_DEBUG_ARGS(cl_program program, cl_device_id device, cl_program_build_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetProgramBuildInfo(program, device, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETPROGRAMBUILDINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETPROGRAMBUILDINFO], _CLFW_CALL_CLGETPROGRAMBUILDINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_kernel (clfw_create_kernel)(CLFW_DEBUG_ARGS(cl_program program, const char *kernel_name))
{
	S32 _err;
	cl_kernel _ret;

	_ret = clCreateKernel(program, kernel_name, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEKERNEL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEKERNEL], _CLFW_CALL_CLCREATEKERNEL, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_create_kernels_in_program)(CLFW_DEBUG_ARGS(cl_program program, U32 num_kernels, cl_kernel *kernels, U32 *num_kernels_ret))
{
	S32 _err;

	_err = clCreateKernelsInProgram(program, num_kernels, kernels, num_kernels_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEKERNELSINPROGRAM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEKERNELSINPROGRAM], _CLFW_CALL_CLCREATEKERNELSINPROGRAM, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_kernel (clfw_clone_kernel)(CLFW_DEBUG_ARGS(cl_kernel source_kernel))
{
	S32 _err;
	cl_kernel _ret;

	_ret = clCloneKernel(source_kernel, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCLONEKERNEL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCLONEKERNEL], _CLFW_CALL_CLCLONEKERNEL, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_retain_kernel)(CLFW_DEBUG_ARGS(cl_kernel kernel))
{
	S32 _err;

	_err = clRetainKernel(kernel);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINKERNEL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINKERNEL], _CLFW_CALL_CLRETAINKERNEL, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_kernel)(CLFW_DEBUG_ARGS(cl_kernel kernel))
{
	S32 _err;

	_err = clReleaseKernel(kernel);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASEKERNEL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASEKERNEL], _CLFW_CALL_CLRELEASEKERNEL, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_kernel_arg)(CLFW_DEBUG_ARGS(cl_kernel kernel, U32 arg_index, U64 arg_size, const void *arg_value))
{
	S32 _err;

	_err = clSetKernelArg(kernel, arg_index, arg_size, arg_value);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETKERNELARG;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETKERNELARG], _CLFW_CALL_CLSETKERNELARG, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_kernel_arg_svm_pointer)(CLFW_DEBUG_ARGS(cl_kernel kernel, U32 arg_index, const void *arg_value))
{
	S32 _err;

	_err = clSetKernelArgSVMPointer(kernel, arg_index, arg_value);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETKERNELARGSVMPOINTER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETKERNELARGSVMPOINTER], _CLFW_CALL_CLSETKERNELARGSVMPOINTER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_kernel_exec_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_kernel_exec_info param_name, U64 param_value_size, const void *param_value))
{
	S32 _err;

	_err = clSetKernelExecInfo(kernel, param_name, param_value_size, param_value);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETKERNELEXECINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETKERNELEXECINFO], _CLFW_CALL_CLSETKERNELEXECINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_kernel_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_kernel_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetKernelInfo(kernel, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETKERNELINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETKERNELINFO], _CLFW_CALL_CLGETKERNELINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_kernel_arg_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, U32 arg_indx, cl_kernel_arg_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetKernelArgInfo(kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETKERNELARGINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETKERNELARGINFO], _CLFW_CALL_CLGETKERNELARGINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_kernel_work_group_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetKernelWorkGroupInfo(kernel, device, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETKERNELWORKGROUPINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETKERNELWORKGROUPINFO], _CLFW_CALL_CLGETKERNELWORKGROUPINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_kernel_sub_group_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, U64 input_value_size, const void* input_value, U64 param_value_size, void* param_value, size_t* param_value_size_ret))
{
	S32 _err;

	_err = clGetKernelSubGroupInfo(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETKERNELSUBGROUPINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETKERNELSUBGROUPINFO], _CLFW_CALL_CLGETKERNELSUBGROUPINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_wait_for_events)(CLFW_DEBUG_ARGS(U32 num_events, const cl_event *event_list))
{
	S32 _err;

	_err = clWaitForEvents(num_events, event_list);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLWAITFOREVENTS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLWAITFOREVENTS], _CLFW_CALL_CLWAITFOREVENTS, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_event_info)(CLFW_DEBUG_ARGS(cl_event event, cl_event_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetEventInfo(event, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETEVENTINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETEVENTINFO], _CLFW_CALL_CLGETEVENTINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_event (clfw_create_user_event)(CLFW_DEBUG_ARGS(cl_context context))
{
	S32 _err;
	cl_event _ret;

	_ret = clCreateUserEvent(context, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEUSEREVENT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEUSEREVENT], _CLFW_CALL_CLCREATEUSEREVENT, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_retain_event)(CLFW_DEBUG_ARGS(cl_event event))
{
	S32 _err;

	_err = clRetainEvent(event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRETAINEVENT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRETAINEVENT], _CLFW_CALL_CLRETAINEVENT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_release_event)(CLFW_DEBUG_ARGS(cl_event event))
{
	S32 _err;

	_err = clReleaseEvent(event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLRELEASEEVENT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLRELEASEEVENT], _CLFW_CALL_CLRELEASEEVENT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_user_event_status)(CLFW_DEBUG_ARGS(cl_event event, S32 execution_status))
{
	S32 _err;

	_err = clSetUserEventStatus(event, execution_status);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETUSEREVENTSTATUS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETUSEREVENTSTATUS], _CLFW_CALL_CLSETUSEREVENTSTATUS, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_set_event_callback)(CLFW_DEBUG_ARGS(cl_event event, S32 command_exec_callback_type, void (*pfn_notify)(cl_event event, S32 event_command_status, void * user_data), void *user_data))
{
	S32 _err;

	_err = clSetEventCallback(event, command_exec_callback_type, pfn_notify, user_data);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETEVENTCALLBACK;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETEVENTCALLBACK], _CLFW_CALL_CLSETEVENTCALLBACK, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_get_event_profiling_info)(CLFW_DEBUG_ARGS(cl_event event, cl_profiling_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret))
{
	S32 _err;

	_err = clGetEventProfilingInfo(event, param_name, param_value_size, param_value, param_value_size_ret);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETEVENTPROFILINGINFO;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETEVENTPROFILINGINFO], _CLFW_CALL_CLGETEVENTPROFILINGINFO, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_flush)(CLFW_DEBUG_ARGS(cl_command_queue command_queue))
{
	S32 _err;

	_err = clFlush(command_queue);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLFLUSH;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLFLUSH], _CLFW_CALL_CLFLUSH, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_finish)(CLFW_DEBUG_ARGS(cl_command_queue command_queue))
{
	S32 _err;

	_err = clFinish(command_queue);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLFINISH;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLFINISH], _CLFW_CALL_CLFINISH, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_read_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_read, U64 offset, U64 size, void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueReadBuffer(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEREADBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEREADBUFFER], _CLFW_CALL_CLENQUEUEREADBUFFER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_read_buffer_rect)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_read, const U64 *buffer_origin, const U64 *host_origin, const U64 *region, U64 buffer_row_pitch, U64 buffer_slice_pitch, U64 host_row_pitch, U64 host_slice_pitch, void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueReadBufferRect(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEREADBUFFERRECT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEREADBUFFERRECT], _CLFW_CALL_CLENQUEUEREADBUFFERRECT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_write_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_write, U64 offset, U64 size, const void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueWriteBuffer(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEWRITEBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEWRITEBUFFER], _CLFW_CALL_CLENQUEUEWRITEBUFFER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_write_buffer_rect)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_write, const U64 *buffer_origin, const U64 *host_origin, const U64 *region, U64 buffer_row_pitch, U64 buffer_slice_pitch, U64 host_row_pitch, U64 host_slice_pitch, const void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueWriteBufferRect(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEWRITEBUFFERRECT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEWRITEBUFFERRECT], _CLFW_CALL_CLENQUEUEWRITEBUFFERRECT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_fill_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, const void *pattern, U64 pattern_size, U64 offset, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueFillBuffer(command_queue, buffer, pattern, pattern_size, offset, size, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEFILLBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEFILLBUFFER], _CLFW_CALL_CLENQUEUEFILLBUFFER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_copy_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, U64 src_offset, U64 dst_offset, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueCopyBuffer(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUECOPYBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUECOPYBUFFER], _CLFW_CALL_CLENQUEUECOPYBUFFER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_copy_buffer_rect)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const U64 *src_origin, const U64 *dst_origin, const U64 *region, U64 src_row_pitch, U64 src_slice_pitch, U64 dst_row_pitch, U64 dst_slice_pitch, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueCopyBufferRect(command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUECOPYBUFFERRECT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUECOPYBUFFERRECT], _CLFW_CALL_CLENQUEUECOPYBUFFERRECT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_read_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, bool blocking_read, const U64 *origin, const U64 *region, U64 row_pitch, U64 slice_pitch, void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueReadImage(command_queue, image, blocking_read, origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEREADIMAGE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEREADIMAGE], _CLFW_CALL_CLENQUEUEREADIMAGE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_write_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, bool blocking_write, const U64 *origin, const U64 *region, U64 input_row_pitch, U64 input_slice_pitch, const void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueWriteImage(command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEWRITEIMAGE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEWRITEIMAGE], _CLFW_CALL_CLENQUEUEWRITEIMAGE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_fill_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, const void *fill_color, const U64 *origin, const U64 *region, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueFillImage(command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEFILLIMAGE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEFILLIMAGE], _CLFW_CALL_CLENQUEUEFILLIMAGE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_copy_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const U64 *src_origin, const U64 *dst_origin, const U64 *region, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueCopyImage(command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUECOPYIMAGE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUECOPYIMAGE], _CLFW_CALL_CLENQUEUECOPYIMAGE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_copy_image_to_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const U64 *src_origin, const U64 *region, U64 dst_offset, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueCopyImageToBuffer(command_queue, src_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUECOPYIMAGETOBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUECOPYIMAGETOBUFFER], _CLFW_CALL_CLENQUEUECOPYIMAGETOBUFFER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_copy_buffer_to_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, U64 src_offset, const U64 *dst_origin, const U64 *region, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueCopyBufferToImage(command_queue, src_buffer, dst_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUECOPYBUFFERTOIMAGE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUECOPYBUFFERTOIMAGE], _CLFW_CALL_CLENQUEUECOPYBUFFERTOIMAGE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

void * (clfw_enqueue_map_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_map, cl_map_flags map_flags, U64 offset, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;
	void * _ret;

	_ret = clEnqueueMapBuffer(command_queue, buffer, blocking_map, map_flags, offset, size, num_events_in_wait_list, event_wait_list, event, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEMAPBUFFER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEMAPBUFFER], _CLFW_CALL_CLENQUEUEMAPBUFFER, clfw_get_error_title(_err), _err);
	return _ret;
}

void * (clfw_enqueue_map_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, bool blocking_map, cl_map_flags map_flags, const U64 *origin, const U64 *region, U64 *image_row_pitch, U64 *image_slice_pitch, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;
	void * _ret;

	_ret = clEnqueueMapImage(command_queue, image, blocking_map, map_flags, origin, region, image_row_pitch, image_slice_pitch, num_events_in_wait_list, event_wait_list, event, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEMAPIMAGE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEMAPIMAGE], _CLFW_CALL_CLENQUEUEMAPIMAGE, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_enqueue_unmap_mem_object)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem memobj, void *mapped_ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueUnmapMemObject(command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEUNMAPMEMOBJECT;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEUNMAPMEMOBJECT], _CLFW_CALL_CLENQUEUEUNMAPMEMOBJECT, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_migrate_mem_objects)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_mem_objects, const cl_mem *mem_objects, cl_mem_migration_flags flags, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueMigrateMemObjects(command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEMIGRATEMEMOBJECTS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEMIGRATEMEMOBJECTS], _CLFW_CALL_CLENQUEUEMIGRATEMEMOBJECTS, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_nd_range_kernel)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_kernel kernel, U32 work_dim, const U64 *global_work_offset, const U64 *global_work_size, const U64 *local_work_size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueNDRangeKernel(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUENDRANGEKERNEL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUENDRANGEKERNEL], _CLFW_CALL_CLENQUEUENDRANGEKERNEL, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_native_kernel)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, void (*user_func)(void *), void *args, U64 cb_args, U32 num_mem_objects, const cl_mem *mem_list, const void ** args_mem_loc, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueNativeKernel(command_queue, user_func, args, cb_args, num_mem_objects, mem_list, args_mem_loc, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUENATIVEKERNEL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUENATIVEKERNEL], _CLFW_CALL_CLENQUEUENATIVEKERNEL, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_marker_with_wait_list)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueMarkerWithWaitList(command_queue, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEMARKERWITHWAITLIST;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEMARKERWITHWAITLIST], _CLFW_CALL_CLENQUEUEMARKERWITHWAITLIST, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_barrier_with_wait_list)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueBarrierWithWaitList(command_queue, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEBARRIERWITHWAITLIST;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEBARRIERWITHWAITLIST], _CLFW_CALL_CLENQUEUEBARRIERWITHWAITLIST, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_svm_free)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_svm_pointers, void *svm_pointers [], void (*pfn_free_func)(cl_command_queue queue, U32 num_svm_pointers, void * svm_pointers [], void * user_data), void *user_data, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueSVMFree(command_queue, num_svm_pointers, svm_pointers, pfn_free_func, user_data, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUESVMFREE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUESVMFREE], _CLFW_CALL_CLENQUEUESVMFREE, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_svm_memcpy)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, bool blocking_copy, void *dst_ptr, const void *src_ptr, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueSVMMemcpy(command_queue, blocking_copy, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUESVMMEMCPY;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUESVMMEMCPY], _CLFW_CALL_CLENQUEUESVMMEMCPY, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_svm_mem_fill)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, void *svm_ptr, const void *pattern, U64 pattern_size, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueSVMMemFill(command_queue, svm_ptr, pattern, pattern_size, size, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUESVMMEMFILL;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUESVMMEMFILL], _CLFW_CALL_CLENQUEUESVMMEMFILL, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_svm_map)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, bool blocking_map, cl_map_flags flags, void *svm_ptr, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueSVMMap(command_queue, blocking_map, flags, svm_ptr, size, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUESVMMAP;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUESVMMAP], _CLFW_CALL_CLENQUEUESVMMAP, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_svm_unmap)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, void *svm_ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueSVMUnmap(command_queue, svm_ptr, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUESVMUNMAP;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUESVMUNMAP], _CLFW_CALL_CLENQUEUESVMUNMAP, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_svm_migrate_mem)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_svm_pointers, const void ** svm_pointers, const U64 *sizes, cl_mem_migration_flags flags, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueSVMMigrateMem(command_queue, num_svm_pointers, svm_pointers, sizes, flags, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUESVMMIGRATEMEM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUESVMMIGRATEMEM], _CLFW_CALL_CLENQUEUESVMMIGRATEMEM, clfw_get_error_title(_err), _err);
	return _err == 0;
}

void * (clfw_get_extension_function_address_for_platform)(CLFW_DEBUG_ARGS(cl_platform_id platform, const char *func_name))
{
	S32 _err;
	void *_ret;

	_ret = clGetExtensionFunctionAddressForPlatform(platform, func_name);
	if (UNLIKELY(_ret == NULL))
		_err = CL_OUT_OF_HOST_MEMORY;
	else
		_err = 0;
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESSFORPLATFORM;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESSFORPLATFORM], _CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESSFORPLATFORM, clfw_get_error_title(_err), _err);
	return _ret;

}

bool (clfw_set_command_queue_property)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_command_queue_properties properties, bool enable, cl_command_queue_properties *old_properties))
{
	S32 _err;

	_err = clSetCommandQueueProperty(command_queue, properties, enable, old_properties);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLSETCOMMANDQUEUEPROPERTY;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLSETCOMMANDQUEUEPROPERTY], _CLFW_CALL_CLSETCOMMANDQUEUEPROPERTY, clfw_get_error_title(_err), _err);
	return _err == 0;
}

cl_mem (clfw_create_image2d)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, U64 image_width, U64 image_height, U64 image_row_pitch, void *host_ptr))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreateImage2D(context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEIMAGE2D;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEIMAGE2D], _CLFW_CALL_CLCREATEIMAGE2D, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_mem (clfw_create_image3d)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, U64 image_width, U64 image_height, U64 image_depth, U64 image_row_pitch, U64 image_slice_pitch, void *host_ptr))
{
	S32 _err;
	cl_mem _ret;

	_ret = clCreateImage3D(context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATEIMAGE3D;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATEIMAGE3D], _CLFW_CALL_CLCREATEIMAGE3D, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_enqueue_marker)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_event *event))
{
	S32 _err;

	_err = clEnqueueMarker(command_queue, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEMARKER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEMARKER], _CLFW_CALL_CLENQUEUEMARKER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_wait_for_events)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_events, const cl_event *event_list))
{
	S32 _err;

	_err = clEnqueueWaitForEvents(command_queue, num_events, event_list);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEWAITFOREVENTS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEWAITFOREVENTS], _CLFW_CALL_CLENQUEUEWAITFOREVENTS, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_enqueue_barrier)(CLFW_DEBUG_ARGS(cl_command_queue command_queue))
{
	S32 _err;

	_err = clEnqueueBarrier(command_queue);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUEBARRIER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUEBARRIER], _CLFW_CALL_CLENQUEUEBARRIER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

bool (clfw_unload_compiler)(CLFW_DEBUG_ARGS())
{
	S32 _err;

	_err = clUnloadCompiler();
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLUNLOADCOMPILER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLUNLOADCOMPILER], _CLFW_CALL_CLUNLOADCOMPILER, clfw_get_error_title(_err), _err);
	return _err == 0;
}

void * (clfw_get_extension_function_address)(CLFW_DEBUG_ARGS(const char *func_name))
{
	S32 _err;
	void *_ret;

	_ret = clGetExtensionFunctionAddress(func_name);
	if (UNLIKELY(_ret == NULL))
		_err = CL_OUT_OF_HOST_MEMORY;
	else
		_err = 0;
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESS;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESS], _CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESS, clfw_get_error_title(_err), _err);
	return _ret;

}

cl_command_queue (clfw_create_command_queue)(CLFW_DEBUG_ARGS(cl_context context, cl_device_id device, cl_command_queue_properties properties))
{
	S32 _err;
	cl_command_queue _ret;

	_ret = clCreateCommandQueue(context, device, properties, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATECOMMANDQUEUE;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATECOMMANDQUEUE], _CLFW_CALL_CLCREATECOMMANDQUEUE, clfw_get_error_title(_err), _err);
	return _ret;
}

cl_sampler (clfw_create_sampler)(CLFW_DEBUG_ARGS(cl_context context, bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode))
{
	S32 _err;
	cl_sampler _ret;

	_ret = clCreateSampler(context, normalized_coords, addressing_mode, filter_mode, &_err);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLCREATESAMPLER;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLCREATESAMPLER], _CLFW_CALL_CLCREATESAMPLER, clfw_get_error_title(_err), _err);
	return _ret;
}

bool (clfw_enqueue_task)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_kernel kernel, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event))
{
	S32 _err;

	_err = clEnqueueTask(command_queue, kernel, num_events_in_wait_list, event_wait_list, event);
	clfw_last_error = _err;
	clfw_last_call = _CLFW_CALL_CLENQUEUETASK;
	if (_err != 0) clfw_error("%s(%d): %s(%d)\n", clfw_func_calls[_CLFW_CALL_CLENQUEUETASK], _CLFW_CALL_CLENQUEUETASK, clfw_get_error_title(_err), _err);
	return _err == 0;
}


#pragma GCC diagnostic pop
