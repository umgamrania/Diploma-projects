/*

================ PROGRAM DETAILS ================

 * TITLE            SHOPPING MALL MGMT. SYSTEM

 * MEMBERS          216020307001 - AMRANIA UMANG
                    216020307008 - BANDHIYA HARDIK
                    216020307058 - VAKHARIA BHAVARTH

 */ 


#include "header\cppbox.h"
#include "header\welcome.h"
#include <vector>
#include <windows.h>

using namespace std;

int totalProds = 0;                                 // STORING TOTAL NUMBER OF PRODUCTS TO SHOW IN SEARCH                            
int dummyInt;
string dummyString;                                 // FOR GENERAL USE

/* GENERAL TASKS */

int check_files();                                  // CHECKS ALL FILES BEFORE STARTING PROGRAM TO PREVENT RUNTIME ERRORS
void replace_in_string(string&, char, char);
inline void pop(string&);
string get_hidden_input();                          // PUT * AS DATA IS ENTERED AND HIDES ORIGINAL MSG

string get_date();
string toStr(int x);
int fileLength(string filename);
void lwr(string &str);

/* CORE TASKS */

int main_screen();                                  // LANDING SCREEN
int view_items(int cat);                            // SHOW ITEMS OF SELECTED CATAGORY
int view_category();                                // SHOW ALL CATAGORIES
int search();                                       // CHECK IF ENTERED KEYWORD MATCHES ANY CATEGORY
int search_core(string);                            // ACTUAL SEARCH TASK
int view_cart();                                    // OPEN THE CART
int change_quantity(int, int);                      // CHANGE QUANTITY OF PRODUCT ADDED TO CART
int get_product_id(string, int);                    // GET ID OF NTH PRODUCT IN GIVEN FILE
int get_next_id(string);                            // GET ID FOR NEXT PRODUCT TO ADD NEW PRODUCT

int remove_from_list(string);   
int delete_file(string);    

void find_total();                                  // FIND TOTAL NUMBER OF PRODUCTS ACROSS ALL CATAGORIES
int toInt(string);  

/* ADMIN TASKS */   

int admin_login();                                  // LOGIN PASSWORD VERIFICATION FOR ADMIN LOGIN
int admin_screen();                                 // ADMIN'S SCREEN
int add_product();                                  // ADD NEW PRODUCT
int remove_product();                               // REMOVE A PRODUCT
int update_price();                                 // UPDATE PRICE OF EXISTING PRODUCT


struct date{
    int d, m, y;
};
date parse_date(string);

class person{
    string account_no;
    string f_name, l_name, address, phone_no, email_id, password;
    date dob;

    public:
        int login();
        int read_data();
        int homepage();
        string get_name(){return f_name + " " + l_name;};
        int view_account();
        int edit_profile();
        int checkout();
        int invoice();
        int save_invoice();
        int confirm_address();
        int create_account();
        int write_user_file();
        int delete_account();
};

class product{
    string name, category, des, mfg;
    int id, warrentyYears;
    float price;

    public:
    void get_product_data(int passId);                  // READ PRODUCT DETAILS FROM FILE
    int add_to_cart(int qty);                           // ADD CURRENT ITEM TO THE CART WITH THE QTY
    int view_product_details();                         // DISPLAY DETAILS OF PRODUCT
    int cart_item_detail(int);                          // DETAILS OF ITEM ADDED TO THE CART
};

void product :: get_product_data(int passId){
        int fid, fyears;
        float fprice;
        string fname, filename, fdes, fmfg;

        // INDENTIFYING FILE NAME BASED ON PRODUCT_ID
        if(passId < 2000){
            category = "clothes"; filename = "clothes.txt";
        }
        else if(passId > 2000 && passId < 3000){
            category = "electronics"; filename = "electronics.txt";
        }
        else if(passId > 3000 && passId < 4000){
            category = "household"; filename = "household.txt";
        }
        else if(passId > 4000 && passId < 5000){
            category = "medical"; filename = "medical.txt";
        }
        else if(passId > 5000 && passId < 6000){
            category = "food"; filename = "food.txt";
        }
        else if(passId > 6000 && passId < 7000){
            category = "stationary"; filename = "stationary.txt";
        }
        else if(passId > 7000){
            category = "kitchen"; filename = "kitchen.txt";
        }

        ifstream list;
        list.open(filename.c_str());

        // READING PRODUCT FILE LINE BY LINE
        while(!list.eof()){
            list >> fid;
            list >> fname;
            list >> fprice;
            list >> fyears;
            list >> fmfg;
            list >> fdes;
            
            // IF FOUND MATCHING PRODUCT ID, ASSIGNING VALUES TO DATA MEMBERS
            if(fid == passId){
                id = fid;
                name = fname;
                price = fprice;
                warrentyYears = fyears;
                des = fdes;
                mfg = fmfg;
                break;
            }
        }

        // REPLACING DASH WITH SPACE
        replace_in_string(name, '-', ' ');
        replace_in_string(name, '_', '-');
        replace_in_string(des, '-', ' ');
        replace_in_string(des, '_', '-');
        replace_in_string(mfg, '_', '-');
}

int product :: view_product_details(){

        CLEAR;

        // COPIED CODE OF LIBRARY FUNCTION (showWindow) (FOR EXCEPTIONAL CASE :- TO PRINT HALF STRING IN DIFFERENT COLOR)

        {
            string leftAligned[4] = {"Product ID    ", "Price         ", "Warrenty      ", "Manufactured  "};
            string rightAligned[4] = {toStr(id), toStr(price), toStr(warrentyYears), mfg};
            int width = 50;
            string title = name;
            int i,j, len = title.length(),lenConst = 2, pl = (width - 2 - len)/2, pr = width - len - pl;

            HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

            for(i = 0; i < 3; i++) NEWLINE;

            /* PRINTING TOP BORDER */
            for(i = 0; i < 5; i++) cout << " ";
            topRow(width);
            NEWLINE;

            /* PRINTING TITLE */
            for(i = 0; i < 5; i++) cout << " ";
            cout << char(V_LINE);
            for(i = 0; i < pl; i++) cout << " ";
            cout << "\033[3;33m";
            cout << title;
            cout << "\033[0m";
            for(i = 0; i < pr-2; i++) cout << " ";
            cout << char(V_LINE);
            NEWLINE;

            /* PRINTING SEPERATOR */
            for(i = 0; i < 5; i++) cout << " ";
            cout << char(T_LEFT);
            drawLine(width-2);
            cout << char(T_RIGHT);
            NEWLINE;

            /* PRINTING TOP PADDING */
            for(j = 0; j < 1; j++){
                for(i = 0; i < 5; i++) cout << " ";
                cout << char(V_LINE);
                for(i = 0; i < width-2; i++) cout << " ";
                cout << char(V_LINE);
                NEWLINE;
            }

            /* PRINTING CONTENT */
            for(i = 0; i < 4; i++){
                len = leftAligned[i].length() + rightAligned[i].length() + 2;
                
                for(j = 0; j < 5; j++) cout << " ";
                cout << char(V_LINE);

                for(j = 0; j < 1; j++) cout << " ";
                setColor(14);
                cout << leftAligned[i];
                setColor(7);
                cout << ": ";
                cout << rightAligned[i];

                for(j = 0; j < (width - lenConst - len - 1); j++) cout << " ";
                cout << char(V_LINE);
                NEWLINE;
            }

            /* PRINTING TOP PADDING */
            for(j = 0; j < 1; j++){
                for(i = 0; i < 5; i++) cout << " ";
                cout << char(V_LINE);
                for(i = 0; i < width-2; i++) cout << " ";
                cout << char(V_LINE);
                NEWLINE;
            }

            /* PRINTING BOTTOM BORDER */
            for(i = 0; i < 5; i++) cout << " ";
            bottomRow(width);
            NEWLINE;
        }

        string s1 = "Product description";

        cout << "\n      ";
        setColor(11);
        cout << s1;
        setColor(7);
        cout << "\n      ";
        for(int i = 0 ; i < s1.length(); i++) cout << char(H_LINE);
        cout << "\n      " << des << endl;

        selector lst;

        if(lst.showSelectorList(15,2, "Add to cart", "Go back") == 0){
            cout << "\n      Enter quantity: ";
            int qty;
            cin >> qty;

            if(qty == 0){
                CLEAR;
                cout << "\n\n\n";
                boxCentered("0 is not a valid quantity!", 5, 50, 12);
                Sleep(1500);
                return 0;
            }

            add_to_cart(qty);

            CLEAR;
            NEWLINE; NEWLINE; NEWLINE;
            boxCentered("Product added to cart!", 5, 50, 2);
            Sleep(1500);
        }

        return 0;
}

