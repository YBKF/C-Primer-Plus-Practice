TARGET = ./stack_test.exe

$(TARGET): stack_test.o stack.o
	gcc $^ -o $@

stack_test.o: stack_test.c stack.h
	gcc -c $< -o $@

stack.o: stack.c stack.h
	gcc -c $< -o $@