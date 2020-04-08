#ifndef DFS_hpp
#define DFS_hpp

#include <map>
#include <cmath>
#include <float.h>
#include "IMinimumWeight.hpp"

class DFS : public IMinimumWeight
{
private:
    struct Node
    {
        int id;
        double x;
        double y;
        bool visited = false;
        std::vector<std::pair<int, double>> neighbours;
    };
    
    double curBest;
    std::vector<int> bestPath;
    
    void nextNode(const int curId, const int targetId, std::vector<int> &path, double dst)
    {
        if (dst > curBest) return;
        
        if (curId == targetId)
        {
            if (dst < curBest)
            {
                curBest = dst;
                bestPath = path;
            }
            return;
        }
        
        for (auto p : nodes[curId]->neighbours)
        {
            if (!nodes[p.first]->visited)
            {
                dst += p.second;
                path.push_back(p.first);
                nodes[p.first]->visited = true;
                nextNode(p.first, targetId, path, dst);
                nodes[p.first]->visited = false;
                path.pop_back();
                dst -= p.second;
            }
        }
    }
  
public:
    std::vector<int> solve(int cityBeg, int cityEnd)
    {
        curBest = DBL_MAX;
        bestPath.clear();
        std::vector<int> path;
        path.push_back(cityBeg);
        
        nextNode(cityBeg, cityEnd, path, 0);
        
        return bestPath;
    }
    
    ~DFS()
    {
        for (auto node : nodes)
            delete node;
        
        nodes.clear();
    }
    
protected:
    virtual void onLoadParams(int vertices, int edges)
    {
        nodes.reserve(vertices);
    }
    
    virtual void onLoadVertex(int id, double x, double y)
    {
        Node *node = new Node();
        node->id = id;
        node->x = x;
        node->y = y;
        nodes.push_back(node);
    }
    
    virtual void onLoadEdge(int a, int b)
    {
        double dst = dstBetweenNodes(a,b);
        
        nodes[a]->neighbours.push_back(std::make_pair(b, dst));
        nodes[b]->neighbours.push_back(std::make_pair(a, dst));
    }
    
private:
    
    double dstBetweenNodes(int a, int b)
    {
        double x = nodes[a]->x - nodes[b]->x;
        double y = nodes[a]->y - nodes[b]->y;
        return sqrt(x*x + y*y);
    }
    
    std::vector<Node*> nodes;
};

#endif /* DFS_hpp */
