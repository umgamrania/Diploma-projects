#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct{
    char AccountNo[10], password[35], FirstName[30], LastName[30], address[50], AccountType[15];
    int day,month,year,age,balance,RecordNo;
} customer;

// Main functions:

void main();
void createAC();
void login();
void loginRec();
void dashboard();
void view();
void deposit();
void withdraw();
void checkBalance();

// under-the-hood functions:

void scanValues();
void undStr(char st[50]);
int findLines();
void printLine(int length);

void main(){
    char c;
    char ch;
    system("cls");
    printf("\n\n\n\t\t");
    printf("%c",201);
    printLine(40);
    printf("%c",187);
    printf("\n\t\t%c                MAIN MENU               %c", 186,186);
    printf("\n\t\t%c",204);
    printLine(40);
    printf("%c",185);
    printf("\n\t\t%c                                        %c", 186,186);
    printf("\n\t\t%c [1] Login with account no.             %c", 186,186);
    printf("\n\t\t%c [2] Login with Record no               %c", 186,186);
    printf("\n\t\t%c [3] Create new account                 %c", 186,186);
    printf("\n\t\t%c [4] Exit                               %c", 186,186);
    printf("\n\t\t%c                                        %c", 186,186);
    printf("\n\t\t%c",200);
    printLine(40);
    printf("%c", 188);
    printf("\n\n\t\tEnter your choice(1-3): ");
    scanf("%c", &c);
    switch(c){
        case '1':
        login();
        break;

        case '2':
        loginRec();
        break;

        case '3':
        createAC();
        break;

        case '4':
        system("cls");
        undStr("Exit");
        printf("\n  Are you sure you want to exit?");
        printf("\n  Enter your choice (y/n): ");
        _flushall();
        scanf("%c", &ch);
        if(ch == 'y' || ch == 'Y'){
            exit(1);
        }

        else{
            main();
        }

        default:
        main();
    }
}

void createAC(){
    FILE *data = fopen("list.txt", "a+");
    FILE *userFile;
    customer.RecordNo = findLines() + 1;
    system("cls");
    undStr("Create new account(Assign initial values)");
    printf("\n  Please enter the following details to create an account\n\n  NOTE: These details will be permanent. They cannot be changed once your account is created.\n\n");
    printf("  Account no.      : ");
    scanf("%s", &customer.AccountNo);

    printf("\n  Password         : ");
    scanf("%s", &customer.password);

    fprintf(data, "%s %s %d\n", customer.AccountNo, customer.password, customer.RecordNo);

    userFile = fopen(strcat(customer.AccountNo, ".txt"), "w");

    printf("\n  First name       : ");
    scanf("%s", &customer.FirstName);

    printf("\n  Last name        : ");
    scanf("%s", &customer.LastName);

    printf("\n  DOB (dd/mm/yyyy) : ");
    _flushall();
    scanf("%d/%d/%d", &customer.day, &customer.month, &customer.year);

    printf("\n  City             : ");
    scanf("%s", &customer.address);

    printf("\n  Balance          : ");
    scanf("%d", &customer.balance);
    printf("\n");
    printf("  **** Available account types ****");
    printf("\n  Savings\n  Current\n  Fixed Deposite\n");
    printf("\n  Account type     : ");
    _flushall();
    gets(customer.AccountType);

    fprintf(userFile, "%s %s\n%d/%d/%d\n%s\n%d\n%s", customer.FirstName, customer.LastName, customer.day, customer.month, customer.year, customer.address, customer.balance, customer.AccountType);
    system("cls");
    undStr("Message");
    printf("\n\n  Account created successfully\n\n  Your record no. is %d", customer.RecordNo);
    printf("\n\n\t\t");
    printf("%c", 201);
    printLine(40);
    printf("%c", 187);
    printf("\n\t\t%c [Enter] Go back to main menu           %c", 186, 186);
    printf("\n\t\t%c", 200);
    printLine(40);
    printf("%c", 188);
    getch();
    fclose(userFile);
    fclose(data);
    main();
}


void login(){
    FILE *list = fopen("list.txt", "a+");
    char tempAC[20], tempPW[20];
    system("cls");
    undStr("Login with account no.");
    printf("\n  Enter account no.  : ");
    scanf("%s", &tempAC);
    scanValues();
    while((fscanf(list, "%s %s %d", &customer.AccountNo, &customer.password, &customer.RecordNo) != EOF)){
        if((strcmp(tempAC, customer.AccountNo)) == 0){
            scanValues();

            printf("\n  Enter password     : ");
            scanf("%s", &tempPW);
            
            if((strcmp(tempPW, customer.password)) == 0){
                system("cls");
                undStr("Message");
                printf("\n  Welcome back %s!\n\n  Press Enter to go to Dashboard", customer.FirstName);     
                getch();
                dashboard();
            }

            else{
                system("cls");
                undStr("Welcome");
                printf("\n  Wrong password! Press Enter to try again");
                getch();
                login();
            }
        }
    }
    system("cls");
    undStr("Message");
    printf("\n  Your account could not be found. Press Enter to try again");
    getch();
    main();
}


