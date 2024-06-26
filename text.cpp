#include "text.h"
#include<fstream>
Text::Text(){
    // c=Cursor();
    g=GapBuffer(1000);
    ptrs=std::vector<int>(50,-1);
    visited=std::map<int,std::pair<int,int>>();
    buffer="";
}

void Text::fillchar(char c1,std::pair<int,int> pos){
    if(ptrs[pos.first]==-1){// newline
        // std::cout<<"newline\n";
        
        if(pos.first!=1){
            // int p=ptrs[pos.first-1]
            
            // g.insert(g.left,'\n');
            int x2=visited[pos.first-1].second;
            int i=0;
            std::pair<int,int> prev={};
            while(x2==0){
                prev=visited[pos.first-1-i];
                x2=visited[pos.first-1-i].second;
                i++;
            }
            // i++;
            int l=0;
            if(i>0){
                i--;
                x2=visited[pos.first-1-i].second;
                g.insert(visited[pos.first-1-i].second,'\n');
                l++;    
                while(i--){
                    int a1=pos.first-1-i;
                    visited[pos.first-1-i]={prev.second+1,prev.second+1};
                    g.insert(visited[pos.first-1-i].second,'\n');
                    l++;
                    ptrs[pos.first-1-i]=prev.second+1;
                    prev=visited[pos.first-1-i];
                }
            }
            if(c1!='\n') g.insert(visited[pos.first-1].second,'\n');
            
            
            ptrs[pos.first]=visited[pos.first-1].second+1;
            // whether to include \n in a line or not
        }
        else{
            ptrs[pos.first]=1;
        }
        // ptrs[pos.first]=g.left;// may need debugging
        // +1 if you include \n in previous line
        visited[pos.first]={ptrs[pos.first],ptrs[pos.first]};
        // visited[pos.first]={g.left,g.left};
        g.insert(visited[pos.first].second,c1);
        
        int x1=visited[pos.first].second;
        visited[pos.first].second++;
    }
    else{
        // std::cout<<"sameline\n";
        int t=visited[pos.first].second;
        int t1=ptrs[pos.first];
        g.insert(ptrs[pos.first]+(pos.second-1),c1);
        visited[pos.first].second++;
        // visited[pos.first].second=std::max(visited[pos.first].second,(ptrs[pos.first]+(pos.second-1)));
    }
    std::map<int,std::pair<int,int>>::iterator it = visited.begin();
    std::map<int,std::pair<int,int>>::iterator end = visited.end();
    for (; it != end; ++it) {
        std::map<int,std::pair<int,int>>::iterator next_it = std::next(it);
        if (next_it != end) {
            int x1=next_it->second.first;
            int x2=it->second.second;
            if(x2==x1){
                next_it->second.first=it->second.second+1;
                next_it->second.second++; // may be wrong for other
                ptrs[next_it->first]=next_it->second.first;
            }
        }
    }
    
}

void Text::removechar(std::pair<int,int> pos){
    
    if(!visited.count(pos.first)){
        if(pos.first==1) return;
        g.remove(visited[pos.first-1].second);
        return;
    }
    int x2=visited[pos.first].second;
    int x1=visited[pos.first].first;
    int position=ptrs[pos.first]+pos.second-1;
    if(x1==x2){
        position--;
    }
    g.remove(position);
    if(visited[pos.first].second<=visited[pos.first].first){
        visited.erase(pos.first);
        ptrs[pos.first]=-1;
    }
    else{
        visited[pos.first].second--;
    }
}
void Text::fillstring(std::string str){

}

void Text::display(){
    int i=1;
    for(char c1:g.buffer){
        // if(i==1 || c1=='\n'){
        //     std::cout<<i<<" ";
        //     i++;
        // }
        if(c1!='_')
            std::cout<<c1;
        
        
    }
}

GapBuffer Text::getbuffer() const{
    return g;
}
std::map<int,std::pair<int,int>> Text::getVisited()const{
    return this->visited;
}


void Text::copytext(std::pair<int,int> pos1,std::pair<int,int> pos2){
    buffer="";
    auto i=pos1;
    g.move(visited[pos2.first].first+(pos2.second-1)+1);
    // g.display();
    // std::cout<<"\n";
    while(i.first<=pos2.first){
        int j=i.second;
        if(i.first==pos2.first){
            while(j<=pos2.second){
                buffer.push_back(g.buffer[visited[i.first].first+(j-1)]);
                j++;
            }
        }
        else{
            while(j<visited[i.first].second){
                buffer.push_back(g.buffer[visited[i.first].first+(j-1)]);
                j++;
            }
            buffer.push_back('\n');
        }

        i={i.first+1,1};
    }
}

