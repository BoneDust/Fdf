# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gtshekel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/02 13:08:25 by gtshekel          #+#    #+#              #
#    Updated: 2017/08/12 11:09:15 by gtshekel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CFLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework Appkit

CC = gcc

LIBS = libft/libft.a

INCLUDES = fdf.h

SRC = drawmap.c map_prep.c initialisation.c configurations.c getdimensions.c\
	  main.c
all: $(NAME)

$(NAME):
	$(MAKE) -C libft/ re
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) $(MLX) $(LIBS)
	
clean:
	$(MAKE) -C libft/ clean
	rm -f $(OBJECTS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

norme:
	@echo "\n\t\t<<<< Norminette all .c files >>>>\n"
	find . -name '*.c' -exec norminette {} \;
	@echo "\n\t\t<<<< Norminette all .h files >>>>\n"
	find . -name '*.h' -exec norminette {} \;

re: fclean all
	$(MAKE) -C libft fclean re
