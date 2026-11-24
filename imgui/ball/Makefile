# Build:  make        Run:  make run        Clean:  make clean
# Needs:  sudo apt install libimgui-dev libglfw3-dev
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra $(shell pkg-config --cflags imgui glfw3) -I/usr/include/imgui/backends
LDLIBS   = $(shell pkg-config --libs imgui glfw3) -lGL

SRC = $(wildcard *.cpp)

ball: $(SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(SRC) -o ball $(LDLIBS)

run: ball
	./ball

clean:
	rm -f ball
