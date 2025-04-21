prog: main.o perso.o
	gcc main.o perso.o -o prog -lSDL -lSDL_image -lSDL_ttf

main.o: main.c perso.h
	gcc -c main.c

perso.o: perso.c perso.h
	gcc -c perso.c

