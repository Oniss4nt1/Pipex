#-------------------------- Makefile for pipex ----------------------------#
################################ Colors ####################################

RED      = \033[1;31m
GREEN    = \033[1;32m
YELLOW   = \033[1;33m
BLUE     = \033[1;34m
RESET    = \033[0m

############################# Project files ################################

NAME        = pipex
NAME_BONUS  = pipex_bonus
LIBFT 		= ./libft
PIPEX 		= ./
HEADER 		= ./mandatory/


############################# Sources #######################################

SUBDIRS       = mandatory bonus
MAND_SRCS     = pipex.c pipex_utils.c pipex_exec.c pipex_free.c main.c
BONUS_SRCS    = pipex_bonus.c pipex_utils_bonus.c pipex_exec_bonus.c heredoc_bonus.c main_bonus.c

SRCS 			= $(addprefix ./mandatory/, $(MAND_SRCS))
SRCS_BONUS 		= $(addprefix ./bonus/, $(BONUS_SRCS))

############################# Objects #######################################

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJDIR = ./objs

############################# Compilation ##################################

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_MAKE = $(MAKE) -C $(LIBFT)
LIBFT_LIB = $(LIBFT)/libft.a

############################# Rules ########################################

all: $(NAME)
	@echo "$(BLUE)Mandatory compiled$(RESET)"

$(NAME): $(LIBFT_LIB) $(OBJS:%=$(OBJDIR)/%)
	@echo "$(BLUE)Compiling pipex...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS:%=$(OBJDIR)/%) -I $(HEADER) -L $(LIBFT) -lft
	@echo "$(GREEN)Done!$(RESET)"

$(LIBFT_LIB):
	@echo "$(BLUE)Compiling Libft...$(RESET)"
	@$(LIBFT_MAKE) 
	@echo "$(GREEN)Libft compiled$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

############################# Norm rules ####################################

$(NAME_BONUS): $(LIBFT_LIB) $(OBJS_BONUS:%=$(OBJDIR)/%)
	@echo "$(BLUE)Compiling bonus...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS:%=$(OBJDIR)/%) -I $(HEADER) -L $(LIBFT) -lft
	@echo "$(GREEN)Done!$(RESET)"

bonus: $(NAME_BONUS)
	@echo "$(BLUE)Bonus compiled!$(RESET)"



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
	@rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@echo "$(YELLOW )pipex objects deleted$(RESET)"
	@$(LIBFT_MAKE) clean

fclean: clean
	@rm -f $(LIBFT_LIB) $(NAME) $(NAME_BONUS)
	@echo "$(YELLOW)pipex deleted$(RESET)"
	@$(LIBFT_MAKE) fclean

re: fclean all

.PHONY: all clean fclean re norm leaks