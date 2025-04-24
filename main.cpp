#include <iostream>
#include <windows.h>
using namespace std;
void printWelcome(){
    cout << "===================\n|     WELCOME     |\n===================" << endl << endl;
}
int id_generator=101;
struct Users {
    int id=id_generator;
    string name;
    int balance;
    int loan=0;
};
Users users[100];
void CreateAccount() {
    Users user;
    user.id=id_generator;
    string name,surname;
    cout<<"Enter First name: ";
    cin>>name;
    cout<<"Enter Surname: ";
    cin>>surname;
    user.name=name+" "+surname;
    cout<<"Enter Balance($): ";
    cin>>user.balance;
    users[id_generator-101]=user;
    id_generator++;

};
void deposit() {
    int id, amount;
    cout << "Enter ID: "; cin >> id;
    cout << "Enter deposit amount($): "; cin >> amount;
    for (int i = 0; i < id_generator - 101; ++i) {
        if (users[i].id == id) {
            if (amount > 0) {
                users[i].balance += amount;
                cout << "$" << amount << " deposited for ID " << id << endl;
            } else {
                cout << "Invalid amount." << endl;
            }
            return;
        }
    }
    cout << "User not found." << endl;
}

void withdraw() {
    int id, amount;
    cout << "Enter ID: "; cin >> id;
    cout << "Enter withdrawal amount($): "; cin >> amount;
    for (int i = 0; i < id_generator - 101; ++i) {
        if (users[i].id == id) {
            if (amount > 0) {
                if (users[i].balance >= amount) {
                    users[i].balance -= amount;
                    cout << "$" << amount << " withdrawn for ID " << id << endl;
                } else {
                    cout << "Insufficient balance ($" << users[i].balance << ")." << endl;
                }
            } else {
                cout << "Invalid amount." << endl;
            }
            return;
        }
    }
    cout << "User not found." << endl;
}
void displayall() {
    if (id_generator == 101) {
        cout << "\n There are no users in the system yet.\n";
    }
    else {
        cout << "\n All User Accounts \n";
        cout << "-----------------------------\n";
        for (int i = 0; i < id_generator - 101; i++) {
            cout << "ID: " << users[i].id << "\n";
            cout << " Name: " << users[i].name << "\n";
            cout << " Balance: $" << users[i].balance << "\n";
            cout << " Loan: $" << users[i].loan << "\n";
            cout << "-----------------------------\n";
        }
    }
}



void displayone() {
    int id;
    cout << " Enter ID to search: ";
    cin>>id;
    int check=0;
    for(int i=0;i<id_generator-101;i++) {
        if (users[i].id == id) {
            cout << "\n User Information \n";
            cout << "-----------------------------\n";
            cout << " ID: " << users[i].id << "\n";
            cout << " Name: " << users[i].name << "\n";
            cout << " Balance: $" << users[i].balance << "\n";
            cout << " Loan: $" << users[i].loan << "\n";
            cout << "-----------------------------\n";
            check=1;

        }
        if (check==0) {
            cout<<"There is no user with this id"<<endl;
        }
    }
}void GetLoan() {
    int id;
    cout << "\n=== Loan Application ===\n";
    cout << "Enter your ID: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < id_generator - 101; i++) {
        if (users[i].id == id) {
            found = true;

            cout << "\n----------------------------------\n";
            cout << "      Loan Information \n";
            cout << "----------------------------------\n";
            cout << " > Interest Rate: 10%\n";
            cout << " > Payment period: 6 months\n";
            cout << " > Penalty for late payment: 5%\n";
            cout << "----------------------------------\n";
            cout << "Enter the amount you want to loan: $";

            float amount;
            cin >> amount;

            float totalWithInterest = amount + (amount * 0.10);

            cout << "\n Loan Approved!\n";
            cout << "You must repay: $" << totalWithInterest << " within 6 months.\n";


            users[i].loan += totalWithInterest;
            break;
        }
    }

    if (!found) {
        cout << "\n No user found with this ID.\n";
    }
}

int loanpay=0;
void PayLoan() {
    int id;
    cout << "\n=== Loan Payment Section ===\n";
    cout << "Enter your ID: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < id_generator - 101; i++) {
        if (users[i].id == id) {
            found = true;

            if (users[i].loan <= 0) {
                cout << "\nYou have no outstanding loan to pay. \n";

            }
            else{
                int timeleft = 6-loanpay;
                cout << "\n----------------------------------\n";
                cout << "    Current Loan: $" << users[i].loan << "\n";
                cout << "    Time left to pay(months): " << timeleft << "\n";
                cout << "----------------------------------\n";
                cout << "Enter amount to pay: $";

                float amount;
                cin >> amount;

                users[i].loan -= amount;

                if (users[i].loan <= 0) {
                    users[i].loan = 0;
                    cout << "\n Congratulations! You have fully repaid your loan.\n";
                    loanpay = 0;
                } else {
                    cout << "\nPartial payment received. Remaining loan: $" << users[i].loan << "\n";
                    loanpay++;

                    if (loanpay >= 6) {
                        float newLoan = users[i].loan * 1.05;
                        users[i].loan = newLoan;
                        cout << "\n Payment period exceeded 6 months!\n";
                        cout << "Your loan has been updated with a 5% penalty.\n";
                        cout << "New remaining loan: $" << newLoan << "\n";
                    }
                }

                break;
            }
        }
    }
    if (!found) {
        cout << "\n No user found with this ID.\n";
    }
}




int main() {

    printWelcome();

    int choice;
    do {
        cout << "=============================\n";
        cout << "        MAIN  MENU          \n";
        cout << "=============================\n";
        cout << " 1.  Create Account        \n";
        cout << " 2.  Deposit               \n";
        cout << " 3.  Withdraw              \n";
        cout << " 4.  Display All Users     \n";
        cout << " 5.  Display One           \n";
        cout << " 6.  Take a Loan           \n";
        cout << " 7.  Pay Loan              \n";
        cout << " 8.  Exit                  \n";
        cout << "=============================\n";
        cout << "Please select an option: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "\n Creating a new account...\n";
            CreateAccount();
            cout << " Account created successfully! \n";
            break;

            case 2:
                cout << "\n Deposit Section \n";
            deposit();
            cout << " Deposit completed! \n";
            break;

            case 3:
                cout << "\n Withdrawal Section \n";
            withdraw();

            break;

            case 4:
                cout << "\n Showing all users...\n";
            displayall();
            cout << " All accounts displayed successfully! \n";
            break;

            case 5:
                cout << "\n Searching for a user...\n";
            displayone();
            cout << "User details displayed! \n";
            break;

            case 6:
                cout << "\n Loan Request Section \n";
            GetLoan();
            cout << " Loan processed (check details above)!\n";
            break;

            case 7:
                cout << "\n Loan Payment Section \n";
            PayLoan();
            cout << " Loan payment updated! \n";
            break;

            case 8:
                cout << "\n Thank you for using our banking system! \n";
            cout << " Goodbye and have a lovely day! \n";
            break;

            default:
                cout << " Invalid option! Please select from the menu. \n";
        }


    } while (choice != 8);

    return 0;



    }


