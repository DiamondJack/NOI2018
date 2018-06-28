dijkstra: dijkstra.cpp core.hpp
	g++ dijkstra.cpp -o dijkstra -std=c++11

spfa: spfa.cpp core.hpp
	g++ spfa.cpp -o spfa -std=c++11

debug: debug.cpp core.hpp
	g++ debug.cpp -o debug -std=c++11

std.cpp: core.hpp
	./get_std.sed core.hpp >std.cpp

std: std.cpp
	g++ std.cpp -o std -std=c++11

clean:
	rm dijkstra spfa debug std.cpp std
