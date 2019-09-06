# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahintz <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/01 08:36:14 by ahintz            #+#    #+#              #
#    Updated: 2019/06/29 14:34:16 by ahintz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = src/ft_*.c src/get_next_line.c
OBJ = ft_*.o get_next_line.o
FLAGS = -Wall -Wextra -Werror 

all: $(NAME) 

$(NAME):
	@gcc $(FLAGS) -c $(SRC)  -I includes
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "libft is compiled"

clean:
	@/bin/rm -f $(OBJ)
	@echo "libft obj files removed"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "libft.a removed"

re: fclean all clean
