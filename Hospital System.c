#include <stdio.h>
#include <stdlib.h>
/**
*@brief Hospital Patient Management Simulation using structures, unions, arrays and pointers
*@return 0
*@author Shahid
*@date 25-12-2025
*/
// Union stores either room charge (int) or consultation fee (float)
union Fee {
    int roomCharge;
    float consultationFee;
};
// Structure to store a single patient's details
struct Patient {
    int id;
    char name[20];
    int patientType;   // 1 = Inpatient, 2 = Outpatient
    union Fee fee;     // Fee depends on patientType
};
int main() {
    struct Patient patients[5];   // Array to hold up to 5 patients
    int count = 0, choice;
    while (1) {   // Menu loop runs until user chooses Exit
        printf("\n---- Hospital Patient Management ----\n");
        printf("1. Add Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Update Patient Fee\n");
        printf("4. Calculate Total Revenue\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        if (choice == 5) {   // Exit condition
            printf("Exiting...\n");
            break;
        }
        switch (choice) {
        case 1: {   // Add new patient
            if (count >= 5) {   // Check array capacity
                printf("Patient storage full.\n");
                break;
            }
            struct Patient *p = &patients[count];   // Pointer to next free slot
            printf("Enter Patient ID: ");
            scanf("%d", &p->id);
            printf("Enter Patient Name: ");
            scanf("%19s", p->name);
            printf("Enter Patient Type (1=Inpatient, 2=Outpatient): ");
            scanf("%d", &p->patientType);
            if (p->patientType == 1) {   // Inpatient: use roomCharge
                printf("Enter Room Charge: ");
                scanf("%d", &p->fee.roomCharge);
            } else if (p->patientType == 2) {   // Outpatient: use consultationFee
                printf("Enter Consultation Fee: ");
                scanf("%f", &p->fee.consultationFee);
            } else {
                printf("Invalid patient type. Patient not added.\n");
                break;
            }
            count++;   // Increase stored patient count
            printf("Patient added successfully!\n");
            break;
        }
        case 2: {   // Display all patients
            if (count == 0) {
                printf("No patients to display.\n");
                break;
            }
            printf("\n--- Patient Details ---\n");
            struct Patient *p = patients;   // Pointer used to traverse array
            for (int i = 0; i < count; i++, p++) {
                printf("ID: %d, Name: %s, Type: %s, ",
                       p->id,
                       p->name,
                       (p->patientType == 1) ? "Inpatient" : "Outpatient");
                if (p->patientType == 1)
                    printf("Room Charge: %d\n", p->fee.roomCharge);
                else
                    printf("Consultation Fee: %.2f\n", p->fee.consultationFee);
            }
            break;
        }
        case 3: {   // Update fee for a specific patient
            if (count == 0) {
                printf("No patients to update.\n");
                break;
            }
            int searchId, found = 0;
            printf("Enter Patient ID to update fee: ");
            scanf("%d", &searchId);
            struct Patient *p = patients;
            for (int i = 0; i < count; i++, p++) {   // Linear search by ID
                if (p->id == searchId) {
                    found = 1;
                    if (p->patientType == 1) {
                        printf("Enter new Room Charge: ");
                        scanf("%d", &p->fee.roomCharge);
                    } else {
                        printf("Enter new Consultation Fee: ");
                        scanf("%f", &p->fee.consultationFee);
                    }
                    printf("Fee updated successfully!\n");
                    break;
                }
            }
            if (!found)
                printf("Patient with ID %d not found.\n", searchId);
            break;
        }
        case 4: {   // Calculate sum of all fees
            if (count == 0) {
                printf("No patients. Total revenue: 0.00\n");
                break;
            }
            float total = 0.0f;
            struct Patient *p = patients;
            for (int i = 0; i < count; i++, p++) {
                if (p->patientType == 1)
                    total += (float)p->fee.roomCharge;   // Cast int to float
                else
                    total += p->fee.consultationFee;
            }
            printf("Total Revenue: %.2f\n", total);
            break;
        }
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
