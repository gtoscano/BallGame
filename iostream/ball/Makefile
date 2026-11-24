# Build:  make        Run:  make run        Clean:  make clean
CXX      = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

SRC = $(wildcard *.cpp)

ball: $(SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(SRC) -o ball

run: ball
	./ball

clean:
	rm -f ball
