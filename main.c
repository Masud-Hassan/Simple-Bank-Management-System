#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info{     //This struct defines the basic structure of every account created through this bank system
    char accountName[30];
    int accountPin;
    float accountBalance;
    float deposit;
    float withdrawn;
}S1;

void credentials(char username[]);
void createAccount();
void balanceCheck();
void withdrawCash();
void depositCash();
void printReceit();

int main()
{
    char username[30]; //Stores the name of the customer trying to login

    printf("Enter you account Login Credentials:\n");

    printf("Account Name: ");
    gets(username);
    fflush(stdin);

    credentials(username); //send the obtained username for verification across saved username database

    return 0;
}

void credentials(char username[])
{
    int conf, choice;
    char name[35];
    int tempPin, pin;
    strcpy(name, username); //copies username to another var for ease of use
    strcat(name, ".txt"); //adds a .txt extension at the end of the username

    FILE *fp;
    fp = fopen(name, "r"); //opening files with the username.txt in the same folder as the project

    if(!fp) //this case is opted when the files is not found.
    {
        printf("Sorry such an account does not exist.\n\nWould you like to create one?\n");
        printf("Enter 1 for YES or 2 for NO: ");
        scanf(" %d", &conf);

        if(conf == 1)
        {
                printf("Opening registration form!!\n\n");
                createAccount(); //if file not found, user is prompted to open an account and sent to registration page
        }
        else
            exit(0);
    }
    else //if the user file is found, the pin is taken and verified against pin stored in the .txt file
    {
        printf("4-Digit Pin: ");
        scanf("%d", &pin);

        fscanf(fp, "%d", &tempPin);
        if(pin == tempPin) //checking the input pin against the stored pin
        {
            printf("Login Successful!");
            strcpy(S1.accountName, username);
            S1.accountPin = pin;
            S1.deposit = 0;
            S1.withdrawn = 0;

            fscanf(fp, "%f", &S1.accountBalance);

            printf("\n\nEnter the number corresponding to the actions listed below:\n"); //once logged in, the user can choose from various options
            printf("1. Check Balance\n");
            printf("2. Withdraw Cash\n");
            printf("3. Deposit Cash\n");
            printf("Your option: ");
            scanf("%d", &choice);
        }
        else
        {
            printf("Wrong pin entered!"); //This case is opted when username matches abut not the pin
            exit(0);
        }
    }

    switch(choice) //when logged in, the user needs to input the number of their prefered task
    {
    case 1:
        balanceCheck(); //choosing 1 lets them check their account balance
        break;
    case 2:
        withdrawCash(); //choosing 2 lets them withdraw money from their account
        break;
    case 3:
        depositCash(); // choosing 3 lets them deposit cash into their account
        break;
    default:
        exit(0); // choosing any other arbitrary number terminates the program
    }
    fclose(fp);
}

void createAccount() //user is sent here to create account if username.txt was not found
{
    int conf;

    fflush(stdin);
    printf("Enter a Username for your account: ");
    gets(S1.accountName);
    printf("Enter a 4-Digit pin for your account: ");
    scanf("%d", &S1.accountPin);

    S1.accountBalance = 0; //initiates the account balance to 0 BDT
    S1.deposit = 0;
    S1.withdrawn = 0;

    printf("\nAccount Created Successfully!\n\n");
    printf("Your current balance is BDT %.2f\n\n", S1.accountBalance);

    printf("Would you like to deposit some cash into your account?\n");
    printf("Enter 1 for YES and 2 for NO: ");
    scanf("%d", &conf);

    FILE *fp;

    char name[35];
    strcpy(name, S1.accountName);
    strcat(name, ".txt");

    fp = fopen(name, "w");
    fprintf(fp, "%d\n", S1.accountPin); //saves the pin entered by the user into the username.txt
    fprintf(fp, "%.2f", S1.accountBalance); //updates the account balance if money is deposited in the username.txt

    fclose(fp);

    if(conf == 1)
        depositCash();
    else
        exit(0);
}

void balanceCheck() //after logging, when user select check balance, this function executes
{
    int choice;

    printf("Your current account balance is: %.2f\n\n", S1.accountBalance);

    printf("Would you get a receipt of the transaction?\n");
    printf("Enter 1 for YES and 2 for NO: ");
    scanf("%d", &choice);

    if(choice == 1)
        printReceit(); //send to a function that prints reciept
    else
        exit(0);

    exit(0);
}

void withdrawCash() //This function deducts money from user balance when cash is withdrawn
{
    float cash;
    int choice;
    printf("Enter the amount of cash you would like to withdraw: BDT ");
    scanf("%f", &cash);

    S1.accountBalance -= cash;
    S1.withdrawn -= cash;

    char name[35];
    strcpy(name, S1.accountName);
    strcat(name, ".txt");

    FILE *fp;
    fp = fopen(name, "w");

    fprintf(fp, "%d\n", S1.accountPin);
    fprintf(fp, "%.2f", S1.accountBalance); //updates the account balance after the withdrawal
    printf("Cash withdrawn successfully!\n");
    printf("\nYour current account balance is BDT %.2f\n\n", S1.accountBalance);


    printf("Would you get a receipt of the transaction?\n"); 
    printf("Enter 1 for YES and 2 for NO: ");
    scanf("%d", &choice);

    if(choice == 1)
        printReceit();
    else
        exit(0);


    fclose(fp);

    exit(0);
}

void depositCash() //This function deposits cash when user opts for this option
{
    float cash;
    int choice;
    printf("\nEnter the amount of cash you would like to deposit: BDT ");
    scanf("%f", &cash);

    S1.accountBalance += cash;
    S1.deposit += cash; //Updates the account balance after the deposition of cash

    char name[35];
    strcpy(name, S1.accountName);
    strcat(name, ".txt");

    FILE *fp;
    fp = fopen(name, "w");

    fprintf(fp, "%d\n", S1.accountPin);
    fprintf(fp, "%.2f", S1.accountBalance); //Updates the account balance after the deposition of cash

    printf("Cash deposited successfully!\n");
    printf("\nYour current account balance is BDT %.2f\n\n", S1.accountBalance);

    printf("Would you get a receipt of the transaction?\n");
    printf("Enter 1 for YES and 2 for NO: ");
    scanf("%d", &choice);

    if(choice == 1)
        printReceit();
    else
        exit(0);

    fclose(fp);

    exit(0);
}

void printReceit() // this function prints the account balance into a .txt file
{
    printf("\nAccount Holder: %s\n", S1.accountName);
    printf("Cash Deposited: %.2f\n", S1.deposit);
    printf("Cash Withdrawn: %.2f\n", S1.withdrawn);
    printf("Current Balance: %.2f\n", S1.accountBalance);

    FILE *fp;
    fp = fopen("Receipt.txt", "w"); //this part opens up recept.exe and prints the account balance in this file

    fprintf(fp, "Account Holder: %s\n", S1.accountName);
    fprintf(fp, "Cash Deposited: %.2f\n", S1.deposit);
    fprintf(fp, "Cash Withdrawn: %.2f\n", S1.withdrawn);
    fprintf(fp, "Current Balance: %.2f\n\n", S1.accountBalance);

    fclose(fp);
}
