#include <stdio.h>
#include "DFS.hpp"
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
    ifstream file("input.txt");
    stringstream ss;
    ss << file.rdbuf();
    file.close();
    
    stringstream ss_copy;
    ss_copy << ss.str();
    unordered_map<int, string> cityIdToName = loadDictionary(ss_copy);
    
    DFS dfs;
    dfs.loadData(ss);
    vector<int> solution = dfs.solve(25, 15);
    
    for (const auto it : solution)
        cout << it << " " << cityIdToName[it] << endl;
    
    return 0;
}
