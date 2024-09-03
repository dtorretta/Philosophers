# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtorrett <dtorrett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 18:29:14 by dtorrett          #+#    #+#              #
#    Updated: 2024/09/03 18:37:04 by dtorrett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_PATH = sources/
OBJ_PATH = objects/
SRC_FILES = 	main.c / 
		errors.c /
		init.c /
		moderator.c /
		philosophers.c /
		one_philo.c /
		utils.c 

SRCS	= $(addprefix $(SRC_PATH), $(SRC_FILES))
OBJ_FILES = $(SRCS:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ_FILES))

INC		= -I ./includes/

# Default target is to build the executable
all: $(NAME)


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@



# Build the executable using object files and libft
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS)
	@echo "\n------------------------------------------\n"
	@echo "📟 philosophers ready!\n"
	@echo "------------------------------------------\n"
#-o specifies the output file
#$@ represents the target, which is the name of the executable

# Compile each source file into object files
%.o: %.c 
	$(CC) $(CFLAGS) . -c $< -o $@
#-I $(LIBMLX_DIR): This flag specifies an additional directory to include header files from. In this case, it includes header files from the libmlx directory.
#-I .: This flag includes the current directory as a directory to search for header files. The dot (.) represents the current directory.
#-c: This flag tells the compiler to generate object files (*.o) without linking. It essentially compiles the source code into an object file.
#$<: This is an automatic variable that represents the first prerequisite (dependency) of the rule. In the context of a compilation rule, it typically represents the source file (*.c file).
#-o $@: This flag specifies the output file name. $@ is an automatic variable representing the target of the rule, which, in this case, is the object file (*.o). So, -o $@ indicates that the compiler should output the compiled object file with the same name as the target.

clean:
	rm -f $(OBJS)
	@echo "\n------------------------------------------\n"
	@echo "💧 Clean done!\n"
	@echo "------------------------------------------\n"

fclean: clean
	rm -f $(NAME)
	@echo "\n------------------------------------------\n"
	@echo "🧼 Fclean done!\n"
	@echo "------------------------------------------\n"

re: fclean all

# Declare these targets as phony (not real files) to avoid conflicts
.PHONY: all clean fclean re