#include <cstdio>
#include <vector>
#include <array>
#include <algorithm>
#include <tuple>
#include "queue.hpp"

struct board {
    int e[3][3];
};

int ord(const board& board){

    int a = 0;
    int k = 1;

    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            a += (board.e[r][c] *k);
            k = k*7;

        }
    }

    return a;
}
void read_board(board& b)
{
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            scanf("%d", &b.e[r][c]);
        }
    }
}

std::tuple<int, int> find_space(const board& b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (b.e[r][c] == 0) return { r, c };
    assert(0);
    return { 0 , 0};
}

board up(const board& b)
{
    const std::tuple<int, int> space = find_space(b);
    const int r = std::get<0>(space);
    const int c = std::get<1>(space);
    if (r == 2) return b;
    board o = b;
    if (o.e[r+1][c] == 1) {
        o.e[r][c] = 3;
    }
    else if (o.e[r+1][c] == 2) {
        o.e[r][c] = 2;
    }
    else if (o.e[r+1][c] == 3) {
        o.e[r][c] = 6;
    }
    else if (o.e[r+1][c] == 4) {
        o.e[r][c] = 4;
    }
    else if (o.e[r+1][c] == 5) {
        o.e[r][c] = 1;
    }
    else if (o.e[r+1][c] == 6) {
        o.e[r][c] = 5;
    }
    o.e[r+1][c] = 0;
    return o;
}

board down(const board& b)
{
    const std::tuple<int, int> space = find_space(b);
    const int r = std::get<0>(space);
    const int c = std::get<1>(space);
    if (r == 0) return b;
    board o = b;
    if (o.e[r-1][c] == 1) {
        o.e[r][c] = 5;
    }
    else if (o.e[r-1][c] == 2) {
        o.e[r][c] = 2;
    }
    else if (o.e[r-1][c] == 3) {
        o.e[r][c] = 1;
    }
    else if (o.e[r-1][c] == 4) {
        o.e[r][c] = 4;
    }
    else if (o.e[r-1][c] == 5) {
        o.e[r][c] = 6;
    }
    else if (o.e[r-1][c] == 6) {
        o.e[r][c] = 3;
    }
    o.e[r-1][c] = 0;
    return o;
}

board left(const board& b)
{
    const std::tuple<int, int> space = find_space(b);
    const int r = std::get<0>(space);
    const int c = std::get<1>(space);
    if (c == 2) return b;
    board o = b;
    if (o.e[r][c+1] == 1) {
        o.e[r][c] = 2;
    }
    else if (o.e[r][c+1] == 2) {
        o.e[r][c] = 6;
    }
    else if (o.e[r][c+1] == 3) {
        o.e[r][c] = 3;
    }
    else if (o.e[r][c+1] == 4) {
        o.e[r][c] = 1;
    }
    else if (o.e[r][c+1] == 5) {
        o.e[r][c] = 5;
    }
    else if (o.e[r][c+1] == 6) {
        o.e[r][c] = 4;
    }
    o.e[r][c+1] = 0;
    return o;
}

board right(const board& b)
{
    const std::tuple<int, int> space = find_space(b);
    const int r = std::get<0>(space);
    const int c = std::get<1>(space);
    if (c == 0) return b;
    board o = b;
    if (o.e[r][c-1] == 1) {
        o.e[r][c] = 4;
    }
    else if (o.e[r][c-1] == 2) {
        o.e[r][c] = 1;
    }
    else if (o.e[r][c-1] == 3) {
        o.e[r][c] = 3;
    }
    else if (o.e[r][c-1] == 4) {
        o.e[r][c] = 6;
    }
    else if (o.e[r][c-1] == 5) {
        o.e[r][c] = 5;
    }
    else if (o.e[r][c-1] == 6) {
        o.e[r][c] = 2;
    }
    o.e[r][c-1] = 0;
    return o;
}


bool is_same(const board& a, const board &b)
{
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (a.e[r][c] != b.e[r][c]) return false;

    return true;
}

enum move { L = 1, R = 2, U = 3, D = 4 };


#define maxstate (40353700)
std::vector<int> solve(const board& src, const board& dest)
{
    queue<board, maxstate> q;
    int visited[maxstate];
    board parent[maxstate];

    enqueue(q, src);
    visited[ord(src)] = L;

    while (!is_empty(q)) {
        board u = dequeue(q);
        if (is_same(u, dest)) {
            std::vector<int> moves;
            board c = u;
            int o = ord(c);
            while (!is_same(c, src)) {
                moves.push_back(visited[o]);
                c = parent[o];
                o = ord(c);
            }
            std::reverse(moves.begin(), moves.end());
            return moves;
        }

        board a = up(u);
        board b = down(u);
        board c = left(u);
        board d = right(u);

        int aord = ord(a);
        int bord = ord(b);
        int cord = ord(c);
        int dord = ord(d);
        
        if (!visited[aord]) {
            visited[aord] = U;
            parent[aord] = u;
            enqueue(q, a);
        }
        if (!visited[bord]) {
            visited[bord] = D;
            parent[bord] = u;
            enqueue(q, b);
        }
        if (!visited[cord]) {
            visited[cord] = L;
            parent[cord] = u;
            enqueue(q, c);
        }
        if (!visited[dord]) {
            visited[dord] = R;
            parent[dord] = u;
            enqueue(q, d);
        }
    }

    printf("\nUnsolvable\n");
    return{0};
}

void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case L: printf("L "); break;
        case R: printf("R "); break;
        case U: printf("U "); break;
        case D: printf("D "); break;
        }
    }
    printf("\n");
}

int main()
{
    board src, dest;

    read_board(src);
     for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            dest.e[r][c]=1;
        }
    }
    dest.e[1][1]=0;
    
    auto moves = solve(src, dest);
    print_moves(moves);

    return 0;
}
