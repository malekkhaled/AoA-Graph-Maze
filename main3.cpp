#include <iostream>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <stack>
#include <set>
using namespace std;


class Graph ;
enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

struct Edge
{
    pair<int,int> b;
    int w;
};
stack <Edge> stk;

class Graph 
{
public:
    map<pair<int,int>, vector<Edge>> adj;
    set<pair<int,int>> vertices;
    void addEdge(pair<int,int> s, pair<int,int> e, int weight);
};
  
void Graph::addEdge(pair<int,int> s, pair<int,int> e, int weight)
{
    Edge temp;
    temp.b = e;
    temp.w = weight;
    adj[s].push_back(temp);
    vertices.insert(e);
}


//Inspired from Dr. William Hendrix's DFS algorithm
void DFS(Graph& g, map<pair<int,int>,mark_t>& marks, pair <int,int>& start, vector<string>& ret, vector<vector<string>>& maze, int er, int ec)
{
    marks[start] = DISCOVERED;
    for(auto p : g.adj[start])
    {
        if(marks[make_pair(er,ec)] == EXPLORED)
            break;
        if(marks[p.b] == UNDISCOVERED && marks[make_pair(er,ec)] != EXPLORED)
            DFS(g,marks,p.b,ret,maze,er,ec);
        if(marks[make_pair(er,ec)] == EXPLORED)
            stk.push({start,p.w});
    }

    marks[start] = EXPLORED;
}



int main()
{
    ifstream in ("large.txt");
    istringstream iss;
    int r,c,rs,cs;
    string line;
    getline(in,line);
    iss.str(line);
    iss >> r >> c;
    iss.clear();
    getline(in,line);
    iss.str(line);
    iss >> rs >> cs;
    iss.clear();

    

    rs-=1;
    cs-=1;
    vector<vector<string>> maze (r, vector<string>(c,""));
    string curr;


    for (int i = 0; i < r; i++)
    {
        getline(in,line);
        iss.clear();
        iss.str(line);
        
        for (int j = 0; j < c; j++)
        {
            iss >> curr;
            maze[i][j] = curr;       
        }
    }
    
    int er,ec;
    Graph g;
    
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[i].size(); j++)
        {
            
            if (maze[i][j] != "X")
            {           
                g.vertices.insert(make_pair(i,j));

                if (maze[i][j] == "N")
                {
                    if((i-3) >= 0 && maze[i-3][j] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i-3,j),3);
                    if((i-4) >= 0 && maze[i-4][j] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i-4,j),4);
                }
                if (maze[i][j] == "S")
                {
                    if((i+3) < r && maze[i+3][j] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i+3,j),3);
                    if((i+4) < r && maze[i+4][j] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i+4,j),4);
                }
                if (maze[i][j] == "E")
                {
                    if((j+3) < c && maze[i][j+3] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i,j+3),3);
                    if((j+4) < c && maze[i][j+4] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i,j+4),4);
                }
                if (maze[i][j] == "W")
                {
                    if((j-3) >= 0 && maze[i][j-3] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i,j-3),3);
                    if((j-4) >= 0 && maze[i][j-4] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i,j-4),4);
                }
                if (maze[i][j] == "NE")
                {
                    if((j+3) < c && (i-3) >= 0 && maze[i-3][j+3] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i-3,j+3),3);
                    if((j+4) < c && (i-4) >= 0 && maze[i-4][j+4] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i-4,j+4),4);
                }
                if (maze[i][j] == "NW")
                {
                    if((j-3) >= 0 && (i-3) >= 0 && maze[i-3][j-3] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i-3,j-3),3);
                    if((j-4) >= 0 && (i-4) >= 0 && maze[i-4][j-4] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i-4,j-4),4);
                }
                if (maze[i][j] == "SE")
                {
                    if((j+3) < c && (i+3) < r && maze[i+3][j+3] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i+3,j+3),3);
                    if((j+4) < c && (i+4) < r && maze[i+4][j+4] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i+4,j+4),4);
                }
                if (maze[i][j] == "SW")
                {
                    if((j-3) >= 0 && (i+3) < r && maze[i+3][j-3] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i+3,j-3),3);
                    if((j-4) >= 0 && (i+4) < r && maze[i+4][j-4] != "X")
                        g.addEdge(make_pair(i,j), make_pair(i+4,j-4),4);
                }
                
                if (maze[i][j] == "J")
                {
                    er = i;
                    ec = j;
                }
            }    
        }
    }
    
    vector<string> ret;
    map<pair<int,int>,mark_t> marks;


    for(auto p : g.vertices)
        marks[p] = UNDISCOVERED;

    pair<int,int> start = make_pair(rs,cs);
    DFS(g, marks, start, ret, maze, er, ec);

    vector<int> wef;

    while(!stk.empty())
    {
        ret.push_back(maze[stk.top().b.first][stk.top().b.second] + "-");
        wef.push_back(stk.top().w);
        stk.pop();
    }

    ofstream out;
    out.open("sol3.txt");

   
    for(int i = 0; i < ret.size(); i++)
    {
        out << ret[i] ;
        out<<wef[i] <<" ";
    }

    
    out.close();


    return 0;
}

