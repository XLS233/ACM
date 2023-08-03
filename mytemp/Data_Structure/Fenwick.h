/* 
 * 树状数组（Fenwick）
 * 模板参数声明：
 * 1. 如若没有加减操作，需要自行重载运算加减运算符
 * 2. 模板参数要具有初始化的构造函数（如：int的默认值为0）
 * 相关函数：
 * 1. Fenwick<T>(int n)：构造函数，n 为数组大小，默认为 0
 * 2. int lowbit(int x)：树状数组核心操作，对 x 进行 lowbit 操作
 * 3. void add(int x, T v)：单点加操作
 * 4. void sub(int x, T v)：单点减操作
 * 5. T query(int x)：查询 x 的前缀信息，即数组下标 [1, x] 的信息和
 * 6. T rangeSum(int l, int r)：查询区间 [l, r] 的信息和
 * 注意：
 * 树状数组下标 0 为非法下标，且值恒为模板初始化构造函数！！！
*/ 

#pragma once

#include <vector>

template <typename T> 
struct Fenwick {
    const int n;
    std::vector<T> tr;
    Fenwick(int n = 0) : n(n), tr(n) {}
    int lowbit(int x) { return x & -x; }
    void add(int x, T v) {
        assert((x > 0, "树状数组下标必须大于0"));
        for (int i = x; i < n; i += lowbit(i)) tr[i] += v; 
    }
    void sub(int x, T v) {
        assert((x > 0, "树状数组下标必须大于0"));
        for (int i = x; i < n; i += lowbit(i)) tr[i] -= v;
    }
    T query(int x) { 
        T res = T();
        for (int i = x; i; i -= lowbit(i)) res += tr[i];
        return res;
    }
    T rangeSum(int l, int r) { 
        return query(r) - query(l - 1);
    }
};