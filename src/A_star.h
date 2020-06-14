//
// Created by Michal on 09.04.2020.
//

#ifndef ALHE_A_STAR_H
#define ALHE_A_STAR_H


#include <vector>

class A_star : public IMinimumWeight {

private:
    class Node {
    public:
        Node() {}
        Node(int id, double x, double y) : id(id), x(x), y(y) {}

        int id;
        double x;
        double y;

        std::vector<Node*> neighbours;

        double bestDistFromStart = 999999;
        double fScore;
        int cameFrom; //node id
    };

    std::vector<Node*> vertices;

    std::vector<Node*> openSet;
    std::vector<Node*> closeSet;

    double distance(const Node& A, const Node& B) {
        double x = A.x - B.x;
        double y = A.y - B.y;
        return sqrt(x*x + y*y);
        //return sqrt(pow(B.x-A.x,2) + pow(B.y-A.y,2));
    }

public:
    std::vector<int> solve(int cityBeg, int cityEnd) override {
        return A_star_alg(cityBeg,cityEnd);
    }

    std::vector<int> reconstruct_path(Node* start, Node* goal) {
        std::vector<int> path;
        path.push_back(goal->id);
        while(goal->id != start->id) {
            goal = vertices[goal->cameFrom];
            path.insert(path.begin(),goal->id);
        }
        return path;
    }

    std::vector<int> A_star_alg(int start, int goal) {

        openSet.push_back(vertices[start]);

        vertices[start]->bestDistFromStart = 0;
        vertices[start]->fScore = distance(*vertices[start],*vertices[goal]);


        while(!openSet.empty()) {
            
            onVisitedCounter();

            Node* current;
            double f_min_value = 99999;
            int index = -1;
            for(int i = 0; i < openSet.size(); i++) {
                if(openSet[i]->fScore< f_min_value) {
                    current = openSet[i];
                    index = i;
                    f_min_value = openSet[i]->fScore;
                }
            }

            if(current->id == goal) {
                return reconstruct_path(vertices[start], current);
            }

            closeSet.push_back(current);
            openSet.erase(openSet.begin() + index);

            for(Node* neighbour : current->neighbours) {

                double distFromStartToNeigh = current->bestDistFromStart + distance(*current,*neighbour);

                if(distFromStartToNeigh < neighbour->bestDistFromStart) {
                    neighbour->cameFrom = current->id;
                    neighbour->bestDistFromStart = distFromStartToNeigh;
                    neighbour->fScore = neighbour->bestDistFromStart + distance(*neighbour,*vertices[goal]);
                    if(!std::count(closeSet.begin(),closeSet.end(),neighbour))
                        openSet.push_back(neighbour);
                }
            }
        }
        
        return std::vector<int>();
    }

protected:
    void onLoadParams(int vertices, int edges) override {
;
    }

    void onLoadVertex(int id, double x, double y) override {
        Node* newNode = new Node(id,x,y);
        vertices.push_back(newNode);
    }

    void onLoadEdge(int a, int b) override {

        vertices[a]->neighbours.push_back(vertices[b]);
        vertices[b]->neighbours.push_back(vertices[a]);
    }

};


#endif //ALHE_A_STAR_H
