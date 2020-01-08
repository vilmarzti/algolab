#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <unordered_set>
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
vector<pair<T, int>> getCount(std::vector<T> &input_vector)
{
    vector<pair<T, int>> unique_vector;
    for (int i = 0; i < input_vector.size(); i++)
    {
        T current_element = input_vector.at(i);

        bool contains = false;
        pair<T, int>* unique_element;
        for (size_t n = 0; n < unique_vector.size(); n++)
        {
            unique_element = &unique_vector.at(n);
            if (unique_element->first == current_element)
            {
                contains = true;
                break;
            }
        }

        if (!contains)
        {
            unique_vector.push_back(make_pair(current_element, 1));
        }
        else
        {
            unique_element->second += 1;
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

    vector<pair<char, int>> unique_note = getCount(note_vector);
    vector<pair<pair<char, char>, int>> unique_pair = getCount(char_pairs);

    graph G(unique_note.size() + unique_pair.size());
    edge_adder adder(G);
    for (size_t i = 0; i < unique_note.size(); i++)
    {
        char note_char = unique_note.at(i).first;
        for (size_t n = 0; n < unique_pair.size(); n++)
        {
            char pair_first = unique_pair.at(n).first.first;
            char pair_second = unique_pair.at(n).first.second;
            if (note_char == pair_first || note_char == pair_second)
            {
                adder.add_edge(i, unique_note.size() + n, unique_pair.at(n).second);
            }
        }
    }

    const vertex_desc v_source = boost::add_vertex(G);
    const vertex_desc v_target = boost::add_vertex(G);

    for (size_t i = 0; i < unique_note.size(); i++)
    {
        adder.add_edge(v_source, i, unique_note.at(i).second);
    }

    for (size_t i = 0; i < unique_pair.size(); i++)
    {
        adder.add_edge(unique_note.size() + i, v_target, unique_pair.at(i).second);
    }

    long flow = boost::push_relabel_max_flow(G, v_source, v_target);
    if (flow == note_vector.size())
    {
        std::cout << "Yes\n";
    }
    else
    {
        std::cout << "No\n";
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