int product :: add_to_cart(int qty){
        if(qty == 0) return 0;

        ifstream cart_check;
        cart_check.open("cart.txt");

        // CHECKING IF PRODUCT IS ALREADY IN THE CART
        int dummy_id, dummy_price, dummy_qty;
        string dummy_name;

        while(1){
            if(cart_check.eof()) break;
            cart_check >> dummy_id;
            cart_check >> dummy_name;
            cart_check >> dummy_price;
            cart_check >> dummy_qty;

            if(dummy_id == id){
                cart_check.close();
                CLEAR;
                window repeat("Do you want to add this product again?");
                repeat.showWindow(2, "You already have this product in your cart.", "Do you want to add more?");

                selector yesNo;
                switch(yesNo.showSelectorList(9, 2, "Yes, add more", "No, go back")){
                    case 0:
                        change_quantity(id, (qty+dummy_qty));
                        return 0;
                    break;
                    
                    case 1:
                        return 0;
                }
                
            }
        }


        string cartName = name;                 // TO STORE THE NAME THAT IS TO BE STORED IN FILE

        replace_in_string(cartName, '-', '_');
        replace_in_string(cartName, ' ', '-');

        ofstream cart;
        cart.open("cart.txt", ios::app);
        cart << id << " " << cartName << " " << price << " " << qty << endl;
        cart.close();
    }

int product :: cart_item_detail(int qty){
    CLEAR;

    string dataLines[3];

    window cartItem(name);

    dataLines[0] = "Quantity : ";
    dataLines[0].append(toStr(qty));

    dataLines[1] = "Rate     : ";
    dataLines[1].append(toStr(price));

    dataLines[2] = "Total    : ";
    dataLines[2].append(toStr(price*qty));

    cartItem.showWindow(3, dataLines);

    selector options;

    int selectedOption = options.showSelectorList(10, 3, "Change quantity", "Remove item", "Go back");

    if(selectedOption == 0){
        int newQty;
        cout << "\n     Enter new quantity: ";
        cin >> newQty;

        change_quantity(id, newQty);

        return 0;
    }

    // REMOVING ITEM == MAKING QUANTITY 0
    else if(selectedOption == 1)
        change_quantity(id, 0);

    else if(selectedOption == 2)
        return 0;

    return 0;
}



int person :: login(){

    string current_try_ac;                  // TO RESET THE NO OF TRIES WHEN ACCOUNT NO CHANGES
    int login_attempts = 4;

    window loginWindow("LOGIN");

    retry:
    CLEAR;

    if(login_attempts == 0){
        cout << "\n\n";
        string msgs[2] = {"You have exceeded the max. no. of attempts to log in", "Please try again after some time"};
        box(2, msgs, 5, 60, 3);
        getch();
        exit(1);
    }

    loginWindow.showWindow(3, "ACCOUNT NO  : ", " ", "PASSWORD    : ");

    consoleGoto(21,7);
    cin >> account_no;

    if(account_no == "stop" || account_no == "exit") return 0;

    // CHECKING IF ACCOUNT NO HAS CHANGED (TO RESET THE MAX ATTEMPTS)
    if(account_no != current_try_ac){
        current_try_ac = account_no;
        login_attempts = 4;
    }

    ifstream list;
    list.open("account_list.txt");

    bool account_found = false;
    string temp_ac_no;
    string temp_pw;

    // CHECKING IF ACCOUNT EXISTS
    while(!list.eof()){
        list >> temp_ac_no;
        list >> temp_pw;

        if(temp_ac_no == account_no){
            account_found = true;
            break;
        }
    }

    list.close();

    if(!account_found){

        CLEAR;
        cout << "\n\n\n";
        boxCentered("Your account could not be found. We regret the inconvinience caused :)", 5, 80, 2);
        _flushall();
        Sleep(2000);
        goto retry;
    }

    else{
        consoleGoto(21,9);
        password = get_hidden_input();

        if(password == "eSc") return 0;

        if(password == temp_pw){
            read_data();

            CLEAR;

            cout << "\n\n\n";
            boxCentered(("Welcome back "+ f_name+"!"), 5, 70, 2);

            Sleep(2000);

            homepage();
        }

        else{
            login_attempts--;
            consoleGoto(0,12);
            string wrong_pw_msg = "Wrong Password! Remaining try(s): ";
            wrong_pw_msg.push_back(login_attempts + 48);                        // DISPLAY NO OF REMAINING ATTEMPTS

            cout << "\n\n";
            boxCentered(wrong_pw_msg, 5, 50, 4);
            _flushall();
            getch();
            goto retry;
        }
    }

    return 0;
}

int person :: read_data(){
    string file_path = "usr\\";
    file_path.append(account_no).append(".txt");

    ifstream usr_file;
    usr_file.open(file_path.c_str());

    if(!usr_file.is_open()){
        CLEAR;
        cout << "User file not open!";
        exit(1);
    }

    else{
        usr_file >> f_name;
        usr_file >> l_name;
        usr_file >> dob.d;
        usr_file >> dob.m;
        usr_file >> dob.y;
        usr_file >> email_id;
        usr_file >> phone_no;
        usr_file >> address;

        replace_in_string(address, '-', ' ');
        replace_in_string(address, '_', '-');
    }

    usr_file.close();

    return 0;
}

int person :: homepage(){
    CLEAR;
    string WindowTitle;
    selector home;
    home.index = true;
    home.enableNum = true;
    home.bracket = '[';
    int choice;

    loop:
    WindowTitle = "Home";
    int spaces = 50 - 8 - f_name.length() - 1 - l_name.length();
    
    // ALIGING USER NAME AND WINDOW TITLE
    for(int i = 0; i < spaces; i++) WindowTitle.append(" ");
    WindowTitle.append(f_name).append(" ").append(l_name);

    home.title = WindowTitle;

    fflush(stdin);
    choice = home.showSelector(6, "Shop by category", "Search product", "View cart", "Checkout", "Account details", "Logout");

    switch(choice){
        case 0:
        case 11:
        view_category();
        break;

        case 1:
        case 12:
        search();
        break;

        case 2:
        case 13:
        view_cart();
        break;

        case 3:
        case 14:
        checkout();
        break;

        case 4:
        case 15:
        if(view_account() == 1) return 0;
        break;

        case 5:
        case 16:
        // CLEANING CART FILE
        ofstream cart;
        cart.open("cart.txt", ios::out);
        cart.close();
        return 0;
        break;
    }

    goto loop;

    return 0;
}

