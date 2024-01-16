# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 18:18:04 by reclaire          #+#    #+#              #
#    Updated: 2024/01/15 18:18:04 by reclaire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

all:
	python3 ./Makefile.py all

clean:
	python3 ./Makefile.py clean

fclean:
	python3 ./Makefile.py fclean

re:
	python3 ./Makefile.py re