std::pair<int,int> Text::pastetext(std::pair<int,int> pos){
    if(buffer=="") return pos;
    auto i=pos;
    std::vector<std::pair<char,int>> positions;
    int line=0, flag=0;
    for(char c:buffer){

        if(c=='\n'){

            if(!flag){
                int j=i.second;
                line=i.first;
                int f=visited[i.first].first;
                int f2=visited[i.first].second;
                // std::cout<<visited[i.first].first<<" "<<visited[i.first].second<<"\n";
                int offset=(visited[i.first].second-visited[i.first].first)-(i.second-1);
                g.move(visited[i.first].first+j+offset-1);
                // g.display();
                int n=visited[i.first].first+j+offset-1;
                for(int k=visited[i.first].first+(j-1);k<n;k++){
                    char o=g.buffer[k];
                    positions.push_back({o,j++});
                }
                 j=i.second;
                //  std::cout<<"removing\n";

                while(j<i.second+offset){
                    removechar(i);
                    // display();
                    // std::cout<<"\n\n";
                    // g.display();
                    j++;
                }
                // std::cout<<"for char c = "<<'*'<<'\n';
                flag=1;
                // display();
                // std::cout<<'\n';
            }
            i.first++;
            i.second=1;
            continue;
        }
        fillchar(c,i);
        // std::cout<<"for char c = "<<(c=='\n'?'*':c)<<'\n';
        // display();
        // std::cout<<'\n';
        i.second++;
       
    }
    int s=0;
    for(auto j:positions){
        char c2=j.first;
        fillchar(j.first,{i.first,i.second});
        i.second++;
        s=i.second;
        // display();
        // std::cout<<"\n\n";
    }
    s=positions.empty()?i.second:s;
    // std::cout<<i.first<<s<<"\n";
    return std::make_pair(i.first,s);

}

void h(Text* t){
    std::ifstream f("test.txt");
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
        t->fillchar(c,{i,j});
        k=0;
        // k=0;
        std::cout<<"\n";
        t->getbuffer().display();
        std::cout<<"\n";
        // // std::cout<<c;
        j++;
    }
    if(k>0){
        t->fillchar('\n',{i,j});
        
    }

    t->display();
    // std::cout<<"\n";
    auto m=t->getVisited();
    for(auto &x:m){
        std::cout<<x.first<<" - {"<<x.second.first<<","<<x.second.second<<"\n";
    }
}


void back(Text &t,Cursor &cursor){
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


// int main(){
//     Text t;
//     h(&t);
//     // t.getbuffer().display();
//         // t.fillchar('1',{1,1});
//         // t.fillchar('2',{1,2});
//     // c.moveLeft();
//         // t.fillchar('3',{1,3});
//         // t.fillchar('4',{1,4});
//         // t.fillchar('5',{1,5});
//     // t.fillchar('0',{1,3});
//     // t.getbuffer().display();
//     // t.fillchar('\n',{1,6});
//         // t.fillchar('6',{1,6});
//         // t.getbuffer().display();
//     // t.fillchar('x',{1,2});
//     // t.fillchar('7',{2,2});
    
//         // t.fillchar('7',{1,7});
//         // t.fillchar('8',{2,1});
//         // t.fillchar('9',{2,2});
//         // t.fillchar('a',{2,3});
    
//     // t.removechar({2,3});
//     // t.display();
//     // std::cout<<"\n";
//     // t.removechar({2,2});
//     // t.display();
//     // std::cout<<"\n";
//     // t.removechar({2,1});
//     // // t.display();
//     // t.getbuffer().display();
//     // std::cout<<"\n";
//     // t.removechar({2,1});
//     // // t.display();
//     // t.getbuffer().display();
//     // t.fillchar('z',{2,1});
//     // t.display();
//     // std::cout<<"\n";
//     // t.copytext({1,2},{2,3});
//     // std::cout<<"\n";
//     // t.fillchar('w',{2,1});
//     // t.display();
//     // std::cout<<"\n Pasted text\n";
//     // auto pos=t.pastetext({2,3});


//     // t.display();
//     // // std::cout<<"\n";
//     // auto m=t.getVisited();
//     // for(auto &x:m){
//     //     std::cout<<x.first<<" - {"<<x.second.first<<","<<x.second.second<<"\n";
//     // }
    
//     // std::cout<<"\n";
//     // t.getbuffer().display();
// }


