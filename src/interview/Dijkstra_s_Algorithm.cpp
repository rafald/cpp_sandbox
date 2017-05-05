// clang++-4.0 -std=c++1z Dijkstra_s_Algorithm.cpp

#include <vector>
#include <utility>
#include <map>
#include <set>
#include <limits>
#include <algorithm>

#include <iostream>

#include <cassert>

using namespace std;

using dist_t = map< pair<char,char>, unsigned>;
using dij_result_t = map< char, pair<char,unsigned>>; // dest, prev node, best dist

#define D(V) //cout << V << "\n";

dij_result_t
dijsktra(char start, const dist_t & dist)
{
	using adj_list_t = map< char, vector<char> >;
	adj_list_t adj_list;
	set<char> not_visited = { start };
	
	for(auto const & [edge, distance]: dist)
	{
		adj_list[edge.first].push_back(edge.second);
		not_visited.insert(edge.second);
		adj_list[edge.second];// make sure that dest node also has an entry /although can be null/
	}
	assert(not_visited.count(start));

	dij_result_t shortest;
	for(auto const & node : not_visited)
	{
		shortest[node] = {{}, numeric_limits<unsigned>::max()};
	}
	
	shortest[start] = {start, 0};
	
	while(not not_visited.empty())
	{
		// find shortest path among unvisited nodes
		auto const e = shortest.end();
		auto min_el = find_if(shortest.begin(), e,
			[&not_visited](auto const & v){ return not_visited.count(v.first); });	//D( "Found first not visited: " << min_el->first);
		for(auto b = shortest.begin(); b!=e; ++b) {
			if(not_visited.count(b->first) and b->second.second < min_el->second.second) {D(b->first << " better then " << min_el->first);
				min_el = b;		
			}
		}
		// mark min_el as visited
		not_visited.erase(min_el->first);	
		
		// traverse outgoing nodes, possibly improving shortest path
		auto const min_node = min_el->first;
		auto const min_node_val = min_el->second.second;
		for(char dest : adj_list.at(min_node))
		{
			auto const candidate_val = min_node_val + dist.at({min_node, dest});
			if( candidate_val < shortest.at(dest).second ) {
				shortest.at(dest) = {min_node,candidate_val};	D(min_node << "->" << dest << " val: " << candidate_val);
			}
		}
	}
	
	return shortest;
}

int
main() {
	dist_t dist = {
		{ {'A','B'}, 20},
		{ {'A','G'}, 90},
		{ {'A','D'}, 80},
		{ {'B','F'}, 10},
		{ {'C','F'}, 50},
		{ {'C','D'}, 10},
		{ {'C','H'}, 20},
		{ {'D','C'}, 10},
		{ {'D','G'}, 20},
		{ {'E','B'}, 50},
		{ {'E','G'}, 30},
		{ {'F','C'}, 10},
		{ {'F','D'}, 40},
		{ {'G','A'}, 20},
	};

	auto const result = dijsktra('A', dist);
	////////////////////////////////////////////////
	map<char, char> prev;
	for( auto const & [dest, best]: result)
	{
		prev[dest] = best.first;
	}
	
	auto chain = [&prev](char dest, char const start) { 
		string r;
		for( auto p = dest; p!=start; p = prev.at(p)) {
			r += p ;
			r += "<-" ; 
		} 
		return r;
	};
	for( auto const & [dest, best]: result)
	{
		cout << chain(dest, 'A') << best.second << "\n";
	}
	
	return 0;
}
