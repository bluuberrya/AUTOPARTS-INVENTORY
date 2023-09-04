#include "partsInventoryCreation.h"
#include "main.h"
#include "fileHandling.h"
#include "partsSupplier.h"

//function to searh parts inventory
int partsInventorySearch(FILE* warehouseFile, partsInventory* S1, char* partID)
{
	int totalRecord = getWarehouseRecordCount(warehouseFile);

	memset(S1, 0, sizeof(partsInventory));

	//loop to read all record
	for (int i = 0; i < totalRecord; i++) {
		readWarehouseRecord(warehouseFile, i, S1);
		//if record with input part ID found, return
		if (strcmp(partID, S1->partID) == 0) {
			return i;
		}
	}
	return -1;
}

//function to searh parts supplier
int partsSupplierSearch(FILE* supplierFile, partsSupplier* S2, char* partID)
{
	int totalRecord = getSupplierRecordCount(supplierFile);

	memset(S2, 0, sizeof(partsSupplier));

	//loop to read all record
	for (int i = 0; i < totalRecord; i++) {
		readSupplierRecord(supplierFile, i, S2);
		//if record with input part ID found, return
		if (strcmp(partID, S2->partID) == 0) {
			return i;
		}
	}
	return -1;
}

//main function
void searchingFunctionalities() {
	//declare pointers, structure and variable
	FILE* warehouseFile;
	FILE* supplierFile;
	partsInventory S1;
	partsSupplier S2;
	char selectID[10];
	char warehouseCode[5];
	char searchOption[15];
	int searchResult;
	char toMenu[3];

	printf("5. Searching Functionalities\n- - - - -\n");

selectSearchFunction:
	printf("1. Part Record\n2. Supplier Details\nSelect Search Function: ");
	scanf("%s", &searchOption);

	//option 1, search for part record
	if (0 == strcmp(searchOption, "1") || 0 == strcmp(searchOption, "Part Record")) {
reinputwarehouse:
		memset(&S1, 0, sizeof(partsInventory));

		//get warehouse code to search
		printf("\nWarehouse Code\n1. WBZ\n2. WSL\n3. WAR\nSelect Warehouse: ");
		scanf("%s", warehouseCode);
		getchar();

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

		//open warehouse file with the given warehouseCode
		warehouseFile = openWarehouseFile(warehouseCode);

		//get part ID to search
		printf("\nInput Part ID to search: ");
		scanf("%s", &selectID);

		printf("\n\nSearch Result\n- - - - - \n");

		//call function to search part ID in file
		searchResult = partsInventorySearch(warehouseFile, &S1, selectID);
		//print data
		printInventoryData(&S1);
		//close file
		closeWarehouseFile(warehouseFile);

	}
	//option 2, search for supplier record
	else if (0 == strcmp(searchOption, "2") || 0 == strcmp(searchOption, "Supplier Details")) {
		memset(&S2, 0, sizeof(partsSupplier));
		
		//open supplier file
		supplierFile = openSupplierFile();

		//get part ID to search
		printf("\nInput Part ID to search: ");
		scanf("%s", &selectID);

		printf("\n\nSearch Result\n- - - - - \n");

		//call function to search for supplier data in file
		partsSupplierSearch(supplierFile, &S2, selectID);
		//print supplier data
		printSupplierData(&S2);
		//close file
		closeSupplierFile(supplierFile);
	}
	else {
		printf("\nInput invalid, try again with (1) or (2)\n");
		goto selectSearchFunction;
	}
	printf("\n");
}