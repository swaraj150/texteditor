#pragma once
#include<stack>
#include "text.h"
#include "cursor.h"
enum eKeys{
    ARROW=224,
    UP=72,
    DOWN=80,
    LEFT=75,
    RIGHT=77,
    ENTER=13,
    SPACE=32,
    BACKSPACE=8,
    ESCAPE=27,
    COPY=3,
    PASTE=22,
    UNDO=26,
    REDO=25,
    CUT=24,
    START=49,
    END=50

};
class Input{
    private:
        Text t;
        Cursor cursor;
        eKeys keys;
        std::stack<std::pair<Text,Cursor>> undoStack;
        std::stack<std::pair<Text,Cursor>> redoStack;
        
    public:
        Input();
        eKeys getKeys()const;
        void saveState(Text t,Cursor c);
        void undo(Text &t,Cursor &c);
        void redo(Text &t,Cursor &c);
        void userinput();
        Text getText()const;
        void setText(Text t);
        Cursor getCursor()const;
        void setCursor(Cursor c);
};