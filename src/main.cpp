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

int main()
{
    ifstream file("C:\\Users\\Michal\\Desktop\\ALHE\\data\\input.txt");
    stringstream ss;
    ss << file.rdbuf();
    file.close();
    
    stringstream ss_copy;
    ss_copy << ss.str();
    unordered_map<int, string> cityIdToName = loadDictionary(ss_copy);
    


    /*DFS dfs;
    dfs.loadData(ss);
    vector<int> solution = dfs.solve(7, 9);
    for (const auto it : solution)
        cout << it << " " << cityIdToName[it] << endl;

     */A_star astar;
    astar.loadData(ss);
    vector<int> solution1 = astar.solve(7, 9);

    for (const auto it : solution1)
        cout << it << " " << cityIdToName[it] << endl;


    return 0;
}
