//Yam Chen Xi TP061635
#include "main.h"
#include "partsInventoryCreation.h"
#include "partsSupplier.h"

//open warehouse file
FILE* openWarehouseFile(char* warehouseCode) {
	char fileName[128] = { 0 };
	FILE* fileHandle = 0;

	//construct file name using warehouseCode
	sprintf(fileName, "%sinventory.txt", warehouseCode);
	
	//read and create the file
	fileHandle = fopen(fileName, "r+b");
	//write and create the file
	if (0 == fileHandle) {
		fileHandle = fopen(fileName, "w+b");
	}
	return fileHandle;
}

//read for specific warehouse record
int readWarehouseRecord(FILE* fileHandle, int recordID, partsInventory* partData) {

	//read fail
	if (0 > fseek(fileHandle, recordID * sizeof(partsInventory), SEEK_SET))
		return -1;

	//read file
	fread(partData, sizeof(partsInventory), 1, fileHandle);

	return 0;
}

//add warehouse record at the end of the file
int addWarehouseRecord(FILE* fileHandle, partsInventory* partData) {
	int s = 0;
	fseek(fileHandle, 0L, SEEK_END);

	s = fwrite(partData, sizeof(partsInventory), 1, fileHandle);

	return (sizeof(partsInventory) == s);
}

//update warehouse record on the original line
int updateWarehouseRecord(FILE* fileHandle, int recordID, partsInventory* partData) {
	int writeSize = 0;

	if (0 > fseek(fileHandle, recordID * sizeof(partsInventory), SEEK_SET))
		return -1;
	writeSize = fwrite(partData, sizeof(partsInventory), 1, fileHandle);
	fflush(fileHandle);
	return 0;
}

//get the total warehouse record count
int getWarehouseRecordCount(FILE* fileHandle) {
	fseek(fileHandle, 0L, SEEK_END);
	return (ftell(fileHandle) / sizeof(partsInventory));
}

//close warehouse file
void closeWarehouseFile(FILE* fileHandle)
{
	fclose(fileHandle);
}

//open supplier file for append
FILE* openSupplierFile() {
	char fileName[128] = { 0 };
	FILE* fileHandle = 0;

	fileHandle = fopen("Supplier.txt", "a+b");
	return fileHandle;
}

//read for specific supplier record
int readSupplierRecord(FILE* fileHandle, int recordID, partsSupplier* supplierData) {

	//read fail
	if (0 > fseek(fileHandle, recordID * sizeof(partsSupplier), SEEK_SET))
		return -1;

	fread(supplierData, sizeof(partsSupplier), 1, fileHandle);

	return 0;
}

//add supplier record at the end of the file
int addSupplierRecord(FILE* fileHandle, partsSupplier* supplierData) {
	int s = 0;
	fseek(fileHandle, 0L, SEEK_END);

	s = fwrite(supplierData, sizeof(partsSupplier), 1, fileHandle);

	return (sizeof(partsSupplier) == s);
}

//update supplier record at the orginal line
int updateSupplierRecord(FILE* fileHandle, int recordID, partsSupplier* supplierData) {
	if (0 > fseek(fileHandle, recordID * sizeof(partsSupplier), SEEK_SET))
		return -1;

	return (sizeof(partsSupplier) == fwrite(supplierData, sizeof(partsSupplier), 1, fileHandle));
}

//get total supplier record count
int getSupplierRecordCount(FILE* fileHandle) {
	fseek(fileHandle, 0L, SEEK_END);
	return (ftell(fileHandle) / sizeof(partsSupplier));
}

//close supplier file
void closeSupplierFile(FILE* fileHandle)
{
	fclose(fileHandle);
}