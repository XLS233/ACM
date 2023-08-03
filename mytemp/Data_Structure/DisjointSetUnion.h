/* 
 * 并查集（DSU）
 * 相关函数：
 * 1. DSU(int n)：构造函数，n 为集合大小，默认为 0
 * 2. int find(int x)：并查集核心函数，返回 x 所属的集合，只使用了路径压缩，没有按秩合并
 * 3. bool same(int x, int y)：返回 x 和 y 是否属于同一集合
 * 4. bool merge(int x, int y)： 合并 x 和 y，并返回是否合并成功
 * 5. int size(int x)：返回 x 所属集合大小
*/ 

#pragma once

#include <vector>
#include <numeric>

struct DSU {
    std::vector<int> p, siz;
    DSU(int n = 0) : p(n), siz(n, 1) { std::iota(p.begin(), p.end(), 0); }
    int find(int x) {
        if (p[x] != x) p[x] = find(p[x]);
        return p[x];
    }
    bool same(int x, int y) { return find(x) == find(y); }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[find(x)]; }
};