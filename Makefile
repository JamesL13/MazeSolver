all: maze

maze: main.o solve.o maze.o
	gcc main.o solve.o maze.o -o maze

main.o: main.c
	gcc -c main.c

solve.o: solve.c
	gcc -c solve.c

maze.o: maze.c
	gcc -c maze.c

clean: 
	rm -rf *o maze
