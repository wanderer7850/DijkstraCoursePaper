#pragma once

#include "GraphAdapterGraphviz.h"
#include <graphviz/gvc.h>
#include <fstream>

struct IOException {
	const std::string message;
	IOException(const std::string& message) : message(message) {}
};

struct IncorrectFileFormat : public IOException {
	IncorrectFileFormat(const std::string& message) : IOException(message) {}
};

struct UnsupportedFileSuffix : public IOException {
	UnsupportedFileSuffix(const std::string& message) : IOException(message) {}
};


void importGraph(std::string filename, GraphAdapterGraphviz& graph, const std::string& start, const std::string& dest);
void exportGraph(const GraphAdapterGraphviz& g, std::string filename);
void markShortestPath(const GraphAdapterGraphviz& g, const std::string& start, const std::string& dest);
