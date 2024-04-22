#include "texteditor.h"
#include<fstream>
TextEditor::TextEditor(){
    fileHandle=FileHandle();
    input=Input();
}

void TextEditor::run(std::string filename){
    input.userinput();
    
    fileHandle.setText(input.getText());    
    fileHandle.saveFile(filename);
}