#----------------------- Makefile for minunit tests -----------------------#
################################ Colors ####################################

GREEN           = \033[1;32m
YELLOW          = \033[1;33m
RED             = \033[1;31m
RESET           = \033[0m

############################# Project files ################################
SRC             = ../mandatory/pipex_utils.c ../mandatory/pipex.c ../mandatory/pipex_exec.c
HEADER_PROJECT  = ../mandatory/pipex.h

############################# Test files ###################################

TESTS           = test_cat_and_sort.c test_grep_backslash.c \
                  test_echo_grep_bslash.c test_list_and_count.c \
				  test_list_and_filter_c_files.c test_lower_text_to_upper.c 

PROGRAM_TEST    = $(patsubst %.c, %, $(TESTS))
HEADER_MINUNIT  = ../minunit.h
TEST_PROGRAMS   = $(PROGRAM_TEST)

############################## Compiler ####################################

all: pipex $(PROGRAM_TEST)

$(PROGRAM_TEST): $(OBJS)
	@cc $(SRC) $@.c -o $@ -L../libft -lft

pipex:
	$(MAKE) -C .. 

test: $(TEST_PROGRAMS)
	@for program in $(TEST_PROGRAMS); do \
		./$$program; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$program passed!$(RESET)"; \
		else \
			echo "$(RED)$$program failed!$(RESET)"; \
		fi \
	done


leak: test
	valgrind --track-origins=yes --error-exitcode=42 --leak-check=full ./${PROGRAM_TEST}

clean-pipex:
	$(MAKE) -C .. fclean

clean: clean-pipex
	@rm -f pipex $(TEST_PROGRAMS)
	@echo "$(YELLOW)Cleaning done!$(RESET)"

fclean: clean

re:	fclean all

.PHONY: all clean fclean re
