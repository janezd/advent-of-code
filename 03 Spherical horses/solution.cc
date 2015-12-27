#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

class Coords {
    public:
        int x, y;
    Coords(int ax, int ay) : x(ax), y(ay)
    {};

    bool operator ==(const Coords &o) const
    { return (x == o.x) && (y == o.y); }

    struct hash {
        size_t operator()(Coords const & c) const
        { return (c.x * 10000 + c.y); }
    };
};


int n_visited(std::string const &path, int n_santas) {
    std::vector<Coords> santas(n_santas, Coords(0, 0));
    std::vector<Coords>::iterator santa(santas.begin());
    std::unordered_set<Coords, Coords::hash> visited;
    visited.insert(Coords(0, 0));
    for(std::string::const_iterator c(path.begin()); c != path.end(); c++) {
        switch (*c) {
            case '^': santa->y--; break;
            case 'v': santa->y++; break;
            case '<': santa->x--; break;
            case '>': santa->x++; break;
        }
        visited.insert(*santa);
        if (++santa == santas.end())
            santa = santas.begin();
    }
    return visited.size();
}


int main(int argc, char *argv[]) {
    std::string path;
    std::cin >> path;
    std::cout << "One santa: " << n_visited(path, 1) << std::endl;
    std::cout << "Two santas: " << n_visited(path, 2) << std::endl;
}
