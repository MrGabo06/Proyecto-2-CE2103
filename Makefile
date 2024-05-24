CXX = g++

RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lglog
LIBS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib
INCS = -I/usr/include -I/usr/local/include -Isrc/include
SRCS =  src/include/*.cpp src/*.cpp

GAME = Game/src/main.cpp
PROPS = Game/src/include/**.cpp Game/src/include/Entities/**.cpp

Selda:
	${CXX} -g ${INCS} ${PROPS} ${GAME} -o selda ${L} ${RAYLIB}
	./selda

clean:
	rm ./selda