int person :: view_account(){

    bool is_long_address = false;
    vector<string> basicDetails;
    vector<string> longAddress;

    CLEAR;
    cout << "\n";
    boxCentered(f_name + " " + l_name + "\'s Account", 5, 60, 2);

    window basic("Basic Details");
    basic.marginTop = 0;
    basic.width = 60;
    
    basicDetails.push_back("Name      : " + f_name + " " + l_name);
    basicDetails.push_back("DOB       : " + toStr(dob.d) + "/" + toStr(dob.m) + "/" + toStr(dob.y));
    basicDetails.push_back("Email     : " + email_id);
    basicDetails.push_back("Phone no. : " + phone_no);

    basic.showWindow(basicDetails);

    // DEALING WITH LONG ADDRESS
    int lastSpace = 0;

    if(address.length() > 60){
        is_long_address = true;
        for(int i = 0; i < 58; i++){
            if(address.at(i) == ' ') lastSpace = i;
        }
        string firstChunk = address.substr(0, lastSpace);
        string lastChunk = address.substr(lastSpace);
        longAddress.push_back(firstChunk);
        longAddress.push_back(lastChunk);
    }

    else longAddress.push_back(address);

    window addr("Address");
    addr.marginTop = 0;
    addr.width = 60;
    addr.showWindow(longAddress);

    selector options;
    options.marginTop = 1;
    options.width = 60;

    int accountAction;

    accountAction = options.showSelectorList(19, 3, "Edit profile", "Delete account", "Go Back");

    switch(accountAction){
        case 0:
            edit_profile();
        break;

        case 1:
            delete_account();
            return 1;
        break;

        case 2:
            return 0;
    }

    return 0;
}

int person :: invoice(){
    CLEAR;

    int currentLine = 13;
    int cartItemCount = fileLength("cart.txt");

    int cartProductId, cartProductQty, cartProductRate, amount;
    int totalQty = 0, grandTotal = 0;
    float gst = 0;
    string cartProductName;

    ifstream cart;
    cart.open("cart.txt");

    NEWLINE; NEWLINE; NEWLINE;
    boxCentered("Invoice", 10, 79, 2);

    NEWLINE;
    setColor(15);
    for(int i = 0; i < 10; i++) cout << " ";
    cout << "Name      : " << "  " + f_name + " " + l_name << endl;
    for(int i = 0; i < 10; i++) cout << " ";
    cout << "Date/Time :   " << get_date();
    setColor(7);

    NEWLINE;


    cout << "            Sr.   Item                                         Qty   Rate    Total(Rs.)" << endl;

    for(int i = 0; i < 10; i++) cout << " ";
    setColor(8);
    for(int i = 0; i < 79; i++) cout << char(H_LINE);
    setColor(7);

    for(int i = 0; i < cartItemCount-1; i++){
        
        cart >> cartProductId;
        cart >> cartProductName;
        cart >> cartProductRate;
        cart >> cartProductQty;

        replace_in_string(cartProductName, '-', ' ');
        replace_in_string(cartProductName, '_', '-');

        amount = cartProductRate * cartProductQty;

        totalQty += cartProductQty;
        grandTotal += amount;
        setColor(14);
        consoleGoto(12, currentLine);
        cout << i+1;

        consoleGoto(18, currentLine);
        cout << cartProductName;

        consoleGoto(63, currentLine);
        cout << cartProductQty;

        consoleGoto(69, currentLine);
        cout << cartProductRate;

        consoleGoto(77, currentLine++);
        cout << amount;
    }

    cart.close();

    NEWLINE; NEWLINE;

    for(int i = 0; i < 10; i++) cout << " ";
    setColor(8);
    for(int i = 0; i < 79; i++) cout << char(H_LINE);
    setColor(7);
    NEWLINE;
    for(int i = 0; i < 12; i++) cout << " ";
    setColor(7);
    cout << "SUB TOTAL";
    for(int i = 0; i < 42; i++) cout << " ";
    cout << totalQty;

    consoleGoto(77, currentLine+2);
    cout << grandTotal << " Rs.";

    NEWLINE;

    for(int i = 0; i < 12; i++) cout << " ";
    cout << "GST";

    consoleGoto(69, currentLine+3);
    cout << "18%";

    gst = grandTotal*0.18;
    grandTotal += gst;

    consoleGoto(77, currentLine+3);
    cout << gst << " Rs.";

    NEWLINE; NEWLINE;

    for(int i = 0; i < 10; i++) cout << " ";
    setColor(8);
    for(int i = 0; i < 79; i++) cout << char(H_LINE);
    setColor(7);

    NEWLINE;
    for(int i = 0; i < 12; i++) cout << " ";
    cout << "\033[3;37mGrand Total";

    consoleGoto(77, currentLine+6);
    cout << grandTotal << " Rs.\033[0m" << endl << endl;
    setColor(7);

    boxCentered(" Thank you, Do visit again and have a nice day :) ", 10, 79, 3);

    write_user_file();

    return 0;
}

int person :: save_invoice(){
    CLEAR;

    ofstream inv;

    inv.open(("INVOICE_" + f_name + ".txt").c_str());

    int currentLine = 13;
    int cartItemCount = fileLength("cart.txt");

    int cartId, cartQty, cartRate, amount;
    int totalQty = 0, grandTotal = 0;
    float gst = 0;
    string cartName;

    ifstream cart;
    cart.open("cart.txt");

    if(!cart.is_open()) {CLEAR; cout << "Cart file not opened!"; exit(1);}

    inv << endl;
    for(int i = 0; i < 49; i++) inv << "=";
    inv << endl;
    for(int i = 0; i < 21; i++) inv << " ";
    inv << "INVOICE";
    for(int i = 0; i < 21; i++) inv << " ";
    inv << endl;
    for(int i = 0; i < 49; i++) inv << "=";
    inv << endl;


    inv << endl << "Name      :    " << (f_name + " " + l_name);
    inv << endl << "Date/Time :    " << get_date() << endl;

    for(int i = 0; i < 49; i++) inv << "=";

    inv << endl << endl;

    for(int i = 0; i < cartItemCount-1; i++){
    
        cart >> cartId;
        cart >> cartName;
        cart >> cartRate;
        cart >> cartQty;

        replace_in_string(cartName, '-', ' ');
        replace_in_string(cartName, '_', '-');

        amount = cartRate * cartQty;

        totalQty += cartQty;
        grandTotal += amount;

        inv << i+1 << ". ";

        inv << cartName << " - ";

        inv << cartQty << " * ";

        inv << cartRate << " = ";

        inv << amount << " Rs." << endl << endl;
    }
    cart.close();

    for(int i = 0; i < 49; i++) inv << "=";

    inv << endl << endl;

    gst = grandTotal*0.18;
    inv << "  Total Items : " << totalQty << endl;
    inv << "  Sub Total   : " << grandTotal << " Rs." << endl;
    inv << "  GST(18%)    : " << gst << " Rs. " << endl << endl;

    grandTotal += gst;

    for(int i = 0; i < 49; i++) inv << "=";

    inv << endl << endl;

    inv << "  Grand total : " << grandTotal << " Rs." << endl << endl;

    for(int i = 0; i < 49; i++) inv << "=";
    inv << endl;

    inv << " Thank you, Do visit again and have a nice day :)" << endl;

    for(int i = 0; i < 49; i++) inv << "=";

    inv.close();

    ofstream clearCart;

    clearCart.open("cart.txt");
    clearCart.close();

    return 0;
}

int person :: checkout(){
    CLEAR;
    int dummyInt;

    // CHECKING IF CART IS EMPTY
    ifstream empCrt;
    empCrt.open("cart.txt");
    empCrt >> dummyString;
    if(empCrt.eof()){
        CLEAR;
        empCrt.close();
        window noItem("Checkout");
        noItem.width = 60;
        noItem.showWindow(2, "\033[3;37mYour cart seems empty, and we don't sell air, yet.       ", "\033[3;37mGo add some products to your cart and we'll see you then!");

        getch();
        return 0;        
    }

    empCrt.close();

    ifstream cart;
    int cartItems = fileLength("cart.txt"), i = 0;
    int qty[cartItems], ids[cartItems];
    string productNames[cartItems];
    cart.open("cart.txt");

    for(i = 0; i < cartItems-1; i++){
        cart >> ids[i];
        cart >> productNames[i];
        cart >> dummyInt;
        cart >> qty[i];

        replace_in_string(productNames[i], '-', ' ');
        replace_in_string(productNames[i], '_', '-');

        productNames[i].append(" (");
        productNames[i].append(toStr(qty[i])).append(")");
    }
    cart.close();

    window crt("Your cart");
    crt.showWindow(i, productNames);

    selector checkOutList;
    string cOps[2] = {"Continue", "Go back"};

    int checkOutListReturn = checkOutList.showSelectorList(cartItems + 3 + 3, 2, "Continue to checkout", "Go back");

    if(checkOutListReturn == 1) return 0;

    if(confirm_address() == 1){
        return 0;
    }

    invoice();

    cout << endl << "          A copy of this invoice will be saved as \"INVOICE_" + f_name + ".txt\" in the current directory";
    cout << endl << "          Press any key to continue...";

    getch();

    save_invoice();

    CLEAR;

    cout << "\n\n";

    boxCentered("Invoice has been saved!", 5, 50, 2);

    Sleep(2000);
    return 0;
}

