#include <stdio.h>
#include "DFS.hpp"
#include "A_star.h"
#include <fstream>
#include <unordered_map>
#include <sstream>
using namespace std;

unordered_map<int, string> loadDictionary(istream &input)
{
    unordered_map<int, string> cityIdToName;
    int cities, links;
    
    input >> cities >> links;
    for (int i = 0; i < cities; ++i)
    {
        string dummy;
        string name;
        input >> dummy >> name >> dummy >> dummy;
        cityIdToName[i] = name;
    }
    
    return cityIdToName;
}

int main(int argc, char *argv[])
{
    ifstream file("input.txt");
    stringstream ss;
    ss << file.rdbuf();
    file.close();
    
    stringstream ss_copy;
    ss_copy << ss.str();
    unordered_map<int, string> cityIdToName = loadDictionary(ss_copy);
    
    int problems = 0;
    bool problem = false;
    
    for (int i = 0; i < 28; ++i)
    {
        for (int j = 0; j < 28; ++j)
        {
            if (i == j) continue;
            
            problem = false;
            
            stringstream ss1;
            ss1 << ss.str();
            stringstream ss2;
            ss2 << ss.str();
            
            DFS dfs;
            dfs.loadData(ss1);
            vector<int> solution1 = dfs.solve(i, j);
            
            A_star astar;
            astar.loadData(ss2);
            vector<int> solution2 = astar.solve(i, j);
            
            if (solution1[0] != i || solution1[solution1.size()-1] != j ||
                solution2[0] != i || solution2[solution2.size()-1] != j)
            {
                problems++;
                problem = true;
            }
            else if (solution1.size() != solution2.size())
            {
                problems++;
                problem = true;
            }
            else
            {
                for (size_t k = 0; k < solution1.size(); ++k)
                {
                    if (solution1[k] != solution2[k])
                    {
                        problems++;
                        problem = true;
                        break;
                    }
                }
            }
        }
    }
    
    cout << "found " << problems << " problems" << endl;
    
    return 0;
}
