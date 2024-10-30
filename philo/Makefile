#######################################################
## ARGUMENTS

NAME = philo
BONUS = philo_bonus

CC	= cc
RM = rm -rf
FLAGS	= -Wall -Wextra -Werror -g3  -pthread #-fsanitize=thread
DEP_FLAGS	:=	-MMD -MP


#######################################################
## SOURCES

SRCS_FILES = philo.c check_input.c  data_init.c \
			utils.c utils2.c #threads.c check_threads.c routine.c \


SRCS_DIR = ./srcs
BONUS_SRCS_DIR = ../philo_bonus/srcs_bonus

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
BONUS_SRCS = $(addprefix $(BONUS_SRCS_DIR)/, $(BONUS_SRCS_FILES))

OBJECTS = $(SRCS:.c=.o) $(LIB_SRCS:.c=.o)
BONUS_OBJECTS = $(BONUS_SRCS:.c=.o) $(LIB_SRCS:.c=.o)
DEP	= $(OBJECTS:.o=.d) $(BONUS_OBJECTS:.o=.d)


#######################################################
## RULES

$(NAME): $(OBJECTS)
			$(CC) $(DEP_FLAGS) $(FLAGS) $(OBJECTS) -o $@
			
all: $(NAME) $(BONUS)


bonus: $(BONUS)


.c.o:
	$(CC) $(DEP_FLAGS) $(FLAGS) -c $< -o $(<:.c=.o)


$(BONUS): $(BONUS_OBJECTS)
			$(CC) $(DEP_FLAGS) $(FLAGS) $(BONUS_OBJECTS) -o $@

clean:
			$(RM) $(OBJECTS) $(BONUS_OBJECTS) $(DEP)

fclean: clean
			$(RM) $(NAME) $(BONUS)

re:	fclean $(NAME)

re_bonus: fclean bonus

.PHONY: all bonus clean  fclean re re_bonus