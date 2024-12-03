/*
Auto generated OpenCL wrapper from 'auto_gen_wrapper.py'
*/

#define CL_USE_DEPRECATED_OPENCL_1_0_APIS
#define CL_TARGET_OPENCL_VERSION 300
#include "CL/cl.h"
#include "log/log.h"
#include "libft/std.h"

#define CLFW_DEBUG_ARGS(...) __VA_ARGS__ FT_IFDEBUG(__VA_OPT__(,) const_string _file, S32 _line)

#define __clfw_expand(x) x

#define _CLFW_CALL_CLGETPLATFORMIDS 1
#define _CLFW_CALL_CLGETPLATFORMINFO 2
#define _CLFW_CALL_CLGETDEVICEIDS 3
#define _CLFW_CALL_CLGETDEVICEINFO 4
#define _CLFW_CALL_CLCREATESUBDEVICES 5
#define _CLFW_CALL_CLRETAINDEVICE 6
#define _CLFW_CALL_CLRELEASEDEVICE 7
#define _CLFW_CALL_CLSETDEFAULTDEVICECOMMANDQUEUE 8
#define _CLFW_CALL_CLGETDEVICEANDHOSTTIMER 9
#define _CLFW_CALL_CLGETHOSTTIMER 10
#define _CLFW_CALL_CLCREATECONTEXT 11
#define _CLFW_CALL_CLCREATECONTEXTFROMTYPE 12
#define _CLFW_CALL_CLRETAINCONTEXT 13
#define _CLFW_CALL_CLRELEASECONTEXT 14
#define _CLFW_CALL_CLGETCONTEXTINFO 15
#define _CLFW_CALL_CLSETCONTEXTDESTRUCTORCALLBACK 16
#define _CLFW_CALL_CLCREATECOMMANDQUEUEWITHPROPERTIES 17
#define _CLFW_CALL_CLRETAINCOMMANDQUEUE 18
#define _CLFW_CALL_CLRELEASECOMMANDQUEUE 19
#define _CLFW_CALL_CLGETCOMMANDQUEUEINFO 20
#define _CLFW_CALL_CLCREATEBUFFER 21
#define _CLFW_CALL_CLCREATESUBBUFFER 22
#define _CLFW_CALL_CLCREATEIMAGE 23
#define _CLFW_CALL_CLCREATEPIPE 24
#define _CLFW_CALL_CLCREATEBUFFERWITHPROPERTIES 25
#define _CLFW_CALL_CLCREATEIMAGEWITHPROPERTIES 26
#define _CLFW_CALL_CLRETAINMEMOBJECT 27
#define _CLFW_CALL_CLRELEASEMEMOBJECT 28
#define _CLFW_CALL_CLGETSUPPORTEDIMAGEFORMATS 29
#define _CLFW_CALL_CLGETMEMOBJECTINFO 30
#define _CLFW_CALL_CLGETIMAGEINFO 31
#define _CLFW_CALL_CLGETPIPEINFO 32
#define _CLFW_CALL_CLSETMEMOBJECTDESTRUCTORCALLBACK 33
#define _CLFW_CALL_CLSVMALLOC 34
#define _CLFW_CALL_CLSVMFREE 35
#define _CLFW_CALL_CLCREATESAMPLERWITHPROPERTIES 36
#define _CLFW_CALL_CLRETAINSAMPLER 37
#define _CLFW_CALL_CLRELEASESAMPLER 38
#define _CLFW_CALL_CLGETSAMPLERINFO 39
#define _CLFW_CALL_CLCREATEPROGRAMWITHSOURCE 40
#define _CLFW_CALL_CLCREATEPROGRAMWITHBINARY 41
#define _CLFW_CALL_CLCREATEPROGRAMWITHBUILTINKERNELS 42
#define _CLFW_CALL_CLCREATEPROGRAMWITHIL 43
#define _CLFW_CALL_CLRETAINPROGRAM 44
#define _CLFW_CALL_CLRELEASEPROGRAM 45
#define _CLFW_CALL_CLBUILDPROGRAM 46
#define _CLFW_CALL_CLCOMPILEPROGRAM 47
#define _CLFW_CALL_CLLINKPROGRAM 48
#define _CLFW_CALL_CLSETPROGRAMRELEASECALLBACK 49
#define _CLFW_CALL_CLSETPROGRAMSPECIALIZATIONCONSTANT 50
#define _CLFW_CALL_CLUNLOADPLATFORMCOMPILER 51
#define _CLFW_CALL_CLGETPROGRAMINFO 52
#define _CLFW_CALL_CLGETPROGRAMBUILDINFO 53
#define _CLFW_CALL_CLCREATEKERNEL 54
#define _CLFW_CALL_CLCREATEKERNELSINPROGRAM 55
#define _CLFW_CALL_CLCLONEKERNEL 56
#define _CLFW_CALL_CLRETAINKERNEL 57
#define _CLFW_CALL_CLRELEASEKERNEL 58
#define _CLFW_CALL_CLSETKERNELARG 59
#define _CLFW_CALL_CLSETKERNELARGSVMPOINTER 60
#define _CLFW_CALL_CLSETKERNELEXECINFO 61
#define _CLFW_CALL_CLGETKERNELINFO 62
#define _CLFW_CALL_CLGETKERNELARGINFO 63
#define _CLFW_CALL_CLGETKERNELWORKGROUPINFO 64
#define _CLFW_CALL_CLGETKERNELSUBGROUPINFO 65
#define _CLFW_CALL_CLWAITFOREVENTS 66
#define _CLFW_CALL_CLGETEVENTINFO 67
#define _CLFW_CALL_CLCREATEUSEREVENT 68
#define _CLFW_CALL_CLRETAINEVENT 69
#define _CLFW_CALL_CLRELEASEEVENT 70
#define _CLFW_CALL_CLSETUSEREVENTSTATUS 71
#define _CLFW_CALL_CLSETEVENTCALLBACK 72
#define _CLFW_CALL_CLGETEVENTPROFILINGINFO 73
#define _CLFW_CALL_CLFLUSH 74
#define _CLFW_CALL_CLFINISH 75
#define _CLFW_CALL_CLENQUEUEREADBUFFER 76
#define _CLFW_CALL_CLENQUEUEREADBUFFERRECT 77
#define _CLFW_CALL_CLENQUEUEWRITEBUFFER 78
#define _CLFW_CALL_CLENQUEUEWRITEBUFFERRECT 79
#define _CLFW_CALL_CLENQUEUEFILLBUFFER 80
#define _CLFW_CALL_CLENQUEUECOPYBUFFER 81
#define _CLFW_CALL_CLENQUEUECOPYBUFFERRECT 82
#define _CLFW_CALL_CLENQUEUEREADIMAGE 83
#define _CLFW_CALL_CLENQUEUEWRITEIMAGE 84
#define _CLFW_CALL_CLENQUEUEFILLIMAGE 85
#define _CLFW_CALL_CLENQUEUECOPYIMAGE 86
#define _CLFW_CALL_CLENQUEUECOPYIMAGETOBUFFER 87
#define _CLFW_CALL_CLENQUEUECOPYBUFFERTOIMAGE 88
#define _CLFW_CALL_CLENQUEUEMAPBUFFER 89
#define _CLFW_CALL_CLENQUEUEMAPIMAGE 90
#define _CLFW_CALL_CLENQUEUEUNMAPMEMOBJECT 91
#define _CLFW_CALL_CLENQUEUEMIGRATEMEMOBJECTS 92
#define _CLFW_CALL_CLENQUEUENDRANGEKERNEL 93
#define _CLFW_CALL_CLENQUEUENATIVEKERNEL 94
#define _CLFW_CALL_CLENQUEUEMARKERWITHWAITLIST 95
#define _CLFW_CALL_CLENQUEUEBARRIERWITHWAITLIST 96
#define _CLFW_CALL_CLENQUEUESVMFREE 97
#define _CLFW_CALL_CLENQUEUESVMMEMCPY 98
#define _CLFW_CALL_CLENQUEUESVMMEMFILL 99
#define _CLFW_CALL_CLENQUEUESVMMAP 100
#define _CLFW_CALL_CLENQUEUESVMUNMAP 101
#define _CLFW_CALL_CLENQUEUESVMMIGRATEMEM 102
#define _CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESSFORPLATFORM 103
#define _CLFW_CALL_CLSETCOMMANDQUEUEPROPERTY 104
#define _CLFW_CALL_CLCREATEIMAGE2D 105
#define _CLFW_CALL_CLCREATEIMAGE3D 106
#define _CLFW_CALL_CLENQUEUEMARKER 107
#define _CLFW_CALL_CLENQUEUEWAITFOREVENTS 108
#define _CLFW_CALL_CLENQUEUEBARRIER 109
#define _CLFW_CALL_CLUNLOADCOMPILER 110
#define _CLFW_CALL_CLGETEXTENSIONFUNCTIONADDRESS 111
#define _CLFW_CALL_CLCREATECOMMANDQUEUE 112
#define _CLFW_CALL_CLCREATESAMPLER 113
#define _CLFW_CALL_CLENQUEUETASK 114

