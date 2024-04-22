#pragma once
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
    ESCAPE=27

};
class Input{
    private:
        Text t;
        Cursor cursor;
        eKeys keys;
    public:
        Input();
        eKeys getKeys()const;
        void userinput();
        Text getText()const;
};