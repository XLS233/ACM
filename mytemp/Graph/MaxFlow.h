#pragma once

#include <vector>
#include <queue>

struct Flow {
    static constexpr int INF = 1e9;
    int n;
    struct Edge {
        int to, cap;
        Edge(int to, int cap) : to(to), cap(cap) {}
    };
    std::vector<Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, d;
    Flow(int n) : n(n), g(n) {}
    bool bfs(int s, int t) {
        cur.assign(n, 0);
        d.assign(n, -1);
        std::queue<int> q;
        cur[s] = 0;
        d[s] = 0;
        q.push(s);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int i : g[u]) {
                int ver = e[i].to;
                if (d[ver] == -1 && e[i].cap) {
                    cur[ver] = 0;
                    d[ver] = d[u] + 1;
                    if (ver == t) return true;
                    q.push(ver);
                }
            }
        }
        return false;
    }
    int find(int u, int t, int limit) {
        if (u == t) return limit;
        int flow = 0;
        for (int i = cur[u]; i < g[u].size() && flow < limit; i ++ ) {
            cur[u] = i;
            int j = g[u][i];
            int ver = e[j].to;
            int c = e[j].cap;
            if (d[ver] == d[u] + 1 && e[j].cap) {
                int a = find(ver, t, std::min(e[j].cap, limit - flow));
                if (!a) d[ver] = -1;
                e[j].cap -= a, e[j ^ 1].cap += a, flow += a;
            }
        }
        return flow;
    }
    void addEdge(int u, int v, int c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    int dinic(int s, int t) {
        int r = 0, flow;
        while (bfs(s, t)) while (flow = find(s, t, INF)) r += flow;
        return r;
    }
    int maxFlow(int s, int t) {
        return dinic(s, t);
    }
};