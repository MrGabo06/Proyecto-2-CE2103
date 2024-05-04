CXX = clang++

RAYLIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
LIBS = -L/usr/lib -L/usr/lib/x86_64-linux-gnu -L/usr/local/lib
INCS = -I/usr/include -I/usr/local/include -Isrc/include
SRCS =  src/include/*.cpp src/*.cpp}
OBJS = ${SRCS:%.c=%.o}

GAME = Game/src/main.cpp
PROPS = Game/src/include/**.cpp

all: selda

selda:
	${CC} -g ${INCS} ${PROPS} ${GAME} -o selda ${L} ${RAYLIB}
	./selda

clean:
	rm ./selda
