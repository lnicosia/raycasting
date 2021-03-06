# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/06 15:56:21 by lnicosia          #+#    #+#              #
#    Updated: 2019/04/08 16:39:59 by lnicosia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

MAKEFILE = Makefile

SRC_DIR = src
OBJ_DIR = obj
INCLUDES_DIR = includes
BIN_DIR = .

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_RAW = raycasting.c

SRC_RAW2 = main.c free_all.c init_sdl.c clear_image.c init_map.c

HEADERS = raycasting.h utils.h

SRC = $(addprefix $(SRC_DIR)/, $(SRC_RAW))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_RAW:.c=.o))
INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

CFLAGS =  -g3 -O3 -Wall -Wextra -Werror -I $(INCLUDES_DIR) \
		  -I $(LIBFT_DIR) \
		  -I ~/Library/Frameworks/SDL2.framework/Versions/A/Headers/ \
		  #-F ~/Library/Frameworks/ -framework SDL2 \

DEBUG ?= 0

#ifeq ($(DEBUG), 1)
#	CFLAGS += -fsanitize=address
#endif

MLX = -L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
SDL = -F ~/Library/Frameworks/ -framework SDL2 \
	  #`sdl-config --cflags --libs` \

RED := "\033[0;31m"
GREEN := "\033[0;32m"
CYAN := "\033[0;36m"
RESET :="\033[0m"

all: 
	@make -C $(LIBFT_DIR)
	@make $(BIN_DIR)/$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(MAKEFILE)
	@gcc -c $< -o $@ $(CFLAGS) 

$(BIN_DIR)/$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@gcc $(CFLAGS) $(OBJ) $(LIBFT) $(SDL) -o $(NAME)
	@echo ${GREEN}"[INFO] Compiled '$(BIN_DIR)/$(NAME)' with success!"${RESET}

clean: 
	@make clean -C libft
	@rm -f $(OBJ)
	@rm -Rf $(OBJ_DIR)
	@echo ${CYAN}"[INFO] Removed objs"${RESET}

fclean:
	@make fclean -C libft
	@rm -f $(OBJ)
	@rm -Rf $(OBJ_DIR)
	@echo ${CYAN}"[INFO] Removed objs"${RESET}
	@rm -Rf $(NAME)
	@echo ${CYAN}"[INFO] Removed $(BIN_DIR)/$(NAME)"${RESET}

re: fclean all

.PHONY: fclean all clean libft
