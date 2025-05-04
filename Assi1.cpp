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

    void bfsPar(int start){
        vector<bool> visited(this->size, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while(!q.empty()){
            int currNode = q.front();
            q.pop();
            cout<<currNode<<endl;
            #pragma omp parallel for
            for(int i=0; i<adjList[currNode].size(); i++){
                bool check_visited;
                #pragma omp critical
                {
                    check_visited = visited[adjList[currNode][i]];
                }
                if(!check_visited){
                    #pragma omp critical
                    {
                    q.push(adjList[currNode][i]);
                    visited[adjList[currNode][i]] = true;
                    }
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

    vector<int> dfs_parallel(int start_vertex){
        vector<int> dfs_traversal;
        map<int, bool> is_visited;
        stack<int> st;
        st.push(start_vertex);
        while (!st.empty()){
            int top = st.top();
            st.pop();
            if (!is_visited[top]){
                dfs_traversal.push_back(top);
                is_visited[top] = true;
                vector<int> adj_elements = adjList[top];
                int l = adj_elements.size();
                #pragma omp parallel for
                for (int i = 0; i < l; i++){
                    bool check_visited ; 
                    #pragma omp critical 
                    {
                        check_visited = is_visited[adj_elements[i]];
                    }
                    if (!check_visited){
                        #pragma omp critical 
                        {
                            st.push(adj_elements[i]);
                        }
                    }
                }
            }
        }
        return dfs_traversal;
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
    g.bfsPar(0);
    cout<<endl;
    g.dfs(0);
    return 0;
}