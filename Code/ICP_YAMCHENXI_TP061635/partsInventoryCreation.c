//Yam Chen Xi TP061635
#include "partsInventoryCreation.h"
#include "main.h"
#include "fileHandling.h"

//to print parts inventory structure
void printInventoryData(partsInventory* inv)
{
	printf("Part ID\t\t: %s\n", inv->partID);
	printf("Section Code\t: %s\n", inv->sectionCode);
	printf("Part Name\t: %s\n", inv->partName);
	printf("Quantity\t: %s\n", inv->quantity);
}

//check whether input char is integer
int isInteger(char* checkData)
{
	if (0 == checkData)
		return 0;
	if (checkData[0] == '0' && strlen(checkData) == 1)
		return 1;
	if (0 == atoi(checkData))
		return 0;

	return 1;
}

//main function
void partsInventoryCreation()
{
	//declare pointers, structure and variable
	FILE* warehouseFile;
	partsInventory S1;
	int quantity = 0;
	int latestRecord = 0;
	char warehouseCode[5];
	int convertquantity;

	printf("1. Parts Inventory Creation in Warehouses\n- - - - -\n");

reinputwarehouse:
	//reset structure memory
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
		printf("\nInvalid warehouse code. Please try again\n\n");
		goto reinputwarehouse;
	}

	//open warehouse file according to the input warehouseCode
	warehouseFile = openWarehouseFile(warehouseCode);

	//get record count to create part ID
	latestRecord = getWarehouseRecordCount(warehouseFile);
	latestRecord = latestRecord + 1;
	sprintf(S1.partID, "%s%03d", warehouseCode, latestRecord);
	printf("\nPart ID\t: %s%03d\n\n", warehouseCode, latestRecord);

	printf("\Enter Section Code: ");
	gets(S1.sectionCode);

	printf("\nEnter Part Name\t: ");
	gets(S1.partName);

reinputquantity:
	printf("\nEnter Quantity\t: ");
	scanf("%s", &S1.quantity);
	getchar();

	//check input quantity whether it is integer
	if (!isInteger(&S1.quantity)) {
		printf("\nInput invalid, please try again with number\n");
		strcpy(S1.quantity, "");
		goto reinputquantity;
	}

	S1.linefeed = '\n';

	//add current record to file
	latestRecord = addWarehouseRecord(warehouseFile, &S1);
	printf("\n\nRecord successfully created!\n- - - - -\n");

	//get current record count number
	latestRecord = getWarehouseRecordCount(warehouseFile);
	printf("Current record count: %d\n", latestRecord);

	//read and print out the latest recorded parts inventory record
	readWarehouseRecord(warehouseFile, latestRecord, &S1);
	printInventoryData(&S1);

	//close file
	closeWarehouseFile(warehouseFile);

}