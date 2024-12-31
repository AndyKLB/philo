#######################################################
## ARGUMENTS

NAME = philo

CC = cc
RM = rm -rf
FLAGS = -Wall -Wextra -Werror -g3 -pthread #-fsanitize=thread
DEP_FLAGS = -MMD -MP

#######################################################
## SOURCES

SRCS_FILES = philo.c check_input.c data_init.c \
             utils.c utils2.c ft_check.c threads.c routine.c check_threads.c

SRCS_DIR = ./srcs
OBJ_DIR = ./obj

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))
DEP = $(OBJECTS:.o=.d)

#######################################################
## RULES

$(NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

all: $(NAME)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(FLAGS) $(DEP_FLAGS) -c $< -o $@

-include $(DEP)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
