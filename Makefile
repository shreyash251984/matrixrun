game:
	gcc -c map.c player_movement.c DAA.c
	g++ main.cpp map.o player_movement.o DAA.o -o game \
	-I/opt/homebrew/include \
	-L/opt/homebrew/lib \
	-lraylib \
	-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo


