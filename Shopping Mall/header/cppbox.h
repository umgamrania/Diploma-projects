/*

 *** CPPBOX.H ***
 (25-APR-2022 MON 22:22)

*/

#include<iostream>
#include<conio.h>
#include<stdarg.h>
#include<stdlib.h>
#include<sstream>
#include<fstream>
#include<string.h>
#include<windows.h>
#include<ctime>
#include<vector>

using namespace std;

#define H_LINE 205              // ═
#define V_LINE 186              // ║    
#define T_LEFT 204              // ╠
#define T_RIGHT 185             // ╣
#define TOP_LEFT 201            // ╔
#define TOP_RIGHT 187           // ╗
#define BOTTOM_LEFT 200         // ╚
#define BOTTOM_RIGHT 188        // ╝
#define NEWLINE cout<<"\n"

#ifdef _WIN32 
    #define CLEAR system("cls")
#else
    #define CLEAR system("clear")
#endif

// FORMATTING FUNCTIONS

void setColor(int);
int drawLine(int);
int topRow(int);
int bottomRow(int);
void undStr(string str);


// BOX FUNCTIONS

int box(int, string, int, int, int);
int boxCentered(string, int, int, int);

// UTILITY FUNCTIONS

int consoleGoto(int x, int y);
int getKey();

class window{
public:
    char bracket, bracketOver;
    int marginTop, marginLeft, paddingX, paddingY, width;
    bool index;
    string title;
    bool enableNum;
    int textColor, titleColor;
    void showWindow(int, ...);
    void showWindow(vector<string>);
    void showWindow(int, string*);
    char showInputWindow(int, ...);
    char showInputWindow(int, string*);
    bool modernTitle;

    window(){
        title = "Default Window Title";
        marginTop = 3;
        marginLeft = 5;
        paddingX = 1;
        paddingY = 1;
        width = 50;
        textColor = 7;
        titleColor = 7;
        index = false;
        // bracket = '(';
        enableNum = false;
        modernTitle = true;
    }

    window(string t){
        title = t;
        marginTop = 3;
        marginLeft = 5;
        paddingX = 1;
        paddingY = 1;
        width = 50;
        textColor = 7;
        titleColor = 7;
        enableNum = false;
        index = false;
        // bracket = '(';
        modernTitle = true;
    }

    void setBrackets(){
        if(bracket == '(') bracketOver = ')';
        else if(bracket == '[') bracketOver = ']';
        else if(bracket == '<') bracketOver = '>';
        else if(bracket == '.'){bracket = ' '; bracketOver = '.';}
        else { bracket = '('; bracketOver = ')'; }
    }
};

class selector : public window{
public:
    int sx, sy, selectedColor;
    char indicator;

    selector() : window(){
        sx = 0;
        sy = 0;
        indicator = 175;
        selectedColor = 3;
    }

    selector(string t) : window(t){
        sx = 0;
        sy = 0;
        indicator = 175;
        selectedColor = 3;
    }

    int showSelectorList(int, int, ...);
    int showSelector(int, ...);
    int showSelector(vector<string>);
    int showSelector(int, string*);
    void flashList(string*, int, int, int, int);
};

// MEMBER FUNCTIONS

void window::showWindow(int args, ...){
    int i,j, len = title.length(),lenConst = 2, pl = (width - 2 - len)/2, pr = width - len - pl;

    if(index){
        lenConst = 6;
        setBrackets();
    }

    va_list list;
    va_start(list, args);
    string items[args], s;

    for(int k = 0; k < args; k++)
        items[k] = va_arg(list, char*);

    showWindow(args, items);
}

void window::showWindow(vector<string> items_vec){
    int i,j, len = title.length(),lenConst = 2, pl = (width - 2 - len)/2, pr = width - len - pl;

    if(index){
        lenConst = 6;
        setBrackets();
    }

    string items[items_vec.size()];

    for(int k = 0; k < items_vec.size(); k++)
        items[k] = items_vec[k];

    showWindow(items_vec.size(), items);
}


