#include <iostream>
#include <vector>

class IMinimumWeight
{
public:
    void loadData(std::istream &inputData)
    {
        int vertices, edges;
        inputData >> vertices >> edges;
        
        for (int i = 0; i < vertices; ++i)
        {
            int id;
            std::string name;
            double x, y;
            inputData >> id >> name >> x >> y;
            onLoadVertex(id, x, y);
        }
        
        for (int i = 0; i < edges; ++i)
        {
            int id;
            std::string name;
            int cityA, cityB;
            inputData >> id >> name >> cityA >> cityB;
            onLoadEdge(cityA, cityB);
        }
    }
    virtual std::vector<int> solve(int cityBeg, int cityEnd) = 0;
    
protected:
    virtual void onLoadVertex(int id, double x, double y) = 0;
    virtual void onLoadEdge(int a, int b) = 0;
};
