//Yam Chen Xi TP061635
#include "partsInventoryCreation.h"
#include "main.h"
#include "fileHandling.h"

//search for the parts that the user wants to update
int partsInventoryFind(FILE* warehouseFile, partsInventory *S1, char *partID)
{
	int totalRecord = getWarehouseRecordCount(warehouseFile);
	
	memset(S1, 0, sizeof(partsInventory));
	for (int i = 0; i < totalRecord; i++) {
		readWarehouseRecord(warehouseFile, i, S1);
		if (strcmp(partID, S1->partID) == 0) {
			return i;
		}
	}
	return -1;
}

//convert str to int to add quantity
void strAdd(char* strQuantity, int addValue)
{
	int intQuantity;
	intQuantity = atoi(strQuantity);
	//add quantity
	intQuantity = intQuantity + addValue;
	//convert int quantity to string
	sprintf(strQuantity, "%d", intQuantity);
}

//convert str to int to substract quantity
int strSubstract(char* strQuantity, int substractValue)
{
	int intQuantity;
	intQuantity = atoi(strQuantity);
	//if substract value is more than initial quantity, return -1
	if (intQuantity < substractValue) {
		return -1;
	}
	//substract quantity
	intQuantity = intQuantity - substractValue;
	//convert int quantity to string
	sprintf(strQuantity, "%d", intQuantity);
	return 0;
}

//main function
void partsInventoryUpdate() {
	//declare pointers, structure and variable
	FILE* warehouseFile;
	partsInventory S1;
	int quantityUpdate = 0;
	char selectID[10];
	char warehouseCode[5];
	char updateOption[10];
	int searchResult;

	printf("1. Parts Inventory Update\n- - - - -\n");
reinputwarehouse:
	//memory reset partsInventory structure
	memset(&S1, 0, sizeof(partsInventory));
	printf("Warehouse Code\n1. WBZ\n2. WSL\n3. WAR\nSelect Warehouse: ");
	scanf("%s", warehouseCode);
	getchar();

	//set warehouseCode as the user input
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
		printf("\nInvalid warehouse code. Please try again\n");
		goto reinputwarehouse;
	}

	//open warehouse file according to the input warehouseCode
	warehouseFile = openWarehouseFile(warehouseCode);

	//user input part ID to update
	printf("\nInput part ID to update: ");
	scanf("%s", &selectID);

	printf("\n\nSearch Result\n- - - - - \n");

	//call function to searchand print the part given part ID's details
	searchResult = partsInventoryFind(warehouseFile, &S1, selectID);
	printInventoryData(&S1);

	printf("\n1. Add Quantity\n2. Substract Quantity\nSelect Update Option: ");
	scanf("%s", updateOption);
	getchar();

reinputquantity:
	printf("\nInput Quantity: ");
	scanf("%d", &quantityUpdate);
	getchar();

	//add quantity
	if (0 == strcmp(updateOption, "1") || 0 == strcmp(updateOption, "Add")) {
		strAdd(S1.quantity, quantityUpdate);
	}
	//substract quantity
	else if (0 == strcmp(updateOption, "2") || 0 == strcmp(updateOption, "Substract")) {
		if (-1 == strSubstract(S1.quantity, quantityUpdate)) {
			printf("\nInsufficient quantity to be substracted. Try input the value again");
			goto reinputquantity;
		}
	}

	//update record in file
	updateWarehouseRecord(warehouseFile, searchResult, &S1);
	printf("\nUpdated info\n- - - - -\n");

	//print updated record
	printInventoryData(&S1);
	//close file
	closeWarehouseFile(warehouseFile);
 
}