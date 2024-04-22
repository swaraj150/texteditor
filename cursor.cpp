#include "cursor.h"


Cursor::Cursor():cursorX(1),cursorY(1){}
Cursor::Cursor(int x,int y):cursorX(x),cursorY(y){}

std::pair<int,int> Cursor::getCursorPosition() const{
    return std::make_pair(cursorX,cursorY);
}

void Cursor::setCursorPosition(Cursor* c,int x,int y){
    c->cursorX=x;
    c->cursorY=y;
    printf("\033[%d;%dH", x, y);
    
}

void Cursor::moveUp(Cursor* c){
    c->cursorX==1?c->cursorX:c->cursorX--;
    
    // display(cursorX,cursorY);

}
void Cursor::moveDown(Cursor* c){
    c->cursorX++;
    
    // display(cursorX,cursorY);
}
void Cursor::moveLeft(Cursor* c){
    c->cursorY==1?c->cursorY:c->cursorY--;
    
    // display(cursorX,cursorY);
}
void Cursor::moveRight(Cursor* c){
    c->cursorY++;
    // std::cout<<"\033[C";
    // display(cursorX,cursorY);
}

void Cursor::display(int x,int y){
    std::cout<<"Line No. "<<x+1<<" Col "<<y+1<<"\n";
}