.PHONY: all clean fclean run

NAME		= .time_cond_make

SRCS		= init_stack.cpp	\
		  constructor_stack.cpp	\
		  empty_stack.cpp	\
		  size_stack.cpp

OBJS		= $(SRCS:.cpp=.o)

CXX		= clang++

CXXFLAGS	= -Wall -Werror -Wextra

RM		= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
	@ echo "\033[1m\033[35mPrograms have been compiled...\033[39m\033[0m"
	@ $(CXX) $(CXXFLAGS) init_stack.o -o init_stack_test
	@ $(CXX) $(CXXFLAGS) constructor_stack.o -o constructor_stack_test
	@ $(CXX) $(CXXFLAGS) empty_stack.o -o empty_stack_test
	@ $(CXX) $(CXXFLAGS) size_stack.o -o size_stack_test
	@ touch .time_cond_make
	@ echo "\033[1m\033[35mExecutables have been created...\033[39m\033[0m"

clean:
	@ echo "\033[1m\033[31mRemoving object files...\033[39m\033[0m"
	@ $(RM) $(OBJS)
	@ $(RM) .time_cond_make

fclean:		clean
	@ echo "\033[1m\033[31mRemoving executables...\033[39m\033[0m"
	@ $(RM) *_stack_test

run:		all
	@ clear
	@ ./init_stack_test
	@ ./constructor_stack_test
	@ ./empty_stack_test
	@ ./size_stack_test
	@ ./init_stack_test
