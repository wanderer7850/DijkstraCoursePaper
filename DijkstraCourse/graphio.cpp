#include "graphio.h"
#include "graphalgo.h"
#include "GraphAdapterGraphviz.h"
#include "utils.h"

#include <string>
#include <sstream>

#define VERTEXCOLOR "green"
#define EDGECOLOR "green"

enum InputState {
	READ_START_DIST,	// read start end destination vertex for searching shortest path
	READ_SEPARATOR,		// read separator between READ_START_DIST and READ_GRAPH states.	
	READ_GRAPH			// read graph for searching
};

void importGraph(std::string filename, GraphAdapterGraphviz& graph, std::string& start, std::string& dest) {
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		throw 1;
	}

	InputState inputState = READ_START_DIST;
	std::string startv, destv;
	std::string line;

	std::string buff;
	std::string in_vertex, out_vertex;
	int weight;
	while (getline(inputFile, line)) {
		auto ss = std::istringstream(line);

		switch (inputState) {
			case READ_START_DIST:
				ss >> startv >> destv;
				inputState = READ_SEPARATOR;
				break;

			case READ_SEPARATOR:
				ss >> buff;
				if (buff != "---") {
					throw IncorrectFileFormat("Expected separator!");
				}
				inputState = READ_GRAPH;
				break;

			case READ_GRAPH:
				ss >> in_vertex;
				graph.addVertex(in_vertex);
				ss >> out_vertex;
				graph.addVertex(out_vertex);
				ss >> weight;
				graph.addEdge(in_vertex, out_vertex, weight);
		}
	}

	start = startv;
	dest = destv;

	inputFile.close();
}

void exportGraph(const GraphAdapterGraphviz& g, std::string filename) {
	GVC_t* gvc;
	gvc = gvContext();
	gvLayout(gvc, g.graph, "dot");
	gvRenderFilename(gvc, g.graph, "png", filename.c_str());
	gvFreeLayout(gvc, g.graph);
}

void markShortestPath(const GraphAdapterGraphviz& g, const std::string& start, const std::string& dest) {
	std::string prev = "";
	int shortestPathWeight;
	std::vector<std::string> path;
	optimized_dijkstra(g, start, dest, shortestPathWeight, path);

	for (auto v : path) {
		Agnode_t* v1 = agnode(g.graph, _(v), false);
		agsafeset(v1, __("fillcolor"), VERTEXCOLOR, "");
		if (prev != "") {
			Agnode_t* v2 = agnode(g.graph, _(prev), false);
			Agedge_t* edge = agedge(g.graph, v1, v2, nullptr, false);
			agsafeset(edge, __("color"), EDGECOLOR, "");
		}
		prev = v;
	}
}
