#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int V, finalState, ans = 0;
        V = (int) graph.size();
        if(V < 2)
            return 0;
        finalState = (1<<V)-1;
        vector<vector<bool>> visited(V, vector<bool>(finalState));
        queue<pair<int, int>> q;
        for(int u = 0; u < V; u++)
            q.push({u, 1<<u});
        while(!q.empty()){
            ++ans;
            int size = (int) q.size();
            while(size--){
                int u, currState;
                u = q.front().first;
                currState = q.front().second;
                q.pop();
                for(auto & v: graph[u]){
                    int nextState = currState | (1<<v);
                    if(nextState == finalState)
                        return ans;
                    if(!visited[v][nextState]){
                        visited[v][nextState] = true;
                        q.push({v, nextState});
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> graph = {{1,2,3},{0},{0},{0}};
    cout << s.shortestPathLength(graph);
    return 0;
}
