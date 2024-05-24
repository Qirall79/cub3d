# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 10:21:18 by wbelfatm          #+#    #+#              #
#    Updated: 2024/05/24 14:05:26 by wbelfatm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Ofast  -fsanitize=address -g  #-Wall -Wextra -Werror 
CC = cc
RM = rm -f

SRCS = main.c hooks.c draw.c raycasting.c utils.c rendering.c sprite.c astar.c minimap.c
OBJS = ${SRCS:.c=.o}
LIBMLX = ./lib/MLX
GLFW = /Users/wbelfatm/.brew/Cellar/glfw/3.4/lib
# GLFW = /opt/homebrew/Cellar/glfw/3.4/lib
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L$(GLFW) -lm
INCLUDES = -I $(LIBMLX)/include
NAME = cub3d
HEADER = cub3d.h

%.o: %.c $(HEADER) 
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

all: libmlx $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(INCLUDES) -o $(NAME)

clean: 
	$(RM) $(OBJS)
	$(RM) -r $(LIBMLX)/build

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re libmlx
	