int person :: confirm_address(){
    CLEAR;

    undStr("Delivery address:");

    cout << endl << address;

    selector checkOutList;
    string cOps[2] = {"Continue", "Go back"};

    int addressReturn = checkOutList.showSelectorList(1, 2, "Continue", "Go back");

    if(addressReturn == 1) return 1;

    else return 0;
}

int person :: create_account(){

    CLEAR;
    string date;
    vector<string> attrs;

    window get_details("Create account");

    attrs.push_back("Account no.      : ");
    attrs.push_back(" ");
    attrs.push_back("Password         : ");
    attrs.push_back(" ");
    attrs.push_back("First name       : ");
    attrs.push_back(" ");
    attrs.push_back("Last name        : ");
    attrs.push_back(" ");
    attrs.push_back("DOB(dd/mm/yyyy)  : ");
    attrs.push_back(" ");
    attrs.push_back("Email ID         : ");
    attrs.push_back(" ");
    attrs.push_back("Phone no.        : ");
    
    get_details.showWindow(attrs);

    // READING INPUTS
    consoleGoto(26,7);
    cin >> account_no;

    consoleGoto(26,9);
    cin >> password;

    consoleGoto(26,11);
    cin >> f_name;

    consoleGoto(26,13);
    cin >> l_name;

    consoleGoto(26,15);
    _flushall();
    getline(cin, date);
    dob = parse_date(date);

    consoleGoto(26,17);
    cin >> email_id;

    consoleGoto(26,19);
    cin >> phone_no;

    

    // VALIDATING INPUTS

    valAccountNo:
    // CHECKING IF LONGER THAN 10 DIGITS
    if(account_no.length() > 10){
        CLEAR;
        setColor(12);
        cout << "  Invalid input received in account no. Account no cannot be longer than 10 digits!\n";
        setColor(7);
        cout << "\n Entered data: " << account_no;
        cout << "\n Enter account no.: ";
        cin >> account_no;
        goto valAccountNo;
    }

    // CHECKING IF ACCOUNT NO. ALREADY EXISTS
    bool found_duplicate = false;
    {    
        ifstream list("account_list.txt");
        string temp_ac_no;

        while(!list.eof()){
            list >> temp_ac_no;
            list >> dummyString;

            if(temp_ac_no == account_no) {
                found_duplicate = true; break;
            }
        }

        list.close();
    }

    if(found_duplicate){
        CLEAR;
        setColor(12);
        cout << "\n\n  There is already an account with this account no. Please enter a different account no.\n";
        setColor(7);
        cout << "\n Entered data: " << account_no;
        cout << "\n Enter account no.: ";
        cin >> account_no;
        goto valAccountNo;
    }

    // CHECKING IF CONTAINS LETTERS
    for(int i = 0; i < account_no.length(); i++)
        if(!(account_no.at(i) >= '0' && account_no.at(i) <= '9')){
            CLEAR;
            cout << "\n\n";
            setColor(12);
            cout << "  Invalid input received in account no. Account no. can only contain numbers!\n";
            setColor(7);
            cout << "\n Entered data: " << account_no;
            cout << "\n Enter account no.: ";
            cin >> account_no;
            goto valAccountNo;
        }


    valFName:
    for(int i = 0; i < f_name.length(); i++)
        if(f_name.at(i) >= '0' && f_name.at(i) <= '9'){
            CLEAR;
            cout << "\n\n";
            setColor(12);
            cout << "  Invalid input received in first name. Name cannot contain digits!\n";
            setColor(7);
            cout << "\n Entered data: " << f_name;
            cout << "\n Enter first name: ";
            cin >> f_name;
            goto valFName;
        }

    valLName:
    for(int i = 0; i < l_name.length(); i++)
        if(l_name.at(i) >= '0' && l_name.at(i) <= '9'){
            CLEAR;
            cout << "\n\n";
            setColor(12);
            cout << "  Invalid input received in last name. Name cannot contain digits!\n";
            setColor(7);
            cout << "\n Entered data: " << l_name;
            cout << "\n Enter last name: ";
            cin >> l_name;
            goto valLName;
        }

    valEmail:
    if(email_id.find("@") == string::npos || email_id.find(".") == string::npos){
        CLEAR;
        cout << "\n\n";
        setColor(12);
        cout << "  Invalid input received in Email Id. Please enter a valid email id\n";
        setColor(7);
        cout << "\n Entered data: " << email_id;
        cout << "\n Enter email id: ";
        cin >> email_id;
        goto valEmail;
    }

    valPhone:
    if(phone_no.length() != 10){
        CLEAR;
        cout << "\n\n";
        setColor(12);
        cout << "  Invalid input received in Phone no. Please enter a valid phone no\n";
        setColor(7);
        cout << "\n Entered data: " << phone_no;
        cout << "\n Enter Phone no: ";
        cin >> phone_no;
        goto valPhone;
    }


    // READING ADDRESS
    CLEAR;
    undStr("Address");

    cout << "\n\n  Enter address: ";
    _flushall();
    cin.clear();
    getline(cin, address);

    // ADDING ACCOUNT TO ACCOUNT_LIST.TXT

    ofstream list;
    list.open("account_list.txt", ios::app);
    list << account_no << " " << password << endl;
    list.close();

    write_user_file();

    CLEAR;

    cout << "\n\n";

    boxCentered("ACCOUNT CREATED SUCCESSFULLY!", 5, 50, 2);
    Sleep(1000);

    return 0;
}

int person :: write_user_file(){
    string file_path = "usr\\";
    file_path.append(account_no).append(".txt");

    ofstream usr;
    usr.open(file_path.c_str(), ios::out);

    if(!usr.is_open()){
        cout << "\nCannot open user file!";
        exit(1);
    }

    string temp_address = address;

    replace_in_string(temp_address, '-', '_');
    replace_in_string(temp_address, ' ', '-');

    // WRITING DATA
    usr << f_name << " " << l_name << endl << dob.d << " " << dob.m << " " << dob.y << endl << email_id << endl << phone_no << endl << temp_address;

    usr.close();

    return 0;
}

