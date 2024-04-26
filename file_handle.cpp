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
    int k=0;
    
    while(f.get(c)){
        // std::cout<<c;
        if(c=='\n'){
            // std::cout<<"\n";
            // t->getbuffer().display();
            // std::cout<<"\n";
            // t->fillchar(c,{i,j});
            // k++;
            i++;
            j=1;
            k++;
            
            
            // t.display()
            // std::cout<<"\n";;
            continue;
            
        } 
       text.fillchar(c,{i,j});
        k=0;
        // k=0;
        // std::cout<<"\n";
        // t->getbuffer().display();
        // std::cout<<"\n";
        // // std::cout<<c;
        j++;
    }
    if(k>0){
        text.fillchar('\n',{i,j});
        i++;
    }
   
    // std::cout<<"from loadfile\n";
    
    
    return std::make_pair(i,j);
    
}


Text FileHandle::getText() const{
    return text;
}
void FileHandle::setText(Text t){
    text=t;
}