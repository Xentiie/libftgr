/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:47:46 by reclaire          #+#    #+#             */
/*   Updated: 2025/02/19 18:32:53 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"

#include "libft/getopt.h"
#include "libft/io.h"
#include "libft/sys/cpuid.h"
#include "libft/debug.h"
#include "libft/limits.h"

enum e_mode
{
	MODE_TEST,
	MODE_BENCHMARK,
};

struct s_target
{
	void (*test)();
	void (*benchmark)();
};

void stretch_img_test();
void stretch_img_benchmark();

void copy_img_test();
void copy_img_benchmark();

static const t_long_opt longopts[] = {
	{"copy", no_argument, NULL, 'C'},
	{"stretch", no_argument, NULL, 'S'},
	{0},
};

static const struct s_target targets[S8_MAX] = {
	[0] = {NULL, NULL},
	['C'] = {.test = copy_img_test, .benchmark = copy_img_benchmark},
	['S'] = {.test = stretch_img_test, .benchmark = stretch_img_benchmark},
};

void print_xmm(U32 *number)
{
	const S32 size = 4;

	ft_printf("0x");
	for (int i = 0; i < size; i++)
	{
		ft_printf("%08x   ", number[i]);
	}
	ft_printf("\n");
}

void print_ymm(U32 *number)
{
	const S32 size = 8;

	ft_printf("0x");
	for (int i = 0; i < size; i++)
	{
		ft_printf("%08x   ", number[i]);
	}
	ft_printf("\n");
}

#define array_len(x) (sizeof(x) / (sizeof(x)[0]))

S32 main()
{
	U32 maxinfos;
	enum e_cpuid_vendor vendor;
	U64 cpuinfos;
	char vendor_str[13];

	maxinfos = ft_cpuid_get_max_infos();
	ft_printf("CPU (%d):\n", maxinfos);

	{ /* vendor */
		vendor = ft_cpuid_get_vendor(vendor_str);
		ft_printf("   vendor_id = %s (%s)\n", ft_cpuid_strvendor(vendor), vendor_str);
	}

	{ /* CPU infos */
		if (!ft_cpuid_get_cpuinfos(maxinfos, &cpuinfos))
		{
			ft_fprintf(ft_fstderr, "%s: ft_cpuid_get_cpuinfos: %s\n", ft_argv[0], ft_strerror2());
			return 1;
		}
		ft_printf("   version information (1/eax):\n\
      processor type  = primary processor (%lu)\n\
      family          = %#lx\n\
      model           = %#lx\n\
      stepping id     = %#lx\n\
      extended family = %#lx\n\
      extended model  = %#lx\n\
      true family     = %#lx\n\
      true model      = %#lx\n\
   miscellaneous (1/ebx):\n\
      process local APIC physical id = %#lx\n\
      maximum IDs for CPUs in pkg    = %#lx\n\
      CLFLUSH line size              = %#lx\n\
      brand index                    = %#lx\n",
				  FT_CPUID_GET_PROC_TYPE(cpuinfos),
				  FT_CPUID_GET_FAMILY_ID(cpuinfos),
				  FT_CPUID_GET_MODEL_ID(cpuinfos),
				  FT_CPUID_GET_STEPPING(cpuinfos),
				  FT_CPUID_GET_EXT_FAMILY_ID(cpuinfos),
				  FT_CPUID_GET_EXT_MODEL_ID(cpuinfos),
				  FT_CPUID_GET_TRUE_FAMILY_ID(cpuinfos),
				  FT_CPUID_GET_TRUE_MODEL_ID(cpuinfos),
				  FT_CPUID_GET_LOCAL_APIC_ID(cpuinfos),
				  FT_CPUID_GET_ADDRABLE_LOG_PROC_ID(cpuinfos),
				  FT_CPUID_GET_CLFLUSH_SIZE(cpuinfos),
				  FT_CPUID_GET_BRAND_INDEX(cpuinfos));
	}

	{ /* flags */
		U64 flgs;
		if (!ft_cpuid_get_flags(maxinfos, &flgs))
		{
			ft_fprintf(ft_fstderr, "%s: ft_cpuid_get_flags: %s\n", ft_argv[0], ft_strerror2());
			return 1;
		}
		ft_printf("   flags (%#lx):\n", flgs);
		for (U64 i = 0; i < 64; i++)
		{
			if ((1 << i) & flgs)
				ft_printf("    - %s: %s\n", ft_cpuid_strflg_short(1 << i), ft_cpuid_strflg_descr(1 << i));
		}
	}

	{ /* cache/tlb */
		struct s_cpuid_ctlb_infos infos;
		if (!ft_cpuid_get_cache_tlb_info(maxinfos, cpuinfos, &infos))
		{
			ft_fprintf(ft_fstderr, "%s: ft_cpuid_get_flags: %s\n", ft_argv[0], ft_strerror2());
			return 1;
		}
		ft_printf("   cache/tlb raw: eax:%#x ebx:%#x ecx:%#x edx:%#x\n", infos.raw[0], infos.raw[1], infos.raw[2], infos.raw[3]);
		ft_printf("   cache (%u):\n", infos.cache_cnt);
		for (U64 i = 0; i < infos.cache_cnt; i++)
		{
			ft_printf("      [%lu]:L%u%c line_size:%lu size:%lu assoc.:%lu\n", //TRIER PAR LEVEL
			i,
			infos.caches[i].level,
			(infos.caches[i].type == FT_CPUID_CACHE_INSTRUCTION) ? 'I' : ((infos.caches[i].type == FT_CPUID_CACHE_DATA) ? 'D' : 'U'),
			infos.caches[i].line_size,
			infos.caches[i].size,
			infos.caches[i].associativity
			);
		}
		ft_printf("   TLB (%u):\n", infos.tlb_cnt);
		for (U64 i = 0; i < infos.tlb_cnt; i++)
		{
			ft_printf("      [%lu]:%cTLB entries_cnt:%lu page_size:%lu assoc.:%lu\n",
			i,
			(infos.tlbs[i].is_data) ? 'D' : 'I',
			infos.tlbs[i].entries_cnt,
			infos.tlbs[i].page_size,
			infos.tlbs[i].associativity
			);
		}
	}

	return 0;

