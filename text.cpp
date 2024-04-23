#include "text.h"
Text::Text(){
    // c=Cursor();
    g=GapBuffer(100);
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
            g.insert(visited[pos.first-1].second,'\n');
            
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
    for(char c1:g.buffer){
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
    // std::cout<<"\n"<<buffer<<"\n";
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
        fillchar(j.first,{i.first,j.second});
        s=j.second;
        // display();
        // std::cout<<"\n\n";
    }
    s=positions.empty()?i.second:s;
    std::cout<<i.first<<s<<"\n";
    return std::make_pair(i.first,s);

}

// int main(){
//     Text t;
//     Cursor c;
//     t.fillchar('1',{1,1});
//     c.moveRight(&c);
//     t.fillchar('2',{1,2});
//     c.moveRight(&c);
    
//     // c.moveLeft();
//     t.fillchar('3',{1,3});
//     c.moveRight(&c);
    
//     t.fillchar('4',{1,4});
//     c.moveRight(&c);
    
//     t.fillchar('5',{1,5});
//     c.moveRight(&c);
//     t.fillchar('0',{1,3});
//     t.getbuffer().display();
//     // t.fillchar('\n',{1,6});
//     t.fillchar('6',{2,1});
//     t.getbuffer().display();
//     t.fillchar('x',{1,2});
//     // t.fillchar('7',{2,2});
//     t.fillchar('7',{2,2});
//     t.fillchar('8',{2,3});
//     t.fillchar('y',{1,4});

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
//     t.fillchar('z',{2,1});
//     t.display();
//     std::cout<<"\n";
//     t.copytext({1,3},{2,2});
//     std::cout<<"\n";
//     t.fillchar('w',{2,1});
//     t.display();
//     std::cout<<"\n Pasted text\n";

//     auto pos=t.pastetext({3,1});
    
//     t.display();
//     std::cout<<"\n";
//     // t.getbuffer().display();
// }

// 1x2y0345
// 2y0345
// z6wz678

