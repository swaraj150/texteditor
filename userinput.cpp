#include "userinput.h"
#ifdef _WIN32
#include<conio.h>
#endif
Input::Input(){
    t=Text();
    cursor=Cursor();
}

eKeys Input::getKeys() const{
    return keys;
}

void Input::userinput(){
    
    std::pair<int,int> pos1={-1,-1};
    std::pair<int,int> pos2={-1,-1};
    std::cout << "\033["<< "@";
    while(true){
        #ifdef _WIN32
            int key=_getch();
        #endif
        if(key==ESCAPE){ // escape
            break;
        }
        else if(key==ARROW){
            #ifdef _WIN32
                key=_getch();
            #endif
            
            switch (key)
            {
            //up
            case UP:{
                cursor.moveUp(&cursor);
                std::cout<<"\033[A";
                
                break;
            }
            //down
            case DOWN:{
                auto p1=cursor.getCursorPosition();
                auto visited=t.getVisited();
                if(visited.count(p1.first+1)){
                    cursor.moveDown(&cursor);
                    std::cout<<"\033[B";
                }
                break;
            }
                
            //left
            case LEFT:{
                cursor.moveLeft(&cursor);
                std::cout<<"\033[D";
                break;
            }
            //right
            case RIGHT:{
                auto p1=cursor.getCursorPosition();
                auto visited=t.getVisited();
                if(visited.count(p1.first) && (visited[p1.first].first+p1.second-1)<visited[p1.first].second){
                    cursor.moveRight(&cursor);
                    std::cout<<"\033[C";
                }
                break;
            }
            default:
                break;
            }

        
        }
        else if(key==ENTER){
            cursor.setCursorPosition(&cursor,cursor.getCursorPosition().first+1,1);

        }
        else if(key==BACKSPACE){
            
            std::cout << "\b \b";
            
            cursor.moveLeft(&cursor);
            auto visited=t.getVisited();
            auto pos=cursor.getCursorPosition();
            
            int x2=visited[pos.first].second;
            int x1=visited[pos.first].first;
            t.removechar(cursor.getCursorPosition());
            if(x2==x1){
                cursor.setCursorPosition(&cursor,pos.first-1,x2-1);
            }
        }
        else if(key==SPACE){
            t.fillchar(' ',cursor.getCursorPosition());
            cursor.moveRight(&cursor);
            std::cout<<' ';

        }
        else if(key==START){
            pos1=cursor.getCursorPosition();
        }
        else if(key==END){
            pos2=cursor.getCursorPosition();
        }
        else if(key==COPY){
            if(pos1.first!=-1 && pos2.first!=-1)
                t.copytext(pos1,pos2);
        }
        else if(key==PASTE){
            auto p=t.pastetext(cursor.getCursorPosition());
            printf("\033[2J");
            printf("\033[%d;%dH", 1,1);
            t.display();
            cursor.setCursorPosition(&cursor,p.first,p.second);
            saveState(t,cursor);
        }
        else if(key==UNDO){
            undo(t,cursor);
            printf("\033[2J");
            printf("\033[%d;%dH", 1,1);
            t.display();
        }
        else if(key==REDO){
            redo(t,cursor);
            printf("\033[2J");
            printf("\033[%d;%dH", 1,1);
            t.display();
        }
        else{
            
            t.fillchar((char)key,cursor.getCursorPosition());
            cursor.moveRight(&cursor);
            std::cout << "\033[" << 1 << "@";
            std::cout<<(char)key; 
            saveState(t,cursor);

            
        }
    }
    
}



Text Input::getText()const{
    return t;
}
void Input::setText(Text t1){
    t=t1;
}

Cursor Input::getCursor()const{
    return cursor;
}

void Input::setCursor(Cursor c){
    cursor=c;
}

void Input::saveState(Text t,Cursor c){
    redoStack=std::stack<std::pair<Text,Cursor>>();
    undoStack.push(std::make_pair(t,c));
}
void Input::undo(Text &t,Cursor &c){
    if(!undoStack.empty()){
        redoStack.push(std::make_pair(t,c));
        t=undoStack.top().first;
        c=undoStack.top().second;
        undoStack.pop();
    }

}
void Input::redo(Text &t,Cursor &c){
    if(!redoStack.empty()){
        undoStack.push(std::make_pair(t,c));
        t=redoStack.top().first;
        c=redoStack.top().second;
        redoStack.pop();
    }

}
