#include "TextEditorUI.h"
#include "texteditor.h"
#include <iostream>
#include <string>
#include<fstream>
#ifdef _WIN32
#include<conio.h>
#endif
TextEditor::TextEditor(){
    fileHandle=FileHandle();
    input=Input();
    
}

// void TextEditor::run(std::string filename){
//     std::cout<<"\033[2J";
//     printf("\033[%d;%dH", 1, 1);

//     auto cursor=fileHandle.loadFile(filename);
//     input.setText(fileHandle.getText());
//     input.setCursor(Cursor(cursor.first,cursor.second));
//     input.saveState(input.getText(),input.getCursor());
//     input.userinput();
//     std::cout<<"\033[2J";
    
//     std::cout<<"Save changes made to file ?\n";
//     std::cout<<"Yes - Y\tNo - N\n";
//     #ifdef _WIN32
//         int key=_getch();
//     #endif
//     if((char)key=='Y' || (char)(key)=='y'){
//         fileHandle.setText(input.getText());    
//         fileHandle.saveFile(filename);
//         std::cout<<"Saved Succesfully!!\n";
//     } 
    
// }


// Custom header file for colors and special characters

void TextEditor::run(std::string filename) {
    // Clear the screen
    system("clear||cls");

    // Print the welcome message with colors
    std::cout << YELLOW << "======== " << GREEN << "Text Editor" << YELLOW << " ========\n" << RESET;

    auto cursor = fileHandle.loadFile(filename);
    input.setText(fileHandle.getText());
    input.setCursor(Cursor(cursor.first+3, cursor.second));
    input.saveState(input.getText(), input.getCursor());

    // Display the file name and content
    std::cout << CYAN << "File: " << filename << RESET << "\n\n";
    input.getText().display();
    input.userinput();

    // Clear the screen
    system("clear||cls");

    // Print the save prompt with colors
    std::cout << YELLOW << "======== " << GREEN << "Save Changes" << YELLOW << " ========\n" << RESET;
    std::cout << "Save changes made to file ?\n\n";
    std::cout << BLUE << "Yes - Y" << RESET << "\t" << RED << "No - N" << RESET << "\n\n";

#ifdef _WIN32
    int key = _getch();
#endif

    if ((char)key == 'Y' || (char)(key) == 'y') {
        fileHandle.setText(input.getText());
        fileHandle.saveFile(filename);
        std::cout << GREEN << "Saved Successfully!" << RESET << "\n";
    } else {
        std::cout << RED << "Changes discarded." << RESET << "\n";
    }

    // Pause for user input before exiting
    system("pause");
}
// int main(){
//     TextEditor t;
//     t.run("test");
// }