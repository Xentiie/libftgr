/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 01:33:38 by reclaire          #+#    #+#             */
/*   Updated: 2024/05/16 18:20:48 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftgr.h"
#include "libft/crypt.h"
#include "libft/images.h"
#include "libft/io.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	file fd = ft_fopen(argv[1], "r");
	t_png_img *img = ft_load_png(fd, TRUE);
	ft_fclose(fd);

	if (img == NULL && ft_errno != FT_OK)
		printf("%d:%s\n", ft_errno, ft_strerror(ft_errno));

	for (t_list *curr = img->text_data; curr; curr = curr->next)
	{
		string str1 = (string)curr->content;
		string str2 = str1 + ft_strlen(str1) + 1;
		printf("%s:%s\n", str1, str2);
	}

	ft_free_png_img(img);
}