#include "file_handle.h"
#include<fstream>
#include <sstream>

FileHandle::FileHandle(){
    text=Text();
    
}

void FileHandle::saveFile(std::string name){
    std::string filename=name+".txt";
    std::ofstream f(filename);
    std::cout<<"\nfrom filehandle\n";
    text.display();
    for(char i:text.getbuffer().buffer){
        if(i!='_'){
            f<<i;
        }
        
    }
    f.close();
}
void FileHandle::renameFile(std::string name){
    
}
void FileHandle::loadFile(std::string path){
    std::ifstream f(path);
    char c;
    int i=0;
    GapBuffer g(100);
    while(f.get(c)){
        g.insert(i++,c);
    }
    text.display();
}


Text FileHandle::getText() const{
    return text;
}
void FileHandle::setText(Text t){
    text=t;
}