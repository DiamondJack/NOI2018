CFLAGS=-std=c++11 -O2

dijkstra: dijkstra.cpp core.hpp
	g++ dijkstra.cpp -o dijkstra ${CFLAGS}

spfa: spfa.cpp core.hpp
	g++ spfa.cpp -o spfa ${CFLAGS}

treeforce: treeforce.cpp core.hpp
	g++ treeforce.cpp -o treeforce ${CFLAGS}

force: force.cpp core.hpp
	g++ force.cpp -o force ${CFLAGS}

debug: debug.cpp core.hpp
	g++ debug.cpp -o debug ${CFLAGS}

std.cpp: core.hpp
	./get_std.sed core.hpp >std.cpp

std: std.cpp
	g++ std.cpp -o std ${CFLAGS}

all: dijkstra spfa treeforce force debug std 

clean:
	rm dijkstra spfa debug std.cpp std
