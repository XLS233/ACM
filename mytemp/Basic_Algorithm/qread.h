#pragma once
#include <iostream>

#ifdef QREAD
struct InputOutputStream {
    enum { SIZE = 1000001 };
    char ibuf[SIZE], *s, *t, obuf[SIZE], *oh;
    bool eof;
    InputOutputStream() : s(), t(), oh(obuf), eof(false) {}
    ~InputOutputStream() { std::fwrite(obuf, 1, oh - obuf, stdout); }
    explicit operator bool() const {
        return static_cast<bool>(eof == false);
    }
    inline char read() {
        if (s == t) t = (s = ibuf) + std::fread(ibuf, 1, SIZE, stdin);
        return s == t ? -1 : *s++;
    }
    inline InputOutputStream &operator>>(char* x) {
        static char c;
        for (c = read(); std::isspace(c); c = read())
            if (c == -1) {eof = true; return *this;}
        for (; !std::isspace(c); c = read()) *x = c, ++x;
        *x = 0;
        return *this;
    }
    template <typename T>
    inline InputOutputStream &operator>>(T &x) {
        static char c;
        static bool iosig;
        for (c = read(), iosig = false; !isdigit(c); c = read()) {
            if (c == -1) {eof = true; return *this;}
            iosig |= c == '-';
        }
        for (x = 0; isdigit(c); c = read()) x = x * 10 + (c ^ '0');
        if (iosig) x = -x;
        return *this;
    }
    inline void print(char c) {
        if (oh == obuf + SIZE) {
            std::fwrite(obuf, 1, SIZE, stdout);
            oh = obuf;
        }
        *oh++ = c;
    }
    template <typename T>
    inline void print(T x) {
        static int buf[23], cnt;
        if (x != 0) {
            if (x < 0) print('-'), x = -x;
            for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 | 48;
            while (cnt) print((char)buf[cnt--]);
        } else print('0');
    }
    template <typename T>
    inline InputOutputStream &operator<<(const T &x) {
        print(x);
        return *this;
    }
    inline void print(const char* x) {
        for(; *x; x++)
            print(*x);
    }
    inline void print(char* x) {
        for(; *x; x++)
            print(*x);
    }    
} io;
#define cin io
#define cout io
#endif