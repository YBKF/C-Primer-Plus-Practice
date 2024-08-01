TARGET = ./quickSort_test.exe

$(TARGET): quickSort_test.o quickSort.o
	gcc $^ -o $@

%.o: %.c
	gcc -c $< -o $@
