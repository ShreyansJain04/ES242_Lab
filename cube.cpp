#include <cstdio>
#include <vector>
#include <array>
#include <iostream>
#include <queue>
#include <math.h>
#include <assert.h>
#include <utility>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

struct board {
    int e[7];
};
struct board2 {
    int o[2];
};
struct colorboard {
    char c[6][4];
};
struct testi {
    string t[21];
};
int fact(int i)
{
    int p = 1;
    for (int j = 2; j <= i; ++j) {
        p *= j;
    }
    return p;
}

testi brg(const colorboard & b){
    testi arr;
    char col[6]={b.c[0][0],b.c[1][0],b.c[2][0],b.c[3][0],b.c[4][0],b.c[5][0]};
    int res[21][3]={
        {0,3,4},{4,0,3},{3,4,0},
        {0,4,1},{1,0,4},{4,1,0},
        {0,5,3},{3,0,5},{5,3,0},
        {0,1,5},{5,0,1},{1,5,0},
        {2,4,3},{3,2,4},{4,3,2},
        {2,1,4},{4,2,1},{1,4,2},
        {2,5,1},{1,2,5},{5,1,2}};
    for(int i=0;i<21;i++){
        string str;
        for(int j=0;j<3;j++){
            str.push_back(col[res[i][j]]);
        }
        arr.t[i]=str;
        str.clear();
    }    
    return arr;
}
board transfer(const colorboard& b,const testi& arr){
    board ans;
    string str;
    str.push_back(b.c[0][0]);
    str.push_back(b.c[3][1]);
    str.push_back(b.c[4][2]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(0)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[0][1]);
    str.push_back(b.c[4][3]);
    str.push_back(b.c[1][0]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(1)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[0][2]);
    str.push_back(b.c[5][0]);
    str.push_back(b.c[3][3]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(2)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[0][3]);
    str.push_back(b.c[1][2]);
    str.push_back(b.c[5][1]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(3)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[2][0]);
    str.push_back(b.c[4][0]);
    str.push_back(b.c[3][0]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(4)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[2][1]);
    str.push_back(b.c[1][1]);
    str.push_back(b.c[4][1]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(5)*3+(i%3);
        }
    }
    str.clear();
    str.push_back(b.c[2][3]);
    str.push_back(b.c[5][3]);
    str.push_back(b.c[1][3]);
    for (int i=0;i<21;i++){
        if (str==arr.t[i]){
            ans.e[i/3]=(6)*3+(i%3);
        }
    }
    return ans;
}
char clr(const char c){
    if(c=='r'){
        return 'o';
    }
    if(c=='o'){
        return 'r';
    }
    if(c=='w'){
        return 'y';
    }
    if(c=='y'){
        return 'w';
    }
    if(c=='b'){
        return 'g';
    }
    if(c=='g'){
        return 'b';
    }
    return ' ';
}
colorboard transfer1(const colorboard & b)
{
    colorboard temp;

    for(int i=0;i<4;i++){
        temp.c[2][i]=b.c[2][2];
    }
    for(int i=0;i<4;i++){
        temp.c[3][i]=b.c[3][2];
    }
    for(int i=0;i<4;i++){
        temp.c[5][i]=b.c[5][2];
    }
    for(int i=0;i<4;i++){
        temp.c[0][i]=clr(b.c[2][2]);
    }
    for(int i=0;i<4;i++){
        temp.c[1][i]=clr(b.c[3][2]);
    }
    for(int i=0;i<4;i++){
        temp.c[4][i]=clr(b.c[5][2]);
    }
    return temp;

}

void read_board(colorboard& b)
{
    for (int r = 0; r < 6; ++r) {
        for(int cl = 0; cl < 4; ++cl){
            scanf("%s", &b.c[r][cl]);
            // if (b.c[r][cl]=='r'){
            //     b.c[r][cl]='o';
            // }else if (b.c[r][cl]=='o'){
            //     b.c[r][cl]='r';
            // }
        }
    }
}

