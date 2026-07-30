CXX := g++
CXXFLAGS := -O2 -std=gnu++17 -Wall -Wextra -Wconversion -Wshadow -Wnull-dereference -Wformat=2
LDFLAGS :=

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f code
