#ifndef fileHandling_Header
#define fileHandling_Header

#include "partsSupplier.h"
#include "partsInventoryCreation.h"

FILE* openWarehouseFile(char* warehouseCode);
int readWarehouseRecord(FILE* fileHandle, int recordID, partsInventory* partData);
int addWarehouseRecord(FILE* fileHandle, partsInventory* partData);
int updateWarehouseRecord(FILE* fileHandle, int recordID, partsInventory* partData);
int getWarehouseRecordCount(FILE* fileHandle);
void closeWarehouseFile(FILE* fileHandle);

FILE* openSupplierFile();
int readSupplierRecord(FILE* fileHandle, int recordID, partsSupplier* supplierData);
int addSupplierRecord(FILE* fileHandle, partsSupplier* supplierData);
int updateSupplierRecord(FILE* fileHandle, int recordID, partsSupplier* supplierData);
int getSupplierRecordCount(FILE* fileHandle);
void closeSupplierFile(FILE* fileHandle);

#endif