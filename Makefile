inv: main.c
	gcc -o inv.out main.c structures.c map.c basic_draws.c image.c invaders.c -lglut -lGLU -lm  -lGL -I.  -Wextra -Wall