board front(const board& b)
{
    board o = b;
    int arr[21]={3,4,5,9,10,11,0,1,2,6,7,8,12,13,14,15,16,17,18,19,20};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

board right(const board& b)
{
    board o = b;
    int arr[21]={0,1,2,17,15,16,6,7,8,4,5,3,12,13,14,19,20,18,11,9,10};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

board up(const board& b)
{
    board o = b;
    int arr[21]={14,12,13,1,2,0,6,7,8,9,10,11,16,17,15,5,3,4,18,19,20};
    for (int i=0;i<7;i++){
        o.e[i]=arr[o.e[i]];
    }
    return o;
}

enum move { R=1,U=2,F=3,R2=4,U2=5,F2=6,R1=7,U1=8,F1=9};

int ord(const board& board){
    int val=0;
    int k=6;
    for (int r = 0; r < 7; ++r) {
        int v=board.e[r];
        val+=v*pow(21,k);
        k-=1;
    }
    return val;
}
board2 decode(const board& res){
    board temp;
    board2 temp1;
    int k=0,val=0;
    for (int i=0;i<7;i++){
        temp.e[i]=(res.e[i]/3)+1;
        val+=(res.e[i]%3)*pow(3,k);
        k++;
    }
    int seen[8] = { 0 };
        int a = 0;
        int t = 6;

        for (int r = 0; r < 7; ++r) {
                int v = temp.e[r];
                int o = 0;
                for (int i = 1; i < v; ++i) {
                    if (!seen[i]) { ++o; }
                }
                a += o * fact(t);
                --t;
                seen[v] = 1;
    }
    temp1.o[0]=a;
    temp1.o[1]=val;
    return temp1;
}
board decode(int ord){
    board node;
    int temp=ord;
    
    for (int r = 6; r >=0; r--) {
        node.e[r]=temp%21;
        temp=temp/21;
    }
    return node;
}
#define maxi1 (5050) 
#define maxi2 (2190) 
std::vector<int> solve(const board& src, const board& dest)
{ 
    queue <int> q;
    int cnt=0;
    int visited[maxi1][maxi2];
    int parent[maxi1][maxi2];
    int initial=ord(src);
    int final=ord(dest);
    q.push(ord(src));
    board2 tem1=decode(src);
    visited[tem1.o[0]][tem1.o[1]] = U;
    int temp=0;
    while (!q.empty()) {
        int child = q.front();
        q.pop();
        board u=decode(child);
        if (child==final) {
            std::vector<int> moves;
            while (child!=initial) {
                board2 tem2=decode(decode(child));
                moves.push_back(visited[tem2.o[0]][tem2.o[1]]);
                child=parent[tem2.o[0]][tem2.o[1]];
            }
            std::reverse(moves.begin(), moves.end());
            std::vector<int> ans;
            int prev=0;
            for (auto cur:moves){
                auto tem=cur;
                if (cur==prev){
                    int fla=ans.back();
                    ans.pop_back();
                    if(fla==cur){
                        tem+=3;
                    }else{
                        tem+=6;
                    }
                }
                prev=cur;
                ans.push_back(tem);
            }
            return ans;
        }

        board a = front(u);
        board b = right(u);
        board c = up(u);

        board2 aord = decode(a);
        board2 bord = decode(b);
        board2 cord = decode(c);

        if (!visited[aord.o[0]][aord.o[1]]) {
            visited[aord.o[0]][aord.o[1]] = F;
            parent[aord.o[0]][aord.o[1]] = child;
            q.push(ord(a));
            cnt+=1;
        }
        if (!visited[bord.o[0]][bord.o[1]]) {
            visited[bord.o[0]][bord.o[1]] = R;
            parent[bord.o[0]][bord.o[1]] = child;
            q.push(ord(b));
            cnt+=1;
        }
        if (!visited[cord.o[0]][cord.o[1]]) {
            visited[cord.o[0]][cord.o[1]] = U;
            parent[cord.o[0]][cord.o[1]] = child;
            q.push(ord(c));
            cnt+=1;
        }
        temp+=1;
    }
    printf("Not possible");
    return std::vector<int>( );
}

void print_moves(const std::vector<int>& moves)
{
    for (auto m: moves) {
        switch (m) {
        case U: printf("U "); break;
        case F: printf("F "); break;
        case R: printf("R "); break;
        case U1: printf("U' "); break;
        case F1: printf("F' "); break;
        case R1: printf("R' "); break;
        case U2: printf("U2 "); break;
        case F2: printf("F2 "); break;
        case R2: printf("R2 "); break;
        }
    }
    printf("\n");
}

int main()
{
    colorboard src1;
    read_board(src1);
    colorboard dest1=transfer1(src1);
    board src=transfer(src1,brg(dest1));
    board dest=transfer(dest1,brg(dest1));
    printf("\n");
    printf("Given Input :\n");
    printf("\n");
    printf("\n");
    printf("Destination :\n");
    printf("\n");
    printf("\n");
    auto moves = solve(src, dest);
    print_moves(moves);
    return 0;
}
