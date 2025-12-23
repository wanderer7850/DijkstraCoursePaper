#include "GraphAdapterGraphviz.h"
#include "utils.h"

#include <graphviz/gvc.h>
#include <vector>
#include <string>

#define GRAPH_NAME "graph"
#define WEIGHT "label"


GraphAdapterGraphviz::GraphAdapterGraphviz() {
	graph = agopen(__(GRAPH_NAME), Agundirected, nullptr);
}

void GraphAdapterGraphviz::addVertex(const std::string& v) {
	Agnode_t* n = agnode(graph, _(v), false);
	if (!n) {
		Agnode_t* n = agnode(graph, _(v), true);
		agsafeset(n, __("style"), __("filled"), "");
		vertexes.push_back(v);
	}
}

void GraphAdapterGraphviz::addEdge(const std::string& v1, const std::string& v2, int weight) {
	Agnode_t* vt1 = agnode(graph, _(v1), false);
	Agnode_t* vt2 = agnode(graph, _(v2), false);

	Agedge_t* edge = agedge(graph, vt1, vt2, NULL, true);
	agsafeset(edge, __(WEIGHT), std::to_string(weight).c_str(), "");
	agsafeset(edge, __("color"), "gray", "");
}

int GraphAdapterGraphviz::getEdgeWeight(const std::string& v1, const std::string& v2) const {
	Agnode_t* vt1 = agnode(graph, _(v1), false);
	Agnode_t* vt2 = agnode(graph, _(v2), false);
	Agedge_t* edge = agedge(graph, vt1, vt2, NULL, false);

	char* str_weight = agget(edge, __(WEIGHT));
	return std::stoi(str_weight);
}

std::vector<std::string> GraphAdapterGraphviz::getVertexes() const {
	return vertexes;
}

std::vector<std::string> GraphAdapterGraphviz::getNeighbors(const std::string& v) const {
	std::vector<std::string> neighbors;
	Agnode_t* n = agnode(graph, _(v), false);
	for (auto e = agfstedge(graph, n); e; e = agnxtedge(graph, e, n)) {
		neighbors.push_back(agnameof(e->node));
	}

	return neighbors;
}

GraphAdapterGraphviz::~GraphAdapterGraphviz()
{
	agclose(graph);
}

