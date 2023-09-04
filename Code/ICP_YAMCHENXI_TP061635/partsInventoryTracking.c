#include "partsInventoryCreation.h"
#include "main.h"
#include "fileHandling.h"

//function to sort parts ID in alphabetical order
int sortPartsAsc(char *warehouseFileName, partsInventory *S1List, int S1ListSize)
{
    //declare pointers, structure and variable
    FILE* warehouseFile;
	partsInventory S1;
	int totalRecord;
	int arraySize = 0;
    int S1ListCount = 0;
    int j;

    //open warehousefile
    warehouseFile = openWarehouseFile(warehouseFileName);
    //get total record count in warehouse file
	totalRecord = getWarehouseRecordCount(warehouseFile);

    //loop line by line to read warehouse record
	for (int i = 0; i < totalRecord; i++) {
        readWarehouseRecord(warehouseFile, i, &S1);

        //add record line to list
        if (S1ListCount == 0)
        {
            memcpy(S1List + S1ListCount, &S1, 64);
        }
        else
        {
            for (j = S1ListCount; j > 0; j--) {
                //data smaller than current array item. move current array item down
                if (0 < strcmp((S1List+ j - 1)->partID, S1.partID)) {
                    memcpy(S1List + j, S1List + j - 1, sizeof(partsInventory));
                }
                else {
                    //copy data to current array item
                    memcpy(S1List + j, &S1, sizeof(partsInventory));
                    break;
                }
            }
            //if j loop until 0 didn't find any smaller item, put data to the first item
            if (j == 0)
                memcpy(S1List, &S1, sizeof(partsInventory));
        }
        S1ListCount += 1;
	}
    //close warehouse file
    closeWarehouseFile(warehouseFile);

    if (S1ListCount > 0)
        return totalRecord;
	return 0;
}

//function to get quantity less than 10
int quantityLessThan10(char* warehouseFileName, partsInventory* S1List, int S1ListSize)
{
    //declare pointers, structure and variable
    FILE* warehouseFile;
    partsInventory S1;
    int totalRecord;
    int arraySize = 0;
    int S1ListCount = 0;
    int j;

    //memory reset S1list
    memset(S1List, 0, S1ListSize * sizeof(partsInventory));

    //open warehouse file
    warehouseFile = openWarehouseFile(warehouseFileName);

    //get total record of the warehouse file
    totalRecord = getWarehouseRecordCount(warehouseFile);

    //loop to read the warehouse file line by line
    for (int i = 0; i < totalRecord; i++) {
        readWarehouseRecord(warehouseFile, i, &S1);
        
        //convert str quantity to int and check for quantity less than 10
        if (atoi(S1.quantity) < 10) {
            //add record to list
            memcpy(S1List + S1ListCount, &S1, sizeof(partsInventory));
            S1ListCount++;
        }
    }

    //close warehouse file
    closeWarehouseFile(warehouseFile);

    //return record count
    if (S1ListCount > 0)
        return S1ListCount;
    return 0;
}

//main function
void partsInventoryTracking()
{
    //declare pointers, structure and variable
	int recordCount;
    char trackingOption[5];
    char warehouseCode[5];
    partsInventory S1List[100];

    //declare list
	char warehouseFile[3][5] = {"WBZ", "WSL", "WAR"};

    printf("Parts Inventory Tracking\n- - - - -\n");
reinputOption:
    printf("\n1. Sort all parts in warehouses\n2. Show stock less than 10 quantity\n\nSelect function, input (1) or (2): ");
    scanf("%s", trackingOption);
    getchar();

    //option 1, sort all parts
    if (0 == strcmp(trackingOption, "1"))
    {
        printf("\n1. Sort all parts in warehouses\n");

        system("cls");
        printf("Sorted Warehouse Data");
        printf("\n- - - - -\n");
        //loop to print record from warehouse by warehouse
        for (int i = 0; i < 3; i++) {
            memset(&S1List, 0, 100 * sizeof(partsInventory));

            //call function to sort all parts from all three warehouses
            recordCount = sortPartsAsc(warehouseFile[i], &S1List[0], 100);

            printf("\n\nWarehouse Code: %s\n", warehouseFile[i]);
            printf("\nRecord count = %d\n", recordCount);
            printf("Part ID\t| Section Code\t| Part Name\t\t| Quantity\t\n");
            printf("------------------------------------------------------------------\n");
            //loop to print sorted inventory records
            for (int j = 0; j < recordCount; j++) {
                printf("%s\t| ", S1List[j].partID);
                printf("%s\t\t| ", S1List[j].sectionCode);
                printf("%s\t\t| ", S1List[j].partName);
                printf("%s\t\n", S1List[j].quantity);
            }
        }
    }
    //option 2, show stock less than 10 quantity
    else if (0 == strcmp(trackingOption, "2")) {
        printf("\n\n2. Show stock less than 10 quantity\n- - - - -\n");
    reinputwarehouse:

        //get warehouse code that the user want to show
        printf("Warehouse Code\n1. WBZ\n2. WSL\n3. WAR\nSelect Warehouse: ");
        scanf("%s", warehouseCode);
        getchar();

        //set user choice as warehousecode
        if (0 == strcmp(warehouseCode, "1") || 0 == strcmp(warehouseCode, "WBZ")) {
            strcpy(warehouseCode, "WBZ");
        }
        else if (0 == strcmp(warehouseCode, "2") || 0 == strcmp(warehouseCode, "WSL")) {
            strcpy(warehouseCode, "WSL");
        }
        else if (0 == strcmp(warehouseCode, "3") || 0 == strcmp(warehouseCode, "WAR")) {
            strcpy(warehouseCode, "WAR");
        }
        else {
            printf("\n\nInvalid warehouse code. Please try again\n");
            goto reinputwarehouse;
        }
        
        //memory reset S1list
        memset(&S1List, 0, 100 * sizeof(partsInventory));
        
        //get record count while call fucntion
        recordCount = quantityLessThan10(warehouseCode, &S1List[0], 100);
        system("cls");
        printf("Stock Quantity that has less then 10 units");
        printf("\n- - - - -\n");

        //print data
        printf("\nWarehouse Code: %s\n", warehouseCode);
        printf("Record Count = %d\n\n", recordCount);
        printf("Part ID\t| Section Code\t| Part Name\t\t| Quantity\t\n");
        printf("------------------------------------------------------------------\n");
        //loop to print the filtered record
        for (int j = 0; j < recordCount; j++) {
            printf("%s\t| ", S1List[j].partID);
            printf("%s\t\t| ", S1List[j].sectionCode);
            printf("%s\t\t| ", S1List[j].partName);
            printf("%s\t\n", S1List[j].quantity);
        }
    }
    else {
        printf("\nInput invalid, try again with (1) or (2)\n");
        goto reinputOption;
    }
}