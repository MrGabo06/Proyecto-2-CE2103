CXX = g++

RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lglog
LIBS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib `pkg-config --libs libserial`
INCS = -I/usr/include -I/usr/local/include -Isrc/include
SRCS =  src/include/*.cpp src/*.cpp

GAME = Game/src/main.cpp
PROPS = Game/src/include/**.cpp Game/src/include/Entities/**.cpp

selda:
	${CXX} -g ${INCS} ${PROPS} ${GAME} -o $@ ${LIBS} ${RAYLIB}
run: selda
	./selda
clean:
	rm ./selda
