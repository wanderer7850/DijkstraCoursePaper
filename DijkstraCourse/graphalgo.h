#pragma once

#include "GraphAdapterGraphviz.h"

#include <vector>

void dijkstra(
	const GraphAdapterGraphviz& g,
	const std::string& start, 
	const std::string& dist,
	int& shortestWayValue, 
	std::vector<std::string>& shortestWay
);

void optimized_dijkstra(
	const GraphAdapterGraphviz& g,
	const std::string& start, 
	const std::string& dist,
	int& shortestWayValue, 
	std::vector<std::string>& shortestWay
);

