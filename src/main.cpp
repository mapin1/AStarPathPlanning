//
// Created by wjg on 18-4-26.
//

#include <iostream>
#include <Utils.h>

using namespace std;

int main(int argc, char** argv)
{
    int width = 50;
    int height = 50;
    SquareGrid::Location start {1, 1};
    SquareGrid::Location destination {48, 48};
    unordered_map<SquareGrid::Location, SquareGrid::Location> came_from;
    unordered_map<SquareGrid::Location, double> cost_so_far;
    GridWithWeights grid(width, height);
    int x, y;
    for (int i=0; i<30; i++)
    {
        grid.walls.insert((SquareGrid::Location {10, i}));
    }
    for (int i=20; i<50; i++)
    {
        grid.walls.insert((SquareGrid::Location {40, i}));
    }
//    grid.walls.insert(SquareGrid::Location {10, 8});
//    grid.walls.insert(SquareGrid::Location {10, 9});
//    grid.walls.insert(SquareGrid::Location {10, 10});
//    grid.walls.insert(SquareGrid::Location {10, 11});
//    grid.walls.insert(SquareGrid::Location {10, 12});
    a_star_search(grid, start, destination, came_from, cost_so_far);
    vector<SquareGrid::Location> path = reconstruct_path(start, destination, came_from);
    if (path.empty())
    {
        cout << "No available path." << endl;
    }
    cout << "Path: ";
    for (int i=0; i<path.size(); i++)
    {
        cout << "[" << std::get<0>(path[i]) << ", " << std::get<1>(path[i]) << "]";
    }
    cout << endl;
    Utils::toJsonFile("out.txt", height, width, path, start, destination, grid.walls);
}