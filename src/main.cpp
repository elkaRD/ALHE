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

struct SingleData
{
    int dst;
    int astar;
    int dfs;
};

struct less_than_key
{
    inline bool operator() (const SingleData& struct1, const SingleData& struct2)
    {
        if (struct1.dst != struct2.dst)
            return struct1.dst < struct2.dst;
                
        return struct1.astar < struct2.astar;
    }
};

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
    
    int aStarBetter = 0;
    int dfsBetter = 0;
    int same = 0;
    
    int allAstarMoves = 0;
    int allDfsMoves = 0;
    int tests = 0;
    
    double astarHardToDescribe = 0;
    double dfsHardToDescribe = 0;
    
    vector<pair<int, int>> amountOfVisitedVerticesAstar;
    vector<pair<int, int>> amountOfVisitedVerticesDfs;
    
    vector<SingleData> visited;
    
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
            
            int astarMoves = astar.getVisitedVerticesCounter();
            int dfsMoves = dfs.getVisitedVerticesCounter();
        
            if (astarMoves < dfsMoves)
            {
                aStarBetter++;
            }
            else if (astarMoves > dfsMoves)
            {
                dfsBetter++;
            }
            else
            {
                same++;
            }
            
            allAstarMoves += astarMoves;
            allDfsMoves += dfsMoves;
            tests++;
            
            double astarTimesMoreThanPathLength = (double) astarMoves / solution1.size();
            double dfsTimesMoreThanPathLength = (double) dfsMoves / solution2.size();
            astarHardToDescribe += astarTimesMoreThanPathLength;
            dfsHardToDescribe += dfsTimesMoreThanPathLength;
            
            cout << dfsMoves << endl;
            
            amountOfVisitedVerticesAstar.push_back(make_pair(solution1.size(), astarMoves));
            amountOfVisitedVerticesDfs.push_back(make_pair(solution2.size(), dfsMoves));
            //TODO: graph of sorted amountOfVertices... (and create one graph for DFS without cutoff
            
            int temp = solution1.size();
            visited.push_back({temp, astarMoves, dfsMoves});
        }
    }
    
    cout << "found " << problems << " problems" << endl;
    cout << "A* better: " << aStarBetter << endl;
    cout << "DFS better: " << dfsBetter << endl;
    cout << "Same result: " << same << endl;
    cout << endl;
    cout << "Avg A*: " << (double) allAstarMoves / tests << endl;
    cout << "Avg DFS: " << (double) allDfsMoves / tests << endl;
    cout << endl;
    cout << "How many times more visited vertices than final path length (avg after all tests):" << endl;
    cout << "A*: " << astarHardToDescribe / tests << endl;
    cout << "DFS: " << dfsHardToDescribe / tests << endl;
    
    sort(amountOfVisitedVerticesAstar.begin(), amountOfVisitedVerticesAstar.end());
    sort(amountOfVisitedVerticesDfs.begin(), amountOfVisitedVerticesDfs.end());
    sort(visited.begin(), visited.end(), less_than_key());
    
    ofstream graphFile("dataForGraph3.txt");
    auto it1 = amountOfVisitedVerticesAstar.begin();
    auto it2 = amountOfVisitedVerticesDfs.begin();
//    for (; it1 != amountOfVisitedVerticesAstar.end(); ++it1, ++it2)
//    {
//        graphFile << it1->first << "; " << it1->second << "; " << it2->second << endl;
//    }
    for (const auto it : visited)
    {
        graphFile << it.dst << "; " << it.astar << "; " << it.dfs << endl;
    }
    graphFile.close();
    
    return 0;
}
