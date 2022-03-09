// AOC10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

struct Point {

    int32_t x, y, vel_x, vel_y;
    void init(int32_t xi, int32_t yi, int8_t vel_xi, int8_t vel_yi)
    {
        x = xi; y = yi;
        vel_x = vel_xi; vel_y = vel_yi;
    }
    void update()
    {
        x += vel_x;
        y += vel_y;
    }
};

void extractPointData(std::vector<Point>& pData, std::string input)
{
    std::string str;
    std::vector<int32_t> pointData;

    std::ifstream file(input);

    if (!file)
    {
        std::cout << "Error in opening indata file!" << std::endl;
    }

    while (std::getline(file, str))
    {
        if (!str.empty())
        {
            std::string numStr = "";
            pointData.clear();

            for (uint8_t i = 0; i < str.size(); i++)
            {
                if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-') // Start of number.
                {
                    numStr += str[i];
                }
                else if ((str[i] == ',') || (str[i] == '>')) // End of number.
                {
                    int32_t number = std::stoi(numStr);
                    pointData.push_back(number);
                    numStr.erase();
                }
            }
            Point p;
            p.init(pointData[0], pointData[1], pointData[2], pointData[3]);
            pData.push_back(p);
        }
    }
}

bool runSim(std::vector<Point>& points, uint16_t& t)
{
    bool ret = false; // Return value.
    t++; // Increase number of simulations done.
    uint16_t pointsWithAdjacentNeighbors = 0;
    std::map<std::pair<int32_t, int32_t>, bool> tempMap;

    // Move all points.
    for (uint16_t i = 0; i < points.size(); i++)
    {
        points[i].update();
        tempMap[std::make_pair(points[i].x, points[i].y)] = 1; // Map used so that only one loop is needed in next step.
    }

    // Check if current point has at least one adjacent neighbor.
    for (uint32_t i = 0; i < points.size(); i++)
    {
        if ((tempMap[std::make_pair(points[i].x - 1, points[i].y)] == 1) || // Left.
            (tempMap[std::make_pair(points[i].x + 1, points[i].y)] == 1) || // Right.
            (tempMap[std::make_pair(points[i].x, points[i].y - 1)] == 1) || // Up.
            (tempMap[std::make_pair(points[i].x, points[i].y + 1)] == 1) || // Down.
            (tempMap[std::make_pair(points[i].x - 1, points[i].y - 1)] == 1) || // Up left.
            (tempMap[std::make_pair(points[i].x - 1, points[i].y + 1)] == 1) || // Up right.
            (tempMap[std::make_pair(points[i].x + 1, points[i].y - 1)] == 1) || // Down left.
            (tempMap[std::make_pair(points[i].x + 1, points[i].y + 1)] == 1))   // Down right.
        {
            pointsWithAdjacentNeighbors++;
        }
    }

    if (pointsWithAdjacentNeighbors == points.size())
        ret = true;

    return ret;
}

int main()
{
    std::vector<Point> pArr; // Data container.
    uint16_t ticks = 0;      // Tick counter.

    // Extract relevant data.
    extractPointData(pArr, "indata.txt");

    // Run simulation until all points has at least one adjacent neighbour.
    while (!runSim(pArr, ticks)) {}

    // Print simulations needed.
    std::cout << "Ticks needed: " << ticks;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
