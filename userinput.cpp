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
                cursor.moveDown(&cursor);
                std::cout<<"\033[B";
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
                cursor.moveRight(&cursor);
                std::cout<<"\033[C";
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
            // if(!t.getVisited().count(cursor.getCursorPosition().first)){
            //     cursor.setCursorPosition(&cursor,t.getVisited()[cursor.getCursorPosition().first].first,t.getVisited()[cursor.getCursorPosition().first].second);
            // }

            
        }
        else if(key==SPACE){
            t.fillchar(' ',cursor.getCursorPosition());
            cursor.moveRight(&cursor);
            std::cout<<' ';

        }
        else if(key==COPY){
            std::pair<int,int> pos1={1,2};
            std::pair<int,int> pos2={2,3};
            t.copytext(pos1,pos2);
        }
        else if(key==PASTE){
            auto p=t.pastetext(cursor.getCursorPosition());
            printf("\033[2J");
            printf("\033[%d;%dH", 1,1);
            t.display();
            cursor.setCursorPosition(&cursor,p.first,p.second);
        }
        else{
            
            t.fillchar((char)key,cursor.getCursorPosition());
            cursor.moveRight(&cursor);
            std::cout << "\033[" << 1 << "@";
            std::cout<<(char)key; 

            
        }
    }

    // t.getbuffer().display();
    
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