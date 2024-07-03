# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 10:21:18 by wbelfatm          #+#    #+#              #
#    Updated: 2024/07/03 21:40:01 by wbelfatm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Ofast  -fsanitize=address -g  #-Wall -Wextra -Werror 
CC = cc
RM = rm -f

SRCS = main.c hooks.c draw.c raycasting.c utils.c rendering.c sprite.c astar.c minimap.c
OBJS = ${SRCS:.c=.o}
LIBMLX = ./lib
# GLFW = /Users/wbelfatm/.brew/Cellar/glfw/3.4/lib
GLFW = /opt/homebrew/Cellar/glfw/3.4/lib
LIBS = $(LIBMLX)/libmlx42.a -ldl -lglfw -L$(GLFW) -lm
INCLUDES = -I $(LIBMLX)
NAME = cub3d
HEADERS = cub3d.h $(LIBMLX)/MLX42.h

%.o: %.c $(HEADERS) 
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(INCLUDES) -o $(NAME)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all re
	