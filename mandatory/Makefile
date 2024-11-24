# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 10:21:18 by wbelfatm          #+#    #+#              #
#    Updated: 2024/08/14 10:05:23 by wbelfatm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -Ofast #-fsanitize=address -g
CC = cc
RM = rm -f

SRCS = main.c src/utils/utils.c src/utils/init.c src/utils/position.c src/utils/textures.c src/utils/ft_atoi.c \
	   src/draw/draw.c src/draw/redraw.c src/draw/utils.c src/utils/map.c src/utils/ft_free.c \
		src/raycasting/raycasting.c src/raycasting/utils.c \
	   src/hooks/hooks.c src/hooks/handlers.c src/hooks/move.c src/hooks/utils.c \
		src/rendering/rendering.c src/rendering/utils.c \
	   src/parsing/get_next_line.c src/parsing/parssing.c src/parsing/tools_1.c src/parsing/tools_2.c src/parsing/tools_3.c \
       src/parsing/parssing_2.c src/parsing/parssing_3.c src/parsing/parssing_4.c src/parsing/ft_strtrim.c
OBJS = ${SRCS:.c=.o}
LIBMLX = ./lib/MLX42

# GLFW = /Users/zmoumni/.brew//Cellar/glfw/3.4/lib
GLFW = /Users/wbelfatm/homebrew//Cellar/glfw/3.4/lib
# GLFW = /opt/homebrew/Cellar/glfw/3.4/lib

LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L$(GLFW) -lm
PARSING = parsing/parsing.a
INCLUDES = -I $(LIBMLX)
NAME = cub3d
HEADERS = cub3d.h parsing.h $(LIBMLX)/include/MLX42/MLX42.h

all: libmlx $(NAME)

%.o: %.c $(HEADERS) 
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(INCLUDES) -o $(NAME)

clean: 
	$(RM) $(OBJS)
	$(RM) -r $(LIBMLX)/build

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean, fclean, all, re, libmlx
	