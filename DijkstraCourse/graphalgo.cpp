#include "graphalgo.h"
#include "GraphAdapterGraphviz.h"

#include <vector>
#include <algorithm>
#include <map>
#include <limits>
#include <queue>
#include <iterator>
#include <cstring>


#define INF INT_MAX


void dijkstra(
	const GraphAdapterGraphviz& g,
	const std::string& start,
	const std::string& dist, 
	int& shortestWayValue,
	std::vector<std::string>& shortestWay
) {
	std::vector <std::string> nodes = g.getVertexes();
	std::map<std::string, int> d;
	std::transform(
		nodes.begin(),
		nodes.end(),
		std::inserter(d, d.end()),
		[start](std::string id) {
			if (id == start) {
				return std::make_pair(id, 0);
			}

			return std::make_pair(id, INT_MAX);
		}
	);

	std::map<std::string, bool> used;
	std::transform(
		nodes.begin(),
		nodes.end(),
		std::inserter(used, used.end()),
		[start](std::string id) {
			return std::make_pair(id, false);
		}
	);

	std::map<std::string, std::string> p;
	std::transform(
		nodes.begin(),
		nodes.end(),
		std::inserter(used, used.end()),
		[start](std::string id) {
			return std::make_pair(id, "");
		}
	);

	for (int i = 0; i < nodes.size(); i++) {
		std::string currv = "";
		for (auto v : nodes) {
			if (!used[v] && (currv == "" || d[v] < d[currv])) {
				currv = v;
			}
		}

		std::vector<std::string> heighbors = g.getNeighbors(currv);
		used[currv] = true;
		for (auto neighbor : heighbors) {
			if (d[neighbor] > d[currv] + g.getEdgeWeight(neighbor, currv)) {
				d[neighbor] = d[currv] + g.getEdgeWeight(neighbor, currv);
				p[neighbor] = currv;
			}
		}
	}

	std::string cp = dist;
	do {
		shortestWay.push_back(cp);
	} while ((cp = p[cp]) != start);
	shortestWay.push_back(start);

	shortestWayValue = d[dist];
}

void optimized_dijkstra(
	const GraphAdapterGraphviz& g,
	const std::string& start,
	const std::string& dist,
	int& shortestWayValue, 
	std::vector<std::string>& shortestWay
) {
	std::vector<std::string> nodes = g.getVertexes();
	std::map<std::string, int> d;
	std::transform(
		nodes.begin(),
		nodes.end(),
		std::inserter(d, d.end()),
		[start](std::string id) {
			if (id == start) {
				return std::make_pair(id, 0);
			}

			return std::make_pair(id, INT_MAX);
		}
	);

	std::map<std::string, bool> used;
	std::transform(
		nodes.begin(),
		nodes.end(),
		std::inserter(used, used.end()),
		[start](std::string id) {
			return std::make_pair(id, false);
		}
	);

	std::map<std::string, std::string> p;
	std::transform(
		nodes.begin(),
		nodes.end(),
		std::inserter(used, used.end()),
		[start](std::string id) {
			return std::make_pair(id, "");
		}
	);

	using pair = std::pair<int, std::string>;
	std::priority_queue <pair, std::vector<pair>, std::greater<pair>> q;
	q.push({0, start });

	while (!q.empty()) {

		std::string currv = q.top().second;
		q.pop();

		std::vector<std::string> neighbors = g.getNeighbors(currv);
		used[currv] = true;
		for (auto neighbor : neighbors) {
			if (d[neighbor] > d[currv] + g.getEdgeWeight(neighbor, currv)) {
				d[neighbor] = d[currv] + g.getEdgeWeight(neighbor, currv);
				q.push({ d[neighbor], neighbor });
				p[neighbor] = currv;
			}
		}

	}
	std::string cp = dist;
	do {
		shortestWay.push_back(cp);
	} while ((cp = p[cp]) != start);
	shortestWay.push_back(start);

	shortestWayValue = d[dist];
}
