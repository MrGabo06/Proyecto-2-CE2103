CC = g++

RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
L = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib
I = -I/usr/include -I/usr/local/include

GAME = Game/src/main.cpp
PROPS = Game/src/include/**.cpp

Selda:
	${CC} -g ${I} ${PROPS} ${GAME} -o output ${L} ${RAYLIB}
	./output

clean:
	rm ./output