void window::showWindow(int args, string *items){
    int i,j, len = title.length(),lenConst = 2, pl = (width - 2 - len)/2, pr = width - len - pl;

    if(index){
        lenConst = 6;
        setBrackets();
    }

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    /* PRINTING TOP MARGIN */
    for(i = 0; i < marginTop; i++) NEWLINE;

    /* PRINTING TOP BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    topRow(width);
    NEWLINE;

    /* PRINTING TITLE */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(V_LINE);
    for(i = 0; i < pl; i++) cout << " ";
    // SetConsoleTextAttribute(hand, titleColor);
    if(modernTitle)
    cout << "\033[3;33m";
    cout << title;
    cout << "\033[0m";
    // SetConsoleTextAttribute(hand, 7);
    for(i = 0; i < pr-2; i++) cout << " ";
    cout << char(V_LINE);
    NEWLINE;

    /* PRINTING SEPERATOR */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(T_LEFT);
    drawLine(width-2);
    cout << char(T_RIGHT);
    NEWLINE;

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING CONTENT */
    for(i = 0; i < args; i++){
        len = items[i].length();
        
        for(j = 0; j < marginLeft; j++) cout << " ";
        cout << char(V_LINE);

        for(j = 0; j < paddingX; j++) cout << " ";
        SetConsoleTextAttribute(hand, textColor);
        if(index) cout << bracket << i+1 << bracketOver << " ";
        cout << items[i];
        SetConsoleTextAttribute(hand, 7);

        for(j = 0; j < (width - lenConst - len - paddingX); j++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING BOTTOM BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;
}

char window::showInputWindow(int args, ...){
    int i,j, len = title.length(), lenConst = 2, pl = (width - 2 - len)/2, pr = width - len - pl;

    if(index){
        lenConst = 6;
        setBrackets();
    }

    va_list list;
    va_start(list, args);
    string items[args], s;

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
    
    for(int k = 0; k < args; k++)
        items[k] = va_arg(list, char*);

    /* PRINTING TOP MARGIN */
    for(i = 0; i < marginTop; i++) NEWLINE;

    /* PRINTING TOP BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    topRow(width);
    NEWLINE;

    /* PRINTING TITLE */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(V_LINE);
    for(i = 0; i < pl; i++) cout << " ";
    SetConsoleTextAttribute(hand, titleColor);
    cout << title;
    SetConsoleTextAttribute(hand, 7);
    for(i = 0; i < pr-2; i++) cout << " ";
    cout << char(V_LINE);
    NEWLINE;

    /* PRINTING SEPERATOR */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(T_LEFT);
    drawLine(width-2);
    cout << char(T_RIGHT);
    NEWLINE;

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING CONTENT */
    for(i = 0; i < args; i++){
        len = items[i].length();
        
        for(j = 0; j < marginLeft; j++) cout << " ";
        cout << char(V_LINE);

        for(j = 0; j < paddingX; j++) cout << " ";
        SetConsoleTextAttribute(hand, textColor);
        if(index) cout << bracket << i+1 << bracketOver << " ";
        cout << items[i];
        SetConsoleTextAttribute(hand, 7);

        for(j = 0; j < (width - lenConst - len - paddingX); j++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING BOTTOM BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;

    for(int q = 0; q < marginLeft; q++) cout << " ";
    cout << "> ";

    char ch;
    cin >> ch;

    return ch;
}

char window::showInputWindow(int args, string *items){
    int i,j, len = title.length(), lenConst = 2, pl = (width - 2 - len)/2, pr = width - len - pl;

    if(index){
        lenConst = 6;
        setBrackets();
    }

    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    /* PRINTING TOP MARGIN */
    for(i = 0; i < marginTop; i++) NEWLINE;

    /* PRINTING TOP BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    topRow(width);
    NEWLINE;

    /* PRINTING TITLE */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(V_LINE);
    for(i = 0; i < pl; i++) cout << " ";
    SetConsoleTextAttribute(hand, titleColor);
    cout << title;
    SetConsoleTextAttribute(hand, 7);
    for(i = 0; i < pr-2; i++) cout << " ";
    cout << char(V_LINE);
    NEWLINE;

    /* PRINTING SEPERATOR */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(T_LEFT);
    drawLine(width-2);
    cout << char(T_RIGHT);
    NEWLINE;

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING CONTENT */
    for(i = 0; i < args; i++){
        len = items[i].length();
        
        for(j = 0; j < marginLeft; j++) cout << " ";
        cout << char(V_LINE);

        for(j = 0; j < paddingX; j++) cout << " ";
        SetConsoleTextAttribute(hand, textColor);
        if(index) cout << bracket << i+1 << bracketOver << " ";
        cout << items[i];
        SetConsoleTextAttribute(hand, 7);

        for(j = 0; j < (width - lenConst - len - paddingX); j++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING BOTTOM BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;

    for(int q = 0; q < marginLeft; q++) cout << " ";
    cout << "> ";

    char ch;
    cin >> ch;

    return ch;
}

int selector::showSelectorList(int kx,int args, ...){
    int cx,cy, dy;

    cx = marginLeft + 2 + sx;
    dy = cy = marginTop + paddingY + 3 + sy;

    // COPIED CODE FROM ORIGINAL showWindow FUNCTION

    int i,j, len = title.length(), pl = (width - 2 - len)/2, pr = width - len - pl;

    va_list list;
    va_start(list, args);

    string items[args], s;
    
    for(int k = 0; k < args; k++)
        items[k] = va_arg(list, char*);

    /* PRINTING TOP MARGIN */
    for(i = 0; i < marginTop; i++) NEWLINE;

    /* PRINTING TOP BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    topRow(width);
    NEWLINE;

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING CONTENT */
    for(i = 0; i < args; i++){
        len = items[i].length();
        
        for(j = 0; j < marginLeft; j++) cout << " ";
        cout << char(V_LINE);

        for(j = 0; j < paddingX; j++) cout << " ";
        cout << "  " << items[i];

        for(j = 0; j < (width - 4 - len - paddingX); j++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING BOTTOM BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;

    // COPIED CODE ENDS HERE

    cy += kx;
    dy += kx;
    consoleGoto(cx,cy);
    cout << indicator;
    consoleGoto(0,cy+args+2);

    char x;

    while(1){
        if(GetAsyncKeyState(VK_ESCAPE)) break;

        switch(x = getKey()){
            case 1: // UP
            consoleGoto(cx,cy);
            cout << " ";
            cy--;
            if(cy < dy) cy = dy+args-1;
            
            break;

            case 2: // DOWN
            consoleGoto(cx,cy);
            cout << " ";
            if(cy > dy+args-2) cy = dy-1;
            cy++;
            break;

            case 11 ... 19:
            if(enableNum)
            return x;

            case 5: // Pressed enter
            return cy - dy;

            default:
                continue;
        }
        
        consoleGoto(cx,cy);
        cout << indicator;
        consoleGoto(0, marginTop + args + paddingY*2 + 4 + kx);
    }

    return 0;
}

int selector::showSelector(int args, ...){
    setBrackets();
    va_list list;
    va_start(list, args);

    string items[args], s;

    for(int k = 0; k < args; k++)
        items[k] = va_arg(list, char*);
    
    return showSelector(args, items);
}

int selector::showSelector(vector<string> _vector){
    setBrackets();
    
    int count = _vector.size();
    string items[count];

    for(int i = 0; i < count; i++){
        items[i] = _vector[i];
    }

    return showSelector(count, items);
}

int selector::showSelector(int args, string *items){
    int cx, cy, dy;

    cx = marginLeft + 2 + sx;
    dy = cy = marginTop + paddingY + 3 + sy;

    CLEAR;

    // COPIED CODE FROM ORIGINAL showWindow FUNCTION

    int i,j, len = title.length(), pl = (width - 2 - len)/2, pr = width - len - pl;
    
    /* PRINTING TOP MARGIN */
    for(i = 0; i < marginTop; i++) NEWLINE;

    /* PRINTING TOP BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    topRow(width);
    NEWLINE;

    /* PRINTING TITLE */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(V_LINE);
    for(i = 0; i < pl; i++) cout << " ";
    if(modernTitle)
    cout << "\033[3;33m";
    cout << title;
    cout << "\033[0m";
    for(i = 0; i < pr-2; i++) cout << " ";
    cout << char(V_LINE);
    NEWLINE;

    /* PRINTING SEPERATOR */
    for(i = 0; i < marginLeft; i++) cout << " ";
    cout << char(T_LEFT);
    drawLine(width-2);
    cout << char(T_RIGHT);
    NEWLINE;

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING CONTENT */
    for(i = 0; i < args; i++){
        len = items[i].length();
        
        for(j = 0; j < marginLeft; j++) cout << " ";
        cout << char(V_LINE);

        for(j = 0; j < paddingX; j++) cout << " ";
        cout << " " << items[i];

        for(j = 0; j < (width - 3 - len - paddingX); j++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING TOP PADDING */
    for(j = 0; j < paddingY; j++){
        for(i = 0; i < marginLeft; i++) cout << " ";
        cout << char(V_LINE);
        for(i = 0; i < width-2; i++) cout << " ";
        cout << char(V_LINE);
        NEWLINE;
    }

    /* PRINTING BOTTOM BORDER */
    for(i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;

    // COPIED CODE ENDS HERE

    // consoleGoto(cx,cy);
    // cout << indicator;
    // consoleGoto(0,cy+args+2);

    int clr = 0;
    char x;
    while(1){
        flashList(items, args, clr, marginLeft+paddingX, marginTop+paddingY+3);

        switch(x = getKey()){
            case -1:
            return -1;
            break;

            case 1: // UP
            if(clr == 0) clr = args;
            clr--;
            break;

            case 2: // DOWN
            if(clr == args-1) clr = -1;
            clr++;
            break;

            case 11 ... 19: // PRESSED NUM KEY
            if(enableNum){
                return x;
            }
            break;
            
            case 5: // Pressed enter
            return clr;
            break;
        }
    }

    return 0;
}

void selector::flashList(string *items,int no, int color, int lsx, int lsy){
    consoleGoto(lsx, lsy);

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; i < no; i++){

        SetConsoleTextAttribute(h, 7);
        consoleGoto(lsx, lsy++);
        if(i == color) {
            SetConsoleTextAttribute(h, selectedColor);
            cout << " " << char(175);
        }
        else{
            cout << "  ";
        }

        if(index == true){
            cout << " " << bracket << i+1 << bracketOver;
        }

        cout << " " << items[i] << " ";
        SetConsoleTextAttribute(h, 7);
    }

    consoleGoto(0, lsy+2);
}



// FORMATTING FUNCTIONS

void setColor(int clr){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, clr);
}

int drawLine(int len){
    int i;
    for(i = 0; i < len; i++)
        printf("%c", H_LINE);
    
    return 0;
}

int topRow(int TotalLength){
    int i;
    printf("%c", TOP_LEFT);
    drawLine(TotalLength - 2);
    printf("%c", TOP_RIGHT);
}

int bottomRow(int TotalLength){
    int i;
    printf("%c", BOTTOM_LEFT);
    drawLine(TotalLength - 2);
    printf("%c", BOTTOM_RIGHT);
}

void undStr(string str){
    cout << str << endl;
    for(int i = 0 ; i < str.length(); i++) cout << char(H_LINE);
    cout << endl;
}


// BOX FUNCTIONS

int box(string msg, int marginLeft, int width, int clr = 7){
    for(int i = 0; i < marginLeft; i++) cout << " ";

    topRow(width);
    NEWLINE;

    for(int i = 0; i < marginLeft; i++) cout << " ";
    setColor(clr);
    cout << char(V_LINE) << " " << msg;
    setColor(7);

    for(int i = 0; i < width - msg.length() - 3; i++)
        cout << " ";
    
    cout << char(V_LINE);
    NEWLINE;

    for(int i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;

    return 0;
}

int box(int count, string *msg, int marginLeft, int width, int clr = 7){
    for(int i = 0; i < marginLeft; i++) cout << " ";

    topRow(width);
    NEWLINE;

    for(int k = 0; k < count; k++){
    for(int i = 0; i < marginLeft; i++) cout << " ";

    cout << char(V_LINE) << " ";
    setColor(clr);
    cout << msg[k];
    setColor(7);

    for(int i = 0; i < width - msg[k].length() - 3; i++)
        cout << " ";
    
    cout << char(V_LINE);
    NEWLINE;
    }

    for(int i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;

    return 0;
}

int boxCentered(string msg, int marginLeft, int width, int clr = 7){
    int len = msg.length(), pl = ((width - 2 - len)/2)+2, pr = width - len - pl;

    /* PRINTING TOP ROW */
    for(int i = 0; i < marginLeft; i++) cout << " ";
    topRow(width);
    NEWLINE;

    /* PRINTING LINE */
    for(int i = 0; i < marginLeft; i++) cout << " ";
    cout << char(V_LINE);
    for(int i = 0; i < pl-1; i++) cout << " ";
    setColor(clr);
    cout << msg;
    setColor(7);
    for(int i = 0; i < pr-1; i++) cout << " ";
    cout << char(V_LINE);
    NEWLINE;

    /* PRINTING BOTTOM ROW */
    for(int i = 0; i < marginLeft; i++) cout << " ";
    bottomRow(width);
    NEWLINE;
    return 0;
}


// UTILITY FUNCTIONS

int fileLength(string filename){
    int lines = 0;
    string dummyString;

    ifstream file;
    file.open(filename.c_str());

    while(!file.eof()){
        getline(file, dummyString);
        lines++;
    }

    file.close();

    return lines;
}

int consoleGoto(int x, int y){
    COORD cs;
    cs.X = x;
    cs.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cs);
    return 0;
}

int getKey(){
	int c, ex;
	
	while(1){

	c = getch();

    if(c > 48 && c < 58){
        return c - 38;
    }

    if(c == 13)
        return 5;

	if(c == 27)
        return -1;
	
	if(c && c != 224){
		return 0;
	}
	
	else{
		switch(ex = getch()){
			case 72:        // UP KEY
				return 1;
			break;
			
			case 80:        // DOWN KEY
				return 2;
			break;
			
			case 75:        // LEFT KEY
				return 3;
			break;
			
			case 77:        // RIGHT KEY
				return 4;
			break;

            case 10:        // ENTER
                return 5;
            break;

            case 13:        // ALTERNATIVE OF ENTER (CARRIAGE RETURN)
                return 5;
            break;
		}
	}
	}
}

int wait(int milisecond){
    for(int i = 0; i < milisecond/10; i++){
        if(kbhit()) return 0;
        Sleep(10);
    }
}
