#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              boost::no_property, boost::property<boost::edge_weight_t, int>>
    weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;

using namespace std;

void testcase()
{
    int n, m;
    std::cin >> n >> m;

    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    edge_desc e;

    for (size_t i = 0; i < m; i++)
    {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        e = boost::add_edge(from, to, G).first;
        weights[e] = weight;
    }


    std::vector<edge_desc> spanning_tree;
    boost::kruskal_minimum_spanning_tree(G, std::back_inserter(spanning_tree));

    int total_weight = 0;
    for (size_t i = 0; i < spanning_tree.size(); i++)
    {
        total_weight += boost::get(boost::edge_weight, G,spanning_tree[i]);
    }

    std::vector<int> dist_map(m);
    boost::dijkstra_shortest_paths(G, 0,boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));


    std::cout <<  total_weight << " " << *std::max_element(dist_map.begin(), dist_map.end())  << "\n";
}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;

    for (size_t i = 0; i < n; i++)
    {
        testcase();
    }
}
