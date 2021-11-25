.PHONY:	all fclean run

CXX		= clang++

CXXFLAGS	= -Wall -Werror -Wextra

RM		= rm -f

all:
	@ $(CXX) $(CXXFLAGS) constructor_vector.cpp -o constructor_vector_test
	@ $(CXX) $(CXXFLAGS) operator=_vector.cpp -o operator=_vector_test
	@ $(CXX) $(CXXFLAGS) begin_end_vector.cpp -o begin_end_vector_test
	@ $(CXX) $(CXXFLAGS) rbegin_rend_vector.cpp -o rbegin_rend_vector_test

fclean:	
	@ $(RM) *_vector_test

run:		all
	@ ./constructor_vector_test
	@ ./operator=_vector_test
	@ ./begin_end_vector_test
	@ ./rbegin_rend_vector_test