int person :: edit_profile(){
    CLEAR;

    string date;
    int change;

    selector detail_to_change("What do you want to change?");
    change = detail_to_change.showSelector(5, "Name", "DOB", "Email ID", "Phone no.", "Go Back");

    CLEAR;

    cout << "\n";
    undStr("Update Account details");
    
    cout << "\n\n Current data: ";

    switch(change){
        case 0:
            cout << f_name << " " << l_name;

            cout << "\n\n Enter new first name: ";
            cin >> f_name;

            cout << "\n Enter new last name: ";
            cin >> l_name;

            valFName:
            for(int i = 0; i < f_name.length(); i++)
            if(f_name.at(i) > '0' && f_name.at(i) < '9'){
                CLEAR;
                cout << "\n\n";
                setColor(12);
                cout << "  Invalid input received in first name. Name cannot contain digits!\n";
                setColor(7);
                cout << "\n Entered data: " << f_name;
                cout << "\n Enter first name: ";
                cin >> f_name;
                goto valFName;
            }



            valLName:
            for(int i = 0; i < l_name.length(); i++)
            if(l_name.at(i) > '0' && l_name.at(i) < '9'){
                CLEAR;
                cout << "\n\n";
                setColor(12);
                cout << "  Invalid input received in last name. Name cannot contain digits!\n";
                setColor(7);
                cout << "\n Entered data: " << l_name;
                cout << "\n Enter last name: ";
                cin >> l_name;
                goto valLName;
            }
        break;

        case 1:
            cout << dob.d << "/" << dob.m << "/" << dob.y << "\n\n Enter new dob: ";
            _flushall();
            getline(cin, date);
            dob = parse_date(date);
        break;

        case 2:
            cout << email_id << "\n\n Enter new email id: ";
            cin >> email_id;

            valEmail:
            if(email_id.find("@") == string::npos || email_id.find(".") == string::npos){
            CLEAR;
            cout << "\n\n";
            setColor(12);
            cout << "  Invalid input received in Email Id. Please enter a valid email id\n";
            setColor(7);
            cout << "\n Entered data: " << email_id;
            cout << "\n Enter email id: ";
            cin >> email_id;
            goto valEmail;
        break;

        case 3:
            cout << phone_no << "\n\n Enter new phone no.: ";
            getline(cin, phone_no);
            valPhone:
            if(phone_no.length() != 10){
                CLEAR;
                cout << "\n\n";
                setColor(12);
                cout << "  Invalid input received in Phone no. Please enter a valid phone no\n";
                setColor(7);
                cout << "\n Entered data: " << phone_no;
                cout << "\n Enter Phone no: ";
                cin >> phone_no;
                goto valPhone;
            }
            }
        break;

        case 4:
        return 0;
    }

    write_user_file();

    CLEAR;

    cout << "\n\n";
    boxCentered("DETAILS UPDATED SUCCESSFULLY!", 5, 50, 3);
    Sleep(1000);

    return 0;
}

int person :: delete_account(){
    CLEAR;

    int choice;

    selector confirm("Are you sure you want to delete your account?");
    choice = confirm.showSelector(2, "No", "Yes");

    if(choice == 0) return 0;

    string conf_password;

    confirmation:
    CLEAR;
    cout << "\n";
    undStr("Delete account");

    cout << "\nConfirm your password: ";
    conf_password = get_hidden_input();

    if(conf_password == password){
        remove_from_list(account_no);
        delete_file(account_no);

        CLEAR;

        cout << "\n\n\n";
        boxCentered("ACCOUNT DELETED PERMANENTLY!", 5, 50, 12);
        Sleep(1000);

        return 0;
    }

    else{
        CLEAR;

        setColor(4);
        cout << "\n\n  WRONG PASSWORD!";
        setColor(7);
        Sleep(1000);
        goto confirmation;
    }

    return 0;
}



int main(){

    showWelcomeScreen();
    check_files();
    find_total();
    main_screen();

    return 0;
}

int main_screen(){
    CLEAR;

    selector mainScr("MAIN MENU");
    mainScr.index = true;
    mainScr.enableNum = true;
    mainScr.bracket = '[';

    mainPoint:
    CLEAR;
    int mainResult = mainScr.showSelector(4, "Login", "Create new account", "Admin login", "Exit");

    CLEAR;

    person user;

    switch(mainResult){
        case 0:
        case 11:
            user.login();
            break;
        
        case 1:
        case 12:
            user.create_account();
            break;

        case 2:
        case 13:
            admin_login();
            break;

        case 3:
        case 14:
            CLEAR;
            cout << "\n\n";
            boxCentered("Thank you :) Have a great day!", 6, 60, 6);
            Sleep(3000);
            return 0;
    }

    goto mainPoint;
}

int view_items(int cat){
    ifstream dataFile;
    string filename, productNames[30], categoryName;

    // VARIABLES FOR READING DATA FROM FILE
    int fid, i, fyear;
    float fprice;
    string fname, fdes, fmfg;


    // SETTING CATAGORY NAME AND FILENAME FROM SELECTED CATAGORY INDEX
    switch(cat){
        case 1:
        filename = "clothes.txt";
        categoryName = "Clothes";
        break;

        case 2:
        filename = "electronics.txt";
        categoryName = "Electronics";
        break;

        case 3:
        filename = "household.txt";
        categoryName = "Household";
        break;

        case 4:
        filename = "medical.txt";
        categoryName = "Medical";
        break;

        case 5:
        filename = "food.txt";
        categoryName = "Food";
        break;

        case 6:
        filename = "stationary.txt";
        categoryName = "Stationary";
        break;

        case 7:
        filename = "kitchen.txt";
        categoryName = "Kitchen ware";
        break;
    }

    // OPEN DATA FILE OF SELECTED CATAGORY
    dataFile.open(filename.c_str());

    // READING DATA FROM FILE
    for(i = 0; !dataFile.eof(); i++){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> fyear;
        dataFile >> fmfg;
        dataFile >> fdes;

        replace_in_string(fname, '-', ' ');
        replace_in_string(fname, '_', '-');

        // STORING NAMES OF PRODUCT IN ARRAY TO DISPLAY
        productNames[i] = fname;
    }

    // LAST OPTION TO GO BACK
    productNames[i] = "Go back";

    selector view(categoryName);

    showProducts:
    int selReturn = view.showSelector(i+1, productNames);

    // INDEX OF "GO BACK" WILL BE i
    if(selReturn == i) return 0;

    else{
        int selectedProductId = get_product_id(filename, selReturn);
        product one;
        one.get_product_data(selectedProductId);         // READ DATA OF SELECTED PRODUCT FROM FILE
        one.view_product_details();
        goto showProducts;
    }
}

int view_category(){
    _flushall();

    int cat;

    selector c("Categories");
    c.enableNum = true;
    c.bracket = '[';

    selectCategory:
    switch(c.showSelector(8, "[1] Clothes", "[2] Electronics", "[3] Household", "[4] Medical", "[5] Food", "[6] Stationary", "[7] Kitchen", "Go Back")){
        case 0:
        case 11:
        cat = 1;
        break;

        case 1:
        case 12:
        cat = 2;
        break;

        case 2:
        case 13:
        cat = 3;
        break;

        case 3:
        case 14:
        cat = 4;
        break;

        case 4:
        case 15:
        cat = 5;
        break;

        case 5:
        case 16:
        cat = 6;
        break;

        case 6:
        case 17:
        cat = 7;
        break;

        case 7:
        case 18:
        return 0;
    }

    if(view_items(cat) != -1) goto selectCategory;    // CALLING VIEWITEMS AFTER SETTING VALUE OF CAT
                                                  // IF CHOSEN GO BACK, RETURNS -1
    else return 0;
}

int search(){
    CLEAR;
    
    string keyWord;
    window searchUi;

    find_total();                                  // GET TOTAL NUMBER OF PRODUCTS

    searchUi.title = "Search across ";
    searchUi.title.append(toStr(totalProds));
    searchUi.title.append(" products");
    startSearch:
    searchUi.showWindow(1, "Search: ");

    cout << "\n\n     \033[3;33m:: AVAILABLE CATEGORIES ::\033[0m\n\n";
    cout << "     CLOTHES\tELECTRONICS\tHOUSEHOLD\tMEDICAL\n     FOOD\tSTATIONARY\tKITCHEN WARE";

    consoleGoto(15, 7);
    getline(cin, keyWord);
    lwr(keyWord);

    if(keyWord == "cloth" || keyWord == "clothes" || keyWord == "clothing" || keyWord == "dressing"){
        view_items(1);
    }

    else if(keyWord == "electronics" || keyWord == "electronic" || keyWord == "appliances" || keyWord == "home appliances" || keyWord == "home appliance"){
        view_items(2);
    }

    else if(keyWord == "household" || keyWord == "home" || keyWord == "house" || keyWord == "general"){
        view_items(3);
    }

    else if(keyWord == "medical" || keyWord == "doctor" || keyWord == "first aid" || keyWord == "pharmacy"){
        view_items(4);
    }

    else if(keyWord == "food" || keyWord == "nasto" || keyWord == "snack" || keyWord == "snacks"){
        view_items(5);
    }

    else if(keyWord == "stationary" || keyWord == "study" || keyWord == "school" || keyWord == "study material"){
        view_items(6);
    }

    else if(keyWord == "kitchen" || keyWord == "kitchenware" || keyWord == "kitchen ware" || keyWord == "cooking"){
        view_items(7);
    }
    
    // IF NO MATCHING KEYWORD FOUND
    else search_core(keyWord);

    return 0;
}

