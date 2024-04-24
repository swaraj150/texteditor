#include "file_handle.h"
#include<fstream>
#include <sstream>

FileHandle::FileHandle(){
    text=Text();
    
}

void FileHandle::saveFile(std::string name){
    std::string filename=name+".txt";
    std::ofstream f(filename);
    // std::cout<<"\nfrom filehandle\n";
    // text.display();
    for(char i:text.getbuffer().buffer){
        if(i!='_'){
            f<<i;
        }
    }
    f.close();
}
void FileHandle::renameFile(std::string name){
    
}
std::pair<int,int> FileHandle::loadFile(std::string path){
    std::ifstream f(path+".txt");
    char c;
    int i=1,j=1;
    
    while(f.get(c)){
        std::cout<<c;
        if(c=='\n'){
            i++;
            j=1;
            continue;
        }
        text.fillchar(c,{i,j});
        // std::cout<<c;
        j++;
    }
    // std::cout<<"from loadfile\n";
    // text.display();
    
    return std::make_pair(i,j);
    
}


Text FileHandle::getText() const{
    return text;
}
void FileHandle::setText(Text t){
    text=t;
}