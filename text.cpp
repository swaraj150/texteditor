#include "text.h"
Text::Text(){
    // c=Cursor();
    g=GapBuffer(100);
    ptrs=std::vector<int>(50,-1);
    visited=std::map<int,std::pair<int,int>>();
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
    int y=visited[pos.first].second;
    y++;
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

// int main(){
//     Text t;
//     Cursor c;
//     // t.setCursor(c);
//     t.fillchar('1',{1,1});
//     c.moveRight(&c);
//     // t.setCursor(c);
//     t.fillchar('2',{1,2});
//     c.moveRight(&c);
//     // t.setCursor(c);
    
//     // c.moveLeft();
//     // t.setCursor(c);
//     t.fillchar('3',{1,3});
//     c.moveRight(&c);
//     // t.setCursor(c);
    
//     t.fillchar('4',{1,4});
//     c.moveRight(&c);
//     // t.setCursor(c);
    
//     t.fillchar('5',{1,5});
//     c.moveRight(&c);
//     // t.setCursor(c);
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

//     t.removechar({2,3});
//     t.display();
//     std::cout<<"\n";
//     t.removechar({2,2});
//     t.display();
//     std::cout<<"\n";
//     t.removechar({2,1});
//     // t.display();
//     t.getbuffer().display();
//     std::cout<<"\n";
//     t.removechar({2,1});
//     // t.display();
//     t.getbuffer().display();
//     std::cout<<"\n";
//     t.fillchar('z',{2,1});
//     t.display();
//     // std::cout<<"\n";
//     // t.getbuffer().display();
// }