bool (clfw_get_platform_ids)(CLFW_DEBUG_ARGS(U32 num_entries, cl_platform_id *platforms, U32 *num_platforms));
bool (clfw_get_platform_info)(CLFW_DEBUG_ARGS(cl_platform_id platform, cl_platform_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_get_device_ids)(CLFW_DEBUG_ARGS(cl_platform_id platform, cl_device_type device_type, U32 num_entries, cl_device_id *devices, U32 *num_devices));
bool (clfw_get_device_info)(CLFW_DEBUG_ARGS(cl_device_id device, cl_device_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_create_sub_devices)(CLFW_DEBUG_ARGS(cl_device_id in_device, const cl_device_partition_property *properties, U32 num_devices, cl_device_id *out_devices, U32 *num_devices_ret));
bool (clfw_retain_device)(CLFW_DEBUG_ARGS(cl_device_id device));
bool (clfw_release_device)(CLFW_DEBUG_ARGS(cl_device_id device));
bool (clfw_set_default_device_command_queue)(CLFW_DEBUG_ARGS(cl_context context, cl_device_id device, cl_command_queue command_queue));
bool (clfw_get_device_and_host_timer)(CLFW_DEBUG_ARGS(cl_device_id device, cl_ulong* device_timestamp, cl_ulong* host_timestamp));
bool (clfw_get_host_timer)(CLFW_DEBUG_ARGS(cl_device_id device, U64 *host_timestamp));
cl_context (clfw_create_context)(CLFW_DEBUG_ARGS(const cl_context_properties *properties, U32 num_devices, const cl_device_id *devices, void (*pfn_notify)(const char * errinfo, const void * private_info, U64 cb, void * user_data), void *user_data));
cl_context (clfw_create_context_from_type)(CLFW_DEBUG_ARGS(const cl_context_properties *properties, cl_device_type device_type, void (*pfn_notify)(const char * errinfo, const void * private_info, U64 cb, void * user_data), void *user_data));
bool (clfw_retain_context)(CLFW_DEBUG_ARGS(cl_context context));
bool (clfw_release_context)(CLFW_DEBUG_ARGS(cl_context context));
bool (clfw_get_context_info)(CLFW_DEBUG_ARGS(cl_context context, cl_context_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_set_context_destructor_callback)(CLFW_DEBUG_ARGS(cl_context context, void (*pfn_notify)(cl_context context, void * user_data), void* user_data));
cl_command_queue (clfw_create_command_queue_with_properties)(CLFW_DEBUG_ARGS(cl_context context, cl_device_id device, const cl_queue_properties *properties));
bool (clfw_retain_command_queue)(CLFW_DEBUG_ARGS(cl_command_queue command_queue));
bool (clfw_release_command_queue)(CLFW_DEBUG_ARGS(cl_command_queue command_queue));
bool (clfw_get_command_queue_info)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_command_queue_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
cl_mem (clfw_create_buffer)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, U64 size, void *host_ptr));
cl_mem (clfw_create_sub_buffer)(CLFW_DEBUG_ARGS(cl_mem buffer, cl_mem_flags flags, cl_buffer_create_type buffer_create_type, const void *buffer_create_info));
cl_mem (clfw_create_image)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, const cl_image_desc *image_desc, void *host_ptr));
cl_mem (clfw_create_pipe)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, U32 pipe_packet_size, U32 pipe_max_packets, const cl_pipe_properties *properties));
cl_mem (clfw_create_buffer_with_properties)(CLFW_DEBUG_ARGS(cl_context context, const cl_mem_properties *properties, cl_mem_flags flags, U64 size, void *host_ptr));
cl_mem (clfw_create_image_with_properties)(CLFW_DEBUG_ARGS(cl_context context, const cl_mem_properties *properties, cl_mem_flags flags, const cl_image_format *image_format, const cl_image_desc *image_desc, void *host_ptr));
bool (clfw_retain_mem_object)(CLFW_DEBUG_ARGS(cl_mem memobj));
bool (clfw_release_mem_object)(CLFW_DEBUG_ARGS(cl_mem memobj));
bool (clfw_get_supported_image_formats)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, cl_mem_object_type image_type, U32 num_entries, cl_image_format *image_formats, U32 *num_image_formats));
bool (clfw_get_mem_object_info)(CLFW_DEBUG_ARGS(cl_mem memobj, cl_mem_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_get_image_info)(CLFW_DEBUG_ARGS(cl_mem image, cl_image_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_get_pipe_info)(CLFW_DEBUG_ARGS(cl_mem pipe, cl_pipe_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_set_mem_object_destructor_callback)(CLFW_DEBUG_ARGS(cl_mem memobj, void (*pfn_notify)(cl_mem memobj, void * user_data), void *user_data));
void * (clfw_svm_alloc)(CLFW_DEBUG_ARGS(cl_context context, cl_svm_mem_flags flags, U64 size, U32 alignment));
bool (clfw_svm_free)(CLFW_DEBUG_ARGS(cl_context context, void *svm_pointer));
cl_sampler (clfw_create_sampler_with_properties)(CLFW_DEBUG_ARGS(cl_context context, const cl_sampler_properties *sampler_properties));
bool (clfw_retain_sampler)(CLFW_DEBUG_ARGS(cl_sampler sampler));
bool (clfw_release_sampler)(CLFW_DEBUG_ARGS(cl_sampler sampler));
bool (clfw_get_sampler_info)(CLFW_DEBUG_ARGS(cl_sampler sampler, cl_sampler_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
cl_program (clfw_create_program_with_source)(CLFW_DEBUG_ARGS(cl_context context, U32 count, const char ** strings, const U64 *lengths));
cl_program (clfw_create_program_with_binary)(CLFW_DEBUG_ARGS(cl_context context, U32 num_devices, const cl_device_id *device_list, const U64 *lengths, const unsigned char ** binaries, S32 *binary_status));
cl_program (clfw_create_program_with_built_in_kernels)(CLFW_DEBUG_ARGS(cl_context context, U32 num_devices, const cl_device_id *device_list, const char *kernel_names));
cl_program (clfw_create_program_with_il)(CLFW_DEBUG_ARGS(cl_context context, const void* il, U64 length));
bool (clfw_retain_program)(CLFW_DEBUG_ARGS(cl_program t_program));
bool (clfw_release_program)(CLFW_DEBUG_ARGS(cl_program t_program));
bool (clfw_build_program)(CLFW_DEBUG_ARGS(cl_program t_program, U32 num_devices, const cl_device_id *device_list, const char *options, void (*pfn_notify)(cl_program program, void * user_data), void *user_data));
bool (clfw_compile_program)(CLFW_DEBUG_ARGS(cl_program t_program, U32 num_devices, const cl_device_id *device_list, const char *options, U32 num_input_headers, const cl_program *input_headers, const char ** header_include_names, void (*pfn_notify)(cl_program program, void * user_data), void *user_data));
cl_program (clfw_link_program)(CLFW_DEBUG_ARGS(cl_context context, U32 num_devices, const cl_device_id *device_list, const char *options, U32 num_input_programs, const cl_program *input_programs, void (*pfn_notify)(cl_program program, void * user_data), void *user_data));
bool (clfw_set_program_release_callback)(CLFW_DEBUG_ARGS(cl_program t_program, void (*pfn_notify)(cl_program program, void * user_data), void *user_data));
bool (clfw_set_program_specialization_constant)(CLFW_DEBUG_ARGS(cl_program t_program, U32 spec_id, U64 spec_size, const void* spec_value));
bool (clfw_unload_platform_compiler)(CLFW_DEBUG_ARGS(cl_platform_id platform));
bool (clfw_get_program_info)(CLFW_DEBUG_ARGS(cl_program t_program, cl_program_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_get_program_build_info)(CLFW_DEBUG_ARGS(cl_program t_program, cl_device_id device, cl_program_build_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
cl_kernel (clfw_create_kernel)(CLFW_DEBUG_ARGS(cl_program t_program, const char *kernel_name));
bool (clfw_create_kernels_in_program)(CLFW_DEBUG_ARGS(cl_program t_program, U32 num_kernels, cl_kernel *kernels, U32 *num_kernels_ret));
cl_kernel (clfw_clone_kernel)(CLFW_DEBUG_ARGS(cl_kernel source_kernel));
bool (clfw_retain_kernel)(CLFW_DEBUG_ARGS(cl_kernel kernel));
bool (clfw_release_kernel)(CLFW_DEBUG_ARGS(cl_kernel kernel));
bool (clfw_set_kernel_arg)(CLFW_DEBUG_ARGS(cl_kernel kernel, U32 arg_index, U64 arg_size, const void *arg_value));
bool (clfw_set_kernel_arg_svm_pointer)(CLFW_DEBUG_ARGS(cl_kernel kernel, U32 arg_index, const void *arg_value));
bool (clfw_set_kernel_exec_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_kernel_exec_info param_name, U64 param_value_size, const void *param_value));
bool (clfw_get_kernel_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_kernel_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_get_kernel_arg_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, U32 arg_indx, cl_kernel_arg_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_get_kernel_work_group_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_device_id device, cl_kernel_work_group_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_get_kernel_sub_group_info)(CLFW_DEBUG_ARGS(cl_kernel kernel, cl_device_id device, cl_kernel_sub_group_info param_name, U64 input_value_size, const void* input_value, U64 param_value_size, void* param_value, size_t* param_value_size_ret));
bool (clfw_wait_for_events)(CLFW_DEBUG_ARGS(U32 num_events, const cl_event *event_list));
bool (clfw_get_event_info)(CLFW_DEBUG_ARGS(cl_event event, cl_event_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
cl_event (clfw_create_user_event)(CLFW_DEBUG_ARGS(cl_context context));
bool (clfw_retain_event)(CLFW_DEBUG_ARGS(cl_event event));
bool (clfw_release_event)(CLFW_DEBUG_ARGS(cl_event event));
bool (clfw_set_user_event_status)(CLFW_DEBUG_ARGS(cl_event event, S32 execution_status));
bool (clfw_set_event_callback)(CLFW_DEBUG_ARGS(cl_event event, S32 command_exec_callback_type, void (*pfn_notify)(cl_event event, S32 event_command_status, void * user_data), void *user_data));
bool (clfw_get_event_profiling_info)(CLFW_DEBUG_ARGS(cl_event event, cl_profiling_info param_name, U64 param_value_size, void *param_value, U64 *param_value_size_ret));
bool (clfw_flush)(CLFW_DEBUG_ARGS(cl_command_queue command_queue));
bool (clfw_finish)(CLFW_DEBUG_ARGS(cl_command_queue command_queue));
bool (clfw_enqueue_read_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_read, U64 offset, U64 size, void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_read_buffer_rect)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_read, const U64 *buffer_origin, const U64 *host_origin, const U64 *region, U64 buffer_row_pitch, U64 buffer_slice_pitch, U64 host_row_pitch, U64 host_slice_pitch, void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_write_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_write, U64 offset, U64 size, const void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_write_buffer_rect)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_write, const U64 *buffer_origin, const U64 *host_origin, const U64 *region, U64 buffer_row_pitch, U64 buffer_slice_pitch, U64 host_row_pitch, U64 host_slice_pitch, const void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_fill_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, const void *pattern, U64 pattern_size, U64 offset, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_copy_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, U64 src_offset, U64 dst_offset, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_copy_buffer_rect)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_buffer, const U64 *src_origin, const U64 *dst_origin, const U64 *region, U64 src_row_pitch, U64 src_slice_pitch, U64 dst_row_pitch, U64 dst_slice_pitch, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_read_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, bool blocking_read, const U64 *origin, const U64 *region, U64 row_pitch, U64 slice_pitch, void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_write_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, bool blocking_write, const U64 *origin, const U64 *region, U64 input_row_pitch, U64 input_slice_pitch, const void *ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_fill_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, const void *fill_color, const U64 *origin, const U64 *region, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_copy_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_image, const U64 *src_origin, const U64 *dst_origin, const U64 *region, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_copy_image_to_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_image, cl_mem dst_buffer, const U64 *src_origin, const U64 *region, U64 dst_offset, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_copy_buffer_to_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem src_buffer, cl_mem dst_image, U64 src_offset, const U64 *dst_origin, const U64 *region, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
void * (clfw_enqueue_map_buffer)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem buffer, bool blocking_map, cl_map_flags map_flags, U64 offset, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
void * (clfw_enqueue_map_image)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem image, bool blocking_map, cl_map_flags map_flags, const U64 *origin, const U64 *region, U64 *image_row_pitch, U64 *image_slice_pitch, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_unmap_mem_object)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_mem memobj, void *mapped_ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_migrate_mem_objects)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_mem_objects, const cl_mem *mem_objects, cl_mem_migration_flags flags, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_nd_range_kernel)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_kernel kernel, U32 work_dim, const U64 *global_work_offset, const U64 *global_work_size, const U64 *local_work_size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_native_kernel)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, void (*user_func)(void *), void *args, U64 cb_args, U32 num_mem_objects, const cl_mem *mem_list, const void ** args_mem_loc, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_marker_with_wait_list)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_barrier_with_wait_list)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_svm_free)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_svm_pointers, void *svm_pointers [], void (*pfn_free_func)(cl_command_queue queue, U32 num_svm_pointers, void * svm_pointers [], void * user_data), void *user_data, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_svm_memcpy)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, bool blocking_copy, void *dst_ptr, const void *src_ptr, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_svm_mem_fill)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, void *svm_ptr, const void *pattern, U64 pattern_size, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_svm_map)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, bool blocking_map, cl_map_flags flags, void *svm_ptr, U64 size, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_svm_unmap)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, void *svm_ptr, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
bool (clfw_enqueue_svm_migrate_mem)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_svm_pointers, const void ** svm_pointers, const U64 *sizes, cl_mem_migration_flags flags, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));
void * (clfw_get_extension_function_address_for_platform)(CLFW_DEBUG_ARGS(cl_platform_id platform, const char *func_name));
bool (clfw_set_command_queue_property)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_command_queue_properties properties, bool enable, cl_command_queue_properties *old_properties));
cl_mem (clfw_create_image2d)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, U64 image_width, U64 image_height, U64 image_row_pitch, void *host_ptr));
cl_mem (clfw_create_image3d)(CLFW_DEBUG_ARGS(cl_context context, cl_mem_flags flags, const cl_image_format *image_format, U64 image_width, U64 image_height, U64 image_depth, U64 image_row_pitch, U64 image_slice_pitch, void *host_ptr));
bool (clfw_enqueue_marker)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_event *event));
bool (clfw_enqueue_wait_for_events)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, U32 num_events, const cl_event *event_list));
bool (clfw_enqueue_barrier)(CLFW_DEBUG_ARGS(cl_command_queue command_queue));
bool (clfw_unload_compiler)(CLFW_DEBUG_ARGS());
void * (clfw_get_extension_function_address)(CLFW_DEBUG_ARGS(const char *func_name));
cl_command_queue (clfw_create_command_queue)(CLFW_DEBUG_ARGS(cl_context context, cl_device_id device, cl_command_queue_properties properties));
cl_sampler (clfw_create_sampler)(CLFW_DEBUG_ARGS(cl_context context, bool normalized_coords, cl_addressing_mode addressing_mode, cl_filter_mode filter_mode));
bool (clfw_enqueue_task)(CLFW_DEBUG_ARGS(cl_command_queue command_queue, cl_kernel kernel, U32 num_events_in_wait_list, const cl_event *event_wait_list, cl_event *event));

