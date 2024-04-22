#pragma once
#include<vector>
#define SIZE 15
class GapBuffer{
    public:
        std::vector<char> buffer;
        int gapSize = 25;
        int left;
        int right;
        GapBuffer(int size);
        GapBuffer();
        void move_left(int position);
        void move_right(int position);
        void grow(int position);
        void move(int position);
        void insert(int position, char c);
        void remove(int position);
        void display();
};