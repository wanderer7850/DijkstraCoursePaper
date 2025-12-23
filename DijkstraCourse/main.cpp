#include "GraphAdapterGraphviz.h"
#include "graphio.h"
#include "graphalgo.h"

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 3) {
		std::cerr << "Not enough arguments. Must be <input_file> <output_file.[png/dot]>\n";
		return 1;
	}

	GraphAdapterGraphviz graph;
	std::string s, d;
	try {
		importGraph(argv[1], graph, s, d); 
	} catch (IOException e) {
		std::cerr << e.message;
	}

	markShortestPath(graph, s, d);
	exportGraph(graph, argv[2]);
}