#if defined(DEBUG)
#define clfw_get_platform_ids(num_entries, platforms, num_platforms) (clfw_get_platform_ids)(num_entries, platforms, num_platforms, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_platform_info(platform, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_platform_info)(platform, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_device_ids(platform, device_type, num_entries, devices, num_devices) (clfw_get_device_ids)(platform, device_type, num_entries, devices, num_devices, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_device_info(device, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_device_info)(device, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_sub_devices(in_device, properties, num_devices, out_devices, num_devices_ret) (clfw_create_sub_devices)(in_device, properties, num_devices, out_devices, num_devices_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_device(device) (clfw_retain_device)(device, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_device(device) (clfw_release_device)(device, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_default_device_command_queue(context, device, command_queue) (clfw_set_default_device_command_queue)(context, device, command_queue, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_device_and_host_timer(device, device_timestamp, host_timestamp) (clfw_get_device_and_host_timer)(device, device_timestamp, host_timestamp, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_host_timer(device, host_timestamp) (clfw_get_host_timer)(device, host_timestamp, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_context(properties, num_devices, devices, pfn_notify, user_data) (clfw_create_context)(properties, num_devices, devices, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_context_from_type(properties, device_type, pfn_notify, user_data) (clfw_create_context_from_type)(properties, device_type, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_context(context) (clfw_retain_context)(context, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_context(context) (clfw_release_context)(context, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_context_info(context, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_context_info)(context, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_context_destructor_callback(context, pfn_notify, user_data) (clfw_set_context_destructor_callback)(context, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_command_queue_with_properties(context, device, properties) (clfw_create_command_queue_with_properties)(context, device, properties, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_command_queue(command_queue) (clfw_retain_command_queue)(command_queue, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_command_queue(command_queue) (clfw_release_command_queue)(command_queue, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_command_queue_info(command_queue, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_command_queue_info)(command_queue, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_buffer(context, flags, size, host_ptr) (clfw_create_buffer)(context, flags, size, host_ptr, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_sub_buffer(buffer, flags, buffer_create_type, buffer_create_info) (clfw_create_sub_buffer)(buffer, flags, buffer_create_type, buffer_create_info, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_image(context, flags, image_format, image_desc, host_ptr) (clfw_create_image)(context, flags, image_format, image_desc, host_ptr, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_pipe(context, flags, pipe_packet_size, pipe_max_packets, properties) (clfw_create_pipe)(context, flags, pipe_packet_size, pipe_max_packets, properties, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_buffer_with_properties(context, properties, flags, size, host_ptr) (clfw_create_buffer_with_properties)(context, properties, flags, size, host_ptr, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_image_with_properties(context, properties, flags, image_format, image_desc, host_ptr) (clfw_create_image_with_properties)(context, properties, flags, image_format, image_desc, host_ptr, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_mem_object(memobj) (clfw_retain_mem_object)(memobj, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_mem_object(memobj) (clfw_release_mem_object)(memobj, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_supported_image_formats(context, flags, image_type, num_entries, image_formats, num_image_formats) (clfw_get_supported_image_formats)(context, flags, image_type, num_entries, image_formats, num_image_formats, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_mem_object_info(memobj, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_mem_object_info)(memobj, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_image_info(image, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_image_info)(image, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_pipe_info(pipe, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_pipe_info)(pipe, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_mem_object_destructor_callback(memobj, pfn_notify, user_data) (clfw_set_mem_object_destructor_callback)(memobj, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_svm_alloc(context, flags, size, alignment) (clfw_svm_alloc)(context, flags, size, alignment, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_svm_free(context, svm_pointer) (clfw_svm_free)(context, svm_pointer, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_sampler_with_properties(context, sampler_properties) (clfw_create_sampler_with_properties)(context, sampler_properties, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_sampler(sampler) (clfw_retain_sampler)(sampler, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_sampler(sampler) (clfw_release_sampler)(sampler, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_sampler_info(sampler, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_sampler_info)(sampler, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_program_with_source(context, count, strings, lengths) (clfw_create_program_with_source)(context, count, strings, lengths, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_program_with_binary(context, num_devices, device_list, lengths, binaries, binary_status) (clfw_create_program_with_binary)(context, num_devices, device_list, lengths, binaries, binary_status, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_program_with_built_in_kernels(context, num_devices, device_list, kernel_names) (clfw_create_program_with_built_in_kernels)(context, num_devices, device_list, kernel_names, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_program_with_il(context, il, length) (clfw_create_program_with_il)(context, il, length, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_program(program) (clfw_retain_program)(program, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_program(program) (clfw_release_program)(program, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_build_program(program, num_devices, device_list, options, pfn_notify, user_data) (clfw_build_program)(program, num_devices, device_list, options, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_compile_program(program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data) (clfw_compile_program)(program, num_devices, device_list, options, num_input_headers, input_headers, header_include_names, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_link_program(context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data) (clfw_link_program)(context, num_devices, device_list, options, num_input_programs, input_programs, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_program_release_callback(program, pfn_notify, user_data) (clfw_set_program_release_callback)(program, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_program_specialization_constant(program, spec_id, spec_size, spec_value) (clfw_set_program_specialization_constant)(program, spec_id, spec_size, spec_value, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_unload_platform_compiler(platform) (clfw_unload_platform_compiler)(platform, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_program_info(program, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_program_info)(program, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_program_build_info(program, device, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_program_build_info)(program, device, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_kernel(program, kernel_name) (clfw_create_kernel)(program, kernel_name, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_kernels_in_program(program, num_kernels, kernels, num_kernels_ret) (clfw_create_kernels_in_program)(program, num_kernels, kernels, num_kernels_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_clone_kernel(source_kernel) (clfw_clone_kernel)(source_kernel, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_kernel(kernel) (clfw_retain_kernel)(kernel, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_kernel(kernel) (clfw_release_kernel)(kernel, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_kernel_arg(kernel, arg_index, arg_size, arg_value) (clfw_set_kernel_arg)(kernel, arg_index, arg_size, arg_value, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_kernel_arg_svm_pointer(kernel, arg_index, arg_value) (clfw_set_kernel_arg_svm_pointer)(kernel, arg_index, arg_value, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_kernel_exec_info(kernel, param_name, param_value_size, param_value) (clfw_set_kernel_exec_info)(kernel, param_name, param_value_size, param_value, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_kernel_info(kernel, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_kernel_info)(kernel, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_kernel_arg_info(kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_kernel_arg_info)(kernel, arg_indx, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_kernel_work_group_info(kernel, device, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_kernel_work_group_info)(kernel, device, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_kernel_sub_group_info(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret) (clfw_get_kernel_sub_group_info)(kernel, device, param_name, input_value_size, input_value, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_wait_for_events(num_events, event_list) (clfw_wait_for_events)(num_events, event_list, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_event_info(event, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_event_info)(event, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_user_event(context) (clfw_create_user_event)(context, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_retain_event(event) (clfw_retain_event)(event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_release_event(event) (clfw_release_event)(event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_user_event_status(event, execution_status) (clfw_set_user_event_status)(event, execution_status, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_event_callback(event, command_exec_callback_type, pfn_notify, user_data) (clfw_set_event_callback)(event, command_exec_callback_type, pfn_notify, user_data, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_event_profiling_info(event, param_name, param_value_size, param_value, param_value_size_ret) (clfw_get_event_profiling_info)(event, param_name, param_value_size, param_value, param_value_size_ret, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_flush(command_queue) (clfw_flush)(command_queue, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_finish(command_queue) (clfw_finish)(command_queue, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_read_buffer(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_read_buffer)(command_queue, buffer, blocking_read, offset, size, ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_read_buffer_rect(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_read_buffer_rect)(command_queue, buffer, blocking_read, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_write_buffer(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_write_buffer)(command_queue, buffer, blocking_write, offset, size, ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_write_buffer_rect(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_write_buffer_rect)(command_queue, buffer, blocking_write, buffer_origin, host_origin, region, buffer_row_pitch, buffer_slice_pitch, host_row_pitch, host_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_fill_buffer(command_queue, buffer, pattern, pattern_size, offset, size, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_fill_buffer)(command_queue, buffer, pattern, pattern_size, offset, size, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_copy_buffer(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_copy_buffer)(command_queue, src_buffer, dst_buffer, src_offset, dst_offset, size, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_copy_buffer_rect(command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_copy_buffer_rect)(command_queue, src_buffer, dst_buffer, src_origin, dst_origin, region, src_row_pitch, src_slice_pitch, dst_row_pitch, dst_slice_pitch, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_read_image(command_queue, image, blocking_read, origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_read_image)(command_queue, image, blocking_read, origin, region, row_pitch, slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_write_image(command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_write_image)(command_queue, image, blocking_write, origin, region, input_row_pitch, input_slice_pitch, ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_fill_image(command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_fill_image)(command_queue, image, fill_color, origin, region, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_copy_image(command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_copy_image)(command_queue, src_image, dst_image, src_origin, dst_origin, region, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_copy_image_to_buffer(command_queue, src_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_copy_image_to_buffer)(command_queue, src_image, dst_buffer, src_origin, region, dst_offset, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_copy_buffer_to_image(command_queue, src_buffer, dst_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_copy_buffer_to_image)(command_queue, src_buffer, dst_image, src_offset, dst_origin, region, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_map_buffer(command_queue, buffer, blocking_map, map_flags, offset, size, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_map_buffer)(command_queue, buffer, blocking_map, map_flags, offset, size, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_map_image(command_queue, image, blocking_map, map_flags, origin, region, image_row_pitch, image_slice_pitch, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_map_image)(command_queue, image, blocking_map, map_flags, origin, region, image_row_pitch, image_slice_pitch, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_unmap_mem_object(command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_unmap_mem_object)(command_queue, memobj, mapped_ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_migrate_mem_objects(command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_migrate_mem_objects)(command_queue, num_mem_objects, mem_objects, flags, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_nd_range_kernel(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_nd_range_kernel)(command_queue, kernel, work_dim, global_work_offset, global_work_size, local_work_size, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_native_kernel(command_queue, user_func, args, cb_args, num_mem_objects, mem_list, args_mem_loc, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_native_kernel)(command_queue, user_func, args, cb_args, num_mem_objects, mem_list, args_mem_loc, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_marker_with_wait_list(command_queue, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_marker_with_wait_list)(command_queue, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_barrier_with_wait_list(command_queue, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_barrier_with_wait_list)(command_queue, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_svm_free(command_queue, num_svm_pointers, svm_pointers, pfn_free_func, user_data, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_svm_free)(command_queue, num_svm_pointers, svm_pointers, pfn_free_func, user_data, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_svm_memcpy(command_queue, blocking_copy, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_svm_memcpy)(command_queue, blocking_copy, dst_ptr, src_ptr, size, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_svm_mem_fill(command_queue, svm_ptr, pattern, pattern_size, size, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_svm_mem_fill)(command_queue, svm_ptr, pattern, pattern_size, size, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_svm_map(command_queue, blocking_map, flags, svm_ptr, size, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_svm_map)(command_queue, blocking_map, flags, svm_ptr, size, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_svm_unmap(command_queue, svm_ptr, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_svm_unmap)(command_queue, svm_ptr, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_svm_migrate_mem(command_queue, num_svm_pointers, svm_pointers, sizes, flags, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_svm_migrate_mem)(command_queue, num_svm_pointers, svm_pointers, sizes, flags, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_extension_function_address_for_platform(platform, func_name) (clfw_get_extension_function_address_for_platform)(platform, func_name, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_set_command_queue_property(command_queue, properties, enable, old_properties) (clfw_set_command_queue_property)(command_queue, properties, enable, old_properties, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_image2d(context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr) (clfw_create_image2d)(context, flags, image_format, image_width, image_height, image_row_pitch, host_ptr, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_image3d(context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr) (clfw_create_image3d)(context, flags, image_format, image_width, image_height, image_depth, image_row_pitch, image_slice_pitch, host_ptr, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_marker(command_queue, event) (clfw_enqueue_marker)(command_queue, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_wait_for_events(command_queue, num_events, event_list) (clfw_enqueue_wait_for_events)(command_queue, num_events, event_list, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_barrier(command_queue) (clfw_enqueue_barrier)(command_queue, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_unload_compiler() (clfw_unload_compiler)(, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_get_extension_function_address(func_name) (clfw_get_extension_function_address)(func_name, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_command_queue(context, device, properties) (clfw_create_command_queue)(context, device, properties, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_create_sampler(context, normalized_coords, addressing_mode, filter_mode) (clfw_create_sampler)(context, normalized_coords, addressing_mode, filter_mode, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#define clfw_enqueue_task(command_queue, kernel, num_events_in_wait_list, event_wait_list, event) (clfw_enqueue_task)(command_queue, kernel, num_events_in_wait_list, event_wait_list, event, __clfw_expand(__FILE__), __clfw_expand(__LINE__))
#endif