#if 0
	t_color pixels[] = {
		ft_color(1, 2, 3, 4),
		ft_color(255, 0, 0, 127),
		ft_color(0xa, 0, 0, 10),
		ft_color(0xb, 0, 0, 11),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
		ft_color(0),
	};

	t_image tmp = {
		.size = (t_iv2){8, 1},
		.pixels = pixels,
	};

	t_color dstpixels[array_len(pixels)] = {[0 ... array_len(pixels) - 1] = {.a = 255, .r = 255, .g = 0, .b = 0}};
	t_image dest = {
		.size = tmp.size,
		.pixels = dstpixels,
	};

	ft_copy_image4(&dest, ivec2(0, 0), &tmp, ivec4(0, 0, tmp.size.x, tmp.size.y));

	print_ymm((void *)dstpixels);
	for (U64 i = 0; i < array_len(pixels); i++)
	{
		ft_printf("(%u %u %u %u)\n", dest.pixels[i].r, dest.pixels[i].g, dest.pixels[i].b, dest.pixels[i].a);
	}

	return 0;
#endif

	enum e_mode mode;
	S8 target_ind;

	{
		S32 opt;

		mode = MODE_TEST;
		target_ind = 0;

		while ((opt = ft_getopt_long(ft_argc, (const_string *)ft_argv, "btCS", longopts, NULL)) > 0)
		{
			switch (opt)
			{
			case 'b':
				mode = MODE_BENCHMARK;
				break;

			case 't':
				mode = MODE_TEST;
				break;

			case 'C':
			case 'S':
				target_ind = opt;
				break;

			case '?':
			default:
				ft_fprintf(ft_fstderr, "%s: unknown argument: %s\n", ft_argv[0], ft_argv[ft_optind]);
				return 1;
			}
		}

		if (!target_ind)
			return 1;
	}

	switch (mode)
	{
	case MODE_TEST:
		if (targets[target_ind].test == NULL)
		{
			ft_fprintf(ft_fstderr, "%s: no test available for '-%c'\n", ft_argv[0], target_ind);
			return 1;
		}
		targets[target_ind].test();
		break;
	case MODE_BENCHMARK:
		if (targets[target_ind].benchmark == NULL)
		{
			ft_fprintf(ft_fstderr, "%s: no benchmark available for '-%c'\n", ft_argv[0], target_ind);
			return 1;
		}
		targets[target_ind].benchmark();
		break;
	}

	return 0;
}
