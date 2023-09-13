#----------------------- Makefile for minunit tests -----------------------#
################################ Colors ####################################

GREEN           	= \033[1;32m
YELLOW          	= \033[1;33m
RED             	= \033[1;31m
RESET           	= \033[0m

############################# Project files ################################
SRC             	= ../mandatory/pipex_utils.c ../mandatory/pipex.c ../mandatory/pipex_exec.c ../mandatory/pipex_free.c 
SRC_BONUS			= ../bonus/pipex_bonus.c ../bonus/pipex_utils_bonus.c ../bonus/pipex_exec_bonus.c ../bonus/heredoc_bonus.c \
				  	../bonus/pipex_check_bonus.c ../bonus/pipex_free_bonus.c

HEADER_PROJECT  	= ../mandatory/pipex.h
HEADER_BONUS		= ../bonus/pipex_bonus.h

############################# Test files ###################################

TESTS           	= ./mandatory/test_cat_and_sort.c ./mandatory/test_grep_backslash.c \
                  	./mandatory/test_echo_grep_bslash.c ./mandatory/test_list_and_count.c \
				  	./mandatory/test_list_and_filter_c_files.c ./mandatory/test_lower_text_to_upper.c \
				  	./mandatory/test_invalid_cmd.c ./mandatory/test_awk_and_printf.c

TESTS_BONUS			= ./bonus/test_ls_grep_sort.c ./bonus/test_echo_grep_sort.c ./bonus/test_cat_sort_trAZ.c \
					./bonus/test_read_makefile_grep_traz.c ./bonus/test_read_makefile_7_cmds.c

PROGRAM_TEST    	= $(patsubst %.c, %, $(TESTS))
PROGRAM_TEST_BONUS 	= $(patsubst %.c, %, $(TESTS_BONUS))
HEADER_MINUNIT  	= ../minunit.h
TEST_PROGRAMS   	= $(PROGRAM_TEST)
TEST_PROGRAMS_BONUS = $(PROGRAM_TEST_BONUS)

########################### Compile tests ###################################

all: pipex pipex_bonus $(PROGRAM_TEST) $(PROGRAM_TEST_BONUS)

$(PROGRAM_TEST): $(OBJS)
	@cc $(SRC) $@.c -o $@ -L../libft -lft

$(PROGRAM_TEST_BONUS): $(OBJS)
	@cc $(SRC_BONUS) $@.c -o $@ -L../libft -lft

########################### Compile pipex ##################################

# Pipex: Call to the Makefile (pipex) in the root directory
pipex:
	$(MAKE) -C .. --no-print-directory --silent

pipex_bonus:
	$(MAKE) -C .. bonus --no-print-directory --silent

############################## Execution ####################################

# Test: Run the tests compiled
test: $(TEST_PROGRAMS)
	@for program in $(TEST_PROGRAMS); do \
		./$$program; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$program passed!$(RESET)"; \
		else \
			echo "$(RED)$$program failed!$(RESET)"; \
		fi \
	done

test_bonus: $(TEST_PROGRAMS_BONUS)
	@for program in $(TEST_PROGRAMS_BONUS); do \
		./$$program; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$program passed!$(RESET)"; \
		else \
			echo "$(RED)$$program failed!$(RESET)"; \
		fi \
	done

m: pipex $(PROGRAM_TEST)
	@for program in $(PROGRAM_TEST); do \
		./$$program; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$program passed!$(RESET)"; \
		else \
			echo "$(RED)$$program failed!$(RESET)"; \
		fi \
	done

b: pipex_bonus $(PROGRAM_TEST_BONUS)
	@for program in $(PROGRAM_TEST_BONUS); do \
		./$$program; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$program passed!$(RESET)"; \
		else \
			echo "$(RED)$$program failed!$(RESET)"; \
		fi \
	done

############################## Valgrind #####################################

# Leak: Run the tests compiled with valgrind with complete leak check
leak: test
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes -s -q ./${PROGRAM_TEST}

leak_bonus: test_bonus
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes -s -q ./${PROGRAM_TEST_BONUS}

############################## Clean ########################################

clean-pipex:
	$(MAKE) -C .. fclean --no-print-directory --silent

clean: clean-pipex
	@rm -f pipex pipex_bonus $(TEST_PROGRAMS) $(TEST_PROGRAMS_BONUS)
	@echo "$(YELLOW)Cleaning done!$(RESET)"

fclean: clean

re:	fclean all

.PHONY: all clean fclean re
