#include "texteditor.h"

int main(int argc,char* argv[]){
    if(argc>2){
        std::cout<<"ERROR!!\n";
        return -1;
    }
    TextEditor textEditor;
    textEditor.run(argv[1]);
    return 0;   
}

//g++ .\main.cpp .\text.cpp .\cursor.cpp .\gap_buffer.cpp .\userinput.cpp .\texteditor.cpp .\file_handle.cpp -o main.exe