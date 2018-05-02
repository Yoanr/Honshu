CC = gcc -Wall -Wextra -ansi -Werror
Lib = librairies/
Test = tests/

all : honshu_A honshu_B

vg_a: honshu_A u_a
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./unit_A

vg_b: honshu_B
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./honshu_B

vg_c: honshu_C
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./honshu_C

u_a: test.o tuile.o grille.o $(Test)tests_unitaires_A.c
	$(CC) $^ -g -o unit_A -lcunit

tests_a: honshu_A
	./honshu_A

honshu_A: test.o tuile.o grille.o $(Test)tests_A.c
	$(CC) $^ -g -o $@ -lcunit

compare: test.o tuile.o grille.o game.o resolution.o O_de_un.o $(Lib)compare.c
	$(CC) $^ -g -o $@

honshu_B:  test.o tuile.o grille.o game.o resolution.o O_de_un.o $(Lib)play.c
	$(CC) $^ -g -o $@

Ode1 : test.o tuile.o grille.o game.o $(Lib)O_de_un.c
	$(CC) $^ -g -o $@

honshu_C: test.o tuile.o grille.o game.o O_de_un.o $(Lib)resolution.c
	$(CC) $^ -g -o $@

%.o : $(Lib)%.c $(Lib)%.h
	$(CC) -c -g $< -o $@

doxygen: Doxygen
Doxygen :
	doxygen Doxyfile

clean: Clean
Clean :
	if [ -d latex ]; then rm -rf latex; fi
	if [ -e honshu_A ]; then rm honshu_A; fi
	if [ -e honshu_B ]; then rm honshu_B; fi
	if [ -e Ode1 ]; then rm Ode1; fi
	if [ -e honshu_C ]; then rm honshu_C; fi
	if [ -d html ]; then rm -rf html; fi
	find ./ -maxdepth 1 -type f -name "*.o" -delete 
	find ./ -type f -name "*.swp" -delete 
