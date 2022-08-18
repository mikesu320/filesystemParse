#include <vector>
#incude <iostream>

using namespace std;

vector<int> solution(vector<vector<int>> g, int s)
{
    int sz = g.size();
    for (int i = 0; i < sz; i++)
        g[i][i] = 0;

    vector<int> sol(g[s].begin(), g[s].end());
    for (int i = 0; i < sz; i++) {
        if (sol[i] == -1)
            sol[i] = INT_MAX;
    }
    cout << endl;
    vector<int> root(sol.begin(), sol.end());
    for (int i = 0; i < sz; i++) {
        if (i == s)
            continue;
        int curRoot = root[i];
        if (curRoot == INT_MAX) {
            continue;
        }
        vector<int> cur = g[i];
        for (int j = 0; j < sz; j++) {
            if (cur[j] == -1 || i == j)
                continue;

            sol[j] = min(sol[j], cur[j] + curRoot);
        }
    }
    return sol;
}