void loginRec(){
    FILE *list = fopen("list.txt", "a+");
    char tempPW[20];
    int tempRec;
    system("cls");
    undStr("Login with record no.");
    printf("\n  Enter Record no.   : ");
    scanf("%d", &tempRec);

    while((fscanf(list, "%s %s %d", &customer.AccountNo, &customer.password, &customer.RecordNo) != EOF)){
        if(tempRec == customer.RecordNo){
            scanValues();

            printf("\n  Enter password     : ");
            scanf("%s", &tempPW);
            scanValues();
            if((strcmp(tempPW, customer.password)) == 0){
                system("cls");
                undStr("Welcome");
                printf("\n  Welcome back %s!\n\n  Press Enter to go to Dashboard", customer.FirstName);     
                getch();
                dashboard();
            }

            else{
                system("cls");
                undStr("Message");
                printf("\n  Wrong password! Press Enter to try again");
                getch();
                loginRec();
            }
        }
    }
    undStr("Message");
    printf("\n  Your account could not be found. Press Enter to try again");
    getch();
    main();
}

void dashboard(){
    char ch;
    system("cls");
    scanValues();
    system("cls");
    printf("\n\n\n\t\t");
    printf("%c",201);
    printLine(40);
    printf("%c",187);
    printf("\n\t\t%c                DASHBOARD               %c", 186,186);
    printf("\n\t\t%c",204);
    printLine(40);
    printf("%c",185);
    printf("\n\t\t%c                                        %c", 186,186);
    printf("\n\t\t%c [1] View account details               %c", 186,186);
    printf("\n\t\t%c [2] Deposit money                      %c", 186,186);
    printf("\n\t\t%c [3] Withdraw money                     %c", 186,186);
    printf("\n\t\t%c [4] Check account balance              %c", 186,186);
    printf("\n\t\t%c [5] Logout                             %c", 186,186);
    printf("\n\t\t%c                                        %c", 186,186);
    printf("\n\t\t%c",200);
    printLine(40);
    printf("%c", 188);
    printf("\n\n\t\tEnter your choice(1-5): ");
    // printf("1. View Account details\n2. Deposit money\n3. Withdraw money\n4. Check balance\n5. Logout");
    _flushall();
    scanf("%c", &ch);

    switch(ch){
        case '1':
        view();
        break;

        case '2':
        deposit();
        break;

        case '3':
        withdraw();
        break;

        case '4':
        checkBalance();
        break;

        case '5':
        main();
        break;

        default:
        system("cls");
        printf("Invalid input. \nPress enter to continue");
        getch();
        _flushall();
        dashboard();
    }
}


void view(){
    system("cls");
    char filename[14] = "";
    FILE *userFile;
    strcat(filename, customer.AccountNo);
    strcat(filename, ".txt");
    userFile = fopen(filename, "r");
    
    undStr("Account details");
    
    // fscanf(userFile, "%s %s %d/%d/%d %s %d", &customer.FirstName, &customer.LastName, &customer.day, &customer.month,&customer.year, &customer.address, &customer.balance);
    printf("\n\n\t\t%c", 201);
    printLine(50);
    printf("%c", 187);
    printf("\n\t\t%c                  ACCOUNT DETAILS                 %c", 186, 186);
    printf("\n\t\t%c",200);
    printLine(50);
    printf("%c", 188);
    printf("\n\t\t NAME          : %s %s", customer.FirstName, customer.LastName);
    printf("\n\t\t ACCOUNT NO    : %s", customer.AccountNo);
    printf("\n\t\t RECORD NO     : %d", customer.RecordNo);
    printf("\n\t\t DOB           : %d/%d/%d", customer.day, customer.month, customer.year);
    printf("\n\t\t City          : %s", customer.address);
    printf("\n\t\t Balance       : %d", customer.balance);
    printf("\n\t\t Account type  : %s", customer.AccountType);
    // printf("\n%s %s\n%d/%d/%d \n%s \n%d\n%s", customer.FirstName, customer.LastName, customer.day, customer.month, customer.year, customer.address, customer.balance, customer.AccountType);
    printf("\n\n\n\t\t");
    printf("%c", 201);
    printLine(50);
    printf("%c", 187);
    printf("\n\t\t%c [ENTER] Go back to dashboard                     %c",186,186);
    printf("\n\t\t%c", 200);
    printLine(50);
    printf("%c",188);
    getch();
    dashboard();
}

