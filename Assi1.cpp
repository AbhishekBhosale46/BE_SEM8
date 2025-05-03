#include<bits/stdc++.h>
using namespace std;

class Graph{

    public:
    int size;
    vector<int> *adjList;

    Graph(int size){
        this->size = size;
        adjList = new vector<int>[size];
    }

    void addEdge(int v1, int v2){
        adjList[v1].push_back(v2);
        adjList[v2].push_back(v1);
    }

    void printGraph(){
        for(int i=0; i<this->size; i++){
            cout<<i<<" : ";
            for(auto j: adjList[i]){
                cout<<j<<" ";
            }
            cout<<endl;
        }
    }

    void bfs(int start){
        vector<bool> visited(this->size, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while(!q.empty()){
            int currNode = q.front();
            q.pop();
            cout<<currNode<<endl;
            for(int i=0; i<adjList[currNode].size(); i++){
                if(!visited[adjList[currNode][i]]){
                    q.push(adjList[currNode][i]);
                    visited[adjList[currNode][i]] = true;
                }
            }
        }
    }

    void dfs(int start){
        vector<bool> visited(this->size, false);
        dfsUtil(start, visited);
    }

    void dfsUtil(int currNode, vector<bool> &visited){
        visited[currNode] = true;
        cout<<currNode<<endl;
        for(int i=0; i<adjList[currNode].size(); i++){
            if(!visited[adjList[currNode][i]]){
                dfsUtil(adjList[currNode][i], visited);
            }
        }
    }

};

int main(){
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 4);
    g.addEdge(1, 3);
    g.addEdge(2, 5);
    g.bfs(0);
    cout<<endl;
    g.dfs(0);
    return 0;
}