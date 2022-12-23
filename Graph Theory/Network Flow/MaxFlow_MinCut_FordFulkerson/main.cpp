/*
 * Edmonds-Karp's algorithm
 * Complexity: O(V*E^2)
 * https://www.infoarena.ro/problema/maxflow 100p
 */

#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <set>
#include <queue>
#include <stack>

using namespace std;

ifstream fin("maxflow.in");
ofstream fout("maxflow.out");

int V, E, s, t;
vector<int> parrent;
vector<vector<int>> capacity;
vector<vector<int>> adjListRes;

void init() {
    s = 1;
    t = V;
    adjListRes.resize(V+1);
    parrent.resize(V+1);
    capacity.resize(V+1, vector<int>(V+1));
}

void read(){
    fin >> V >> E;
    init();
    for(int i = 1; i <= E; i++){
        int u, v;
        long c;
        fin >> u >> v >> c;
        adjListRes[u].push_back(v);
        adjListRes[v].push_back(u);
        capacity[u][v] = c;
    }
}

bool bf(){
    vector<bool> visited(V+1);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parrent[s] = -1;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(auto v: adjListRes[u]){
            if(!visited[v] and capacity[u][v]){
                parrent[v] = u;
                if(v == t)
                    return true;
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

int maxFlow(){
    long max_flow = 0;
    set<int> temp;
    while(bf()){
        int u, v, path_flow = INT_MAX;
        for(v = t; v != s; v = parrent[v]){
            u = parrent[v];
            if(capacity[u][v] < path_flow)
                path_flow = capacity[u][v];
        }
        for(v = t; v != s; v = parrent[v]){
            u = parrent[v];
            capacity[u][v] -= path_flow;
            capacity[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

set<int> minCut(){
    vector<bool> visited(V+1);
    stack<int> stack;
    stack.push(s);
    set<int> solution;
    while(!stack.empty()){
        int u = stack.top();
        stack.pop();
        visited[u] = true;
        solution.insert(u);
        for(auto v: adjListRes[u]){
            if(!visited[v] && capacity[u][v]){
                stack.push(v);
            }
        }
    }
    return solution;
}

int main() {
    read();
    /* max-flow */
    int _maxFlow = maxFlow();
    fout << _maxFlow; // infoarena
    cout << _maxFlow << '\n';
    /* min-cut*/
    set<int> _minCut = minCut();
    for(auto u: _minCut)
        cout << u << " ";
    return 0;
}