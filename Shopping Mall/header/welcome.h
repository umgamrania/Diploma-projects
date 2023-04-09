#include<iostream>
#include<windows.h>

using namespace std;

int drawBoxAnim(){
    int marginLeft = 20, height = 7, width = 70;
    CLEAR;
    consoleGoto(20, 4);
    cout << (char)TOP_LEFT;
    for(int i = 0; i < width+10; i++){
        if(i < width){
            consoleGoto(21+i, 4);
            cout << (char)H_LINE;
        }
        if(i < height){
            consoleGoto(20, 5+i);
            cout << (char)V_LINE;
        }
        if(i == height){ consoleGoto(marginLeft, height+5); cout << (char)BOTTOM_LEFT;}

        if(i > height && i < width+height+1){
            consoleGoto(20-height+i, height+5);
            cout << (char)H_LINE;
        }
        if(kbhit()){
            char c = getch();
        }
        Sleep(5);
    }

    consoleGoto(marginLeft + width, 4); cout << (char)TOP_RIGHT;

    for(int i = 0; i < height; i++){
        consoleGoto(marginLeft + width, 5+i);
        cout << (char)V_LINE;
        Sleep(5);
    }
    consoleGoto(marginLeft + width, 5+height); cout << (char)BOTTOM_RIGHT;
    return 0;
}

int welText(){
    int col = 2;

    setColor(3);

    for(int i = 0; i < 30; i++){
        if(i == 29){
            setColor(3);
        }
        consoleGoto(21+i, 8);
        cout << "       ";
        consoleGoto(22+i, 8);
        cout << "WELCOME";
        if(kbhit()){
            char c = getch();
        }
        Sleep(30);
    }

    setColor(7);

    return 0;
}

int slideLine(){
    for(int i = 0; i < 69; i++){
        consoleGoto(21+i, 5);
        cout << (char)196;
        // cout << '#';
        consoleGoto(89-i, 11);
        cout << (char)196;
        // cout << '#';
        if(kbhit()){
            char c = getch();
        }
        Sleep(10);
    }
}

int showWelcomeScreen(){
    drawBoxAnim();
    setColor(2);
    slideLine();
    setColor(7);
    welText();
    setColor(7);
    Sleep(1500);
}