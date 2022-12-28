/*
 *
 * https://leetcode.com/problems/valid-arrangement-of-pairs/discussion/
 * Complexity: O(V+E)
 */
#include <bits/stdc++.h>

using namespace std;

class Solution {
    void postOrderDFS(unordered_map<int, stack<int>>& adjList, vector<vector<int>>& solution, int u){
        stack<int>& edgesStack = adjList[u];
        while(!edgesStack.empty()){
            int v = edgesStack.top();
            edgesStack.pop();
            postOrderDFS(adjList, solution, v);
            solution.push_back({u, v});
        }
    }
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        int s; // the starting node if it exists
        unordered_map<int, stack<int>> adjList;
        unordered_map<int, int> inDeg, outDeg;
        adjList.reserve(pairs.size());
        inDeg.reserve(pairs.size());
        outDeg.reserve(pairs.size());
        for(auto & pair: pairs){
            int u, v;
            u = pair[0];
            v = pair[1];
            adjList[u].push(v);
            inDeg[v]++;
            outDeg[u]++;
        }
        for(auto & i : adjList) {
            int u = i.first;
            if (inDeg[u] + 1 == outDeg[u]) {
                s = u;
                break;
            }
        }
        vector<vector<int>> solution;
        postOrderDFS(adjList, solution, s);
        reverse(solution.begin(), solution.end());
        return solution;
    }
};

int main() {
    Solution s;
    vector<vector<int>> pairs = {{5,1},{4,5},{11,9},{9,4}};
    auto result = s.validArrangement(pairs);
    for(auto & pair: result)
        cout << '[' << pair[0] << ',' << pair[1] << "] ";
    return 0;
}