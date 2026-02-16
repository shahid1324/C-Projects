#include <stdio.h>
#include <stdlib.h>
 
/**
*
*@brief Temperature Sensor using union vs full-structure-style display
*@author Shahid
*@date 15-12-2025
*/
 
// Union: only ONE of these values is valid at a time
union Temperature{
    float celsius;
    float fahrenheit;
	char status;
};
 
// Structure: sensor info + union + type flag
struct Sensor{
	int id;
	char location[20];
    union Temperature temp;
	int temptype;  	// 1 = C, 2 = F, 3 = status
};
 
int main(){
    struct Sensor s[5];       	// Array to store up to 5 sensors
	int subchoice, i;
	int choice = 0, structplace = 0;
 
	// Menu loop
    while(choice != 4){
        printf("\n----Temperature Sensor Menu----\n");
        printf("1. Add Sensor Data\n");
        printf("2. Display Sensor Data (Union)\n");
        printf("3. Display Sensor Data (Full Structure)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
 
        switch(choice){
        case 1:
            // Add new sensor data
            if(structplace >= 5){
                printf("Storage full\n");
                break;
            }
            printf("Enter Sensor ID: ");
            scanf("%d",&s[structplace].id);
            printf("Enter sensor location: ");
            scanf("%19s",s[structplace].location);
            printf("Enter Temperature type(1=celsius,2=Fahrenheit,3=status): ");
            scanf("%d",&subchoice);
            s[structplace].temptype = subchoice;
 
            // Store only one union member, depending on type
            if(subchoice == 1){
                printf("Enter celsius value: ");
                scanf("%f",&s[structplace].temp.celsius);
            }
            else if(subchoice == 2){
                printf("Enter Fahrenheit value: ");
                scanf("%f",&s[structplace].temp.fahrenheit);
            }
            else if(subchoice == 3){
                printf("Enter Status: ");
                scanf(" %c",&s[structplace].temp.status);
            }
            printf("Saved successfully!\n");
            structplace += 1;  	// Increase sensor count
            break;
 
        case 2:
            // Direct union-based display: shows last stored member only
            printf("Sensor Data using union: \n");
            for(i = 0; i < structplace; i++){
                printf("Sensor ID: %d, Location: %s, ",s[i].id,s[i].location);
                if(s[i].temptype == 1)
                	printf("Celsius: %f\n",s[i].temp.celsius);
                else if(s[i].temptype == 2)
                	printf("Fahrenheit: %f\n",s[i].temp.fahrenheit);
                else
                	printf("Status: %c\n",s[i].temp.status);
            }
            break;
 
        case 3:
            // “Full structure” style display: derives status from value
            printf("Sensor Data using Full structure:\n");
            for(i = 0; i < structplace; i++){
                printf("Sensor ID: %d, Location: %s, ",s[i].id,s[i].location);
 
                if(s[i].temptype == 1){
                	// Only Celsius was actually stored in union
                	printf("Celsius: %.2f, Fahrenheit =0, ",s[i].temp.celsius);
                	if(s[i].temp.celsius < 20) printf("Status: L\n");
                	else if(s[i].temp.celsius <= 40) printf("Status: N\n");
                	else printf("Status: H\n");
                }
                else if(s[i].temptype == 2){
                	// Only Fahrenheit was actually stored in union
                	printf("Calsius =00, Fahrenheit: %.2f, ",s[i].temp.fahrenheit);
                	if(s[i].temp.fahrenheit < 68) printf("Status: L\n");
                	else if(s[i].temp.fahrenheit < 104) printf("Status: N\n");
                	else printf("Status: H\n");
                }
            }
            break;
 
        case 4:
            // Exit option
            printf("Exiting program...");
            break;
        }
	}
    return 0;
}
