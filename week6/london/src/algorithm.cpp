#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_capacity_t, long, boost::property<boost::edge_residual_capacity_t, long, boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder
{
    graph &G;

public:
    explicit edge_adder(graph &G) : G(G) {}
    void add_edge(int from, int to, long capacity)
    {
        auto c_map = boost::get(boost::edge_capacity, G);
        auto r_map = boost::get(boost::edge_reverse, G);
        const auto e = boost::add_edge(from, to, G).first;
        const auto rev_e = boost::add_edge(to, from, G).first;
        c_map[e] = capacity;
        c_map[rev_e] = 0; // reverse edge has no capacity!
        r_map[e] = rev_e;
        r_map[rev_e] = e;
    }
};

template <class T>
std::vector<std::pair<T, int>> getCount(std::vector<T> input_vector)
{
    std::vector<T, int> unique_vector;
    for (int i = 0; i < input_vector.length(); i++)
    {
        T current_element = unique_vector.at(i);
        // If element is already in the  unique vecotor skip 
        if (std::find(unique_vector.first(), unique_vector.end(), current_element) == unique_vector.end())
        {
            int counter = 0;
            for (int n = i; n < input_vector.length(); n++)
            {
                counter = input_vector.at(i) == current_element ? counter + 1 : counter;
            }
            std::pair<T, int> counter_pair = std::make_pair(current_element, counter);
            unique_vector.push_back(counter_pair);
        }
    }
    return unique_vector;
}

void testcase()
{
    size_t h, w;
    string note;
    std::vector<string> raw_string;
    std::vector<pair<char, char>> char_pairs;

    // read size of h and w
    std::cin >> h >> w;
    std::cin >> note;

    // read all the strings
    for (size_t i = 0; i < h; i++)
    {
        string a;
        std::cin >> a;
        raw_string.push_back(a);
    }

    // generate pairs
    for (size_t i = 0; i < h; i++)
    {
        string a;
        std::cin >> a;

        for (size_t n = 0; n < w; n++)
        {
            char first_char = raw_string.at(i).at(n);
            char second_char = a.at(w - n - 1);
            char_pairs.push_back(std::make_pair(first_char, second_char));
        }
    }

    if (h * w < note.length())
    {
        std::cout << "No" << std::endl;
    }
    else
    {
        std::cout << "Yes" << std::endl;
    }

    std::vector<char> note_vector(note.begin(), note.end());
    std::vector<std::pair<char, int>> unique_note = getCount(note_vector);

    graph G(unique_note.size() + char_pairs.size());
    edge_adder adder(G);
    for(size_t i=0; i < char_pairs.size(); i++){
        
    }

}

int main(int argc, char const *argv[])
{
    ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    for (size_t i; i < n; i++)
    {
        testcase();
    }
}