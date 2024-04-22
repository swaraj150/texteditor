#include "texteditor.h"
#include<fstream>
#ifdef _WIN32
#include<conio.h>
#endif
TextEditor::TextEditor(){
    fileHandle=FileHandle();
    input=Input();
}

void TextEditor::run(std::string filename){
    std::cout<<"\033[2J";
    printf("\033[%d;%dH", 1, 1);

    auto cursor=fileHandle.loadFile(filename);
    input.setText(fileHandle.getText());
    input.setCursor(Cursor(cursor.first,cursor.second));
    input.userinput();
    std::cout<<"\033[2J";
    
    std::cout<<"Save changes made to file ?\n";
    std::cout<<"Yes - Y\tNo - N\n";
    #ifdef _WIN32
        int key=_getch();
    #endif
    if((char)key=='Y' || (char)(key)=='y'){
        fileHandle.setText(input.getText());    
        fileHandle.saveFile(filename);
        std::cout<<"Saved Succesfully!!\n";
    } 
    
}