all: std debug

std: std.cpp
	g++ std.cpp -o std -std=c++11

debug: std.cpp
	g++ std.cpp -o debug -std=c++11 -DDEBUG

clean:
	rm std debug