int search_core(string key){
    ifstream dataFile;
    int fid, ids[200], foundCounter = 0;
    string fname, productNames[200];
    float fprice;

    if(key.empty()){
        CLEAR;

        cout << "\n\n\n";

        boxCentered("Please enter something to search!", 5, 50, 14);
        Sleep(2000);
        return 0;
    }

    lwr(key);   // CONVERTING STRING TO LOWER CASE

    // SEARCHING EACH FILE FOR SUPPLIED KEY TO LOOK FOR A MATCH

    dataFile.open("clothes.txt");
    while(!dataFile.eof()){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> dummyString;
        dataFile >> dummyString;
        dataFile >> dummyString;
        
        string compareName = fname;
        lwr(compareName);

        if(compareName.find(key) != string::npos){
            ids[foundCounter] = fid;
            replace_in_string(fname, '-', ' ');
            replace_in_string(fname, '_', '-');
            productNames[foundCounter++] = fname;
        }
    }

    dataFile.close();
    dataFile.open("electronics.txt");

    while(!dataFile.eof()){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> dummyString;
        dataFile >> dummyString;
        dataFile >> dummyString;

        string compareName = fname;
        lwr(compareName);

        if(compareName.find(key) != string::npos){
            ids[foundCounter] = fid;
            replace_in_string(fname, '-', ' ');
            replace_in_string(fname, '_', '-');
            productNames[foundCounter++] = fname;
        }
    }
    dataFile.close();
    dataFile.open("household.txt");
    

    while(!dataFile.eof()){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> dummyString;
        dataFile >> dummyString;
        dataFile >> dummyString;

        string compareName = fname;
        lwr(compareName);

        if(compareName.find(key) != string::npos){
            ids[foundCounter] = fid;
            replace_in_string(fname, '-', ' ');
            replace_in_string(fname, '_', '-');
            productNames[foundCounter++] = fname;
        }
    }
    dataFile.close();
    dataFile.open("medical.txt");

    while(!dataFile.eof()){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> dummyString;
        dataFile >> dummyString;
        dataFile >> dummyString;

        string compareName = fname;
        lwr(compareName);

        if(compareName.find(key) != string::npos){
            ids[foundCounter] = fid;
            replace_in_string(fname, '-', ' ');
            replace_in_string(fname, '_', '-');
            productNames[foundCounter++] = fname;
        }
    }

    dataFile.close();
    dataFile.open("food.txt");

    while(!dataFile.eof()){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> dummyString;
        dataFile >> dummyString;
        dataFile >> dummyString;

        string compareName = fname;
        lwr(compareName);

        if(compareName.find(key) != string::npos){
            ids[foundCounter] = fid;
            replace_in_string(fname, '-', ' ');
            replace_in_string(fname, '_', '-');
            productNames[foundCounter++] = fname;
        }
    }

    dataFile.close();
    dataFile.open("stationary.txt");

    while(!dataFile.eof()){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> dummyString;
        dataFile >> dummyString;
        dataFile >> dummyString;

        string compareName = fname;
        lwr(compareName);

        if(compareName.find(key) != string::npos){
            ids[foundCounter] = fid;
            replace_in_string(fname, '-', ' ');
            replace_in_string(fname, '_', '-');
            productNames[foundCounter++] = fname;
        }
    }

    dataFile.close();
    dataFile.open("kitchen.txt");

    while(!dataFile.eof()){
        dataFile >> fid;
        dataFile >> fname;
        dataFile >> fprice;
        dataFile >> dummyString;
        dataFile >> dummyString;
        dataFile >> dummyString;

        string compareName = fname;
        lwr(compareName);

        if(compareName.find(key) != string::npos){
            ids[foundCounter] = fid;
            replace_in_string(fname, '-', ' ');
            replace_in_string(fname, '_', '-');
            productNames[foundCounter++] = fname;
        }
    }

    dataFile.close();

    CLEAR;

    productNames[foundCounter] = "Go back";
    ids[foundCounter] = -1;

    // IF NO MATCH FOUND
    if(foundCounter == 0){
        window noItems;
        noItems.title = "Search results for \"";
        noItems.title.append(key);
        noItems.title.append("\"");    
        noItems.showWindow(2, "No items found! Try something different", "Press any key to go back");
        getch();
        return 0;
    }

    selector searchResult;

    searchResult.title = "Search results for \"";
    searchResult.title.append(key);
    searchResult.title.append("\"");
    showResult:
    int searchReturn = ids[searchResult.showSelector(foundCounter+1, productNames)];

    if(searchReturn == -1) return 0;            // ID OF "GO BACK" IS SET TO -1 (LINE 602)

    else{
        product searched;

        searched.get_product_data(searchReturn);
        searched.view_product_details();
        goto showResult;
    }

    return 0;
}

int view_cart(){
    CLEAR;
    int dummyInt;
    selector cart("Your cart");

    ifstream cartFile;

    backPoint:
    int cartItems = fileLength("cart.txt"), i = 0;
    int qty[cartItems], ids[cartItems];
    string productNames[cartItems];
    cartItems = fileLength("cart.txt");
    cartFile.open("cart.txt");


    // CHECKING IF CART IS EMPTY
    ifstream empCart;
    empCart.open("cart.txt");
    empCart >> dummyString;
    if(empCart.eof()){
        CLEAR;
        empCart.close();
        window noItem("Your cart");
        noItem.showWindow(2, "\033[3;37mThere\'s nothing to show here!                  ", "\033[3;37mPress any key to go back\033[0m                       ");

        getch();
        return 0;
    }

    empCart.close();

    for(i = 0; i < cartItems-1; i++){
        cartFile >> ids[i];
        cartFile >> productNames[i];
        cartFile >> dummyInt;
        cartFile >> qty[i];

        replace_in_string(productNames[i], '-', ' ');
        replace_in_string(productNames[i], '_', '-');

        productNames[i].append(" (");
        productNames[i].append(toStr(qty[i])).append(")");
    }
    cartFile.close();

    cout << i;

    productNames[i] = "Go Back";
    ids[i] = -1;


    int selReturn = cart.showSelector(i+1, productNames);
    int cartReturn = ids[selReturn];

    if(cartReturn != -1){
        product cartPro;
        cartPro.get_product_data(cartReturn);
        cartPro.cart_item_detail(qty[selReturn]);
        cartFile.close();
        goto backPoint;
    }

    else{
        return 0;
    }
}

int change_quantity(int cId, int cQty){
    int fId, fQty;
    string fName;

    ifstream old_cart;
    ofstream new_cart;

    int iterate = fileLength("cart.txt");

    old_cart.open("cart.txt");
    new_cart.open("tempCart.txt", ios::app);

    for(int i = 0; i < iterate-1; i++){
        old_cart >> fId;
        old_cart >> fName;
        old_cart >> dummyInt;
        old_cart >> fQty;

        if(fId == cId) {
            if(cQty == 0) continue;
            else fQty = cQty;
        }

        new_cart << fId << " " << fName << " " << dummyInt << " " << fQty << endl;
    }

    old_cart.close();
    new_cart.close();

    system("del cart.txt");
    system("ren tempCart.txt cart.txt");

    return 0;
}

int get_product_id(string filename, int n){
    ifstream data;
    data.open(filename.c_str());

    int productCount = fileLength(filename);
    int ids[productCount];

    // STORING PRODUCT IDS IN ARRAY
    for(int i = 0; i < productCount; i++){
        data >> ids[i];

        for(int j = 0; j < 5; j++)              // TO IGNORE 5 EXTRA STRINGS AFTER THE ID (PRICE, DESCRIPTION, ETC.)
            data >> dummyString;
    }

    data.close();

    // RETURNING REQUIRED ID
    return ids[n];
}



