#pragma once
#include "text.h"
#include "userinput.h"
class FileHandle{
    private:
        Text text;
    public:
        FileHandle();
        void saveFile(std::string name);
        void renameFile(std::string name);
        std::pair<int,int> loadFile(std::string path);
        Text getText()const;
        void setText(Text t);
        
};