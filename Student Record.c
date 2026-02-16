/**
 * @brief Menu-driven program to manage student records using structures.
 *
 * This program defines a Student structure to store roll number, name,
 * marks in five subjects, total marks, percentage, and grade. It implements
 * multiple functions to input student details, calculate results, display
 * all student records in a tabular format, search a student by roll number,
 * and find the highest scorer (topper) of the class.
 *
 * A menu-driven approach is used in the main function to allow the user
 * to repeatedly perform operations until the exit option is selected.
 *
 * Grade calculation criteria:
 *  - Percentage >= 75 : Grade A
 *  - Percentage >= 60 : Grade B
 *  - Percentage >= 50 : Grade C
 *  - Otherwise        : Grade F
 *
 * The program demonstrates practical usage of structures, arrays of
 * structures, pointer-based function arguments, and modular programming
 * in C.
 *
 * @author Shahid
 */


#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[50];
    int marks[5];
    int total;
    float percentage;
    char grade;
};

void calculateResult(struct Student *s) {
    s->total = 0;
    for (int i = 0; i < 5; i++) {
        s->total += s->marks[i];
    }

    s->percentage = s->total / 5.0;

    if (s->percentage >= 75)
        s->grade = 'A';
    else if (s->percentage >= 60)
        s->grade = 'B';
    else if (s->percentage >= 50)
        s->grade = 'C';
    else
        s->grade = 'F';
}

void inputStudents(struct Student s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d\n", i + 1);

        printf("Roll No: ");
        scanf("%d", &s[i].roll_no);

        printf("Name: ");
        scanf(" %[^\n]", s[i].name);

        printf("Enter marks of 5 subjects:\n");
        for (int j = 0; j < 5; j++) {
            scanf("%d", &s[i].marks[j]);
        }

        calculateResult(&s[i]);
    }
}

void displayStudents(struct Student s[], int n) {
    printf("\nRoll\tName\t\tTotal\tPercent\tGrade\n");
    printf("---------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%-10s\t%d\t%.2f\t%c\n",
               s[i].roll_no,
               s[i].name,
               s[i].total,
               s[i].percentage,
               s[i].grade);
    }
}

void searchByRoll(struct Student s[], int n, int roll) {
    for (int i = 0; i < n; i++) {
        if (s[i].roll_no == roll) {
            printf("\nStudent Found\n");
            printf("Roll No: %d\n", s[i].roll_no);
            printf("Name: %s\n", s[i].name);
            printf("Total: %d\n", s[i].total);
            printf("Percentage: %.2f\n", s[i].percentage);
            printf("Grade: %c\n", s[i].grade);
            return;
        }
    }
    printf("Student not found!\n");
}

void highestScorer(struct Student s[], int n) {
    if (n == 0) {
        printf("No student records available.\n");
        return;
    }

    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (s[i].total > s[maxIndex].total) {
            maxIndex = i;
        }
    }

    printf("\nTopper Details\n");
    printf("Roll No: %d\n", s[maxIndex].roll_no);
    printf("Name: %s\n", s[maxIndex].name);
    printf("Total: %d\n", s[maxIndex].total);
    printf("Percentage: %.2f\n", s[maxIndex].percentage);
    printf("Grade: %c\n", s[maxIndex].grade);
}

int main() {

    struct Student students[50];
    int count = 0;
    int choice;

    while (1) {
        printf("\n--- Student Record Management ---\n");
        printf("1. Input Students\n");
        printf("2. Display All Students\n");
        printf("3. Search by Roll No\n");
        printf("4. Show Topper\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number of students: ");
                scanf("%d", &count);
                inputStudents(students, count);
                break;

            case 2:
                displayStudents(students, count);
                break;

            case 3: {
                int roll;
                printf("Enter roll number to search: ");
                scanf("%d", &roll);
                searchByRoll(students, count, roll);
                break;
            }

            case 4:
                highestScorer(students, count);
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
}

