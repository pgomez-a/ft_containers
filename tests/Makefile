.PHONY:	all clean fclean re run					\
	vector clean_vector fclean_vector re_vector run_vector

all:
	@ clear
	@ echo "\033[1m\033[33mCOMPILING VECTOR AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make -C ./vector_tests/

clean:
	@ make clean -C ./vector_tests/

fclean:
	@ make fclean -C ./vector_tests/

re:		all fclean

run:		all
	@ clear
	@ make run -C ./vector_tests/


vector:
	@ echo "\033[1m\033[33mCOMPILING VECTOR AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make -C ./vector_tests/

clean_vector:
	@ make clean -C ./vector_tests/

fclean_vector:	clean_vector
	@ make fclean -C ./vector_tests/

re_vector:	fclean_vector vector

run_vector:	vector
	@ clear
	@ make run -C ./vector_tests/
