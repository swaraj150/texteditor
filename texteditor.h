#pragma once
#include "file_handle.h"
#include "userinput.h"
class TextEditor{
    private:
        FileHandle fileHandle;
        Input input;
    public:
        TextEditor();
        void run(std::string filename);
};