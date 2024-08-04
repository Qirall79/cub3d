# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 10:21:18 by wbelfatm          #+#    #+#              #
#    Updated: 2024/08/04 16:03:08 by wbelfatm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -Ofast #-fsanitize=address -g
CC = cc
RM = rm -f

SRCS = main.c src/utils/utils.c src/utils/init.c src/utils/position.c src/utils/textures.c \
	   src/astar/astar.c src/astar/neighbors.c src/astar/nodes.c src/astar/utils.c \
	   src/draw/draw.c src/draw/redraw.c src/draw/score.c src/draw/utils.c \
	   src/sprite/sprite.c src/sprite/utils.c src/raycasting/raycasting.c src/raycasting/utils.c \
	   src/hooks/hooks.c src/hooks/handlers.c src/hooks/move.c src/hooks/utils.c \
	   src/minimap/minimap.c src/minimap/utils.c src/rendering/rendering.c src/rendering/utils.c
OBJS = ${SRCS:.c=.o}
LIBMLX = ./lib/MLX42
GLFW = /goinfre/wbelfatm/homebrew/Cellar/glfw/3.4/lib
# GLFW = /opt/homebrew/Cellar/glfw/3.4/lib
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L$(GLFW) -lm
INCLUDES = -I $(LIBMLX)
NAME = cub3d
HEADERS = cub3d.h $(LIBMLX)/MLX42.h

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
	