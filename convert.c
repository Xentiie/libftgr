/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 00:15:04 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/30 00:27:14 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned char codes[] = {
	192, 193, 194, 195, 196, 197, 198, 199
};

unsigned short a[] = {
	3, 131, 67, 195, 35, 163, 99, 227
};

unsigned short reverse(unsigned short b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int main()
{
	for(int i = 0; i < (sizeof(codes) / sizeof(codes[0])); i++)
	{
		unsigned char reversed = reverse(codes[i]);

		printf("%u, ", reversed);
		if (i % 20 == 0 && i != 0)
			printf("\n");
	}
	printf("\n");
}

