.PHONY:	all clean fclean re run vector stack benchmarks

all:
	@ clear
	@ echo "\033[1m\033[33mCOMPILING VECTOR AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make -C ./vector_tests/
	@ echo "\033[1m\033[33mCOMPILING STACK AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make -C ./stack_tests/
	@ echo "\033[1m\033[33mCOMPILING MAP AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make -C ./map_tests/

clean:
	@ make clean -C ./vector_tests/
	@ make clean -C ./stack_tests/
	@ make clean -C ./map_tests/

fclean:
	@ make fclean -C ./vector_tests/
	@ make fclean -C ./stack_tests/
	@ make fclean -C ./map_tests/

re:		all fclean

run:		all
	@ clear
	@ make run -C ./vector_tests/
	@ make run -C ./stack_tests/
	@ make run -C ./map_tests/
	@ clear
	@ make -C ./benchmarks/


vector:
	@ echo "\033[1m\033[33mCOMPILING VECTOR AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make run -C ./vector_tests/
	@ make fclean -C ./vector_tests/

stack:
	@ echo "\033[1m\033[33mCOMPILING STACK AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make run -C ./stack_tests/
	@ make fclean -C ./stack_tests/

map:
	@ echo "\033[1m\033[33mCOMPILING MAP AND CREATING EXECUTABLES\033[39m\033[0m"
	@ make run -C ./map_tests/
	@ make fclean -C ./map_tests/

benchmarks:
	@ echo "\033[1m\033[33mRUNNING BENCHMARKS\033[39m\033[0m"
	@ make -C ./benchmarks/

