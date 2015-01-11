all:
	gcc ward/ward.c -lncurses -lm  
debug:
	gcc ward/ward.c -lncurses -lm -ggdb -pg
run:
	./a.out exampleMemory
valgrind:
	make debug;
	valgrind --track-origins=yes --leak-check=full ./a.out diamond 2>a;true
	less a;
	rm a
