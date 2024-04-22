#include "gap_buffer.h"
#include <iostream>

GapBuffer::GapBuffer(int size) : buffer(size, '_') ,left(1),right(size-left){}
GapBuffer::GapBuffer() {}

void GapBuffer::move_left(int position)
{
    while (position < left)
    {
        left--, right--;
        buffer[right + 1] = buffer[left];
        buffer[left] = '_';
        // std::cout << "in left ";
        // display();
        // std::cout << "\n";
    }
}

void GapBuffer::move_right(int position)
{
    while (position > right)
    {
        left++, right++;
        buffer[left - 1] = buffer[right];
        buffer[right] = '_';
        // std::cout << "in right ";
        // display();
        // std::cout << "\n";
    }
}

void GapBuffer::grow(int position)
{
    std::vector<char> temp;
    for (int i = position; i < buffer.size(); i++)
    {
        temp.push_back(buffer[i]);
    }

    buffer.resize(buffer.size() + 5, '_');

    for (int i = position; i < buffer.size(); i++)
    {
        buffer[i] = '_';
    }

    for (int i = 0; i < temp.size(); i++)
    {
        int k = position + gapSize + i;
        buffer[k] = temp[i];
    }

    left = position;
    right = left + gapSize - 1;
}

void GapBuffer::move(int position)
{
    if (position < left)
    {
        move_left(position);
    }
    else if (position > right)
    {
        move_right(position);
    }
    else{
        while(position!=left){
            left++, right++;
            buffer[left - 1] = buffer[right];
            buffer[right] = '_';
        }
        // std::cout<<"from else\n";
        // display();
    }
    

}

void GapBuffer::insert(int position, char c)
{
    if (left > right)
    {
        grow(position);
    }

    if (position != left)
        move(position);

    buffer[position] = c;
    left++;
}

void GapBuffer::remove(int position)
{
    if (position < left)
    {
        move_left(position);
        if(right<buffer.size()) buffer[++right] = '_';
        else buffer[right]='_';
    }
    else if (position > right)
    {
        move_right(position);
        if(left>0) buffer[--left] = '_';
        else buffer[left]='_';
    }
    else{
        while(position!=left){
            left++, right++;
            buffer[left - 1] = buffer[right];
            buffer[right] = '_';
        }
        if(right<buffer.size()) buffer[++right] = '_';
        else buffer[right]='_';
    }
}
void GapBuffer::display()
{
    for (auto i : buffer)
    {
        if(i=='\n') std::cout<<'*';
        else std::cout << i << " ";

    }
    std::cout << "\n";
}

// int main(){
//     gap_buffer g(SIZE);
//     char c;
//     int position=0;
//     g.insert(0,'0');
//     g.display();
//     g.insert(1,'1');
//     g.display();
//     g.insert(2,'2');
//     g.display();
//     g.insert(3,'3');
//     g.display();
//     g.insert(4,'4');
//     g.display();
//     g.insert(5,'5');
//     g.display();
//     g.insert(6,'6');
//     g.display();
//     g.insert(7,'7');
//     g.display();
//     g.insert(8,'8');
//     g.display();
//     g.insert(9,'9');
//     g.display();
//     g.insert(10,'A');
//     g.display();
//     g.insert(11,'B');
//     g.display();
//     g.insert(12,'C');
//     g.display();
//     g.insert(2,'w');
//     g.display();
//     g.insert(3,'c');
//     g.display();
//     g.insert(7,'d');
//     g.display();
//     g.remove(14);
//     g.display();

//     while(true){
//         g.display();
//         cin>>c;

//         if(c=='0') break;
//         cin>>position;
//         if (position < 0) {
//             cout << "Invalid position\n";
//             continue;
//         }
//         g.insert(position,c);

//     }
//     return 0;
// }