# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 18:29:14 by dtorrett          #+#    #+#              #
#    Updated: 2024/10/07 17:15:44 by dtorrett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name
NAME = philo

# Compiler and Flags
CC = cc

# add -fsanitize=address to check data races
CFLAGS = -Wall -Wextra -Werror

# Includes
INC		= -I ./includes

# Source files
SRC_PATH = sources/
SRC_FILES = 	$(SRC_PATH)main.c \
				$(SRC_PATH)errors.c \
				$(SRC_PATH)init.c \
				$(SRC_PATH)moderator.c \
				$(SRC_PATH)philosophers.c \
				$(SRC_PATH)one_philo.c \
				$(SRC_PATH)utils.c 

# Object files
OBJ_PATH = objects/
OBJ = $(SRC_FILES:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

# Build rules
all: $(NAME)

# Compile object files from source files
$(OBJ_PATH)%.o: $(SRC_PATH)%.c
				@mkdir -p $(OBJ_PATH)
				$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME):        $(OBJ)
				$(CC) $(CFLAGS) $(OBJ) -o $@
				@echo "\n------------------------------------------\n"
				@echo "📟 philosophers ready!\n"
				@echo "------------------------------------------\n"

#-o specifies the output file
#$@ represents the target, which is the name of the executable

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\n------------------------------------------\n"
	@echo "💧 Clean done!\n"
	@echo "------------------------------------------\n"

fclean: clean
	@rm -f $(NAME)
	@echo "\n------------------------------------------\n"
	@echo "🧼 Fclean done!\n"
	@echo "------------------------------------------\n"

re: fclean all

# Declare these targets as phony (not real files) to avoid conflicts
.PHONY: all clean fclean re