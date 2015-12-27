#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

typedef vector<vector<int> > IntArray;

void read_distances(istream &s, IntArray &dists) {
    set<string> names;
    map<pair<string, string>, int> distances;
    string place1, place2, foo;
    int dist;
    for(;;) {
        s >> place1 >> foo >> place2 >> foo >> dist;
        if (s.eof()) {
            break;
        }
        distances[make_pair(place1, place2)] = dist;
        distances[make_pair(place2, place1)] = dist;
        names.insert(place1);
        names.insert(place2);
    }
    dists.clear();
    set<string>::const_iterator n1i, n2i, nb = names.begin(), ne = names.end();
    vector<int>::iterator di;
    for(n1i = nb; n1i != ne; n1i++) {
        dists.push_back(vector<int>(names.size()));
        for(n2i = nb, di = dists.back().begin(); n2i != ne; n2i++, di++) {
            *di = distances[make_pair(*n1i, *n2i)];
        }
    }
}

int compute_length(vector<int> const &order, IntArray const &distances) {
    int res = 0;
    for(vector<int>::const_iterator a = order.begin() + 1; a != order.end(); a++) {
        res += distances[*(a - 1)][*a];
    }
    return res;
}

int main(int argc, char *argv[]) {
    IntArray distances;
    read_distances(cin, distances);

    vector<int> order;
    for(int i = 0; i < distances.size(); i++) {
        order.push_back(i);
    }

    int min_length, max_length, length;
    min_length = max_length = compute_length(order, distances);
    while(next_permutation(order.begin(), order.end())) {
        length = compute_length(order, distances);
        if (length < min_length)
            min_length = length;
        if (length > max_length)
            max_length = length;
    }
    cout << min_length << ' ' << max_length << endl;
}
