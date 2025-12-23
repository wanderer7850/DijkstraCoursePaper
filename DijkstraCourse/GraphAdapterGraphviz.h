#pragma once

#include <graphviz/cgraph.h>
#include <vector>
#include <string>

class GraphAdapterGraphviz {
public:
	GraphAdapterGraphviz();
	void addVertex(const std::string& v);
	void addEdge(const std::string& v1, const std::string& v2, int weight);
	int getEdgeWeight(const std::string& v1, const std::string& v2) const;
	std::vector<std::string> getVertexes() const;
	std::vector<std::string> getNeighbors(const std::string& v) const;
	~GraphAdapterGraphviz();

	friend void importGraph(
		std::string filename, 
		GraphAdapterGraphviz& graph, 
		std::string& start,
		std::string& dest
	);

	friend void exportGraph(
		const GraphAdapterGraphviz& g,
		std::string filename
	);

	friend void markShortestPath(
		const GraphAdapterGraphviz& g,
		const std::string& start, 
		const std::string& dest
	);

private:
	Agraph_t* graph = nullptr;
	std::vector<std::string> vertexes;
};