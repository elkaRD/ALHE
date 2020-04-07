#include <fstream>
#include <iostream>
#include <unordered_map>
using namespace std;

const string CITIES_FILENAME = "exported_cities.txt";
const string LINKS_FILENAME = "exported_links.txt";
const string RESULT_FILENAME = "input.txt";

int main()
{
    int citiesCounter = 0;
    int linksCounter = 0;
    unordered_map <string, int> nameToId;
    
    ifstream file(CITIES_FILENAME.c_str());
    if (file.good())
    {
        string dummy;
        while (file >> dummy >> dummy >> dummy >> dummy)
            citiesCounter++;
    }
    file.close();
    
    file.open(LINKS_FILENAME.c_str());
    if (file.good())
    {
        string dummy;
        while (file >> dummy >> dummy >> dummy)
            linksCounter++;
    }
    file.close();
    
    ofstream output(RESULT_FILENAME.c_str(), ios::trunc);
    output << citiesCounter << " " << linksCounter << endl;
    
    file.open(CITIES_FILENAME.c_str());
    if (file.good())
    {
        int id;
        string name, x, y;
        while (file >> id >> name >> x >> y)
        {
            nameToId[name] = id;
            output << id << " " << name << " " << x << " " << y << endl;
        }
    }
    file.close();
    
    file.open(LINKS_FILENAME.c_str());
    if (file.good())
    {
        int id = 0;
        string name, cityA, cityB;
        while (file >> name >> cityA >> cityB)
        {
            output << id++ << " " << name << " " << nameToId[cityA] << " " << nameToId[cityB] << endl;
        }
    }
    file.close();
    
    output.close();
    
    return 0;
}
