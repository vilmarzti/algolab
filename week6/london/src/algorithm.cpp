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
    std::vector<pair<T, int>> unique_vector;
    for (int i = 0; i < input_vector.size(); i++)
    {
        T current_element = input_vector.at(i);
        int count = std::count(input_vector.begin(), input_vector.end(), current_element);

        bool contains = false;
        for (size_t n = 0; n < unique_vector.size(); n++)
        {
            if (unique_vector.at(n).first == current_element)
            {
                contains = true;
                break;
            }
        }

        if (!contains)
        {
            pair<T, int> current_pair = make_pair(current_element, count);
            unique_vector.push_back(make_pair(current_element, count));
        }
    }

    return unique_vector;
}

void testcase()
{
    size_t h, w;
    string note;
    vector<string> raw_string;
    vector<pair<char, char>> char_pairs;

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
            pair<char, char> char_pair = make_pair(first_char, second_char);
            char_pairs.push_back(char_pair);
        }
    }

    if (h * w < note.length())
    {
        std::cout << "No" << std::endl;
        return;
    }

    std::vector<char> note_vector(note.begin(), note.end());
    std::vector<std::pair<char, int>> unique_note = getCount(note_vector);

    graph G(unique_note.size() + char_pairs.size());
    edge_adder adder(G);
    for (size_t i = 0; i < unique_note.size(); i++)
    {
        char note_char = unique_note.at(i).first;
        for (size_t n = 0; n < char_pairs.size(); n++)
        {
            char pair_first = char_pairs.at(i).first;
            char pair_second = char_pairs.at(i).second;
            if (note_char == pair_first || note_char == pair_second)
            {
                std::cout << note_char << " (" << pair_first << ", " << pair_second << ")" << std::endl;
                adder.add_edge(i, unique_note.size() + n, 1);
            }
        }
    }

    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    for (size_t i = 0; i < unique_note.size(); i++)
    {
        adder.add_edge(v_source, i, unique_note.at(i).second);
    }

    for (size_t i = 0; i < char_pairs.size(); i++)
    {
        adder.add_edge(unique_note.size() + i, v_target, 1);
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    //const auto c_map = boost::get(boost::edge_capacity, G);
    //const auto rc_map = boost::get(boost::edge_residual_capacity, G);
    //std::cout << flow << std::endl;
    //std::cout << note_vector.size() << std::endl;

    if (flow == note_vector.size()){
        std::cout << "Yes" << std::endl;
    }
    else{
        std::cout << "No" << " " << flow << " " << note_vector.size() << std::endl;
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