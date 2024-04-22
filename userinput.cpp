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
    printf("\033[2J");
    
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
            
        }
        else if(key==SPACE){
            t.fillchar(' ',cursor.getCursorPosition());
            cursor.moveRight(&cursor);
            std::cout<<' ';

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