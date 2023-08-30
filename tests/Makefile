#----------------------- Makefile for minunit tests -----------------------#
################################ Colors ####################################

GREEN 			= \033[1;32m
YELLOW 			= \033[1;33m
RED 			= \033[1;31m
RESET 			= \033[0m


############################# Project files ################################
SRC 			= ../mandatory/pipex_utils.c ../mandatory/pipex.c ../mandatory/pipex_exec.c

HEADER_PROJECT 	= ../mandatory/pipex.h

############################# Test files ###################################

TESTS 			= test_list_and_count.c test_list_and_filter_c_files.c \
				test_lower_text_to_upper.c test_cat_and_sort.c test_grep_backslash.c \
				test_echo_grep_bslash.c
PROGRAM_TEST 	= $(patsubst %.c, %, $(TESTS))
HEADER_MINUNIT 	= ../minunit.h

############################## Compiler ####################################

all:		pipex $(PROGRAM_TEST)

$(TEST):	$(SRC) $(TEST).c
			@cc $(SRC) $(TEST).c -o $(TEST)
			@./$(PROGRAM_TEST)
			@echo "$(YELLOW) Testing $(TEST)done!$(RESET)"
			@rm -f $(TEST)
			@echo "$(YELLOW)Cleaning done!$(RESET)"


$(PROGRAM_TEST): $(OBJS)
			@cc $(SRC) $@.c -o $@ 

pipex:
			$(MAKE) -C .. 

leak:	test
			@valgrind --track-origins=yes --error-exitcode=42 --leak-check=full ./${PROGRAM_TEST}

clean-pipex:
			$(MAKE) -C .. fclean

clean:		clean-pipex
			@rm -f pipex ${PROGRAM_TEST} 
			@echo "$(YELLOW)Cleaning done!$(RESET)"

fclean:		clean

re:			fclean all

.PHONY: 	
