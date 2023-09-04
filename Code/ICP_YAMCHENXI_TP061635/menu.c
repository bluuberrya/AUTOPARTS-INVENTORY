#include "partsInventoryCreation.h"
#include "partsSupplier.h"
#include "partsInventoryTracking.h"
#include "partsInventoryUpdate.h"
#include "searchingFunctionalities.h"

void menu(){
	printf("1. Parts Inventory Creation in Warehouses\n2. Parts Supplier Creation\n3. Parts Inventory Update\n");
	printf("4. Parts Inventory Tracking\n5. Searching Functionalities\n6. Exit\n");
    int option;

    //User select menu option
	printf("\nMenu Option: ");
    scanf("%d", &option);
    getchar();
    printf("\n");


    //Switch case to call function
    switch (option){
        case 1:
            system("cls");
            partsInventoryCreation();
            break;
        case 2:
            system("cls");
            partsSupplierCreation();
            break;
        case 3:
            system("cls");
            partsInventoryUpdate();
            break;
        case 4:
            system("cls");
            partsInventoryTracking();
            break;
        case 5:
            system("cls");
            searchingFunctionalities();
            system("pause");
            break;
        case 6:
            break;
        default:
            printf("\nInvalid menu selection, select only from (1) to (6)\n\n");
            system("pause");
            break;
    }
}