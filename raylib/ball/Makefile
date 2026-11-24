# Build:  make        Run:  make run        Clean:  make clean
RAYLIB   = ../external/raylib/src
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -I$(RAYLIB)
LDLIBS   = -L$(RAYLIB) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = main.cpp

ball: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o ball $(LDLIBS)

run: ball
	./ball

clean:
	rm -f ball
