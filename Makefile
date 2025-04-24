prog:main.o function.o
	gcc main.o function.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf
main.o:main.c 
	gcc -c main.c -g
function.o:function.c
	gcc -c function.c -g