int admin_login(){
    string pw;

    int tries = 3;

    // CHECK IF SUSPENDED FOR 5 MIN
    ifstream sus;
    sus.open("suspend.tmp");
    if(sus.is_open()){
        long int suspend_time;
        int dif;
        sus >> suspend_time;
        sus.close();

        time_t current_time = time(0);
        dif = current_time - suspend_time;

        if(dif < 300){

            window no_entry("YOU CANNOT LOGIN");

            string msgs[4] = {"You have made too many unsuccessful attempts", ("to login. You can try again after " + toStr((300 - dif)/60) + " minutes")," " , "Press any key to continue"};

            no_entry.showWindow(4, msgs);

            getch();
            return 0;
        }

        else{
            system("del suspend.tmp");
        }
    }

    window readPw;
    readPw.title = "ADMIN LOGIN";

    read:
    pw.clear();
    CLEAR;
    _flushall();
    readPw.showWindow(1, "PASSWORD:");
    consoleGoto(17,7);

    // READING AND HIDING PASSWORD
    pw = get_hidden_input();

    if(pw == "eSc") return 0;

    if(pw == "AdminPassword") admin_screen();

    else{
        if(tries == 1){
            CLEAR;
            cout << "\n  You have exceeded max no. of attempts to log in!\n  You cannot continue!\n  You can try again after 5 minutes";

            // GENERATING SUSPEND FILE

            ofstream suspend;
            suspend.open("suspend.tmp", ios::out);

            time_t current_time = time(0);

            suspend << current_time;

            suspend.close();

            getch();
            return 0;
        }
        consoleGoto(0,12);
        boxCentered("WRONG PASSWORD!", 5, 50, 4);
        cout << "\n\t REMAINING TRY(s): " << --tries;
        getch();
        goto read;
    }
    return 0;
}

int admin_screen(){
    CLEAR;

    selector admin("ADMIN");

    admin.index = true;
    admin.enableNum = true;
    admin.bracket = '[';
    
    select_task:
    switch(admin.showSelector(4, "ADD PRODUCT", "REMOVE PRODUCT", "UPDATE PRICE", "LOGOUT")){
        case 0:
        case 11:
        add_product();
        break;

        case 1:
        case 12:
        remove_product();
        break;

        case 2:
        case 13:
        update_price();
        break;

        case 3:
        case 14:
        return 0;
    }

    goto select_task;
}

int add_product(){
    CLEAR;

    selector category("Select category to add Product");
    string filename;

    // SELECT CATAGORY

    CLEAR;

    int selectedCat = category.showSelector(8, "Clothes", "Electronics", "Household", "Medical", "Food", "Stationary", "Kitchen", "Go back");

    switch(selectedCat){
        case 0:
            filename = "clothes";
        break;
        
        case 1:
            filename = "electronics";
        break;

        case 2:
            filename = "household";
        break;

        case 3:
            filename = "medical";
        break;

        case 4:
            filename = "food";
        break;

        case 5:
            filename = "stationary";
        break;

        case 6:
            filename = "kitchen";
        break;

        case 7:
            return 0;
    }
    filename.append(".txt");

    string productName, desc, date;
    int years;
    float price;

    // GET PRODUCT DETAILS
    CLEAR;
    string input_attrs[4] = {"ENTER PRODUCT NAME   : ", "ENTER PRICE          : ", "ENTER WARRENTY YEARS : ", "ENTER MFG DATE       : "};

    cout << "\n\n\n";

    box(4, input_attrs, 5, 50);

    consoleGoto(30,4);
    getline(cin, productName);
    _flushall();
    consoleGoto(30,5);
    _flushall();
    cin >> price;
    consoleGoto(30,6);
    _flushall();
    cin >> years;
    consoleGoto(30,7);
    _flushall();
    getline(cin, date);

    replace_in_string(productName, '-', '_');
    replace_in_string(productName, ' ', '-');
    replace_in_string(date, '-', '_');
    replace_in_string(date, ' ', '-');

    CLEAR;

    cout << "\n\n\n";
    boxCentered("ENTER PRODUCT DESCRIPTION", 5,50);
    consoleGoto(7,7);
    _flushall();
    getline(cin, desc);

    replace_in_string(desc, '-', '_');
    replace_in_string(desc, ' ', '-');

    int nextId = get_next_id(filename);

    // WRITING TO FILE
    ofstream dataFile;
    dataFile.open(filename.c_str(), ios::app);
    if(!dataFile.is_open()) cout << "File not open";
    dataFile << "\n" << nextId << " " << productName << " " << price << " " << years << " " << date << " " << desc;
    dataFile.close();


    // SHOWING SUCCESS MSG
    
    CLEAR;
    cout << "\n\n";
    boxCentered("NEW PRODUCT ADDED SUCCESSFULLY", 5, 55, 2);

    Sleep(1000);

    _flushall();

    return 0;
}

int remove_product(){
    int remId;
    string file;

    ifstream data_file;
    vector<string> items;
    vector<int> item_ids;


    selectCategory:
    CLEAR;
    selector category("Select category");
    int selectedCategory = category.showSelector(8, "Clothes", "Electronics", "Household", "Medical", "Food", "Stationary", "Kitchen", "Go back");

    CLEAR;

    if(selectedCategory == 7) return 0;

    switch(selectedCategory){
        case 0:
        file = "clothes.txt";
        break;
        
        case 1:
        file = "electronics.txt";
        break;
        
        case 2:
        file = "household.txt";
        break;
        
        case 3:
        file = "medical.txt";
        break;
        
        case 4:
        file = "food.txt";
        break;
        
        case 5:
        file = "stationary.txt";
        break;
        
        case 6:
        file = "kitchen.txt";
        break;
    }

    // READING FILE OF SELECTED CATEGORY
    data_file.open(file);
    
    items.clear();
    item_ids.clear();

    while(!data_file.eof()){
        data_file >> dummyInt;
        item_ids.push_back(dummyInt);
        data_file >> dummyString;
        replace_in_string(dummyString, '-', ' ');
        replace_in_string(dummyString, '_', '-');
        items.push_back(dummyString);

        for(int i = 0; i < 4; i++)
            data_file >> dummyString;
    }

    data_file.close();

    // ADDING OPTION TO GO BACK
    items.push_back("Go back");
    item_ids.push_back(-1);

    selector product("Select product");
    int selectedItem = product.showSelector(items);

    remId = item_ids[selectedItem];

    if(remId == -1) goto selectCategory;

    CLEAR;

    cout << "\n\n";
    boxCentered("Are you sure you want to remove the product? (Y/N)", 10, 70);
    char c = getch();
    if(c != 'y' && c != 'Y') return 0;

    string newFile = "TEMP_";
    newFile.append(file);

    ifstream oldData;
    ofstream newData;
    oldData.open(file.c_str());
    newData.open(newFile.c_str());

    // VARIABLES TO STORE FILE DATA TEMPORARILY
    int oId, oPrice, oYear;
    string oName, oDate, oDes;

    for(int i = 0;!oldData.eof();i++){

        oldData >> oId;
        oldData >> oName;
        oldData >> oPrice;
        oldData >> oYear;
        oldData >> oDate;
        oldData >> oDes;

        if(oId == remId) continue;
        
        if(i != 0) newData << endl;

        newData << oId << " " << oName << " " << oPrice << " " << oYear << " " << oDate << " " << oDes;
    }

    oldData.close();
    newData.close();

    string delcmd = "del ";
    delcmd.append(file);

    string renCmd = "ren ";
    renCmd.append(newFile + " ");
    renCmd.append(file + " ");

    system(delcmd.c_str());
    system(renCmd.c_str());

    find_total();

    CLEAR;

    cout << "\n\n";
    boxCentered("Product removed!", 10, 30);
    Sleep(1000);
    _flushall();
    return 0;
}

