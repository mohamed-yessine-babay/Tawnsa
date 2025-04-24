prog:main.o background.o
	gcc main.o background.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -lm -g 
main.o:main.c
	gcc -c main.c -g
background.o:background.c
	gcc -c background.c -g 
