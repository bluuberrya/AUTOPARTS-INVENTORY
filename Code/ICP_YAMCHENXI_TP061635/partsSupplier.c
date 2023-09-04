#include "partsSupplier.h"
#include "main.h"
#include "fileHandling.h"

//to print supplier data structure
void printSupplierData(partsSupplier* sup)
{
	printf("Supplier ID\t: %s\n", sup->supplierID);
	printf("Supplier Name\t: %s\n", sup->supplierName);
	printf("Location\t: %s\n", sup->location);
	printf("Part ID\t\t: %s\n", sup->partID);
	printf("Part Name\t: %s\n", sup->partName);
}

//main function
void partsSupplierCreation()
{
	//declare pointers, structure and variable
	FILE* supplierFile;
	partsSupplier S2;
	int latestRecord = 0;

	printf("2. Parts Supplier Creation\n- - - - -\n");

	//memory reset partsSupplier structure
	memset(&S2, 0, sizeof(partsSupplier));

	//open supplier file
	supplierFile = openSupplierFile();

	//get supplier data
	printf("*Input existing Supplier ID if there is any\nEnter Supplier ID\t: ");
	gets(S2.supplierID);

	printf("\nEnter Supplier Name\t: ");
	gets(S2.supplierName);

	printf("\nEnter location\t\t: ");
	gets(S2.location);

	printf("\nEnter Part ID\t\t: ");
	gets(S2.partID);
	
	printf("\nEnter Part Name\t\t: ");
	gets(S2.partName);

	S2.linefeed1 = '\n';
	
	//call function to add record to file
	latestRecord = addSupplierRecord(supplierFile, &S2);
	printf("\n\nRecord successfully created!\n- - - - -\n");

	//get and print supplier record count
	latestRecord = getSupplierRecordCount(supplierFile);
	printf("Current record count: %d\n", latestRecord);

	//read and print the latest recorded supplier data
	readSupplierRecord(supplierFile, latestRecord, &S2);
	printSupplierData(&S2);

	//close supplier file
	closeSupplierFile(supplierFile);
}