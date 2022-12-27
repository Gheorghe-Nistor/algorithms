/*
 * Edmonds-Karp's algorithm
 * https://www.infoarena.ro/problema/harta
 */
#include <bits/stdc++.h>

using namespace std;

ifstream in("harta.in");
ofstream out("harta.out");

int V, E, s, t;
vector<pair<int, int>> parrent, rightNodes;
vector<vector<pair<int, pair<int, int>>>> adjListRes;

void addEdge(int u, int v){
    adjListRes[u].push_back({v, {1, adjListRes[v].size()}});
    adjListRes[v].push_back({u, {0, adjListRes[u].size()-1}});
    if(v == t)
        rightNodes.emplace_back(u, adjListRes[u].size()-1);
}

void init() {
    s = 0;
    t = 2*V+1;
    parrent.resize(t+1);
    adjListRes.resize(t+1);
    for(int u = 1; u <= V; u++)
        for(int v = 1; v <= V; v++){
            if(u == v)
                continue;
            addEdge(u, V+v);
        }
}

void read(){
    in >> V;
    init();
    for(int i = 1; i <= V; i++){
        int outDeg, inDeg;
        in >> outDeg >> inDeg;
        addEdge(s, i);
        adjListRes[s][i-1].second.first = outDeg;
        addEdge(V+i, t);
        adjListRes[V+i][adjListRes[V+i].size()-1].second.first = inDeg;
    }
}

bool bf(){
    vector<bool> visited(t+1);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parrent[s] = {-1, -1};
    while(!q.empty()){
        int u = q.front();
        q.pop();
        if(u == t)
            continue;
        int i = 0;
        for(auto node: adjListRes[u]){
            int v, c; // node, capacity
            v = node.first;
            c = node.second.first;
            if(!visited[v] and c){
                parrent[v] = {u, i};
                visited[v] = true;
                q.push(v);
            }
            i++;
        }
    }
    return visited[t];
}

long long int maxFlow(){
    long long int max_flow = 0;
    while(bf()) {
        for (auto node: rightNodes) {
            int u, v, i, j, min_path = 1;
            parrent[t] = node;
            v = t;
            while (parrent[v].first != -1) {
                u = parrent[v].first;
                i = parrent[v].second;
                min_path = min(min_path, adjListRes[u][i].second.first);
                v = u;
            }
            v = t;
            while (parrent[v].first != -1) {
                u = parrent[v].first;
                i = parrent[v].second;
                j = adjListRes[u][i].second.second;
                adjListRes[u][i].second.first -= min_path;
                adjListRes[v][j].second.first += min_path;
                v = u;
            }
            max_flow += min_path;
        }
    }
    return max_flow;
}

int main(){
    read();
    out << maxFlow() << '\n';
    for(int u = 1; u <= V; u++) {
        for (auto node: adjListRes[u]) {
            int v, c;
            v = node.first;
            c = node.second.first;
            if(v && c == 0)
                out << u << " " << v-V << '\n';
        }
    }
    return 0;
}