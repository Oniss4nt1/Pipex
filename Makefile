#-------------------------- Makefile for pipex ----------------------------#
################################ Colors ####################################

RED      = \033[1;31m
GREEN    = \033[1;32m
YELLOW   = \033[1;33m
BLUE     = \033[1;34m
RESET    = \033[0m

############################# Project files ################################

NAME        = pipex
LIBFT 		= ./libft
PIPEX 		= ./
HEADER 		= ./mandatory/


############################# Sources #######################################

SUBDIRS       = mandatory bonus
MAND_SRCS     = pipex.c pipex_utils.c pipex_exec.c main.c
# BONUS_SRCS    = check_chars.c check_map.c check_path.c
SRCS = $(addprefix ./mandatory/, $(MAND_SRCS))

############################# Objects #######################################

OBJS = $(SRCS:.c=.o)
OBJDIR = ./objs

############################# Compilation ##################################

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_MAKE = $(MAKE) -C $(LIBFT)
LIBFT_LIB = $(LIBFT)/libft.a

############################# Rules ########################################

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS:%=$(OBJDIR)/%)
	@echo "$(BLUE)Compiling pipex...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS:%=$(OBJDIR)/%) -I $(HEADER) -L $(LIBFT) -lft
	@echo "$(GREEN)pipex compiled$(RESET)"

$(LIBFT_LIB):
	@echo "$(BLUE)Compiling Libft...$(RESET)"
	@$(LIBFT_MAKE)
	@echo "$(GREEN)Libft compiled$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

############################# Norm rules ####################################

norm:
	@echo "$(YELLOW)Norminette...$(RESET)"
	@norminette $(SRCS) $(HEADER)
	@echo "$(GREEN)Norminette done$(RESET)"

############################# Valgrind rules ################################

leaks:
	@echo "$(YELLOW)Valgrind...$(RESET)"
	@valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes ./$(NAME)
	@echo "$(GREEN)Valgrind done$(RESET)"

############################# Clean rules ###################################

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW )pipex objects deleted$(RESET)"
	@$(LIBFT_MAKE) clean

fclean: clean
	@rm -f $(LIBFT_LIB) $(NAME)
	@echo "$(YELLOW)pipex deleted$(RESET)"
	@$(LIBFT_MAKE) fclean

re: fclean all

.PHONY: all clean fclean re norm leaks
