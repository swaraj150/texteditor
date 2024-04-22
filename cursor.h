#pragma once
#include<iostream>
class Cursor{

    public:
        int cursorX,cursorY;
        Cursor();
        Cursor(int x,int y);
        std::pair<int,int> getCursorPosition() const;  
        void setCursorPosition(Cursor* c,int x,int y);  
        void moveUp(Cursor* c);
        void moveDown(Cursor* c);
        void moveLeft(Cursor* c);
        void moveRight(Cursor* c);
        void display(int x,int y);
};