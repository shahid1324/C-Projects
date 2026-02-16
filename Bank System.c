/**
 * @brief Simulates a simple bank management system using structures.
 *
 * This program models a basic banking system using user-defined structures.
 * It defines an Address structure to store city, state, and pincode details,
 * and a BankAccount structure to store account number, account holder name,
 * balance, and address information.
 *
 * The program implements functions to create new bank accounts, deposit
 * money, withdraw money (with balance validation), transfer funds between
 * two accounts, display account details, and search for an account using
 * the account number.
 *
 * An array of structures is maintained to store details of up to 50 bank
 * customers. A menu-driven approach in the main function allows the user
 * to perform banking operations repeatedly until the exit option is chosen.
 *
 * The program demonstrates practical concepts such as nested structures,
 * passing structures by value and by reference, array-based record
 * management, and modular programming in C.
 *
 * @author Shahid
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address {
    char city[30];
    char state[30];
    int pincode;
};

struct BankAccount {
    int account_no;
    char name[50];
    float balance;
    struct Address addr;
};

void createAccount(struct BankAccount *b) {
    printf("Enter Account No: ");
    scanf("%d", &b->account_no);

    printf("Enter Name: ");
    scanf(" %[^\n]", b->name);

    printf("Enter City: ");
    scanf("%s", b->addr.city);

    printf("Enter State: ");
    scanf("%s", b->addr.state);

    printf("Enter Pincode: ");
    scanf("%d", &b->addr.pincode);

    b->balance = 0.0f;

    printf("Account created successfully!\n");
}

void deposit(struct BankAccount *b, float amt) {
    b->balance += amt;
    printf("Deposited %.2f, New Balance: %.2f\n", amt, b->balance);
}

void withdraw(struct BankAccount *b, float amt) {
    if (b->balance >= amt) {
        b->balance -= amt;
        printf("Withdrawn %.2f, New Balance: %.2f\n", amt, b->balance);
    } else {
        printf("Insufficient balance!\n");
    }
}

void transfer(struct BankAccount *from, struct BankAccount *to, float amt) {
    if (from->balance >= amt) {
        from->balance -= amt;
        to->balance += amt;
        printf("Transfer successful!\n");
    } else {
        printf("Insufficient balance for transfer!\n");
    }
}

void displayAccount(struct BankAccount b) {
    printf("Account No: %d\n", b.account_no);
    printf("Name: %s\n", b.name);
    printf("Balance: %.2f\n", b.balance);
    printf("Address: %s, %s - %d\n",
           b.addr.city, b.addr.state, b.addr.pincode);
}

int searchAccount(struct BankAccount b[], int n, int acc_no) {
    for (int i = 0; i < n; i++) {
        if (b[i].account_no == acc_no)
            return i;
    }
    return -1;
}

int main() {
    struct BankAccount accounts[50];
    int count = 0;
    int choice;

    while (1) {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. Display All Accounts\n");
        printf("6. Search Account\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 7)
            exit(0);

        int acc_no, idx, idx2;
        float amt;

        switch (choice) {
            case 1:
                if (count < 50)
                    createAccount(&accounts[count++]);
                else
                    printf("Account limit reached!\n");
                break;

            case 2:
                printf("Enter Account No: ");
                scanf("%d", &acc_no);
                idx = searchAccount(accounts, count, acc_no);
                if (idx != -1) {
                    printf("Enter amount to deposit: ");
                    scanf("%f", &amt);
                    deposit(&accounts[idx], amt);
                } else {
                    printf("Account not found!\n");
                }
                break;

            case 3:
                printf("Enter Account No: ");
                scanf("%d", &acc_no);
                idx = searchAccount(accounts, count, acc_no);
                if (idx != -1) {
                    printf("Enter amount to withdraw: ");
                    scanf("%f", &amt);
                    withdraw(&accounts[idx], amt);
                } else {
                    printf("Account not found!\n");
                }
                break;

            case 4:
                printf("Enter Sender Account No: ");
                scanf("%d", &acc_no);
                idx = searchAccount(accounts, count, acc_no);

                printf("Enter Receiver Account No: ");
                scanf("%d", &acc_no);
                idx2 = searchAccount(accounts, count, acc_no);

                if (idx != -1 && idx2 != -1) {
                    printf("Enter amount to transfer: ");
                    scanf("%f", &amt);
                    transfer(&accounts[idx], &accounts[idx2], amt);
                } else {
                    printf("One or both accounts not found!\n");
                }
                break;

            case 5:
                for (int i = 0; i < count; i++) {
                    displayAccount(accounts[i]);
                    printf("--------------------\n");
                }
                break;

            case 6:
                printf("Enter Account No: ");
                scanf("%d", &acc_no);
                idx = searchAccount(accounts, count, acc_no);
                if (idx != -1)
                    displayAccount(accounts[idx]);
                else
                    printf("Account not found!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    }
}
