#pragma once

#include <bits/stdc++.h>

template<class Edge>
struct Graph {
    std::vector<std::vector<std::pair<int, Edge>>> adj;
    Graph(int n = 0) : adj(n) {}
    void addEdge(int u, int v, Edge &e) {
        adj[u].push_back({v, e});
    }
    std::vector<int> topSort() {
        int n = adj.size();
        std::vector<int> in(n);
        for (int u = 0; u < n; u++) {
            for (auto &[v, w] : adj[u]) {
                in[v]++;
            }
        }
        std::queue<int> q;
        std::vector<int> ver;
        for (int i = 0; i < n; i++) {
            if (in[i] == 0) {
                q.push(i);
                ver.push_back(i);
            }
        }
        while (q.size()) {
            auto u = q.front();
            q.pop();
            for (auto &[v, w] : adj[u]) {
                if (--in[v] == 0) {
                    q.push(v);
                    ver.push_back(v);
                }
            }
        }
        return ver;
    }
    std::vector<Edge> dijkstra(int u, int v, Edge inf) {
        int n = adj.size();
        std::vector<Edge> dist(n, inf);
        dist[u] = Edge();
        std::vector<int> st(n);
        std::priority_queue<std::pair<Edge, int>> heap;
        heap.emplace(-dist[u], u);
        while (heap.size()) {
            auto [_, u] = heap.top();
            heap.pop();
            if (st[u]) continue;
            st[u] = true;
            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    heap.emplace(-dist[v], v);
                }
            }
        }
        return dist;
    }
};

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