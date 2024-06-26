#pragma once
#include "gap_buffer.h"
#include "cursor.h"
#include<map>
class Text{
    private:
        GapBuffer g;
        std::vector<int> ptrs;
        std::map<int,std::pair<int,int>> visited;
        std::string buffer;
         
        // Cursor c;
    public:
        Text();
    
        void fillchar(char c,std::pair<int,int> pos);
        void copytext(std::pair<int,int> pos1,std::pair<int,int> pos2);
        std::pair<int,int> pastetext(std::pair<int,int> pos1);
        void fillstring(std::string c);
        void removechar(std::pair<int,int> pos);
        GapBuffer getbuffer() const;
        std::map<int,std::pair<int,int>> getVisited()const;
        // Cursor getcursor() const;
        // void setCursor(Cursor c1);
        // Cursor getCursor();
        // std::vector<int> getptrs();
        
        // std::vector<GapBuffer> getbuffer();
        void display();
        // std::vector<GapBuffer> copytext();
        // void pastetext(std::vector<GapBuffer> g1);
        // void undo();
        // void redo();
    
        

          
};