void deposit(){
    int depositAmount;
    char tempPW[30];
    char filename[14] = "";
    FILE *userFile;
    strcat(filename, customer.AccountNo);
    strcat(filename, ".txt");
    userFile = fopen(filename, "w");
    system("cls");
    undStr("Deposit money");

    printf("\n  Current balance: %d", customer.balance);

    printf("\n\n  Enter the amount to deposit : ");
    scanf("%d", &depositAmount);

    printf("\n  Confirm your password       : ");
    scanf("%s", &tempPW);

    if((strcmp(tempPW, customer.password)) == 0){
        customer.balance += depositAmount;
        printf("\n  %d rupees deposited successfully to your account (A/c no. %s)\n\n  Account balance: %d", depositAmount, customer.AccountNo, customer.balance);
        fprintf(userFile, "%s %s\n%d/%d/%d\n%s\n%d\n%s", customer.FirstName, customer.LastName, customer.day, customer.month, customer.year, customer.address, customer.balance, customer.AccountType);
        fclose(userFile);
        printf("\n\n\n\t\t");
        printf("%c", 201);
        printLine(40);
        printf("%c",187);
        printf("\n\t\t%c [ENTER] Go back to dashboard           %c",186,186);
        printf("\n\t\t%c", 200);
        printLine(40);
        printf("%c", 188);
        getch();
        dashboard();
    }

    else{
        system("cls");
        undStr("Message");
        printf("\n  Wrong password!\nPress Enter to try again");
        fclose(userFile);
        getch();
        deposit();
    }
}


void withdraw(){
    int withdrawAmount;
    char tempPW[30];
    char filename[14] = "";
    FILE *userFile;
    strcat(filename, customer.AccountNo);
    strcat(filename, ".txt");
    userFile = fopen(filename, "w");
    system("cls");
    undStr("Withdraw money");

    printf("\n  Current balance: %d", customer.balance);

    printf("\n\n  Enter the amount to withdraw : ");
    scanf("%d", &withdrawAmount);

    if(withdrawAmount > customer.balance){
        printf("\n Your account balance is %d rs. so you cannot withdraw %d rs.\n You can only withdraw a maximum of %d rs.\n Press enter to continue", customer.balance, withdrawAmount, customer.balance);
        getch();
        withdraw();
    }

    printf("\n  Confirm your password        : ");
    scanf("%s", &tempPW);

    if((strcmp(tempPW, customer.password)) == 0){
        customer.balance -= withdrawAmount;
        printf("\n  %d rupees withdrawed successfully from your account (A/c no. %s)\n\n  Account balance: %d", withdrawAmount, customer.AccountNo, customer.balance);
        fprintf(userFile, "%s %s\n%d/%d/%d\n%s\n%d\n%s", customer.FirstName, customer.LastName, customer.day, customer.month, customer.year, customer.address, customer.balance, customer.AccountType);
        fclose(userFile);
        printf("\n\n\n\t\t");
        printf("%c", 201);
        printLine(40);
        printf("%c",187);
        printf("\n\t\t%c [ENTER] Go back to dashboard           %c",186,186);
        printf("\n\t\t%c", 200);
        printLine(40);
        printf("%c", 188);
        getch();
        dashboard();
    }

    else{
        system("cls");
        undStr("Message");
        printf("\n  Wrong password!\n\n Press Enter to try again");
        fclose(userFile);
        getch();
        withdraw();
    }
}


void checkBalance(){
    char ch;
    system("cls");
    undStr("Check balance");
    printf("\n  Your account balance as of today : %d", customer.balance);
    printf("\n\n\n\t\t%c", 201);
    printLine(40);
    printf("%c", 187);
    printf("\n\t\t%c [1] Withdraw money                     %c", 186, 186);
    printf("\n\t\t%c [2] Deposit money                      %c", 186, 186);
    printf("\n\t\t%c [3] Go back to dashboard               %c", 186, 186);
    printf("\n\t\t%c", 200);
    printLine(40);
    printf("%c", 188);
    printf("\n\n\t\tEnter your choice(1-3): ");
    _flushall();
    scanf("%c", &ch);

    switch(ch){
        case '1':
        withdraw();
        break;

        case '2':
        deposit();
        break;

        case '3':
        dashboard();
        break;

        default:
        system("cls");
        undStr("Message");
        printf("\n  Invalid input. Press Enter to try again");
        getch();
        checkBalance();
    }
}







void scanValues(){
    char filename[14] = "";
    char demoString[20];
    FILE *userFile;
    strcat(filename, customer.AccountNo);
    strcat(filename, ".txt");
    userFile = fopen(filename, "r");
    fscanf(userFile, "%s %s\n%d/%d/%d\n%s\n%d\n", &customer.FirstName, &customer.LastName, &customer.day, &customer.month, &customer.year, &customer.address, &customer.balance);
    fgets(customer.AccountType, sizeof(demoString), userFile);
}

void undStr(char st[50]){
	printf("%s\n", st);
	for(int i = 0; i < strlen(st); i++){
		printf("%c", 205);
	}
	printf("\n");
}


int findLines(){
    FILE *dataFile = fopen("list.txt", "a+");
    int count = 0;
    for (char c = getc(dataFile); c != EOF; c = getc(dataFile)){
        if(c == '\n'){
            count++;
        }
    }
    fclose(dataFile);
    return count;
}


void printLine(int length){
    int i; 
    for (i = 0; i < length; i++){
        printf("%c", 205);
    }
}
