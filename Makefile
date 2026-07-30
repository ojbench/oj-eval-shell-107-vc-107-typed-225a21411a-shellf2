CXX := g++
CXXFLAGS := -O2 -std=gnu++17 -Wall -Wextra -Wconversion -Wshadow -Wformat=2 -Wno-null-dereference
LDFLAGS :=

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f code