int update_price(){
    CLEAR;

    int updateId, newP;
    string file;
    ifstream data_file;
    vector<string> items;
    vector<int> item_ids;

    selectCategory:
    CLEAR;
    selector category("Select category");
    int selectedCategory = category.showSelector(8, "Clothes", "Electronics", "Household", "Medical", "Food", "Stationary", "Kitchen", "Go back");

    CLEAR;

    if(selectedCategory == 7) return 0;

    switch(selectedCategory){
        case 0:
        file = "clothes.txt";
        break;
        
        case 1:
        file = "electronics.txt";
        break;
        
        case 2:
        file = "household.txt";
        break;
        
        case 3:
        file = "medical.txt";
        break;
        
        case 4:
        file = "food.txt";
        break;
        
        case 5:
        file = "stationary.txt";
        break;
        
        case 6:
        file = "kitchen.txt";
        break;
    }

    // READING FILE OF SELECTED CATEGORY
    data_file.open(file);

    items.clear();
    item_ids.clear();

    while(!data_file.eof()){
        data_file >> dummyInt;
        item_ids.push_back(dummyInt);
        data_file >> dummyString;
        replace_in_string(dummyString, '-', ' ');
        replace_in_string(dummyString, '_', '-');
        items.push_back(dummyString);

        for(int i = 0; i < 4; i++)
            data_file >> dummyString;
    }

    data_file.close();

    // ADDING OPTION TO GO BACK
    items.push_back("Go back");
    item_ids.push_back(-1);

    selector product("Select product");
    int selectedItem = product.showSelector(items);

    updateId = item_ids[selectedItem];

    if(updateId == -1) goto selectCategory;

    CLEAR;

    cout << "\n\n\n  ENTER NEW PRICE: ";
    cin >> newP;

    string newFile = "TEMP_";
    newFile.append(file);

    ifstream oldData;
    ofstream newData;

    oldData.open(file.c_str());
    newData.open(newFile.c_str());


    int oId, oPrice, oYear;
    string oName, oDate, oDes;

    for(int i = 0;!oldData.eof();i++){

        oldData >> oId;
        oldData >> oName;
        oldData >> oPrice;
        oldData >> oYear;
        oldData >> oDate;
        oldData >> oDes;

        if(oId == updateId) oPrice = newP;
        
        if(i != 0) newData << endl;

        newData << oId << " " << oName << " " << oPrice << " " << oYear << " " << oDate << " " << oDes;
    }

    oldData.close();
    newData.close();

    string delcmd = "del ";
    delcmd.append(file);

    string renCmd = "ren ";
    renCmd.append(newFile + " ");
    renCmd.append(file + " ");

    system(delcmd.c_str());
    system(renCmd.c_str());

    CLEAR;

    cout << "\n\n";
    boxCentered("PRICE UPDATED SUCCESSFULLY!", 5, 50, 2);
    Sleep(1000);

    return 0;
}

int remove_from_list(string ac){
    ifstream old_list;
    ofstream new_list;

    old_list.open("account_list.txt");
    new_list.open("new_account_list.txt", ios::out);

    string _ac, _pw;

    while(1){
        old_list >> _ac >> _pw;

        if(old_list.eof()) break;
        
        if(_ac == ac) continue;

        new_list << _ac << " " << _pw << endl;
    }

    new_list.close();
    old_list.close();

    system("del account_list.txt");
    system("ren new_account_list.txt account_list.txt");

    return 0;
}

int delete_file(string ac){
    string file_path = "usr\\";
    file_path.append(ac).append(".txt");

    string command = "del ";
    command.append(file_path);

    system(command.c_str());

    return 0;
}

void find_total(){
    ifstream dataFile;
    string dummyString;

    totalProds = 0;

    // COUNTING NO OF PRODUCTS IN EACH FILE

    totalProds += fileLength("clothes.txt");
    totalProds += fileLength("electronics.txt");
    totalProds += fileLength("household.txt");
    totalProds += fileLength("medical.txt");
    totalProds += fileLength("food.txt");
    totalProds += fileLength("stationary.txt");
    totalProds += fileLength("kitchen.txt");
}


void replace_in_string(string &str, char o, char n){
    for(int i = 0; i < str.length(); i++){
        if(str.at(i) == o) str.at(i) = n;
    }
}

int check_files(){

    int foundErr = 0;

    string files[8] = {"clothes.txt", "electronics.txt", "household.txt", "food.txt", "kitchen.txt", "medical.txt", "stationary.txt", "account_list.txt"};

    // CHECKING PRODUCT FILES
    ifstream file;
    for(int i = 0; i < 8; i++){
        file.open(files[i].c_str(), ios::in);
        if(!file.is_open()){
            setColor(4);
            cout << "ERROR_MISSING_FILE: ";
            setColor(7);
            cout << files[i];
            foundErr = 1;
        }
        file.close();
    }
    if(file.is_open()) file.close();

    // CHECKING FOR EXISTING INVOICE FILE
    file.open("INVOICE.txt");
    if(file.is_open()){
        file.close();
        system("del INVOICE.txt");
    }

    // REMOVING DATA FROM EXISTING CART FILE
    ofstream cart;
    cart.open("cart.txt");
    cart.close();

    if(foundErr){
        cout << "\n\nPress any key to exit";
        _flushall();
        getch();
        exit(1);
    }

    return 0;
}

int get_next_id(string filename){

    ifstream file;
    file.open(filename.c_str());

    int id;

    for(int i = 0; i < fileLength(filename); i++){
        file >> id;
        for(int j = 0; j < 5; j++)
            file >> dummyString;                // TO IGNORE 5 EXTRA STRINGS AFTER THE ID (PRICE, DESCRIPTION, ETC.)
    }
    
    file.close();

    return id+1;
}

int toInt(string s){
    int num = 0;

    for(int i = 0; i < s.length(); i++){
        num = num * 10 + (s.at(i) - '0');
    }

    return num;
}

date parse_date(string dt){
    // CONVERTING DATE STRING TO COMPATIBLE FORMAT
    replace_in_string(dt, '.', '-');
    replace_in_string(dt, ' ', '-');
    replace_in_string(dt, '/', '-');
    
    string date, month, year;

    int i;

    // READING UNTIL '-' IS OCCURED
    for(i = 0; i < dt.length(); i++){
        if(dt.at(i) == '-') break;
        else date.push_back(dt.at(i));
    }
    i++;

    for(i; i < dt.length(); i++){
        if(dt.at(i) == '-') break;
        else month.push_back(dt.at(i));
    }
    i++;

    for(i; i < dt.length(); i++){
        if(dt.at(i) == '-') break;
        else year.push_back(dt.at(i));
    }

    int d = toInt(date);
    int m = toInt(month);
    int y = toInt(year);

    struct date parsed_date;
    parsed_date.d = d;
    parsed_date.m = m;
    parsed_date.y = y;

    return parsed_date;
}

string get_hidden_input(){
    string msg;
    char c = 0;

    while(c != 13){
        _flushall();
        c = getch();
        if(c == 27) return "eSc";
        if(c == 8){
            if(msg.length() == 0) continue;
            pop(msg);
            cout << "\b \b";
            continue;
        }

        cout << "*";
        msg.push_back(c);
    }

    pop(msg);

    return msg;
}

inline void pop(string &str){
    str.resize(str.length()-1);
}



string get_date(){
    time_t now = time(0);
    char* dt = ctime(&now);

    stringstream date;
    date << dt;

    return date.str();
}

string toStr(int x){
    stringstream ss;
    ss << x;
    string str = ss.str();
    return str;
}

string toStr(float x){
    stringstream ss;
    ss << x;
    string str = ss.str();
    return str;
}

void lwr(string &str){
    for(int i = 0; i < str.length(); i++){
        str.at(i) = tolower(str.at(i));
    }
}
