prog:fonc_enemy.o main_enemy.o
	gcc fonc_enemy.o main_enemy.o -o prog -lSDL -lSDL_image -lm -g
fonc_enemy.o:fonc_enemy.c
	gcc -c fonc_enemy.c -g
main_enemy.o:main_enemy.c
	gcc -c main_enemy.c -g
