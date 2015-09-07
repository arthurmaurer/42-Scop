# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/11 01:49:54 by amaurer           #+#    #+#              #
#    Updated: 2015/09/07 20:45:59 by amaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_DIR		=	src/
OBJ_DIR		=	build/
INC_DIR		=	include ftlst glfw/include include/obj /nfs/zfs-student-5/users/2013/amaurer/.brew/Cellar/glew/1.12.0/include
BIN_DIR		=	bin/

NAME		=	scop
BIN_NAME	=	$(BIN_DIR)$(NAME)
SRC			=	src/control.c \
				src/gfx.c \
				src/light.c \
				src/main.c \
				src/matrix.c \
				src/obj/add_vertex.c \
				src/obj/is_property_defined.c \
				src/obj/obj_delete_data.c \
				src/obj/obj_parse.c \
				src/obj/obj_print_data.c \
				src/obj/parse_color.c \
				src/obj/parse_comment.c \
				src/obj/parse_line.c \
				src/obj/parse_normal.c \
				src/obj/parse_polygon.c \
				src/obj/parse_position.c \
				src/obj/parse_vec2.c \
				src/obj/parse_vec3.c \
				src/obj/parser_die.c \
				src/obj/tokens_utils.c \
				src/render.c \
				src/shader.c \
				src/tga/parse_bmp.c \
				src/triangulate.c \
				src/util.c \
				src/vec3.c \
				src/window.c

OBJ			=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))

CC			=	clang
CC_FLAGS	=	-Wall -Werror -Wextra -pedantic -g3
CC_LIBS		=	-lftlst -Lftlst -lglfw3 -Lglfw/src/ -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -Lglfw/include -L/nfs/zfs-student-5/users/2013/amaurer/.brew/Cellar/glew/1.12.0/lib -lGLEW

all: submodules ftlst glfw/src/libglfw3.a $(BIN_NAME)
	@echo "\033[32m•\033[0m $(NAME) is ready."

$(BIN_NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_NAME) $(CC_LIBS) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS)$(subst $() $(), -I, $(INC_DIR)) -o $@ -c $<

clean:
	make -C ftlst clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C ftlst fclean
	rm -rf $(BIN_NAME)

re: fclean all

submodules:
	git submodule init
	git submodule update

ftlst:
	(cd ftlst && git pull origin 42)
	make -C ftlst

glfw/src/libglfw3.a:
	(cd glfw && git pull origin master && cmake .)
	make -C glfw

.PHONY: all re fclean clean libft ftlst minilibx